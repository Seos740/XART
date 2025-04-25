int malloc(__CHAR32_TYPE__ *pages, __CHAR16_TYPE__ *page_size_bytes, __CHAR32_TYPE__ *start_page, __CHAR16_TYPE__ *pid) {

    // Page size check

    if(*page_size_bytes == 0) {
        *page_size_bytes = 4096;
    }

    // Start by converting pages to bytes

    __CHAR32_TYPE__ TOTAL_MALLOC_BYTES = *pages * *page_size_bytes;
    __CHAR32_TYPE__ STARTING_BYTE = *start_page * *page_size_bytes;

    // Get the start pointer
    
    __CHAR32_TYPE__* start_pointer = (__CHAR32_TYPE__*)STARTING_BYTE;

    // Code here to send the data to the GPC (global process table)

    return start_pointer;
}

int madd(__CHAR16_TYPE__ *pid, __CHAR32_TYPE__ *page_num) {

    // This code will retrieve the process's allocated memory from the GPC and return the data at the specified pointer if owned

}
