#include <math.h>

#include "maths.h"

double
dotp2d(struct vec2d *a, struct vec2d *b)
{
  return a->x * b->x
       + a->y * b->y;
}

void
sum2d(struct vec2d *a, struct vec2d *b, struct vec2d *dst)
{
  dst->x = a->x + b->x;
  dst->y = a->y + b->y;
}

void
sub2d(struct vec2d *a, struct vec2d *b, struct vec2d *dst)
{
  dst->x = a->x - b->x;
  dst->y = a->y - b->y;
}

void
scalarmult2d(double c, struct vec2d *a, struct vec2d *dst)
{
  dst->x = c * a->x;
  dst->y = c * a->y;
}

void
scalardiv2d(double c, struct vec2d *a, struct vec2d *dst)
{
  dst->x = a->x / c;
  dst->y = a->y / c;
}

double
norm2d(struct vec2d *v)
{
  return pow(dotp2d(v, v), 0.5);
}

// FIXME: compatibility name. delete this
void
assign2d(struct vec2d *dst, struct vec2d *src)
{
  vec2d_assign(dst, src);
}

void
vec2d_assign(struct vec2d *dst, struct vec2d *src)
{
  *dst = *src;
}

