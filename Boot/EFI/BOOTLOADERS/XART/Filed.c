#include <stdint.h>

#define SECTOR_SIZE 512
#define CLUSTER_BUFFER_SIZE (128 * SECTOR_SIZE)  // 64 KB
#define MAX_PATH_PARTS 8
#define MAX_FILENAME_LEN 11

// === YOU MUST IMPLEMENT THIS ===
extern int read_sector(uint32_t lba, void* buffer);

// === INTERNAL BUFFERS ===
static uint8_t sector_buffer[SECTOR_SIZE];
static uint8_t fat_table[128 * SECTOR_SIZE];  // ~64KB for FAT
static uint8_t cluster_buffer[CLUSTER_BUFFER_SIZE];

// === GLOBALS FROM BPB ===
static uint32_t fat_start_lba;
static uint32_t cluster_heap_start_lba;
static uint32_t sectors_per_cluster;
static uint32_t root_dir_cluster;
static uint32_t fat_size;

// === HELPERS ===
static int memcmp(const char* a, const char* b, int len) {
    for (int i = 0; i < len; ++i)
        if (a[i] != b[i]) return 1;
    return 0;
}

static void memcpy(void* dest, const void* src, uint32_t len) {
    uint8_t* d = dest;
    const uint8_t* s = src;
    while (len--) *d++ = *s++;
}

static int strlen(const char* str) {
    int len = 0;
    while (*str++) ++len;
    return len;
}

static int strcmp(const char* a, const char* b) {
    while (*a && (*a == *b)) a++, b++;
    return (unsigned char)*a - (unsigned char)*b;
}

// Convert 8.3 string to uppercase padded 11-byte FAT name
static void format_filename(const char* input, char* out) {
    int i = 0, j = 0;
    while (input[i] && input[i] != '.' && j < 8) {
        out[j++] = (input[i] >= 'a' && input[i] <= 'z') ? (input[i] - 32) : input[i];
        ++i;
    }
    while (j < 8) out[j++] = ' ';

    if (input[i] == '.') ++i;
    int k = 0;
    while (input[i] && k < 3) {
        out[j++] = (input[i] >= 'a' && input[i] <= 'z') ? (input[i] - 32) : input[i];
        ++i; ++k;
    }
    while (j < 11) out[j++] = ' ';
}

// Cluster ↔ LBA
static uint32_t cluster_to_lba(uint32_t clus) {
    return cluster_heap_start_lba + ((clus - 2) * sectors_per_cluster);
}

static uint32_t read_fat_entry(uint32_t cluster) {
    return *((uint32_t*)(fat_table + cluster * 4)) & 0x0FFFFFFF;
}

static int is_end_cluster(uint32_t entry) {
    return (entry >= 0x0FFFFFF8);
}

// === PATH PARSER ===
static int split_path(const char* path, char parts[MAX_PATH_PARTS][MAX_FILENAME_LEN + 1]) {
    int count = 0, i = 0, j = 0;
    while (*path && count < MAX_PATH_PARTS) {
        if (*path == '/') {
            if (j != 0) {
                parts[count][j] = 0;
                ++count;
                j = 0;
            }
            ++path;
            continue;
        }
        if (j < MAX_FILENAME_LEN)
            parts[count][j++] = *path++;
        else
            return -1;
    }
    if (j != 0) {
        parts[count][j] = 0;
        ++count;
    }
    return count;
}

// === FS INIT ===
int fat32_init(uint32_t vbr_lba) {
    if (read_sector(vbr_lba, sector_buffer)) return -1;

    sectors_per_cluster = sector_buffer[13];
    fat_size = *(uint32_t*)&sector_buffer[36];
    root_dir_cluster = *(uint32_t*)&sector_buffer[44];
    fat_start_lba = vbr_lba + *(uint16_t*)&sector_buffer[14];
    cluster_heap_start_lba = fat_start_lba + (fat_size * sector_buffer[16]);

    for (uint32_t i = 0; i < fat_size; ++i) {
        if (read_sector(fat_start_lba + i, fat_table + (i * SECTOR_SIZE))) return -1;
    }

    return 0;
}

// === FILE LOADING ===
int load_file(const char* path, void* dest_buffer, uint32_t* file_size_out) {
    char path_parts[MAX_PATH_PARTS][MAX_FILENAME_LEN + 1];
    int parts = split_path(path, path_parts);
    if (parts < 1) return -1;

    uint32_t current_cluster = root_dir_cluster;

    for (int pi = 0; pi < parts; ++pi) {
        // Load cluster chain
        while (!is_end_cluster(current_cluster)) {
            for (uint32_t s = 0; s < sectors_per_cluster; ++s) {
                if (read_sector(cluster_to_lba(current_cluster) + s, sector_buffer)) return -1;

                for (int offset = 0; offset < SECTOR_SIZE; offset += 32) {
                    uint8_t* entry = sector_buffer + offset;
                    if (entry[0] == 0x00) goto not_found;
                    if (entry[0] == 0xE5 || entry[11] == 0x0F) continue;

                    char fat_name[12];
                    format_filename(path_parts[pi], fat_name);

                    if (memcmp((char*)entry, fat_name, 11) == 0) {
                        uint32_t next_cluster = (*(uint16_t*)(entry + 20) << 16) | *(uint16_t*)(entry + 26);
                        if (pi == parts - 1) {
                            // It's a file!
                            uint32_t file_size = *(uint32_t*)(entry + 28);
                            *file_size_out = file_size;

                            // Load file content
                            uint8_t* buf = dest_buffer;
                            uint32_t bytes_read = 0;
                            uint32_t clus = next_cluster;

                            while (!is_end_cluster(clus) && bytes_read < file_size) {
                                for (uint32_t cs = 0; cs < sectors_per_cluster; ++cs) {
                                    if (bytes_read >= file_size) break;

                                    if (read_sector(cluster_to_lba(clus) + cs, buf + bytes_read)) return -1;
                                    bytes_read += SECTOR_SIZE;
                                }
                                clus = read_fat_entry(clus);
                            }

                            return 0; // Success
                        } else {
                            // It's a directory
                            current_cluster = next_cluster;
                            goto next_part;
                        }
                    }
                }
            }
            current_cluster = read_fat_entry(current_cluster);
        }

    not_found:
        return -1;

    next_part:;
    }

    return -1;
}
