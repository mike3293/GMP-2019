.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	includelib ../Debug/StaticLib.lib

	EXTERN printS :PROC
	EXTERN printN :PROC
	EXTERN raise :PROC
	ExitProcess PROTO :DWORD

.stack 4096

.const
	L1 WORD 1
	L2 WORD 2
	L3 WORD 3
	L4 BYTE 'a more than b', 0
	L5 BYTE 'bye', 0
	L6 WORD 0

.data
	maina WORD 0
	mainb WORD 0
	mainc WORD 0

.code
	main PROC
	push L1
	pop mainb
	push L2
	pop maina
	push L3
	pop mainc
	mov ax, maina
	cmp ax, mainb
	jg m0
	jl m1
	je m1
m0:
	push offset L4
	call printS
m1:
	push offset L5
	call printS
	push 0
	jmp theend
theend:
	call ExitProcess
main ENDP
end main