# bfc

brainfuck interpreter and repl with some optimizations implemented in.

## building

bfc uses [premake5](https://premake.github.io/) to generate the required build files.

```
main:bfc (master) premake gmake # build files for gnu make
main:bfc (master) bear -- make  # using bear to generate the compile_commands.json file for clangd
main:bfc (master) ./bin/debug/bfc --help
usage: ./bfc [path] [-d] [-h]

optional arguments:
    -d, --debug     run the interpreter in debug mode
    -h, --help      print this text
```

## images

![mandelbrot](https://i.imgur.com/5KMSYy2.png)

![repl](https://i.imgur.com/xHvyp4R.png)