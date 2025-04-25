#include "sys_tablesd.h"

int BITMAP_RENDERD_START() {
    GLOBAL_REGISTER_PROC('bitmap_renderd', 4096, 15625); // bitmap_renderd starts at page 4096 and uses 64MB of memory for BMP images

    
}