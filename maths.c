#include <math.h>

#include "maths.h"

double
dotp2d(struct vec2d *a, struct vec2d *b)
{
  return a->x * b->x
       + a->y * b->y;
}

double
dotp3d(struct vec3d *a, struct vec3d *b)
{
  return a->x * b->x
       + a->y * b->y
       + a->z * b->z;
}

void
sum2d(struct vec2d *a, struct vec2d *b, struct vec2d *dst)
{
  dst->x = a->x + b->x;
  dst->y = a->y + b->y;
}

void
sum3d(struct vec3d *a, struct vec3d *b, struct vec3d *dst)
{
  dst->x = a->x + b->x;
  dst->y = a->y + b->y;
  dst->z = a->z + b->z;
}

void
sub2d(struct vec2d *a, struct vec2d *b, struct vec2d *dst)
{
  dst->x = a->x - b->x;
  dst->y = a->y - b->y;
}

void
sub3d(struct vec3d *a, struct vec3d *b, struct vec3d *dst)
{
  dst->x = a->x - b->x;
  dst->y = a->y - b->y;
  dst->z = a->z - b->z;
}

void
scalarmult2d(double c, struct vec2d *a, struct vec2d *dst)
{
  dst->x = c * a->x;
  dst->y = c * a->y;
}

void
scalarmult3d(double c, struct vec3d *a, struct vec3d *dst)
{
  dst->x = c * a->x;
  dst->y = c * a->y;
  dst->z = c * a->z;
}

void
scalardiv2d(double c, struct vec2d *a, struct vec2d *dst)
{
  dst->x = a->x / c;
  dst->y = a->y / c;
}

void
scalardiv3d(double c, struct vec3d *a, struct vec3d *dst)
{
  dst->x = a->x / c;
  dst->y = a->y / c;
  dst->z = a->z / c;
}

double
norm2d(struct vec2d *v)
{
  return pow(dotp2d(v, v), 0.5);
}

double
norm3d(struct vec3d *v)
{
  return pow(dotp3d(v, v), 0.5);
}

void
assign2d(struct vec2d *dst, struct vec2d *src)
{
  *dst = *src;
}

void
assign3d(struct vec3d *dst, struct vec3d *src)
{
  *dst = *src;
}

