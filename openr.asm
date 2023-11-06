global openr
section .text

openr:
    mov rax, 2      ; system call number for open()
    mov rdi, rdi    ; file path
    xor rsi, rsi    ; flags for read only (O_READ or O_RDONLY)
    syscall         ; make the system call
    ret             ; return to caller