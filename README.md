# bfc

brainfuck interpreter and repl with some simple optimizations implemented in.

## building

bfc uses [premake5](https://premake.github.io/) to generate the required build files.

```
sh-5.1$ premake5 --cc=clang gmake # build files for gnu make
Building configurations...
Running action 'gmake'...
Generated Makefile...
Generated build/Makefile...
Done (28ms).
sh-5.1$
sh-5.1$ bear -- make config=debug # using bear to generate compile_commands.json for clangd
==== Building bfc (debug) ====
Creating obj/release
main.c
compiler.c
opcode.c
vm.c
Creating release
Linking bfc
sh-5.1$
sh-5.1$ ./build/debug/bfc totally valid args
usage: ./build/debug/bfc [path]
sh-5.1$
```

## images

![mandelbrot](https://i.imgur.com/2CuTF1p.png)

![repl](https://i.imgur.com/4a7AW9C.png)