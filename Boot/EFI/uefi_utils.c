#include <efi.h>
#include <efilib.h>

EFI_SYSTEM_TABLE *gST = NULL;
EFI_BOOT_SERVICES *gBS = NULL;

void init_uefi(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
    gST = SystemTable;
    gBS = SystemTable->BootServices;
    InitializeLib(ImageHandle, SystemTable);
}

// === Console ===

void uefi_print(CHAR16 *str) {
    gST->ConOut->OutputString(gST->ConOut, str);
}

void uefi_clear_screen() {
    gST->ConOut->ClearScreen(gST->ConOut);
}

void uefi_set_cursor_position(UINTN column, UINTN row) {
    gST->ConOut->SetCursorPosition(gST->ConOut, column, row);
}

void uefi_set_text_attribute(UINTN attribute) {
    gST->ConOut->SetAttribute(gST->ConOut, attribute);
}

// === Input ===

EFI_STATUS uefi_wait_for_key(CHAR16 *out_char) {
    EFI_INPUT_KEY key;
    EFI_STATUS status;

    uefi_print(L"Press a key...\r\n");
    gBS->WaitForEvent(1, &gST->ConIn->WaitForKey, NULL);
    status = gST->ConIn->ReadKeyStroke(gST->ConIn, &key);

    if (EFI_ERROR(status)) return status;

    *out_char = key.UnicodeChar;
    return EFI_SUCCESS;
}

// === Sleep ===

void uefi_sleep(UINTN milliseconds) {
    gBS->Stall(milliseconds * 1000); // microseconds
}

// === System Halt ===

void uefi_halt() {
    while (1) {
        __asm__ __volatile__("hlt");
    }
}

// === File System and File Access ===

EFI_STATUS uefi_load_file(EFI_HANDLE ImageHandle, CHAR16 *filename, EFI_FILE_PROTOCOL **file) {
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *fs;
    EFI_FILE_PROTOCOL *root;

    EFI_STATUS status = gBS->HandleProtocol(
        ImageHandle,
        &gEfiSimpleFileSystemProtocolGuid,
        (void**)&fs
    );
    if (EFI_ERROR(status)) return status;

    status = fs->OpenVolume(fs, &root);
    if (EFI_ERROR(status)) return status;

    return root->Open(root, file, filename, EFI_FILE_MODE_READ, 0);
}

EFI_STATUS uefi_get_file_info(EFI_FILE_PROTOCOL *file, EFI_FILE_INFO **file_info) {
    UINTN buffer_size = sizeof(EFI_FILE_INFO) + 1024;
    *file_info = AllocatePool(buffer_size);
    if (!*file_info) return EFI_OUT_OF_RESOURCES;

    return file->GetInfo(
        file,
        &gEfiFileInfoGuid,
        &buffer_size,
        *file_info
    );
}

EFI_STATUS uefi_load_kernel(EFI_FILE_PROTOCOL *file, VOID **kernel_buffer, UINTN *kernel_size) {
    EFI_FILE_INFO *info;
    EFI_STATUS status = uefi_get_file_info(file, &info);
    if (EFI_ERROR(status)) return status;

    *kernel_size = info->FileSize;
    *kernel_buffer = AllocatePool(*kernel_size);
    if (!*kernel_buffer) return EFI_OUT_OF_RESOURCES;

    status = file->Read(file, kernel_size, *kernel_buffer);
    FreePool(info);
    return status;
}

EFI_STATUS uefi_list_files(EFI_HANDLE ImageHandle) {
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *fs;
    EFI_FILE_PROTOCOL *root;
    EFI_FILE_INFO *file_info;
    UINTN buffer_size = 0;
    EFI_STATUS status;

    status = gBS->HandleProtocol(ImageHandle, &gEfiSimpleFileSystemProtocolGuid, (void**)&fs);
    if (EFI_ERROR(status)) return status;

    status = fs->OpenVolume(fs, &root);
    if (EFI_ERROR(status)) return status;

    EFI_FILE_PROTOCOL *file;
    status = root->Open(root, &file, L"\\", EFI_FILE_MODE_READ, 0);
    if (EFI_ERROR(status)) return status;

    buffer_size = 1024;
    file_info = AllocatePool(buffer_size);
    
    if (!file_info) return EFI_OUT_OF_RESOURCES;

    while (TRUE) {
        buffer_size = 1024;
        status = file->Read(file, &buffer_size, file_info);
        if (EFI_ERROR(status) || buffer_size == 0) break;

        uefi_print(file_info->FileName);
        uefi_print(L"\r\n");
    }

    FreePool(file_info);
    file->Close(file);
    return EFI_SUCCESS;
}

// === Memory and Boot Services ===

EFI_STATUS uefi_allocate(UINTN pages, EFI_PHYSICAL_ADDRESS *addr) {
    return gBS->AllocatePages(AllocateAnyPages, EfiLoaderData, pages, addr);
}

EFI_STATUS uefi_get_memory_map(
    UINTN *MemoryMapSize,
    EFI_MEMORY_DESCRIPTOR *MemoryMap,
    UINTN *MapKey,
    UINTN *DescriptorSize,
    UINT32 *DescriptorVersion
) {
    return gBS->GetMemoryMap(
        MemoryMapSize,
        MemoryMap,
        MapKey,
        DescriptorSize,
        DescriptorVersion
    );
}

EFI_STATUS uefi_exit_boot_services(EFI_HANDLE ImageHandle, UINTN MapKey) {
    return gBS->ExitBootServices(ImageHandle, MapKey);
}

EFI_STATUS uefi_set_mem(void *buffer, UINTN size, UINT8 value) {
    return gBS->SetMem(buffer, size, value);
}

EFI_STATUS uefi_copy_mem(void *dest, void *src, UINTN size) {
    return gBS->CopyMem(dest, src, size);
}

// === Loaded Image Info ===

EFI_STATUS uefi_get_loaded_image(EFI_HANDLE ImageHandle, EFI_LOADED_IMAGE_PROTOCOL **loadedImage) {
    return gBS->HandleProtocol(
        ImageHandle,
        &gEfiLoadedImageProtocolGuid,
        (void**)loadedImage
    );
}

// === Exit Application ===

EFI_STATUS uefi_exit(EFI_HANDLE ImageHandle, EFI_STATUS status) {
    return gBS->Exit(ImageHandle, status, 0, NULL);
}

// === Framebuffer ===

typedef struct {
    void *BaseAddress;
    UINTN BufferSize;
    UINT32 Width;
    UINT32 Height;
    UINT32 PixelsPerScanLine;
    EFI_GRAPHICS_PIXEL_FORMAT PixelFormat;
} FRAMEBUFFER;

EFI_STATUS uefi_init_framebuffer(FRAMEBUFFER *fb) {
    EFI_GUID gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;
    EFI_STATUS status;

    status = gBS->LocateProtocol(&gopGuid, NULL, (void **)&gop);
    if (EFI_ERROR(status)) {
        uefi_print(L"Failed to locate GOP\r\n");
        return status;
    }

    fb->BaseAddress = (void *)(UINTN)gop->Mode->FrameBufferBase;
    fb->BufferSize = gop->Mode->FrameBufferSize;
    fb->Width = gop->Mode->Info->HorizontalResolution;
    fb->Height = gop->Mode->Info->VerticalResolution;
    fb->PixelsPerScanLine = gop->Mode->Info->PixelsPerScanLine;
    fb->PixelFormat = gop->Mode->Info->PixelFormat;

    return EFI_SUCCESS;
}

void uefi_draw_pixel(FRAMEBUFFER *fb, UINT32 x, UINT32 y, UINT32 color) {
    if (x >= fb->Width || y >= fb->Height) return;

    UINT32 *pixelPtr = (UINT32 *)fb->BaseAddress;
    pixelPtr[y * fb->PixelsPerScanLine + x] = color;
}

void uefi_clear_screen_fb(FRAMEBUFFER *fb, UINT32 color) {
    for (UINT32 y = 0; y < fb->Height; y++) {
        for (UINT32 x = 0; x < fb->Width; x++) {
            uefi_draw_pixel(fb, x, y, color);
        }
    }
}

EFI_STATUS uefi_read_file(EFI_FILE_PROTOCOL *file, void **buffer, UINTN *size) {
    EFI_STATUS status;

    // Get file size
    EFI_FILE_INFO *fileInfo;
    UINTN infoSize = sizeof(EFI_FILE_INFO) + 512;
    status = gBS->AllocatePool(EfiLoaderData, infoSize, (void**)&fileInfo);
    if (EFI_ERROR(status)) return status;

    status = file->GetInfo(file, &gEfiFileInfoGuid, &infoSize, fileInfo);
    if (EFI_ERROR(status)) {
        gBS->FreePool(fileInfo);
        return status;
    }

    *size = fileInfo->FileSize;

    // Allocate buffer for file contents
    status = gBS->AllocatePool(EfiLoaderData, *size, buffer);
    if (EFI_ERROR(status)) {
        gBS->FreePool(fileInfo);
        return status;
    }

    // Read file into buffer
    status = file->Read(file, size, *buffer);

    gBS->FreePool(fileInfo);
    return status;
}


