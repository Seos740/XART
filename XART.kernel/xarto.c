typedef unsigned char  u8;
typedef unsigned int   u32;
typedef unsigned short u16;
typedef long           LONG;
typedef int            __CHAR32_TYPE;

extern int load_file(const char* path, void* dest_buffer, u32* file_size_out);
extern int mwrite(LONG page, LONG data_to_write, LONG pid);
extern void* malloc_memory(__CHAR32_TYPE pages, __CHAR32_TYPE page_size_bytes, __CHAR32_TYPE start_page);
extern void free_memory_block(__CHAR32_TYPE ptr);

// Adjusted to 8 bytes for clean casting
struct xarto_header {
    char magic[8];       // 'X','A','R','T','O',0,0,0
    u8 version;
    u16 arch_id;
    u16 reserved;
    u32 code_offset;
    u32 data_offset;
    u32 entry_point;
    u32 flags;
    u16 section_count;
};

int main() {
    u32 file_size;
    void* buffer = malloc_memory(4, 4096, 0);
    if (!buffer)
        return -1;

    if (load_file("my_program.xarto", buffer, &file_size) != 0)
        return -2;

    struct xarto_header* hdr = (struct xarto_header*)buffer;

    // Verify magic number
    if (hdr->magic[0] != 'X' || hdr->magic[1] != 'A' ||
        hdr->magic[2] != 'R' || hdr->magic[3] != 'T' || hdr->magic[4] != 'O') {
        return -3;
    }

    // Write fields to memory (pages 100–110)
    mwrite(100, *(LONG*)&hdr->magic[0], 0);      // first 8 bytes
    mwrite(101, hdr->version, 0);
    mwrite(102, hdr->arch_id, 0);
    mwrite(103, hdr->reserved, 0);
    mwrite(104, hdr->code_offset, 0);
    mwrite(105, hdr->data_offset, 0);
    mwrite(106, hdr->entry_point, 0);
    mwrite(107, hdr->flags, 0);
    mwrite(108, hdr->section_count, 0);

    free_memory_block((__CHAR32_TYPE)buffer);
    return 0;
}
