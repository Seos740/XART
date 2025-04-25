#include "Filed.c"

int SYS_KERNEL_MAIN() {
    // Put some code here
    fat32_init;
    GLOBAL_PROC_TABLE_SETUP();

}

int SYS_START_DAEMONS() {

    load_file("/Boot/EFI/Bootloaders/XART/daemons/bitmap_renderd.bin", 65536, 65536); // Buffer and File size of 65,536 (~64KB) for bitmap render agent

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