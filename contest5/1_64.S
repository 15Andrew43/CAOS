#include </usr/include/sys/syscall.h>
 
    .intel_syntax noprefix
    .text
    .global _start

_start:
    
    push    rax
    push    rdi
    push    rsi
.Loop:
    mov     rax, __NR_read
    mov     rdi, 0 // 0 - input, 1 - output, 2 - stderr
    mov     rsi, hello_world_ptr
    mov     rdx, 1 // how much read
//    int     0x80
    syscall

    cmp    rax, 0 // *ecx == '\0'
    je      .Loop_return


    mov     rax, __NR_write
    mov     rdi, 1 // 0 - input, 1 - output, 2 - stderr
    mov     rdx, 1 // how much read
//    int     0x80
    syscall

    jmp     .Loop

.Loop_return:
    mov     rax, __NR_exit
    mov     rdi, 1
//    int     0x80
    syscall
    pop rax
    pop rdi
    pop rsi
    .data

hello_world:
    .string ""

hello_world_ptr:
    .long hello_world