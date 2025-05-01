global syscall_entry
extern syscall_handler

section .text
syscall_entry:
    swapgs                      ; swap to kernel GS base
    mov    gs:[0], rsp          ; save user stack
    mov    rsp, gs:[8]          ; load kernel stack

    push   rcx                  ; save volatile registers
    push   r11

    mov    rdi, rax             ; syscall number
    mov    rsi, rdi             ; dummy arg

    call   syscall_handler      ; call actual handler

    pop    r11                  ; restore
    pop    rcx
    swapgs
    sysretq
