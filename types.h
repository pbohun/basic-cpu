// copyright 2017 Philip Bohun
#ifndef TYPES_H
#define TYPES_H

#define FIRST_BYTE 0x00000000000000FF
#define byte unsigned char
#define u64 unsigned long long
#define i64 long long
#define f64 double

enum registers {
	R0, R1, R2, R3, R4, R5, R6, R7,
	F0, F1, F2, F3, F4, F5, F6, F7,
	NUM_REGISTERS
};

typedef struct {
	i64 *mem;
	i64 max_mem;

	// registers
	i64 pc;
	i64 sp;
	i64 r[8];
	f64 fr[8];

	// instruction parts
	i64 inst;
	i64 dest;
	i64 src;

	// flags
	i64 zero;
	i64 ltz;
	i64 gtz;
} cpu;

#endif // TYPES_H
