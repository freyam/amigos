![](/src/header.png)

## Amigos - A Rich Social Media Experience

Amigos is an clever Friend Recommendation Application that inventively suggests friends to Users. The User Database is stored in an array of polished AVL (Adelson-Velsky and Landis) Trees.

### Motivation

### File Structure

```
.
├── amigos
├── amigos.c
├── amigos.h
├── avl.c
├── data
│   ├── CustomUserDatabase.csv
│   └── RandomUserDatabase.csv
├── dump.c
├── graph
│   ├── friendship-network.png
│   └── graphviz.dot
├── heap.c
├── interface.c
├── lab.c
├── main.c
├── Makefile
├── queue.c
├── README.md
├── redblack.c
├── src
│   ├── header.png
│   ├── header-square.png
│   └── project.pdf
└── todo.md
```

### Setup

- Install [Compiler (gcc 10.2.0) and Debuggger (gdb 9.2)](https://gcc.gnu.org/)
  - `sudo apt-get install build-essential`
- Install [Graphviz (Graph Visualization Software)](https://graphviz.org/)
  - `sudo apt-get install graphviz`
- Download the Source Code of Amigos ([Direct Link](https://github.com/freyam/amigos/archive/refs/heads/main.zip))

### Instructions

- I have a `Makefile` which allows me to compile/run/test/debug/clean/etc. the Amigos Application using simple short commands in the terminal (tested on Linux).
  - `> make` to compile and run the Amigos App.
  - `> make com` to only compile the Amigos App.
  - `> make run` to run a successfully compiled Amigos App.
  - `> make dbg` to compile the Amigos App with the `-g` flag to run `gdb` for debugging purposes.
  - `> make test` to test new features before adding to the main branch.
  - `> make import` to import Random User Data created by an online API (Mockaroo).
  - `> make clean` to clean the residual files and prepare a consistent file structure.
