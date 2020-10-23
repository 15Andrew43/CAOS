	.global summ
	.intel_syntax noprefix
	.text
summ:
	mov 	esi, [esp + 4] // int n
	mov 	edi, [esp + 8] // const int A*
	mov 	edx, [esp + 12] // const int B*
	mov 	ecx, [esp + 16] // int R*
	mov 	eax, 0 // cnt
Loop:
	cmp 	eax, esi
	jae 	Exit // if (cnt >= N) : return

	mov 	ebx, [edi + 4 * eax] // ebx = *(edi + 4 * cnt)
	add 	ebx, [edx + 4 * eax] // ebx += *(edx + 4 * cnt)
	mov 	[ecx + 4 * eax], ebx // *(ecx + 4 * cnt) = ebx
	add 	eax, 1 // ++cnt
	jmp 	Loop
Exit:
	ret