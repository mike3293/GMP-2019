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
	L1 WORD 17
	L2 WORD 18
	L3 BYTE 'Mikhail', 0
	L4 BYTE 'a less than b', 0
	L5 WORD 0

.data
	minresult WORD 0
	mainname1 DWORD 0
	mainname2 DWORD 0
	maina WORD 0
	mainb WORD 0
	mainc WORD 0
	mainresult WORD 0

.code
min PROC mina : WORD, minb : WORD
	mov ax, minb
	cmp ax, mina
	jl m0
	jg m1
	je m1
m0:
	push minb
	pop minresult
	jmp e0
m1:
	push mina
	pop minresult
e0:
	push minresult
	jmp local0
local0:
	pop ax
	ret
min ENDP


	main PROC
	push L1
	pop mainb
	push L2
	pop mainc
	push offset L3
	pop mainname1
	push offset mainname1
	pop mainname2
	mov ax, maina
	cmp ax, mainb
	jl m2
	jg m3
	je m3
m2:
	push mainc
	push mainb
	call min
	push ax
	pop maina
	jmp e1
m3:
	push offset L4
	call printS
e1:
	mov ax, maina
	cmp ax, mainb
	je m4
	jg m4
	jl m5
m4:
	push mainb
	call printN
m5:
	push 0
	jmp theend
theend:
	call ExitProcess
main ENDP
end main