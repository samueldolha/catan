define files
execute-program
main
render-program
render-window
run-application
endef

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

formatFiles = $(addprefix $(1),$(addsuffix $(2),$(3)))
sourceFiles ::= $(call formatFiles,src/,.c,$(files))
headerFiles ::= $(call formatFiles,include/,.h,$(filter-out main,$(files)))

ifeq ($(OS),Windows_NT)
	libraryFlags ::= -lglew32 -lglfw3 -lopengl32
else
	ifeq ($(shell uname -s),Darwin)
		libraryFlags ::= -framework OpenGL -lglew -lglfw
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
