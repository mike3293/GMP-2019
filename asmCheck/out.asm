.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	includelib ../Debug/StaticLib.lib

	EXTERN printS :PROC
	EXTERN printN :PROC
	ExitProcess PROTO :DWORD

.stack 4096

.const
	L1 BYTE 'Mikalai', 0
	L2 BYTE 'Mikhail', 0
	L3 WORD 0

.data
	mainname1 DWORD ?
	mainname2 DWORD ?
	maina DWORD ?

.code

	main PROC
		push offset L2
		call printS

		push 0
		call ExitProcess
	main ENDP
end main