.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	includelib ../Debug/StaticLib.lib

	EXTERN printS :PROC
	EXTERN printN :PROC
	EXTERN raiseto :PROC
	EXTERN compare :PROC
	ExitProcess PROTO :DWORD

.stack 4096

.const
	L1 BYTE 'First argument more than second', 0
	L2 BYTE 'Second argument more than first', 0
	L3 WORD 17
	L4 WORD 18
	L5 BYTE 'Mikhail', 0
	L6 WORD 1
	L7 BYTE 'strings are not equal', 0
	L8 WORD 2
	L9 WORD 300
	L10 WORD 0

.data
	minresult WORD 0
	ismoreresult DWORD 0
	mainstr1 DWORD 0
	mainstr2 DWORD 0
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
	pop eax
	ret
min ENDP

ismore PROC ismorea : WORD, ismoreb : WORD
	mov ax, ismorea
	cmp ax, ismoreb
	jg m2
	jl m3
	je m3
m2:
	push offset L1
	pop ismoreresult
	jmp e1
m3:
	push offset L2
	pop ismoreresult
e1:
	push ismoreresult
	jmp local1
local1:
	pop eax
	ret
ismore ENDP


main PROC
	push L3
	pop mainb
	push L4
	pop mainc
	push offset L5
	pop mainstr1
	push mainstr1
	pop mainstr2
	push mainstr2
	push mainstr1
	call compare
	push eax
	pop mainresult
	mov ax, mainresult
	cmp ax, L6
	je m4
	jg m5
	jl m5
m4:
	movzx eax, mainc
	push eax
	movzx eax, mainb
	push eax
	call min
	push eax
	pop maina
	jmp e2
m5:
	push offset L7
	call printS
e2:
	mov ax, maina
	cmp ax, mainb
	je m6
	jg m6
	jl m7
m6:
	movzx eax, L8
	push eax
	movzx eax, mainc
	push eax
	call raiseto
	push eax
	pop mainb
	push mainb
	call printN
m7:
	movzx eax, L9
	push eax
	movzx eax, mainb
	push eax
	call ismore
	push eax
	pop mainstr1
	push mainstr1
	call printS
	push 0
	jmp theend
theend:
	call ExitProcess
main ENDP
end main