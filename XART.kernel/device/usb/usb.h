#pragma once

#include "types.h"  // Instead of stdint.h

void usb_init(void);
void usb_poll(void);
void usb_handle_reset(void);
void usb_handle_control_transfer(void);
