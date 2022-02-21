#ifndef MATHS_H
#define MATHS_H

#include "maths_types.h"

double
dotp2d(struct vec2d *, struct vec2d *);

void
sum2d(struct vec2d *, struct vec2d *, struct vec2d *);

void
sub2d(struct vec2d *, struct vec2d *, struct vec2d *);

void
scalarmult2d(double, struct vec2d *, struct vec2d *);

void
scalardiv2d(double, struct vec2d *, struct vec2d *);

double
norm2d(struct vec2d *);

void
assign2d(struct vec2d *, struct vec2d *);

#endif // MATHS_H
