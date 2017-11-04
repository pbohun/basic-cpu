// copyright 2017 Philip Bohun
// To compile use the following command:
// gcc -std=c99 -o example example.c
#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"

void print_list(i64 *lst, int size) {
	for (int i = 0; i < size - 1; i++) {
		printf("%llu,", lst[i]);
	}
	printf("%llu\n", lst[size-1]);
}

void print_registers(cpu *c) {
	for (int i = 0; i < 7; i++) {
		printf("%llu,", c->r[i]);
	}
	printf("%llu\n", c->r[7]);
}

void print_fregisters(cpu *c) {
	for (int i = 0; i < 7; i++) {
		printf("%f,", c->fr[i]);
	}
	printf("%f\n", c->fr[7]);
}

int main() {
	i64 b[] = {
		LII, R0, 1,
		LII, R1, 5,
		LII, R2, 1,
		MUL, R0, R1,
		SUB, R1, R2,
		JNZ, 8,
		HLT 
	};

	printf("instructions:\n");
	print_list(b, 18);

	// create new cpu with the given i64 array for memory
	cpu *c = new_cpu(b, 18);

	run_cpu(c);

	printf("registers:\n");
	print_registers(c);
	printf("floating registers:\n");
	print_fregisters(c);

	free_cpu(c);

	return 0;
}
