	.global my_sin
	.intel_syntax noprefix
	.text

my_sin:

	push	ebp
	mov		ebp, esp

	movsd 	xmm0, [ebp + 8] // x
	movsd 	xmm1, [ebp + 8] // x
	sub		esp, 8
	mov 	eax, 1
	cvtsi2sd xmm2, eax // 1.0

	movsd 	xmm3, [ebp + 8] // x
	mulsd 	xmm3, xmm3 // x**2
	mov 	edx, -1
	cvtsi2sd xmm2, edx // -1.0
	mulsd 	xmm3, xmm2 // -x**2

Loop:
	mulsd 	xmm1, xmm3// xmm1 *= (-x**2)

	add 	eax, 1
	cvtsi2sd xmm2, eax 
	divsd 	xmm1, xmm2 // x**t / eax
	add 	eax, 1
	cvtsi2sd xmm2, eax
	divsd 	xmm1, xmm2 // x**t / (eax+1)

	movsd 	xmm4, xmm0
	addsd 	xmm0, xmm1
	comisd xmm0, xmm4
	jne	Loop

	movsd 	[ebp - 8], xmm0
	fld	qword ptr [ebp - 8]

	mov 	esp, ebp
	pop		ebp
	ret