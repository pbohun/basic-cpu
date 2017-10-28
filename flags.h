// copyright 2017 Philip Bohun
#ifndef FLAGS_H 
#define FLAGS_H

void clear_flags(cpu *c) {
	c->zero = 0;
	c->ltz = 0;
	c->gtz = 0;
}

void set_flags(cpu *c, u64 dest) {
	c->zero = (dest == 0);
	c->ltz = (dest < 0);
	c->gtz = (dest > 0);
}

void fset_flags(cpu *c, f64 dest) {
	c->zero = (dest == 0);
	c->ltz = (dest < 0);
	c->gtz = (dest > 0);
}

#endif // FLAGS_H
