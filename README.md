# Basic-CPU
This is a very simple, compact, virtual cpu written in c.
It's a project for fun and learning, so feel free to play around with it to try out different ideas. Don't be surprised if you find some bugs. 

You can find a video walkthrough of the cpu here:

https://www.youtube.com/watch?v=cfPDeso3XwI

## Prerequisites
You'll need a c compiler that compiles to the c99 standard, and git is recommended.

## Get basic-cpu
Use the following command to get the repository:

`git clone https://github.com/pbohun/basic-cpu.git`

## Usage
Include the `cpu.h` file in your program and you're ready to go. You have to use the `new_cpu()` function to create a new cpu and `free_cpu()` function at the end.  

## Runing the tests
To compile and run the tests use the following commands:

`gcc -std=c99 -o tests tests.c`  
`./tests`

## Trying the example
To compile the example program use the following command:

`gcc -std=c99 -o example example.c`

The example program calculates 5 factorial and stores the answer in the register 0 (R0).

## Writing Programs
Note that this is just a cpu. There are no mechanisms for input, output, monitors, long term storage, etc. You have to create memory for the cpu and fill it with machine code. An example of this is found in the `example.c` file.

Everything in the cpu is 64 bit, defined as u64 and f64 for 64 bit floating point. Most instructions involve registers. Here's an example of what a move instruction would look like in an array of memory. Note that it's designed to look a lot like assembly language. 

`MOV, R0, R1`

Take a look at the `example.c` file and the `tests.c` file to see how to use the `cpu.h` library.
