section .data
    message db 'Hello, World!',0

section .text
    global _start

_start:
    ; write(1, message, 13) syscall
    mov edx, 13
    mov ecx, message
    mov ebx, 1
    mov eax, 4
    int 0x80

    ; exit(0) syscall
    mov eax, 1
    xor ebx, ebx
    int 0x80
