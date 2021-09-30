# bfc

brainfuck interpreter and repl with some optimizations implemented in.

## building

bfc uses [premake5](https://premake.github.io/) to generate the required build files.

```
main:bfc (master) premake gmake
Building configurations...
Running action 'gmake'...
Generated Makefile...
Generated bin/Makefile...
Done (82ms).
main:bfc (master) bear -- make
==== Building bfc (debug) ====
Creating obj/debug
main.c
compiler.c
linenoise.c
opcode.c
repl.c
utils.c
vm.c
Creating debug
Linking bfc
main:bfc (master) ./bin/debug/bfc --help
usage: ./bfc [path] [-d] [-h]
```

## images

![mandelbrot](https://i.imgur.com/5KMSYy2.png)

![repl](https://i.imgur.com/dy3cQel.png)