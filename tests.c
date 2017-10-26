#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cpu.h"

#define MAX_MEM 100

void print_registers(cpu *c) {
	for (int i = 0; i < 7; i++) {
		printf("%lu,", c->r[i]);
	}
	printf("%lu\n", c->r[7]);
}

void print_float_registers(cpu *c) {
	for (int i = 0; i < 7; i++) {
		printf("%f,", c->fr[i]);
	}
	printf("%f\n", c->fr[7]);
}

void run_integer_tests();
void run_float_tests();
// TODO: create tests for bitwise and logical operations

void main() {
	run_integer_tests();
	run_float_tests();
	printf("All tests passed\n");
}

void run_integer_tests() {
	printf("Running tests on integer instructions\n");
	u64 *mem = malloc(sizeof(u64) * MAX_MEM);

	// calc factorial of 5
	mem[0] = LDI | (R0 << 8);
	mem[1] = 1;
	mem[2] = LDI | (R1 << 8);
	mem[3] = 5;
	mem[4] = MOV | (R2 << 8) | (R0 << 16);
	mem[5] = MUL | (R0 << 8) | (R1 << 16);
	mem[6] = SUB | (R1 << 8) | (R2 << 16);
	mem[7] = JNZ;
	mem[8] = 4;
	// push and pop
	mem[9] = PSH | (R0 << 8);
	mem[10] = POP | (R7 << 8);
	// divide R7 by 2
	mem[11] = LDI | (R6 << 8);
	mem[12] = 2;
	mem[13] = DIV | (R7 << 8) | (R6 << 16);
	// mov store and load
	mem[14] = MVS;
	mem[15] = 50;
	mem[16] = R7;
	mem[17] = MVL;
	mem[18] = R5;
	mem[19] = 50;
	// add 1 to R7
	mem[20] = ADD | (R7 << 8) | (R2 << 16);
	mem[21] = HLT;
	
	cpu *c = new_cpu(mem, MAX_MEM);
	run_cpu(c);
	print_registers(c);
	printf("mem50:%lu\n", c->mem[50]);
	assert(c->r[0] == 120);
	assert(c->r[7] == 61);
	assert(c->mem[50] == 60);
	assert(c->r[5] == 60);

	free_cpu(c);
	free(mem);

	printf("All integer tests passed\n");
}

void run_float_tests() {
	printf("Running tests on floating point instructions\n");
	u64 *mem = malloc(sizeof(u64) * MAX_MEM);

	printf("float r0: %d\n", F0);

	// calc factorial of 5
	mem[0] = LDI | (F0 << 8);
	mem[1] = 1.0;
	mem[2] = LDI | (F1 << 8);
	mem[3] = 5.0;
	mem[4] = MOV | (F2 << 8) | (F0 << 16);
	mem[5] = FMUL | (F0 << 8) | (F1 << 16);
	mem[6] = FSUB | (F1 << 8) | (F2 << 16);
	mem[7] = JNZ;
	mem[8] = 4;
	// push and pop
	mem[9] = PSH | (F0 << 8);
	mem[10] = POP | (F7 << 8);
	// divide F7 by 2
	mem[11] = LDI | (F6 << 8);
	mem[12] = 2.0;
	mem[13] = FDIV | (F7 << 8) | (F6 << 16);
	// mov store and load
	mem[14] = MVS;
	mem[15] = 50;
	mem[16] = F7;
	mem[17] = MVL;
	mem[18] = F5;
	mem[19] = 50;
	// add 1 to F7
	mem[20] = FADD | (F7 << 8) | (F2 << 16);
	mem[21] = HLT;
	
	cpu *c = new_cpu(mem, MAX_MEM);
	printf("new cpu created\n");
	run_cpu(c);
	print_registers(c);
	print_float_registers(c);
	printf("mem50:%lu\n", c->mem[50]);
	assert(c->fr[0] == 120);
	assert(c->fr[7] == 61);
	assert(c->mem[50] == 60);
	assert(c->fr[5] == 60);

	free_cpu(c);
	free(mem);

	printf("All floating point tests passed\n");
}
