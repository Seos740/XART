#include "usb.h"

// Hardware-specific base addresses (adjust if needed)
#define RCC_BASE        0x40021000
#define GPIOA_BASE      0x40010800
#define USB_BASE        0x40005C00

// Peripheral registers
#define RCC_APB2ENR     (*(volatile uint32_t *)(RCC_BASE + 0x18))
#define RCC_APB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x1C))
#define GPIOA_CRH       (*(volatile uint32_t *)(GPIOA_BASE + 0x04))
#define USB_CNTR        (*(volatile uint32_t *)(USB_BASE + 0x40))
#define USB_ISTR        (*(volatile uint32_t *)(USB_BASE + 0x44))
#define USB_DADDR       (*(volatile uint32_t *)(USB_BASE + 0x4C))
#define USB_BTABLE      (*(volatile uint32_t *)(USB_BASE + 0x50))

// Constants
#define RCC_APB2ENR_IOPAEN (1 << 2)
#define RCC_APB1ENR_USBEN  (1 << 23)

#define USB_CNTR_FRES   (1 << 0)
#define USB_CNTR_PDWN   (1 << 1)
#define USB_CNTR_RESETM (1 << 10)
#define USB_CNTR_CTRM   (1 << 15)

#define USB_DADDR_EF    (1 << 7)

#define USB_ISTR_RESET  (1 << 10)
#define USB_ISTR_CTR    (1 << 15)

void usb_init(void) {
    // Enable GPIOA and USB clocks
    RCC_APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC_APB1ENR |= RCC_APB1ENR_USBEN;

    // Configure USB pins: PA11 (DM), PA12 (DP) as floating input
    GPIOA_CRH &= ~((0xF << 12) | (0xF << 16)); // Clear PA11, PA12
    GPIOA_CRH |= (0x4 << 12) | (0x4 << 16);    // Input floating

    // Power up and reset USB
    USB_CNTR = USB_CNTR_FRES;   // Force Reset
    USB_CNTR = 0;               // Exit reset

    // Enable RESET and Correct Transfer interrupts
    USB_CNTR = USB_CNTR_RESETM | USB_CNTR_CTRM;
}

void usb_poll(void) {
    uint32_t istr = USB_ISTR;

    if (istr & USB_ISTR_RESET) {
        USB_ISTR &= ~USB_ISTR_RESET; // Clear interrupt
        usb_handle_reset();
    }

    if (istr & USB_ISTR_CTR) {
        USB_ISTR &= ~USB_ISTR_CTR; // Clear interrupt
        usb_handle_control_transfer();
    }
}

void usb_handle_reset(void) {
    // After RESET, set default device address = 0, enable function
    USB_DADDR = USB_DADDR_EF | 0x00;

    // Configure buffer table location (example, BTABLE at 0x00)
    USB_BTABLE = 0x00;
}

void usb_handle_control_transfer(void) {
    // Here:
    //  - Parse setup packet
    //  - Respond to host (send descriptors, etc.)
    // (Very complex in full form — can be expanded)

    // For now, just acknowledge it silently
}
