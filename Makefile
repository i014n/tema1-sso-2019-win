CC = cl
L = link
CFLAGS = /c /MD /nologo /W3 /DDLL_IMPORTS

build: tema1.exe

tema1.exe: tema1.obj compare.lib
	$(L) /out:tema1.exe /nologo tema1.obj compare.lib 

tema1.obj: tema1.cpp
	$(CC) $(CFLAGS) tema1.cpp



clean:
	del /Q /S /F tema1.obj tema1.exe
