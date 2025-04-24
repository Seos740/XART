#include "uefi_utils.h"

int param_buffer_size = 128;

int xart_main() {
    // Allocate 16MB of RAM for the loader or kernel space
    // 16MB / 4096 = 4096 pages
    uefi_allocate(4096, 0x00000000);

    // Load kernel parameters from args.conf
    CHAR8 args_buffer[param_buffer_size + 1];  // With null terminator
    uefi_read_file("\\Boot\\ARGS.conf\\args.conf", args_buffer, param_buffer_size);
    
    args_buffer[param_buffer_size] = '\0';

    // parse the stuff
    
    parse_params();

    // post parse: getting the params

    __SCHAR_MAX__ KERNEL_TYPE = ($KernelParam, 3, 2);

    if(KERNEL_TYPE = 'XART') {
        uefi_load_file("/Boot/EFI/XART/kernel_init.efi")
    }

    return 0;
}

typedef struct {
    CHAR8 *key;
    CHAR8 *value;
} KernelParam;

#define MAX_PARAMS 16
KernelParam params[MAX_PARAMS];

int parse_params(CHAR8 *args_buffer, KernelParam *params, int max_params) {
    int param_count = 0;
    CHAR8 *current = args_buffer;
    CHAR8 *key_start, *value_start;
    
    while (*current != '\0' && param_count < max_params) {
        // Skip any leading spaces
        while (*current == ' ' || *current == '\t') {
            current++;
        }

        if (*current == '\0') break; // End of buffer

        // Find the key (before the '=')
        key_start = current;
        while (*current != '=' && *current != '\0') {
            current++;
        }

        // Null terminate the key
        if (*current == '=') {
            *current = '\0';
            value_start = ++current; // Skip the '=' and point to value
        } else {
            break; // No '=' found, exit
        }

        // Find the value (until the end of line or null)
        while (*current != '\0' && *current != '\n') {
            current++;
        }

        // Null terminate the value
        if (*current == '\n') {
            *current = '\0';
        }

        // Handle special cases like '\\' in value for file paths
        // The parser should store '\\' as a literal in the value
        for (CHAR8 *v = value_start; *v != '\0'; v++) {
            if (*v == '\\' && *(v + 1) == '\\') {
                *v = '/';  // Change double backslashes to a slash
                memmove(v + 1, v + 2, strlen(v + 2) + 1);  // Move the rest of the string left
            }
        }

        // Store the key-value pair
        params[param_count].key = key_start;
        params[param_count].value = value_start;
        param_count++;

        // Check if we reached 'eof.'
        if (strcmp((char*)current, "eof.") == 0) {
            break;
        }
    }
    
    return param_count;  // Return the number of parameters found
}

CHAR8* get_param_value(const KernelParam *params, int param_count, const CHAR8 *key) {
    for (int i = 0; i < param_count; i++) {
        if (strcmp((char*)params[i].key, (char*)key) == 0) {
            return params[i].value;  // Return the value if the key matches
        }
    }
    return NULL;  // Return NULL if the key is not found
}