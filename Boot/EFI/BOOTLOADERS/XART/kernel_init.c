#include "Filed.c"
#include "utils/thread_spawn.c"
#include "daemons.h"

int SYS_KERNEL_MAIN() {
    // Put some code here
    fat32_init;
    
    GLOBAL_PROC_TABLE_SETUP();

}

int SYS_START_DAEMONS() {

    thread_t* t = create_thread(SYS_USERS_LOOP, (void*)" ");

}

int MEM_ALLOC_TABLE_LOADER() {
    // Init the memalloctable here
    struct MEM_BASE_ALLOC_TABLE() {
        int KERNEL_BUFFER_SIZE_MIN = 131072;
        int USER_BUFFER_SIZE_MIN = 500000;
        int FREE_SPACE_MIN = 131072;
    }

    struct MEM_BASE_ALLOCATION_RATIOS() {
        int KERNEL_BASE_RATIO = 17;
        int USER_BASE_RATIO = 67;
        int FREE_BASE_RATIO = 16;
    }

    struct MEM_BASE_ALLOC_TABLE();
    struct MEM_BASE_ALLOCATION_RATIOS();
}

void KERNEL_INIT_EXIT() {

    

}