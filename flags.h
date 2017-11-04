// copyright 2017 Philip Bohun
#ifndef FLAGS_H 
#define FLAGS_H

void clear_flags(cpu *c) {
	c->zero = 0;
	c->ltz = 0;
	c->gtz = 0;
}

void set_flags(cpu *c, i64 a, i64 b) {
	i64 res = a - b;
	c->zero = (res == 0);
	c->ltz = (res < 0);
	c->gtz = (res > 0);
}

void fset_flags(cpu *c, f64 a, f64 b) {
	f64 res = a - b;
	c->zero = (res == 0);
	c->ltz = (res < 0);
	c->gtz = (res > 0);
}

#endif // FLAGS_H
