#include "XART.h"

#define LONG int
#define DLONG 255
#define QDLONG 511
#define MAX_PROC 16384 // Max proccess the system allows for

// Process info struct
struct sys_proc {
    LONG proc_name;
    LONG mem_start_addr_page;
    LONG mem_end_addr_page;
};

// Global process table struct
struct GLOBAL_PROC_TABLE {
    int CURRENT_LATEST_PROC;
    struct sys_proc sys_list[MAX_PROC];  // pid 1 = sys_list[0], pid 2 = sys_list[1], etc.
};

// Global instance
struct GLOBAL_PROC_TABLE GPT;

// Initialize process table
int GLOBAL_PROC_TABLE_SETUP() {
    GPT.CURRENT_LATEST_PROC = 1;

    // Setup PID 1 (sys_1)
    GPT.sys_list[0].proc_name = 1;
    GPT.sys_list[0].mem_start_addr_page = 0;
    GPT.sys_list[0].mem_end_addr_page = 31250;

    return 0;
}

// Register next process
int GLOBAL_REGISTER_PROC(LONG *proc_name, LONG *Mem_start_addr, LONG *Malloc_length_pages) {
    // Increment PID
    int new_pid = GPT.CURRENT_LATEST_PROC + 1;

    if (new_pid > MAX_PROC)
        return -1; // No more space

    GPT.CURRENT_LATEST_PROC = new_pid;

    int index = new_pid - 1;  // sys_1 = index 0

    GPT.sys_list[index].proc_name = *proc_name;
    GPT.sys_list[index].mem_start_addr_page = *Mem_start_addr;
    GPT.sys_list[index].mem_end_addr_page = *Mem_start_addr + *Malloc_length_pages;

    return new_pid;
}

int GLOBAL_KILL_PROC_NEWEST() {
    LONG Victim - GPT.CURRENT_LATEST_PROC;

    GPT.CURRENT_LATEST_PROC = GPT.CURRENT_LATEST_PROC - 1;

    GPT.sys_list[Victim].proc_name = 0;

    LONG destroyable_memory = (GPT.sys_list[Victim].mem_end_addr_page * 4096) - (GPT.sys_list[Victim].mem_start_addr_page * 4096);
    LONG destroy_index = destroyable_memory;
    LONG destroy_start = GPT.sys_list[Victim].mem_start_addr_page * 4096;

    GPT.sys_list[Victim].mem_start_addr_page = 0;
    GPT.sys_list[Victim].mem_start_addr_page = 0;

    While(destroy_index != 0) {
        malloc_memory((destroyable_memory / 4096), 4096, (destory_start / 4096));
    }
}

int GLOBAL_CHECK_BOUNDS(LONG *pid, LONG *mem_addr) {
    // Safety check
    if (*pid <= 0 || *pid > GPT.CURRENT_LATEST_PROC) {
        return -1; // Invalid PID
    }

    // Get process from table
    struct sys_proc *p = &GPT.sys_list[*pid - 1];

    // Check if address is within bounds
    if (*mem_addr >= p->mem_start_addr_page && *mem_addr < p->mem_end_addr_page) {
        return 1;  // In bounds
    }

    return 0;  // Out of bounds
}
