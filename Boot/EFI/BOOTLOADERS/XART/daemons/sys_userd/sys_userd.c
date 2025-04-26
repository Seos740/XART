struct User {
    int PVG;
    int UID;
};

int SETUP_SYSTEM_USERS() {
    struct User ROOT        = { .PVG = 0,   .UID = 0 };
    struct User SYSTEM_INIT = { .PVG = 11,  .UID = 1 };
    struct User SYSTEM      = { .PVG = 30,  .UID = 2 };
    struct User VIRTd       = { .PVG = 110, .UID = 3 };
    struct User USER        = { .PVG = 255, .UID = 4 };

    return 0;
}