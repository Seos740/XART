; example

section .text
global user_start

user_start:
    mov rax, 0         ; syscall number
    mov rdi, 100       ; argument
    syscall            ; jump to ring 0
    hlt                ; stop (for testing)
