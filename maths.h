#ifndef MATHS_H
#define MATHS_H

#include "maths_types.h"

double
dotp2d(struct vec2d *, struct vec2d *);
double
dotp3d(struct vec3d *, struct vec3d *);

void
sum2d(struct vec2d *, struct vec2d *, struct vec2d *);
void
sum3d(struct vec3d *, struct vec3d *, struct vec3d *);

void
sub2d(struct vec2d *, struct vec2d *, struct vec2d *);
void
sub3d(struct vec3d *, struct vec3d *, struct vec3d *);

void
scalarmult2d(double, struct vec2d *, struct vec2d *);
void
scalarmult3d(double, struct vec3d *, struct vec3d *);

void
scalardiv2d(double, struct vec2d *, struct vec2d *);
void
scalardiv3d(double, struct vec3d *, struct vec3d *);

double
norm2d(struct vec2d *);
double
norm3d(struct vec3d *);

void
assign2d(struct vec2d *, struct vec2d *);
void
assign3d(struct vec3d *, struct vec3d *);

void
multmat2d(struct mat2d *, struct mat2d *, struct mat2d *);


#endif // MATHS_H
