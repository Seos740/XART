int XART_ROUND(float number) {
    float temp = number * 10000000.0f;  // Shift the decimal point 7 places to the right
    if (number >= 0) {
        temp += 0.5f;  // Round up for positive numbers
    } else {
        temp -= 0.5f;  // Round down for negative numbers
    }
    return (int)(temp);  // Convert back to integer after rounding
}
