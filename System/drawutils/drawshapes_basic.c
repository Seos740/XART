#include "graphics/defualt.c"
#include "XART_ERRORS.c"
#include "XART_MATH.c"

int DrawRect(int X, int Y, int Width, int Height, uint32_t Color) {
    int StartX = X;
    int StartY = Y;
    
    for (int row = 0; row < Height; row++) {
        for (int col = 0; col < Width; col++) {
            draw_pixel(X + col, Y + row, Color);
        }
    }

    return xart_success;
}

int DrawRectGradientHorizontal(int X, int Y, int Width, int Height, uint32_t ColorStart, uint32_t ColorEnd) {
    int StartX = X;
    int StartY = Y;

    float GradientRate = ((ColorEnd - ColorStart) / (float)Width);
    GradientRate = XART_ROUND(GradientRate);  // Apply rounding to the gradient rate

    for (int row = 0; row < Height; row++) {
        for (int col = 0; col < Width; col++) {
            uint32_t Color = (uint32_t)(ColorStart + GradientRate * col);
            Color = XART_ROUND(Color);  // Apply rounding to the interpolated color value
            draw_pixel(X + col, Y + row, Color);
        }
    }

    return xart_success;
}
