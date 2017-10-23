// copyright 2017 Philip Bohun
#ifndef CPU_H
#define CPU_H

#include "types.h"
#include "instructions.h"
#include "alu-math.h"

void execute(cpu *c);
void decode(cpu *c);
void fetch(cpu *c);

void *get_loc(cpu *c, u64 num) {
	if (num < 8) return &c->r[num];
	if (num >= 8) return &c->fr[num - 8];
}

cpu *new_cpu(u64 *memory) {
	cpu *c = malloc(sizeof(cpu));
	c->mem = memory;
}

void free_cpu(cpu *c) {
	free(c->mem);
	free(c);
}

void run(cpu *c) {
	while (c->inst != HLT) {
		decode(c);
		execute(c);
		fetch(c);
	}
}

void fetch(cpu *c) {
	c->pc++;
}

void decode(cpu *c) {
	c->inst = c->mem[c->pc] & FIRST_BYTE;
	c->dest = (c->mem[c->pc] >> 8) & FIRST_BYTE;
	c->src = (c->mem[c->pc] >> 16) & FIRST_BYTE;
}

void execute(cpu *c) {
	switch (c->inst) {
	u64 *id;
	u64 *is;
	u64 *fd;
	u64 *fs;
	case CLF:
		clear_flags(c);
		break;
	case MOV:
		if (c->dest < 8) {
			*(u64*)get_loc(c, c->dest) = *(u64*)get_loc(c, c->src);
		} else {
			*(f64*)get_loc(c, c->dest) = *(f64*)get_loc(c, c->src);
		}
		break;
	case MVS:
		c->mem[c->dest] = *(u64*)get_loc(c, c->src);
		break;
	case MVL:
		*(u64*)get_loc(c, c->dest) = c->mem[c->src];
		break;
	case LDI:
		if (c->dest < 8) *(u64*)get_loc(c, c->dest) = c->mem[++(c->pc)];
		else *(f64*)get_loc(c, c->dest) = (f64)c->mem[++(c->pc)];
		break;
	case PSH:
		c->mem[c->sp--] = *(u64*)get_loc(c, c->dest);
		break;
	case POP:
		if (c->dest < 8) *(u64*)get_loc(c, c->dest) = c->mem[c->sp++];
		else *(f64*)get_loc(c, c->dest) = c->mem[c->sp++];
		break;
	case ADD:
		add(c, get_loc(c, c->dest), get_loc(c, c->src));
		break;
	case SUB:
		sub(c, get_loc(c, c->dest), get_loc(c, c->src));
		break;
	case MUL:
		mul(c, get_loc(c, c->dest), get_loc(c, c->src));
		break;
	case DIV:
		idiv(c, get_loc(c, c->dest), get_loc(c, c->src));
		break;
	case FADD:
		fadd(c, get_loc(c, c->dest), get_loc(c, c->src));
		break;
	case FSUB:
		fsub(c, get_loc(c, c->dest), get_loc(c, c->src));
		break;
	case FMUL:
		fmul(c, get_loc(c, c->dest), get_loc(c, c->src));
		break;
	case FDIV:
		fdiv(c, get_loc(c, c->dest), get_loc(c, c->src));
		break;
	case JLZ:
		if (c->ltz) c->pc = c->mem[++(c->pc)];
		else ++(c->pc);
		break;
	case JGZ:
		if (c->gtz) c->pc = c->mem[++(c->pc)];
		else ++(c->pc);
		break;
	case JEZ:
		if (c->zero) c->pc = c->mem[++(c->pc)];
		else ++(c->pc);
		break;
	case JNZ:
		if (!c->zero) c->pc = c->mem[++(c->pc)];
		else ++(c->pc);
		break;
	case JMP:
		c->pc = c->mem[++(c->pc)];
		break;
	case SHL:
		*(u64*)get_loc(c, c->dest) <<= c->mem[++(c->pc)];
		break;
	case SHR:
		*(u64*)get_loc(c, c->dest) >>= c->mem[++(c->pc)]; 
		break;
	case BAND:
		*(u64*)get_loc(c, c->dest) &= *(u64*)get_loc(c, c->src);
		break;
	case BOR:
		*(u64*)get_loc(c, c->dest) |= *(u64*)get_loc(c, c->src);
		break;
	case BNOT:
		*(u64*)get_loc(c, c->dest) = ~(*(u64*)get_loc(c, c->dest));
		break;
	case BXOR:
		*(u64*)get_loc(c, c->dest) ^= *(u64*)get_loc(c, c->src);
		break;
	case LAND:
		*(u64*)get_loc(c, c->dest) = *(u64*)get_loc(c, c->dest) && *(u64*)get_loc(c, c->src);
		break;
	case LOR:
		*(u64*)get_loc(c, c->dest) = *(u64*)get_loc(c, c->dest) || *(u64*)get_loc(c, c->src);
		break;
	case LNOT:
		*(u64*)get_loc(c, c->dest) = !(*(u64*)get_loc(c, c->dest));
		break;
	}
}

#endif // CPU_H
