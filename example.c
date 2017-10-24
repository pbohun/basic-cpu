// copyright 2017 Philip Bohun
// To compile use the following command:
// gcc -std=c99 -o example example.c
#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"

void print_list(u64 *lst, int size) {
	for (int i = 0; i < size - 1; i++) {
		printf("%lu,", lst[i]);
	}
	printf("%lu\n", lst[size-1]);
}

void print_registers(cpu *c) {
	for (int i = 0; i < 7; i++) {
		printf("%lu,", c->r[i]);
	}
	printf("%lu\n", c->r[7]);
}

void print_fregisters(cpu *c) {
	for (int i = 0; i < 7; i++) {
		printf("%f,", c->fr[i]);
	}
	printf("%f\n", c->fr[7]);
}

void main() {

	u64 b[] = {
		LDI | (R0 << 8), 1, 		// load 1 into register 0
		LDI | (R1 << 8), 5,		// load 5 into register 1
		LDI | (R2 << 8), 1,		// load 1 into register 2
		MUL | (R0 << 8) | (R1 << 16),	// multiply R0 and R1, store in R0
		SUB | (R1 << 8) | (R2 << 16),	// subtract R2 from R1
		JNZ, 5,				// jump to address 5 if not zero
		HLT				// halt
	};
	printf("instructions:\n");
	print_list(b, 11);

	// create new cpu with the given u64 array for memory
	cpu *c = new_cpu(b);

	run(c);

	printf("registers:\n");
	print_registers(c);
	printf("floating registers:\n");
	print_fregisters(c);

	// normally, you'd call free_cpu(c) here, but since we allocated 
	// b on the stack we can't call it here as it would call a 
	// double free error. Use malloc in "real life"!
}
