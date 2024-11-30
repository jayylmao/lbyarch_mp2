; Jay Michael Carlos and Janica Megan Reyes - LBYARCH S14
section .data
	msg	db	"Hello world", 13, 10, 0				; hello world message. get rid of this.
section .text
bits 64												; define project as 64-bit.
default rel

global asmDotProduct								; make assembly code accessible to c file.
extern printf										; include external function printf.

asmDotProduct:
	sub	rsp, 8 * 5									; set up stack frame. (mandatory 40 bytes.)
	lea	rcx, [msg]									; print hello world.
	call	printf
	add	rsp, 8 * 5