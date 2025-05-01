#include "graphics/defualt.c"

#define BYTE char
#define LONG 32  // Assuming a LONG is 32-bit (4 bytes)

#define FONT_WIDTH 8
#define FONT_HEIGHT 8
#define MAX_CHARS 256  // Maximum number of characters (ASCII 0-255)

// Font data for all characters (0-255)
// The 8x8 bitmap for each character. Each row represents a byte where the bits
// represent pixels, 0 = off, 1 = on.
unsigned char font_data[MAX_CHARS][FONT_HEIGHT];

// Function to load font data (for now, we just initialize with dummy values)
void load_font_data(const char *font_file) {
    int pid = 0;  // Assuming process ID 0 for us

    // Use XART_OPEN_FILE to load the font data into page 1056
    int page_number = 0x1056;  // Page number where we want to load the font (1056 in this case)
    if (XART_OPEN_FILE(font_file, page_number, pid) != 0) {
        printf("Error: Could not load font file %s\n", font_file);

        for (int i = 0; i < MAX_CHARS; i++) {
            for (int row = 0; row < FONT_HEIGHT; row++) {
                font_data[i * FONT_HEIGHT + row] = 0xFF;  // Example: each character is fully "on" (all bits 1)
            }
        }

        return 0;
    }

}

// Function to draw a pixel (replace with actual pixel drawing code)
void draw_pixel(int x, int y, int color) {
    // Placeholder for actual pixel drawing function (adjust to your hardware)
    // Example: printf("Drawing pixel at (%d, %d) with color %d\n", x, y, color);
}

// Function to print a single character
int XART_PRINT_CHAR(BYTE character, int x, int y) {
    if (character >= MAX_CHARS) return -1;  // Out of bounds check
    
    unsigned char* char_bitmap = font_data[character];  // Get the character's pixel pattern
    
    // Render the 8x8 bitmap for the character
    for (int row = 0; row < FONT_HEIGHT; row++) {
        for (int col = 0; col < FONT_WIDTH; col++) {
            if (char_bitmap[row] & (1 << (FONT_WIDTH - 1 - col))) {
                draw_pixel(x + col, y + row, 1);  // Draw the pixel (assuming color=1)
            }
        }
    }
    
    return 0;  // Success
}

// Function to print a string of characters (as a single string variable)
int XART_PRINT_STRING(const char *str, int x, int y) {
    int offset = 0;
    
    // Continue until the null terminator
    while (str[offset] != '\0') {
        BYTE character = (BYTE)str[offset];
        XART_PRINT_CHAR(character, x + (offset * (FONT_WIDTH + 1)), y);  // Space between characters
        offset++;
    }
    
    return 0;  // Success
}

// Example usage function
void example_usage() {
    // Example: Print "Hello, World!" at position (10, 10)
    const char *str = "Hello, World!";  // Null-terminated string
    XART_PRINT_STRING(str, 10, 10);
}

int main() {
    // Load the font data (replace this with actual font loading code)
    load_font_data();  // Initialize font data with dummy values
    
    // Example usage to print a string
    example_usage();
    
    return 0;
}
