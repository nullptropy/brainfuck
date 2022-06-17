project('brainfuck', 'c', version: '0.1.0')

inc = include_directories('include')
src = []

foreach s: ['compiler.c', 'linenoise.c', 'main.c', 'opcode.c', 'repl.c', 'utils.c', 'vm.c']
  src += 'src' / s
endforeach

exe = executable(
  'brainfuck', src, include_directories: inc)
