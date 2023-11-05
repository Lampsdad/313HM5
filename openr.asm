section .text
global openr

; Constants for system calls
SYS_OPEN equ 2
O_RDONLY equ 0

openr:
    ; Function prologue
    push rbp
    mov rbp, rsp

    ; Arguments:
    ; [rbp + 16] = path

    ; Open the file
    mov rax, SYS_OPEN
    mov rdi, [rbp + 16]
    mov rsi, O_RDONLY

    syscall

    pop rbp
    ret
