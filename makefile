.PHONY: run
run: catan
	./catan.exe

catan: catan.c
	gcc -Wall -Werror catan.c -o catan.exe

.PHONY: clean
clean:
	rm catan.exe
