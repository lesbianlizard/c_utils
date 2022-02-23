#ifndef MATHS_H
#define MATHS_H

#include <stdbool.h>

#include "maths_types.h"

double
dotp2d(struct vec2d *, struct vec2d *);
double
dotp3d(struct vec3d *, struct vec3d *);
double
dotp4d(struct vec4d *, struct vec4d *);

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
void
multmat3d(struct mat3d *, struct mat3d *, struct mat3d *);
void
multmat4d(struct mat4d *, struct mat4d *, struct mat4d *);

void
transmat2d(struct mat2d *, struct mat2d *);
void
transmat3d(struct mat3d *, struct mat3d *);
void
transmat4d(struct mat4d *, struct mat4d *);

void
assignmat4d(struct mat4d *, struct mat4d *);

void
initmat4d(struct mat4d *, bool);

void
print_mat4d(struct mat4d *, char *);


#endif // MATHS_H
