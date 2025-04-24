#include "uefi_utils.h"

int xart_main() {
    // Code goes here
    uefi_allocate(15625, 0x00000000); // 16MB of ram for the XART loader

    // This code segment will load the kernel params
    
    
}