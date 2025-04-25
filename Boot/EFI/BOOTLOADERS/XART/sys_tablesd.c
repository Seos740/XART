#define LONG 127
#define DLONG 255
#define QDLONG 511

int GLOBAL_PROC_TABLE_SETUP() {
    struct GLOBAL_PROC_TABLE {
        int CURRENT_LATEST_PROC;  // Assuming 32-bit int for CURRENT_LATEST_PROC
        
        struct sys_1 {
            LONG proc_name;                // Process name (probably an identifier)
            LONG mem_start_addr_page;      // Memory start address in pages
            LONG mem_end_addr_page;        // Memory end address in pages
        } kernel_proc;  // This struct holds kernel process-related data
    };

    // Initialize the struct
    struct GLOBAL_PROC_TABLE gpt;
    gpt.CURRENT_LATEST_PROC = 1;  // Set the latest process ID to 1
    gpt.kernel_proc.proc_name = 1;  // Use an integer ID for the process name (or other identifier)
    gpt.kernel_proc.mem_start_addr_page = 0;
    gpt.kernel_proc.mem_end_addr_page = 31250;  // As per your original comment

    return 0;
}
