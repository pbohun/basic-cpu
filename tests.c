#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cpu.h"

void print_registers(cpu *c) {
	for (int i = 0; i < 7; i++) {
		printf("%llu,", c->r[i]);
	}
	printf("%llu\n", c->r[7]);
}

void print_float_registers(cpu *c) {
	for (int i = 0; i < 7; i++) {
		printf("%f,", c->fr[i]);
	}
	printf("%f\n", c->fr[7]);
}

void run_integer_tests();
void run_float_tests();
void run_bitwise_tests();
void run_logic_tests();
void run_jump_tests();

int main() {
	printf("Begin running tests\n");
	run_integer_tests();
	run_float_tests();
	run_bitwise_tests();
	run_logic_tests();
	run_jump_tests();
	printf("All tests passed\n");

	return 0;
}

void run_integer_tests() {
	printf("Running tests on integer instructions\n");

	i64 mem[] = {
		LII, R0, 1,
		LII, R1, 5,
		MOV, R2, R0,
		MUL, R0, R1,
		SUB, R1, R2,
		CMPI, R1, 0,
		JNZ, 8,
		PSH, R0,
		POP, R7,
		LII, R6, 2,
		DIV, R7, R6,
		STI, 42, R7,
		LDI, R5, 42,
		ADD, R7, R2,
		HLT,
		0, 0, 0,
		0, 0, 0
	};

	cpu *c = new_cpu(mem, 46);
	run_cpu(c);
	print_registers(c);
	assert(c->r[0] == 120);
	assert(c->r[7] == 61);
	assert(c->mem[42] == 60);
	assert(c->r[5] == 60);

	free_cpu(c);
	printf("All integer tests passed\n");
}

void run_float_tests() {
	printf("Running tests on float instructions\n");

	i64 mem[] = {
		LIF, F0, 1.0,
		LIF, F1, 5.0,
		MOVF, F2, F0,
		MULF, F0, F1,
		SUBF, F1, F2,
		CMPFI, F1, 0,
		JNZ, 8,
		PSHF, F0,
		POPF, F7,
		LIF, F6, 2.0,
		DIVF, F7, F6,
		STF, 42, F7, // 27, 28, 29
		LDF, F5, 42, // 30, 31, 32
		ADDF, F7, F2,
		HLT,
		0, 0, 0,
		0, 0, 0
	};

	cpu *c = new_cpu(mem, 46);
	run_cpu(c);
	print_float_registers(c);
	assert(c->fr[0] == 120.0);
	assert(c->fr[7] == 61.0);
	assert((f64)c->mem[42] == 60.0);
	assert(c->fr[5] == 60.0);

	free_cpu(c);
	printf("All integer tests passed\n");
}

void run_bitwise_tests() {
	printf("Running tests on bitwise instructions\n");

	i64 mem[] = {
		LII, R0, 5,
		LII, R1, 3,
		LII, R2, 6,
		BOR, R0, R1,
		MOV, R3, R0,
		SUB, R3, R2,
		BXOR, R1, R2,
		LII, R4, 7,
		BNOT, R4,
		LII, R5, 5,
		LII, R6, 3,
		BAND, R5, R6,
		LII, R7, 1,
		SHL, R7, 2,
		SHR, R7, 1,
		HLT
	};

	cpu *c = new_cpu(mem, 45);
	run_cpu(c);
	print_registers(c);

	assert(c->r[0] == 7);
	assert(c->r[1] == 5);
	assert(c->r[4] == ~(i64)7);
	assert(c->r[5] == 1);
	assert(c->r[7] == 2);

	free_cpu(c);
	printf("All bitwise tests passed\n");
}

void run_logic_tests() {
	printf("Running tests on logic instructions\n");

	i64 mem[] = {
		LII, R0, 1,
		LII, R1, 0,
		LII, R2, 1,
		LII, R3, 1,
		LAND, R0, R1,
		LOR, R1, R2,
		LNOT, R3,
		HLT
	};

	cpu *c = new_cpu(mem, 21);
	run_cpu(c);
	print_registers(c);
	
	assert(c->r[0] == 0);
	assert(c->r[1] == 1);
	assert(c->r[3] == 0);

	free_cpu(c);
	printf("All logic tests passed\n");
}

void run_jump_tests() {
	printf("Running tests on jump instructions\n");

	i64 mem[] = {
		LII, R0, 0,
		LII, R1, 1,
		INC, R1,
		DEC, R1,
		LII, R2, 2,
		LII, R3, 1,
		CMP, R0, R1,
		JLZ, 30,
		CMP, R1, R3,
		JEZ, 32,
		CMP, R1, R0,
		JGZ, 34,
		JMP, 20,
		JMP, 25,
		HLT
	};

	cpu *c = new_cpu(mem, 34);
	run_cpu(c);
	print_registers(c);

	free_cpu(c);
	printf("All jump tests passed\n");
}
