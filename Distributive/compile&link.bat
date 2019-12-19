cd %0/..

ml /c /coff main.asm

link "main.obj" /DYNAMICBASE "C:\Users\admin\Desktop\LP\GMP-2019\Distributive\StaticLib.lib" /SUBSYSTEM:console /out:"C:\Users\admin\Desktop\LP\GMP-2019\Distributive\out.exe"

out.exe