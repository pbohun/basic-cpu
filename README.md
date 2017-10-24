# Basic-CPU
This is a very simple, compact, virtual cpu written in c.
It's a project for fun and learning, so feel free to play around with it to try out different ideas. The code hasn't been fully tested, so don't be surprised if you find some bugs. Maybe I'll get around to writing a full test suite.

## Prerequisites
You'll need a c compiler that compiles to the c99 standard, and git is recommended.

## Get basic-cpu
Use the following command to get the repository:

`git clone https://github.com/pbohun/basic-cpu.git`

## Usage
Include the `cpu.h` file in your program and you're ready to go. You have to use the `new_cpu()` function to create a new cpu and `free_cpu()` function at the end. Note that in the `example.c` program we don't use the `free_cpu()` function because we allocated our memory on the stack. In reality, you should always allocate your memory for your cpu on the heap. 

## Trying the example
To compile the example program use the following command:

`gcc -std=c99 -o example example.c`

The example program calculates 5 factorial and stores the answer in the register 0 (R0).

## Writing Programs
Note that this is just a cpu. There are no mechanisms for input, output, monitors, long term storage, etc. You have to create memory for the cpu and fill it with machine code. An example of this is found in the `example.c` file.

Everything in the cpu is 64 bit, defined as u64 and f64 for 64 bit floating point. Most instructions involve registers. The registers get combined into the instruction to create more compact bytecode. Here's an example of a MOV instruction:

`MOV | (R0 << 8) | (R1 << 16)`

## Instruction format
The format for writing instructions (in general) is:

`<instruction> <destination-register> <source-register>`

In the MOV instruction above, the value from register 1 is moved into register 0.

The format of the instructions are as follows:

00000sdi

The first 5 bytes are always 0. The 6th byte is the source register number, the 7th byte is the destination register number, and the 8th byte is the instruction number. This is why we use bit shifting and or-ing on our register numbers.

The only time we don't bit shift is when referring to a memory location or an immediate value. Here is an example of loading an immediate value 5 into register 0:

`LDI | (R0 << 8), 5`
