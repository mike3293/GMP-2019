.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	includelib ../Debug/StaticLib.lib

	EXTERN _printS :PROC
	EXTERN _printN :PROC
	EXTERN _pow :PROC
	EXTERN _compare :PROC
	EXTERN _pause :PROC
	ExitProcess PROTO :DWORD

.stack 4096

.const
	L1 BYTE '../Debug/StaticLib.lib', 0
	L2 BYTE 'First argument more than second', 0
	L3 BYTE 'Second argument more than first', 0
	L4 WORD 17
	L5 WORD 18
	L6 BYTE 'Mikhail', 0
	L7 WORD 1
	L8 BYTE 'strings are not equal', 0
	L9 WORD 2
	L10 WORD 300
	L11 WORD 0

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
	jl p0
	jg p1
	je p1
p0:
	push minb
	pop minresult
	jmp ife0
p1:
	push mina
	pop minresult
ife0:
	push minresult
	pop eax
	ret
min ENDP

ismore PROC ismorea : WORD, ismoreb : WORD
	mov ax, ismorea
	cmp ax, ismoreb
	jg p2
	jl p3
	je p3
p2:
	push offset L2
	pop ismoreresult
	jmp ife1
p3:
	push offset L3
	pop ismoreresult
ife1:
	push ismoreresult
	pop eax
	ret
ismore ENDP


main PROC
	push L4
	pop mainb
	push L5
	pop mainc
	push offset L6
	pop mainstr1
	push mainstr1
	pop mainstr2
	push mainstr2
	push mainstr1
	call _compare
	push eax
	pop mainresult
	mov ax, mainresult
	cmp ax, L7
	je p4
	jg p5
	jl p5
p4:
	movzx eax, mainc
	push eax
	movzx eax, mainb
	push eax
	call min
	push eax
	pop maina
	jmp ife2
p5:
	push offset L8
	call _printS
ife2:
	mov ax, maina
	cmp ax, mainb
	je p6
	jg p6
	jl p7
p6:
	movzx eax, L9
	push eax
	movzx eax, mainc
	push eax
	call _pow
	push eax
	pop mainb
	push mainb
	call _printN
p7:
	movzx eax, L10
	push eax
	movzx eax, mainb
	push eax
	call ismore
	push eax
	pop mainstr1
	push mainstr1
	call _printS
	push 0
	call _pause
	call ExitProcess
main ENDP
end main