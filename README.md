![](/src/header.png)

## Amigos App - A Rich Social Media Experience

Amigos is a clever Friend Recommendation Application that inventively suggests friends to Users. The User Database is stored in an array of polished AVL (Adelson-Velsky and Landis) Trees. We are not just any other Social Media. Our remarkable **CompatiFriend** algorithm is using excellent computation to deliver accurate results.

### Motivation

Everyone needs a good friend who stands next to them during their good and challenging times. We understand this and work towards making everyone's social lives better. At Amigos, we believe in the positive influence a good friend can have in one's life. Our sole motivation is to unite similar-minded people across the world!

<p align="center">
  <img src="src/gifs/nondoggo-1.gif">
</p>

### Core Functions

- `checkFriendshipUID()`
- `checkFriendshipName()`
- `recommendFriendsNewUser()`
- `recommendFriendsExisitngUser()`

### Analysis of the Data Structures and Algorithms Used

The Detailed Analysis of our choices can be found in our [Project Report](https://github.com/freyam/amigos/blob/main/src/report.pdf).

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

- Install the necessary Build Setup (`gcc 10.2` and `gdb 9.2`)
  - `sudo apt-get install build-essential`
- Install [Graphviz](https://graphviz.org/) (Graph Visualization Software)
  - `sudo apt-get install graphviz`

### Instructions

- Download the source code of the Amigos App from GitHub.
- I have a `Makefile` which allows me to compile/run/test/debug/clean/etc. the Amigos Application using simple short commands in the terminal (tested on Linux).
  - `> make` to compile and run the Amigos App.
  - `> make com` to only compile the Amigos App.
  - `> make run` to run a successfully compiled Amigos App.
  - `> make dbg` to compile the Amigos App with the `-g` flag to run `gdb` for debugging.
  - `> make test` to test new features before adding to the main branch.
  - `> make import` to import Random User Data created by an online API (Mockaroo).
  - `> make clean` to clean the residual files and prepare a consistent file structure.

### User Interface

![](/src/interface/menus.png)
![](/src/interface/graph.png)

### Some Happy Faces

We have helped many users find their true friends.

<a align="center">
  <img src="src/gifs/nondoggo-2.gif">
  <img src="src/gifs/nondoggo-3.gif">
</a>

<a align="center">
  <img src="src/gifs/doggo-1.gif">
  <img src="src/gifs/doggo-2.gif">
</a>

<br>
<br>

_This Application was developed as part of the Final Project of the Data Structures and Algorithms Course taught by Sujit Gujar and Ravi Kiran S at IIIT Hyderabad._
_Special thanks to Dixit Garg for helping us._
