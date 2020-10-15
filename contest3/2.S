	.text
	.global main
main:
	push {ip, lr}
loop:
	ldr r0, .input_flow
	ldr r0, [r0]
	
	bl fgetc

	cmp r0, #-1
	beq exit	
	
	cmp r0, #57
	bhi loop
	cmp r0, #48
	bcc loop

	ldr r1, .output_flow
	ldr r1, [r1]
		
	bl fputc
		
	b loop

exit:
	pop {ip, pc}

.input_flow:
	.word stdin

.output_flow:
	.word stdout