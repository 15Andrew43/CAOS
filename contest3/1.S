	.text
	.global main
main:
	push {ip, lr}
	//ldr r0, printf_fmt_ptr
	//mov r1, #15
	//bl printf

	ldr r0, scanf_fmt_ptr
	sub sp, #8
	mov r1, sp
	mov r2, sp
	add r2, #4
	bl scanf 	

	ldr r1, [sp]
	add sp, #4
	ldr r2, [sp]

	add r1, r1, r2

	ldr r0, printf_fmt_ptr
	bl printf

	add sp, #4

	pop {ip, pc}


printf_fmt_ptr:
	.word printf_fmt

printf_fmt:
	.ascii "%d\n\0\0"


scanf_fmt_ptr:
	.word scanf_fmt

scanf_fmt:
	.ascii "%d%d\0\0"