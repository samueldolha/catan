define sourceFiles
generate-island
generate-vertex-arrays
load-program
load-textures
main
render-program
render-window
run-application
endef

define headerFiles
generate-island
generate-vertex-arrays
load-program
load-textures
polygon
polygon-count
render-program
render-window
run-application
texture
texture-count
three-dimensional-vector
triangle-index
two-dimensional-vector
vertex
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
formattedSourceFiles ::= $(call formatFiles,src/,.c,$(sourceFiles))
formattedHeaderFiles ::= $(call formatFiles,include/,.h,$(headerFiles))

ifeq ($(OS),Windows_NT)
	libraryFlags ::= -lglew32 -lglfw3 -lopengl32 -ltiff
else
	ifeq ($(shell uname -s),Darwin)
		libraryFlags ::= -framework OpenGL -lglew -lglfw -ltiff
	endif
endif

$(pathToExecutable): $(formattedSourceFiles) $(formattedHeaderFiles)
	if [ ! -d $(executableDirectory) ]; then mkdir -p $(executableDirectory); fi
	gcc -o $@ \
	$(formattedSourceFiles) \
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
