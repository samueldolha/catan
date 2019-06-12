define compilerFlags
g
pedantic
std=c11
Wall
Werror
Wextra
endef

executableDirectory ::= bin/
pathToExecutable ::= $(executableDirectory)catan.exe

.PHONY: all
all: $(pathToExecutable)

sourceFiles ::= $(shell ls src/*)
headerFiles ::= $(shell ls include/*)

ifeq ($(OS),Windows_NT)
	libraryFlags ::= -lglew32 -lglfw3 -lopengl32 -ltiff
else
	ifeq ($(shell uname -s),Darwin)
		libraryFlags ::= -framework OpenGL -lglew -lglfw -ltiff
	endif
endif

$(pathToExecutable): $(sourceFiles) $(headerFiles)
	if [ ! -d $(executableDirectory) ]; then mkdir -p $(executableDirectory); fi
	gcc -o $@ \
	$(sourceFiles) \
	$(addprefix -,$(compilerFlags)) \
	-Iinclude/ $(libraryFlags)

.PHONY: run
run: $(pathToExecutable)
	$^

.PHONY: clean
clean:
	if [ -d $(executableDirectory) ]; \
	then \
	rm $(pathToExecutable); \
	rmdir $(executableDirectory); \
	fi
