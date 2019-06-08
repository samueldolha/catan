define files
execute-program
main
render-program
render-window
run-application
endef

define flags
g
pedantic
std=c11
Wall
Werror
Wextra
endef

define libraries
glew32
glfw3
opengl32
endef

executableDirectory ::= bin/
pathToExecutable ::= $(executableDirectory)catan.exe

.PHONY: all
all: $(pathToExecutable)

formatFiles = $(addprefix $(1),$(addsuffix $(2),$(3)))
sourceFiles ::= $(call formatFiles,src/,.c,$(files))
headerFiles ::= $(call formatFiles,include/,.h,$(filter-out main,$(files)))

$(pathToExecutable): $(sourceFiles) $(headerFiles)
	if [ ! -d $(executableDirectory) ]; then mkdir -p $(executableDirectory); fi
	gcc -o $@ \
	$(sourceFiles) \
	$(addprefix -,$(flags)) \
	-Iinclude/ $(addprefix -l,$(libraries))

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
