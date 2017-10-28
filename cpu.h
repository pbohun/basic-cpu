// copyright 2017 Philip Bohun
#ifndef CPU_H
#define CPU_H

#include "types.h"
#include "instructions.h"
#include "flags.h"

void execute(cpu *c);
void fetch(cpu *c);

void *get_loc(cpu *c, u64 num) {
	if (num < 8) return &c->r[num];
	if (num >= 8) return &c->fr[num - 8];
}

cpu *new_cpu(u64 *memory, u64 mem_size) {
	cpu *c = malloc(sizeof(cpu));
	c->mem = memory;
	c->sp = mem_size - 1;
	c->max_mem = mem_size;
	c->pc = -1;
	c->inst = 0;
	return c;
}

void free_cpu(cpu *c) {
	free(c);
}

void run_cpu(cpu *c) {
	while (c->inst != HLT) {
		fetch(c);
		execute(c);
	}
}

void fetch(cpu *c) {
	c->pc++;
	c->inst = c->mem[c->pc] & FIRST_BYTE;
}

void execute(cpu *c) {
	switch (c->inst) {
		case CLF:
			clear_flags(c);
			break;
		case MOV:
			c->r[c->mem[c->pc+1]] = c->r[c->mem[c->pc+2]];
			c->pc += 2;
			break;
		case MOVF:
			c->fr[c->mem[c->pc+1]-8] = c->fr[c->mem[c->pc+2]-8];
			c->pc += 2;
			break;
		case STI:
			c->mem[c->mem[c->pc+1]] = c->r[c->mem[c->pc+2]];
			c->pc += 2;
			break;
		case STF:
			c->mem[c->mem[c->pc+1]] = (u64)c->fr[c->mem[c->pc+2]-8];
			c->pc += 2;
			break;
		case LDI:
			c->r[c->mem[c->pc+1]] = c->mem[c->mem[c->pc+2]];
			c->pc += 2;
			break;
		case LDF:
			c->fr[c->mem[c->pc+1]-8] = (f64)c->mem[c->mem[c->pc+2]];
			c->pc += 2;
			break;
		case LII:
			c->r[c->mem[c->pc+1]] = c->mem[c->pc+2];
			c->pc += 2;
			break;
		case LIF:
			c->fr[c->mem[c->pc+1]-8] = (f64)c->mem[c->pc+2];
			c->pc += 2;
			break;
		case PSH:
			c->mem[--c->sp] = c->r[c->mem[++c->pc]];
			break;
		case PSHF:
			c->mem[--c->sp] = (u64)c->fr[c->mem[++c->pc]-8];
			break;
		case POP:
			c->r[c->mem[++c->pc]] = c->mem[c->sp++];
			break;
		case POPF:
			c->fr[c->mem[++c->pc]-8] = (f64)c->mem[c->sp++];
			break;
		case ADD:
			c->r[c->mem[c->pc+1]] += c->r[c->mem[c->pc+2]];
			set_flags(c, c->r[c->mem[c->pc+1]]);
			c->pc += 2;
			break;
		case SUB:
			c->r[c->mem[c->pc+1]] -= c->r[c->mem[c->pc+2]];
			set_flags(c, c->r[c->mem[c->pc+1]]);
			c->pc += 2;
			break;
		case MUL:
			c->r[c->mem[c->pc+1]] *= c->r[c->mem[c->pc+2]];
			set_flags(c, c->r[c->mem[c->pc+1]]);
			c->pc += 2;
			break;
		case DIV:
			c->r[c->mem[c->pc+1]] /= c->r[c->mem[c->pc+2]];
			set_flags(c, c->r[c->mem[c->pc+1]]);
			c->pc += 2;
			break;
		case FADD:
			c->fr[c->mem[c->pc+1]-8] += c->fr[c->mem[c->pc+2]-8];
			fset_flags(c, c->fr[c->mem[c->pc+1]-8]);
			c->pc +=2;
			break;
		case FSUB:
			c->fr[c->mem[c->pc+1]-8] -= c->fr[c->mem[c->pc+2]-8];
			fset_flags(c, c->fr[c->mem[c->pc+1]-8]);
			c->pc +=2;
			break;
		case FMUL:
			c->fr[c->mem[c->pc+1]-8] *= c->fr[c->mem[c->pc+2]-8];
			fset_flags(c, c->fr[c->mem[c->pc+1]-8]);
			c->pc +=2;
			break;
		case FDIV:
			c->fr[c->mem[c->pc+1]-8] /= c->fr[c->mem[c->pc+2]-8];
			fset_flags(c, c->fr[c->mem[c->pc+1]-8]);
			c->pc +=2;
			break;
		case JLZ:
			if (c->ltz) c->pc = c->mem[++(c->pc)];
			else c->pc++;
			break;
		case JGZ:
			if (c->gtz) c->pc = c->mem[++(c->pc)];
			else c->pc++;
			break;
		case JEZ:
			if (c->zero) c->pc = c->mem[++(c->pc)];
			else c->pc++;
			break;
		case JNZ:
			if (!c->zero) c->pc = c->mem[++(c->pc)];
			else c->pc++;
			break;
		case JMP:
			c->pc = c->mem[++(c->pc)];
			break;
		case SHL:
			c->r[c->mem[c->pc+1]] <<= c->r[c->mem[c->pc+2]];
			c->pc += 2;
			break;
		case SHR:
			c->r[c->mem[c->pc+1]] >>= c->r[c->mem[c->pc+2]];
			c->pc += 2;
			break;
		case BAND:
			c->r[c->mem[c->pc+1]] &= c->r[c->mem[c->pc+2]];
			c->pc += 2;
			break;
		case BOR:
			c->r[c->mem[c->pc+1]] |= c->r[c->mem[c->pc+2]];
			c->pc += 2;
			break;
		case BNOT:
			c->r[c->mem[c->pc+1]] = ~c->r[c->mem[c->pc+1]];
			c->pc++;
			break;
		case BXOR:
			c->r[c->mem[c->pc+1]] ^= c->r[c->mem[c->pc+2]];
			c->pc += 2;
			break;
		case LAND:
			c->r[c->mem[c->pc+1]] = c->r[c->mem[c->pc+1]] && c->r[c->mem[c->pc+2]];
			c->pc += 2;
			break;
		case LOR:
			c->r[c->mem[c->pc+1]] = c->r[c->mem[c->pc+1]] || c->r[c->mem[c->pc+2]];
			c->pc += 2;
			break;
		case LNOT:
			c->r[c->mem[c->pc+1]] = !c->r[c->mem[c->pc+1]];
			c->pc++;
			break;
	}
}

#endif // CPU_H
