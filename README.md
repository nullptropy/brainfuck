# bfc

brainfuck interpreter and repl with some optimizations implemented in: for the time being it can detect clear loops, combine repeating operations (-><+) and it can link loops at compile time.

## building

bfc uses the [meson](https://github.com/mesonbuild/meson) build system.

```sh
$ meson setup build
$ meson configure --buildtype release build
$ meson compile -C build
$ ./build/brainfuck --help
usage: ./bfc [path] [-d] [-h]

optional arguments:
    -d, --debug     run the interpreter in debug mode
    -h, --help      print this text
```
