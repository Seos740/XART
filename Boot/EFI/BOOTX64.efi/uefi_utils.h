#ifndef UEFI_UTILS_H
#define UEFI_UTILS_H

#include <efi.h>
#include <efilib.h>

// === Global References ===
extern EFI_SYSTEM_TABLE *gST;
extern EFI_BOOT_SERVICES *gBS;

// === UEFI Basics ===
void init_uefi(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable);
void uefi_print(CHAR16 *str);
EFI_STATUS uefi_wait_for_key(CHAR16 *out_char);
void uefi_halt();
EFI_STATUS uefi_allocate(UINTN pages, EFI_PHYSICAL_ADDRESS *addr);
EFI_STATUS uefi_load_file(EFI_HANDLE ImageHandle, CHAR16 *filename, EFI_FILE_PROTOCOL **file);
EFI_STATUS uefi_read_file(EFI_FILE_PROTOCOL *file, void **buffer, UINTN *size);

// === Framebuffer ===
typedef struct {
    void *BaseAddress;
    UINTN BufferSize;
    UINT32 Width;
    UINT32 Height;
    UINT32 PixelsPerScanLine;
    EFI_GRAPHICS_PIXEL_FORMAT PixelFormat;
} FRAMEBUFFER;

EFI_STATUS uefi_init_framebuffer(FRAMEBUFFER *fb);
void uefi_draw_pixel(FRAMEBUFFER *fb, UINT32 x, UINT32 y, UINT32 color);
void uefi_clear_screen_fb(FRAMEBUFFER *fb, UINT32 color);

#endif // UEFI_UTILS_H
