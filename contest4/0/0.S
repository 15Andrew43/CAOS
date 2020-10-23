	.global summ
	.intel_syntax noprefix
	.text
summ:
// rdi = N, rsi = *A, rdx = *B, rcx = *R
	push	rbx // tmp
.Loop:
	dec		rdi
	mov 	rbx, [rsi]
	mov		[rcx], rbx
	mov		rbx, [rdx]
	add		[rcx], rbx
	add		rsi, 4
	add 	rdx, 4
	add 	rcx, 4
	cmp		rdi, 0
	jne		.Loop

	pop 	rbx
	ret
