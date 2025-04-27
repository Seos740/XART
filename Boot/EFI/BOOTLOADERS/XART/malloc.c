#include "sys_tablesd.h"
#define xart_gpf -1
#define xart_unknown_ptr -2

// TODO: Implement avaliable memory checking here

int malloc(__CHAR32_TYPE__ *pages, __CHAR16_TYPE__ *page_size_bytes, __CHAR32_TYPE__ *start_page, __CHAR16_TYPE__ *pid) {

    // Page size check
    if (*page_size_bytes == 0) {
        *page_size_bytes = 4096;  // Default page size in bytes
    }

    // Convert pages to bytes
    __CHAR32_TYPE__ TOTAL_MALLOC_BYTES = *pages * *page_size_bytes;
    __CHAR32_TYPE__ STARTING_BYTE = *start_page * *page_size_bytes;

    // Get the start pointer
    __CHAR32_TYPE__* start_pointer = (__CHAR32_TYPE__*)STARTING_BYTE;

    // Code here to send the data to the GPC (global process table)

    return (int)start_pointer;  // Return the start pointer cast to an integer (if needed)
}

int madd(__CHAR16_TYPE__ *pid, __CHAR32_TYPE__ *page_num, __CHAR32_TYPE__ *Data_add) {

    // This code will retrieve the process's allocated memory from the GPC
    // and add the data at the specified pointer if owned
    __CHAR16_TYPE__ CanWrite = GLOBAL_CHECK_BOUNDS(pid, page_num);

    if (CanWrite == 1) {
        // Code to write data at the memory address
        LONG* MemAddrToWrite = (LONG*)(*page_num * 4096);  // Ensure it's a pointer
        *MemAddrToWrite = *Data_add;  // Write data to the address
    } else if (CanWrite == 0) {
        return xart_gpf;  // XART general protection fault
    } else if (CanWrite == -1) {
        return xart_unknown_ptr;  // Invalid pointer
    }

    return 0;  // Success (or another return code as needed)
}