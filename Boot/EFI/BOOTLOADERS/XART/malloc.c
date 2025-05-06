#include "XART.h"

#define __CHAR32_TYPE __CHAR32_TYPE__
#define __CHAR16_TYPE __CHAR16_TYPE__

#define PAGE_SIZE_BYTES 4096

#define MAX_ALLOCATIONS 65536

__CHAR32_TYPE memory_bitmap[MAX_ALLOCATIONS];

__CHAR32_TYPE memory_allocations[MAX_ALLOCATIONS];

__CHAR32_TYPE total_memory = 0;
__CHAR32_TYPE free_memory = 0;

void init_memory_system(__CHAR32_TYPE total_pages, __CHAR32_TYPE page_size_bytes) {
    total_memory = total_pages * page_size_bytes;
    free_memory = total_memory;

    for (__CHAR32_TYPE i = 0; i < MAX_ALLOCATIONS; i++) {
        memory_bitmap[i] = 0;
    }
}

int malloc_memory(__CHAR32_TYPE pages, __CHAR32_TYPE page_size_bytes, __CHAR32_TYPE start_page) {
    if (page_size_bytes == 0) {
        page_size_bytes = PAGE_SIZE_BYTES;
    }

    __CHAR32_TYPE total_malloc_bytes = pages * page_size_bytes;

    if (free_memory < total_malloc_bytes) {
        return xart_no_memory;
    }

    __CHAR32_TYPE pages_needed = pages;
    for (__CHAR32_TYPE i = start_page; i < MAX_ALLOCATIONS; i++) {
        if (memory_bitmap[i] == 0) {
            memory_bitmap[i] = 1;
            memory_allocations[i] = i * page_size_bytes;

            free_memory -= page_size_bytes;
            pages_needed--;

            if (pages_needed == 0) {
                return (int)(memory_allocations[i]);
            }
        }
    }

    return xart_no_memory;
}

int mwrite(LONG page, LONG data_to_write, LONG pid) {

    LONG pagebyte = page * 4096;

    if(page >= GPT.sys_list[pid].mem_start_addr_page) {
        if(page <= GPT.sys_list[pid].mem_end_addr_page) {
            LONG *malloc_write = (LONG *)pagebyte;

            *malloc_write = data_to_write;

            return xart_success;
        } else {
            return xart_gpf;
        }
    } else {
        return xart_gpf;
    }
}

int free_memory_block(__CHAR32_TYPE ptr) {
    for (__CHAR32_TYPE i = 0; i < MAX_ALLOCATIONS; i++) {
        if (memory_allocations[i] == ptr) {
            if (memory_bitmap[i] == 1) {
                memory_bitmap[i] = 0;
                free_memory += PAGE_SIZE_BYTES;
                return 0;
            } else {
                return xart_invalid_free;
            }
        }
    }

    return xart_unknown_ptr;
}

int madd(__CHAR16_TYPE *pid, __CHAR32_TYPE *page_num, __CHAR32_TYPE *Data_add) {
    __CHAR16_TYPE CanWrite = GLOBAL_CHECK_BOUNDS(pid, page_num);

    if (CanWrite == 1) {
        __CHAR32_TYPE* MemAddrToWrite = (__CHAR32_TYPE*)(*page_num * PAGE_SIZE_BYTES);
        *MemAddrToWrite = *Data_add;
    } else if (CanWrite == 0) {
        return xart_gpf;
    } else if (CanWrite == -1) {
        return xart_unknown_ptr;
    }

    return 0;
}

int XART_WAIT(__CHAR16_TYPE cycles) {
    int wait_cycles = cycles;
    while (wait_cycles != 0) {
        wait_cycles--;
    }
    return 0;
}

int GET_EARLIEST_AVAILABLE_MEMORY() {
    for (__CHAR32_TYPE i = 0; i < MAX_ALLOCATIONS; i++) {
        if (memory_bitmap[i] == 0) {
            return (int)(memory_allocations[i]);
        }
    }
    XART_OOM();
}

int XART_OOM() {

}