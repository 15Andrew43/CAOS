	.text
	.global f
f:
	// a *= x
	mul r0, r0, r3
	// a *= x
	mul r0, r0, r3
	// b *= x
	mul r1, r1, r3

	// a += b
	add r0, r0, r1
	// a += c
	add r0, r0, r2

	bx lr
