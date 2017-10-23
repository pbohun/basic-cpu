// copyright 2017 Philip Bohun
#ifndef ALU_H
#define ALU_H

void clear_flags(cpu *c) {
	c->zero = 0;
	c->ltz = 0;
	c->gtz = 0;
}

void set_flags(cpu *c, u64 *dest) {
	c->zero = (*dest == 0);
	c->ltz = (*dest < 0);
	c->gtz = (*dest > 0);
}

void fset_flags(cpu *c, f64 *dest) {
	c->zero = (*dest == 0);
	c->ltz = (*dest < 0);
	c->gtz = (*dest > 0);
}

u64 twos_complement(u64 n) {
	return -(u64)n;
}

void add(cpu *c, u64 *dest, u64 *src) {
	*dest += *src;
	set_flags(c, dest);
}

void fadd(cpu *c, f64 *dest, f64 *src) {
	*dest += *src;
	fset_flags(c, dest);
}

void sub(cpu *c, u64 *dest, u64 *src) {
	*dest += twos_complement(*src);
	set_flags(c, dest);
}

void fsub(cpu *c, f64 *dest, f64 *src) {
	*dest -= *src;
	fset_flags(c, dest);
}

void mul(cpu *c, u64 *dest, u64 *src) {
	*dest *= *src;
	set_flags(c, dest);
}

void fmul(cpu *c, f64 *dest, f64 *src) {
	*dest *= *src;
	fset_flags(c, dest);
}

void idiv(cpu *c, u64 *dest, u64 *src) {
	*dest /= *src;
	set_flags(c, dest);
}

void fdiv(cpu *c, f64 *dest, f64 *src) {
	*dest /= *src;
	fset_flags(c, dest);
}

#endif // ALU_H
