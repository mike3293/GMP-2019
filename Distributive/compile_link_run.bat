
cd %0/..

ml /c /coff %1

link "%~n1.obj" /DYNAMICBASE "%2" /SUBSYSTEM:console /out:"out.exe"

out.exe