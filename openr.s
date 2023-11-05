section .bss
    buffer resb 4096   ; Buffer to read file contents

section .text
global openr
openr:
    ; Arguments:
    ; rdi - const char *pathname (pointer to the pathname)

    ; System call number for 'open'
    mov rax, 2

    ; Mode (O_RDONLY)
    mov rdi, rdi     ; rdi already contains the pointer to the pathname

    ; Flags (0 or O_RDONLY)
    xor rsi, rsi

    ; Invoke the 'open' system call
    syscall

    ; Check for errors (RAX will contain the return value)
    cmp rax, -1
    jz .error

    ; File descriptor is now in RAX

    ; Read and write the contents of the file to stdout
    mov rdi, rax        ; File descriptor
    mov rax, 0          ; System call number for 'read'
    mov rsi, buffer     ; Buffer for reading
    mov rdx, 4096       ; Buffer size

.read_loop:
    syscall

    ; Check if we've reached the end of the file (RAX will contain the number of bytes read)
    test rax, rax
    jz .done

    ; Write the read data to stdout
    mov rax, 1          ; System call number for 'write'
    mov rdi, 1          ; File descriptor for stdout
    mov rsi, buffer     ; Buffer with data
    mov rdx, rax        ; Number of bytes to write
    syscall

    ; Continue reading
    jmp .read_loop

.done:
    ; Close the file
    mov rax, 3          ; System call number for 'close'
    syscall

    ; Return 0 (success)
    mov rax, 0
    ret

.error:
    ; An error occurred, return the error code in RAX
    ret