# mybf

Optimizing brainfuck interpreter written in C++17.

## Building

Just run `make` inside repo root. It uses `clang++` as a compiler because it gives a 5% speed boost on heavy workloads.
(`Makefile` is a litte mess because it's my first one, PRs are welcome!)

## Running

`./bf_interpreter <input file>`
