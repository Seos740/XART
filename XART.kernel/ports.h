#include "malloc.c"

int XART_PORT_CLOSER = 0x00;
int XART_CLOSE_PORT = 0x00;
int XART_PORT_OPENER = 0x00;
int XART_OPEN_PORT = 0x00;
int XART_IS_DATA_SENT = 0x00;
LONG XART_PORT_DATA = 0x00;

int XART_DISABLE_PORT(LONG port_id) {
    XART_PORT_CLOSER = 0x0F;
    XART_CLOSE_PORT = port_id;
    XART_WAIT(65536);
    RESET();
}

int XART_ENABLE_PORT(LONG port_id) {
    XART_PORT_OPENER = 0x0F;
    XART_OPEN_PORT = port_id;
    XART_WAIT(65536);
    RESET();
}

int RESET() {
    XART_PORT_CLOSER = 0x00;
    XART_CLOSE_PORT = 0x00;
    XART_PORT_OPENER = 0x00;
    XART_OPEN_PORT = 0x00;
    XART_IS_DATA_SENT = 0x00;
    XART_PORT_DATA = 0x00;
}

int XART_PORT_DATA_SEND(LONG *send_data, LONG port_id) {
    XART_IS_DATA_SENT = port_id;
    XART_PORT_DATA = *send_data;
    XART_WAIT(65536);
    RESET();
}