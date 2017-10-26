// copyright 2017 Philip Bohun
#ifndef TYPES_H
#define TYPES_H

#define FIRST_BYTE 0x00000000000000FF
#define byte unsigned char
#define u64 unsigned long
#define i64 long
#define f64 double

enum registers {
	R0, R1, R2, R3, R4, R5, R6, R7,
	F0, F1, F2, F3, F4, F5, F6, F7,
	NUM_REGISTERS
};

typedef struct {
	u64 *mem;
	u64 max_mem;

	// registers
	u64 pc;
	u64 sp;
	u64 r[8];
	f64 fr[8];

	// instruction parts
	u64 inst;
	u64 dest;
	u64 src;

	// buses
	u64 busA;
	u64 busB;

	// flags
	u64 zero;
	u64 ltz;
	u64 gtz;
} cpu;

#endif // TYPES_H
