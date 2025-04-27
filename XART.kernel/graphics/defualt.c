#include "malloc.c"

#define MAKE_COLOR(r, g, b) ((0xFF << 24) | ((r) << 16) | ((g) << 8) | (b))

typedef unsigned int   uint32_t;
typedef unsigned long  uintptr_t;

extern uint32_t framebuffer_width;
extern uint32_t framebuffer_height;
extern void* framebuffer_address;

int sys_setup_framebuffer(__CHAR16_TYPE__ x_length, __CHAR16_TYPE__ y_length, __CHAR32_TYPE__ *framebuffer_starting_page, short bits_per_pixel) {
    if (framebuffer_starting_page == (void*)0) {
        return xart_gpf; // XART general protection fault
    }

    
    framebuffer_width = (uint32_t)x_length;
    framebuffer_height = (uint32_t)y_length;
    
    *framebuffer_starting_page = (__CHAR32_TYPE__) ((uintptr_t)framebuffer_address);

    malloc(framebuffer_width * framebuffer_height * (bits_per_pixel / 8), 4096, *framebuffer_starting_page, 1); // length - page size in bytes - starting page - pid

    return 0; 
}

int draw_pixel(int x_pos, int y_pos, uint32_t color) {
    // check bounds
    if (x_pos < 0 || y_pos < 0 || x_pos >= (int)framebuffer_width || y_pos >= (int)framebuffer_height) {
        return xart_gpf; // XART general protection fault
    }

    // Draw the pixel
    unsigned int* pixel_ptr = (unsigned int*)framebuffer_address;
    unsigned int offset = (y_pos * framebuffer_width) + x_pos;

    pixel_ptr[offset] = (unsigned int)color; // Cast LONG to unsigned int

    return 0; 
}