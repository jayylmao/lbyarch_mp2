; Jay Michael Carlos and Janica Megan Reyes - LBYARCH S14
section .data
	sdot	dd	0.0
section .text
bits 64												; define project as 64-bit.
default rel

global asmDotProduct								; make assembly code accessible to c file.
extern printf

asmDotProduct;
	; compute for the vector dot products of two vectors a and b of length n.
	; Arguments:
	; rcx: vector length.
	; rdx: address of vector a.
	; r8: address of vector b.
	lea		r10, [sdot]
	xorps	xmm0, xmm0								; set xmm0 to 0 be used as accumulator.
	mov		rbx, 4									; for optimization, move constant 4 to rbx, as we increment by 4 later on.

loopStart:
	cmp		rcx, 0									; if all elements have been processed, stop loop.
	jz		end

	movss	xmm1, [rdx]								; load float a[i] into xmm1
	movss	xmm2, [r8]								; load float b[i] into xmm2
	mulss	xmm1, xmm2								; multiply a[i] * b[i]
	addss	xmm0, xmm1								; add result to accumulator.

	add		rdx, rbx								; move to next element in a.
	add		r8, rbx									; move to next element in b.
	dec		rcx										; restart loop if rcx is not 0.
	jmp		loopStart
end:
	movss	[r10], xmm0								; store the result in sdot.
	ret