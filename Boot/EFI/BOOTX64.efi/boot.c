#include "uefi_utils.h"

#define KERNEL_PATH L"\\Boot\\EFI\\XART.efi\\xart_init.bin"
#define KERNEL_LOAD_ADDRESS 0x100000

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
    init_uefi(ImageHandle, SystemTable);

    // Open the kernel file
    EFI_FILE_PROTOCOL *kernel_file;
    EFI_STATUS status = uefi_load_file(ImageHandle, KERNEL_PATH, &kernel_file);
    if (EFI_ERROR(status)) {
        uefi_print(L"Failed to open kernel_init.bin\r\n");
        uefi_halt();
    }

    // Get file info to determine size
    EFI_FILE_INFO *file_info;
    UINTN info_size = sizeof(EFI_FILE_INFO) + 200;
    status = gBS->AllocatePool(EfiLoaderData, info_size, (void**)&file_info);
    if (EFI_ERROR(status)) {
        uefi_print(L"Failed to allocate memory for file info\r\n");
        uefi_halt();
    }

    status = kernel_file->GetInfo(kernel_file, &gEfiFileInfoGuid, &info_size, file_info);
    if (EFI_ERROR(status)) {
        uefi_print(L"Could not get kernel file info\r\n");
        uefi_halt();
    }

    UINTN kernel_size = file_info->FileSize;
    uefi_print(L"Kernel file size detected. Loading...\r\n");

    // Allocate memory and read file into it
    EFI_PHYSICAL_ADDRESS kernel_address = KERNEL_LOAD_ADDRESS;
    UINTN pages = (kernel_size + 0xFFF) / 0x1000;
    status = uefi_allocate(pages, &kernel_address);
    if (EFI_ERROR(status)) {
        uefi_print(L"Failed to allocate memory for kernel\r\n");
        uefi_halt();
    }

    status = kernel_file->Read(kernel_file, &kernel_size, (void*)kernel_address);
    if (EFI_ERROR(status)) {
        uefi_print(L"Failed to read kernel into memory\r\n");
        uefi_halt();
    }

    // Exit boot services
    UINTN map_size = 0, map_key, desc_size;
    UINT32 desc_ver;
    gBS->GetMemoryMap(&map_size, NULL, &map_key, &desc_size, &desc_ver);
    map_size += desc_size * 8;
    EFI_MEMORY_DESCRIPTOR *map;
    gBS->AllocatePool(EfiLoaderData, map_size, (void**)&map);
    gBS->GetMemoryMap(&map_size, map, &map_key, &desc_size, &desc_ver);
    gBS->ExitBootServices(ImageHandle, map_key);

    // Jump to kernel
    void (*kernel_entry)(void) = ((__attribute__((sysv_abi)) void(*)(void))kernel_address);
    kernel_entry();

    return EFI_SUCCESS; // We should never return here.
}
