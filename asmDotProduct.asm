; Jay Michael Carlos and Janica Megan Reyes - LBYARCH S14
section .data
	one	dd	1.0										; temporary variable to return 1.
section .text
bits 64												; define project as 64-bit.
default rel

global asmDotProduct								; make assembly code accessible to c file.

asmDotProduct:
	movss	xmm1, [one]
	addss	xmm0, xmm1
	ret