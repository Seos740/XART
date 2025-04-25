#ifndef SYS_TABLESD_H
#define SYS_TABLESD_H

#define MAX_PROC 64
#define LONG int

struct sys_proc {
    LONG proc_name;
    LONG mem_start_addr_page;
    LONG mem_end_addr_page;
};

struct GLOBAL_PROC_TABLE {
    int CURRENT_LATEST_PROC;
    struct sys_proc sys_list[MAX_PROC];
};

extern struct GLOBAL_PROC_TABLE GPT;

int GLOBAL_REGISTER_PROC(LONG *proc_name, LONG *mem_start_addr, LONG *malloc_length_pages);
int GLOBAL_CHECK_BOUNDS(LONG *pid, LONG *mem_addr);

#endif
