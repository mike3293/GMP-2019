.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	includelib ../Debug/Standard_Library.lib
	ExitProcess PROTO :DWORD

	outc PROTO: DWORD
	outd PROTO: DWORD
	strl PROTO: DWORD
	power PROTO: DWORD, :DWORD

.stack 4096
.const
	L1 BYTE Mikalai, 0
	L2 WORD 0
.data
	name1 DWORD ?
	name2 DWORD ?
	a DWORD ?
