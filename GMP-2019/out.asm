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
