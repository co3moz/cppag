all: clearcache srctolib micromodtolib libtobin executebin
clearcache:
	echo =============== CLEARING COLOR BUFFER ===============================
	echo =============== CLEARING COLOR BUFFER ===============================
	echo =============== CLEARING COLOR BUFFER ===============================
	echo =============== CLEARING COLOR BUFFER ===============================
	echo =============== CLEARING COLOR BUFFER ===============================
	echo =============== CLEARING COLOR BUFFER ===============================
	echo =============== CLEARING COLOR BUFFER ===============================
	echo =============== CLEARING COLOR BUFFER ===============================
	echo =============== CLEARING COLOR BUFFER ===============================
	echo =============== CLEARING COLOR BUFFER ===============================
	echo =============== CLEARING COLOR BUFFER ===============================
	echo =============== CLEARING COLOR BUFFER ===============================
	echo =============== CLEARING COLOR BUFFER ===============================
	echo =============== CLEARING COLOR BUFFER ===============================
	echo =============== CLEARING COLOR BUFFER ===============================
	echo =============== CLEARING COLOR BUFFER ===============================
	echo =============== CLEARING COLOR BUFFER ===============================
	echo =============== CLEARING COLOR BUFFER ===============================
	echo =============== CLEARING COLOR BUFFER ===============================
	echo =============== CLEARING COLOR BUFFER ===============================
	echo =============== CLEARING COLOR BUFFER ===============================
	echo =============== CLEARING COLOR BUFFER ===============================
	echo =============== CLEARING COLOR BUFFER ===============================
	echo =============== CLEARING COLOR BUFFER ===============================
	echo =============== CLEARING COLOR BUFFER ===============================
	echo =============== CLEARING COLOR BUFFER ===============================
	echo =============== CLEARING COLOR BUFFER ===============================
	echo =============== CLEARING COLOR BUFFER ===============================
	echo =============== CLEARING COLOR BUFFER ===============================
	cls
srctolib:
	g++ -c src\main.cpp -o lib\main.o -w -fno-exceptions
micromodtolib:
	gcc -c -ansi -pedantic -Wall src\soundcore\w32player.c -o lib\micromod.o -w -fno-exceptions
libtobin:
	g++ lib\micromod.o lib\main.o -o bin\main.exe "lib\libgdi32.a"  -lwinmm -O -fno-exceptions
executebin:
	bin\main.exe