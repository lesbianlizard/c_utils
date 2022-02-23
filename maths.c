#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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

double
dotp4d(struct vec4d *a, struct vec4d *b)
{
  return a->x * b->x
       + a->y * b->y
       + a->z * b->z
       + a->w * b->w;
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

void
multmat4d(struct mat4d *dst, struct mat4d *mat1, struct mat4d *mat2)
{
  struct mat4d tmp1[1];
  struct mat4d tmp2[1];
  assignmat4d(tmp1, mat1);
  transmat4d(tmp2, mat2);
  
  dst->row1.x = dotp4d(&tmp2->row1, &tmp1->row1);
  dst->row2.x = dotp4d(&tmp2->row1, &tmp1->row2);
  dst->row3.x = dotp4d(&tmp2->row1, &tmp1->row3);
  dst->row4.x = dotp4d(&tmp2->row1, &tmp1->row4);

  dst->row1.y = dotp4d(&tmp2->row2, &tmp1->row1);
  dst->row2.y = dotp4d(&tmp2->row2, &tmp1->row2);
  dst->row3.y = dotp4d(&tmp2->row2, &tmp1->row3);
  dst->row4.y = dotp4d(&tmp2->row2, &tmp1->row4);

  dst->row1.z = dotp4d(&tmp2->row3, &tmp1->row1);
  dst->row2.z = dotp4d(&tmp2->row3, &tmp1->row2);
  dst->row3.z = dotp4d(&tmp2->row3, &tmp1->row3);
  dst->row4.z = dotp4d(&tmp2->row3, &tmp1->row4);

  dst->row1.w = dotp4d(&tmp2->row4, &tmp1->row1);
  dst->row2.w = dotp4d(&tmp2->row4, &tmp1->row2);
  dst->row3.w = dotp4d(&tmp2->row4, &tmp1->row3);
  dst->row4.w = dotp4d(&tmp2->row4, &tmp1->row4);
}

void
transmat4d(struct mat4d *dst, struct mat4d *mat)
{
  dst->row1.x = mat->row1.x; 
  dst->row2.x = mat->row1.y; 
  dst->row3.x = mat->row1.z; 
  dst->row4.x = mat->row1.w; 

  dst->row1.y = mat->row2.x; 
  dst->row2.y = mat->row2.y; 
  dst->row3.y = mat->row2.z; 
  dst->row4.y = mat->row2.w; 

  dst->row1.z = mat->row3.x; 
  dst->row2.z = mat->row3.y; 
  dst->row3.z = mat->row3.z; 
  dst->row4.z = mat->row3.w; 

  dst->row1.w = mat->row4.x; 
  dst->row2.w = mat->row4.y; 
  dst->row3.w = mat->row4.z; 
  dst->row4.w = mat->row4.w; 
}

void assignmat4d(struct mat4d *dst, struct mat4d *src)
{
  dst->row1 = src->row1;
  dst->row2 = src->row2;
  dst->row3 = src->row3;
  dst->row4 = src->row4;
}

void
initmat4d(struct mat4d *mat, enum mat_trans_type type, void *init_data)
{
  memset(mat, 0, 4*sizeof(struct vec4d));

  if (type == UNIT)
  {
    mat->row1.x = 1;
    mat->row2.y = 1;
    mat->row3.z = 1;
    mat->row4.w = 1;
  }
  else if (type == SCALE)
  {
    struct vec3d *scale = (struct vec3d *) init_data; 
    mat->row1.x = scale->x;
    mat->row2.y = scale->y;
    mat->row3.z = scale->z;
    mat->row4.w = 1;
  }
  else if (type == TRANS)
  {
    struct vec3d *trans= (struct vec3d *) init_data; 
    mat->row1.w = trans->x;
    mat->row2.w = trans->y;
    mat->row3.w = trans->z;
    mat->row1.x = 1;
    mat->row2.y = 1;
    mat->row3.z = 1;
    mat->row4.w = 1;
  }
  else if (type == ROT_2D_ZAXIS)
  {
    double theta = *((double *) init_data);
    mat->row1.x = cos(theta);
    mat->row1.y = -sin(theta);
    mat->row2.x = sin(theta);
    mat->row2.y = cos(theta);

    mat->row3.z = 1;
    mat->row4.w = 1;
  }
}

void
print_mat4d(struct mat4d *mat, char *label)
{
  printf("mat4d at %p \"%s\"\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n",
    mat, label,
    mat->row1.x, mat->row1.y, mat->row1.z, mat->row1.w,
    mat->row2.x, mat->row2.y, mat->row2.z, mat->row2.w,
    mat->row3.x, mat->row3.y, mat->row3.z, mat->row3.w,
    mat->row4.x, mat->row4.y, mat->row4.z, mat->row4.w
  );
}

