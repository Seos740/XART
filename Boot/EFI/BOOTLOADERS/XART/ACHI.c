#include <stdint.h>

#define HBA_PORT_DEV_PRESENT 0x3
#define HBA_PORT_IPM_ACTIVE  0x1
#define ATA_CMD_READ_DMA_EXT 0x25
#define SECTOR_SIZE 512

typedef volatile struct {
    uint32_t clb;       // 0x00, command list base address
    uint32_t clbu;      // 0x04, command list base address upper 32 bits
    uint32_t fb;        // 0x08, FIS base address
    uint32_t fbu;       // 0x0C, FIS base address upper 32 bits
    uint32_t is;        // 0x10, interrupt status
    uint32_t ie;        // 0x14, interrupt enable
    uint32_t cmd;       // 0x18, command and status
    uint32_t reserved0; // 0x1C
    uint32_t tfd;       // 0x20, task file data
    uint32_t sig;       // 0x24, signature
    uint32_t ssts;      // 0x28, SATA status (SCR0)
    uint32_t sctl;      // 0x2C, SATA control (SCR2)
    uint32_t serr;      // 0x30, SATA error (SCR1)
    uint32_t sact;      // 0x34, SATA active (SCR3)
    uint32_t ci;        // 0x38, command issue
    uint32_t sntf;      // 0x3C, SATA notification (SCR4)
    uint32_t fbs;       // 0x40, FIS-based switch control
    uint32_t reserved1[11];  // 0x44 ~ 0x6F
    uint32_t vendor[4];      // 0x70 ~ 0x7F
} HBA_PORT;

typedef volatile struct {
    uint32_t cap;       // 0x00, Host capability
    uint32_t ghc;       // 0x04, Global host control
    uint32_t is;        // 0x08, Interrupt status
    uint32_t pi;        // 0x0C, Ports implemented
    uint32_t vs;        // 0x10, Version
    uint32_t ccc_ctl;   // 0x14, Command completion coalescing control
    uint32_t ccc_pts;   // 0x18, Command completion coalescing ports
    uint32_t em_loc;    // 0x1C, Enclosure management location
    uint32_t em_ctl;    // 0x20, Enclosure management control
    uint32_t cap2;      // 0x24, Host capabilities extended
    uint32_t bohc;      // 0x28, BIOS/OS handoff control and status
    uint8_t  reserved[0xA0 - 0x2C];
    uint8_t  vendor[0x100 - 0xA0];
    HBA_PORT ports[32]; // 0x100 - 0x1100, one per port
} HBA_MEM;

HBA_PORT* find_sata_port(HBA_MEM* abar) {
    uint32_t pi = abar->pi;
    for (int i = 0; i < 32; i++) {
        if (pi & (1 << i)) {
            HBA_PORT* port = &abar->ports[i];
            uint32_t ssts = port->ssts;
            uint8_t ipm = (ssts >> 8) & 0x0F;
            uint8_t det = ssts & 0x0F;
            if (det == HBA_PORT_DEV_PRESENT && ipm == HBA_PORT_IPM_ACTIVE)
                return port;
        }
    }
    return 0; // No active device found
}

int ahci_read_sector(HBA_PORT* port, uint64_t lba, void* buf) {
    // Ensure the port is not running
    port->cmd &= ~0x01; // Clear ST (start)
    port->cmd &= ~0x10; // Clear FRE (FIS receive enable)
    while (port->cmd & 0x8000); // Wait until CR (command list running) is cleared
    while (port->cmd & 0x4000); // Wait until FR (FIS receive running) is cleared

    // Allocate command list and command table (physically mapped)
    static uint8_t clb_area[1024] __attribute__((aligned(1024)));
    static uint8_t fb_area[256] __attribute__((aligned(256)));
    static uint8_t ct_area[256] __attribute__((aligned(128)));

    port->clb = (uint32_t)(uintptr_t)clb_area;
    port->fb  = (uint32_t)(uintptr_t)fb_area;

    // Fill command header
    uint8_t slot = 0;
    typedef struct {
        uint16_t flags;
        uint16_t prdt_length;
        uint32_t prdbc;
        uint32_t ctba;
        uint32_t ctbau;
        uint32_t reserved[4];
    } HBA_CMD_HEADER;

    HBA_CMD_HEADER* cmd_hdr = (HBA_CMD_HEADER*)clb_area;
    cmd_hdr[slot].flags = (1 << 5); // Read, 1 PRDT
    cmd_hdr[slot].prdt_length = 1;
    cmd_hdr[slot].ctba = (uint32_t)(uintptr_t)ct_area;

    // Fill command table
    typedef struct {
        uint32_t dba;
        uint32_t dbau;
        uint32_t reserved;
        uint32_t dbc; // Byte count + interrupt bit
    } HBA_PRDT_ENTRY;

    typedef struct {
        uint8_t cfis[64];
        uint8_t acmd[16];
        uint8_t reserved[48];
        HBA_PRDT_ENTRY prdt[1];
    } HBA_CMD_TBL;

    HBA_CMD_TBL* cmd_tbl = (HBA_CMD_TBL*)ct_area;
    cmd_tbl->prdt[0].dba = (uint32_t)(uintptr_t)buf;
    cmd_tbl->prdt[0].dbau = 0;
    cmd_tbl->prdt[0].dbc = SECTOR_SIZE - 1; // 512 bytes
    cmd_tbl->prdt[0].dbc |= (1 << 31); // Interrupt on completion

    // Setup FIS
    uint8_t* cfis = cmd_tbl->cfis;
    cfis[0] = 0x27; // Host to Device FIS
    cfis[1] = 0x80; // Command
    cfis[2] = ATA_CMD_READ_DMA_EXT;

    cfis[4] = (uint8_t)(lba);
    cfis[5] = (uint8_t)(lba >> 8);
    cfis[6] = (uint8_t)(lba >> 16);
    cfis[7] = (uint8_t)(lba >> 24);
    cfis[8] = (uint8_t)(lba >> 32);
    cfis[9] = (uint8_t)(lba >> 40);

    cfis[12] = 1; // Sector count

    // Re-enable
    port->cmd |= (0x10 | 0x01); // FRE | ST
    port->ci = 1 << slot;

    // Wait for completion
    while (port->ci & (1 << slot));
    return 0;
}
