global gdt_flush

gdt_flush:
    lgdt [rdi]               ; rdi = &gdtr
    mov ax, si               ; si = code segment selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    push si
    lea rax, [rel .reload_cs]
    push rax
    lretq                   ; far jump to reload CS

.reload_cs:
    ret
