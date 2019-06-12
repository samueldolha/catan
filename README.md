# Catan

## Introduction

This application automates the task of randomizing the hexes and number tokens
for a variable set-up game of [Catan](https://www.catan.com/game/catan). Tested
on Windows 7 64-bit running [MSYS2](https://www.msys2.org/) and macOS Mojave
10.14.5 with [Homebrew](https://brew.sh/).

## Dependencies

- TIFFs of the hexes and number tokens (e.g., those on the
[example-textures](https://github.com/samueldolha/catan/tree/example-textures)
branch);
- [GNU Make 4.2.1](https://www.gnu.org/software/make/);
- [GLEW 2.1.0](http://glew.sourceforge.net/);
- [GLFW 3.3](https://www.glfw.org/);
- [OpenGL 4.1](https://www.opengl.org/); and
- [LibTIFF 3.6.1](http://www.libtiff.org/).

## Usage

- `make all` (default) compiles the application as `./bin/catan.exe`;
- `make run` compiles and executes the application; and
- `make clean` resets the directory to its original state.

# License

[MIT](./LICENSE)
