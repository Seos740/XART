#include "system_print.c"

int PANIC(char *panic_id) {
    // Load the font data from the specified location (replace with actual path)
    load_font_data("/XART.kernel/sys_fonts/sys-defualt-8x8.psf");

    // Print panic message
    XART_PRINT_STRING("Warning: XART has run into an issue.", 0, 0);
    XART_PRINT_STRING("SYSTEM STOP CODE:", 0, 10);
    XART_PRINT_STRING(panic_id, 0, 20);  // Display the panic ID
    XART_PRINT_STRING("Panic: We are hanging here...", 0, 50);
    XART_PRINT_STRING("The system may be shut down manually.", 0, 60);

    // Infinite loop to halt the system
    while (1) {
        XART_WAIT(1024);  // Wait in a loop, assuming this halts the system or simulates waiting
    }

    return 0;  // Should not reach here, as the loop above halts execution
}
