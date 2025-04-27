#include "malloc.c"

int XART_PORT_CLOSER = 0x00;
int XART_CLOSE_PORT = 0x00;
int XART_PORT_OPENER = 0x00;
int XART_OPEN_PORT = 0x00;

int XART_DISABLE_PORT(LONG port_id) {
    XART_PORT_CLOSER = 0x0F;
    XART_CLOSE_PORT = port_id;
}

int XART_ENABLE_PORT(LONG port_id) {
    XART_PORT_OPENER = 0x0F;
    XART_OPEN_PORT = port_id;
}

int RESET() {
    XART_PORT_CLOSER = 0x00;
    XART_CLOSE_PORT = 0x00;
    XART_PORT_OPENER = 0x00;
    XART_OPEN_PORT = 0x00;
}