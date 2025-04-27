#include "ports.h"

LONG recived_data = 0;

struct User {
    int PVG;
    int UID;
};

    struct User ROOT        = { .PVG = 0,   .UID = 0 };
    struct User SYSTEM_INIT = { .PVG = 11,  .UID = 1 };
    struct User SYSTEM      = { .PVG = 30,  .UID = 2 };
    struct User VIRTd       = { .PVG = 110, .UID = 3 };
    struct User USER        = { .PVG = 255, .UID = 4 };

int SYS_USERS_LOOP() {
    while(1 == 1) {
        int XART_PORT_1 = 1; // XART port 1 is open

        if(XART_PORT_CLOSER = 0x0F) {
            if(XART_CLOSE_PORT = 0x01) {
                XART_PORT_1 = 0x00; // Close the port
                break;
            }
        }

        if(XART_IS_DATA_SENT = 1) {
            recived_data = XART_PORT_DATA;
            // proceed to ignore that monky data and do our own thing (for now)
        }
    }
}