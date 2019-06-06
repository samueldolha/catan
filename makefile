.PHONY: run
run: catan
	./catan.exe

catan:
	gcc -Wall -Werror catan.c -o catan.exe
