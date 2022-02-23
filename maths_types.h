#ifndef MATHS_TYPES_H
#define MATHS_TYPES_H

enum mat_trans_type
{
  NONE,
  UNIT,
  SCALE,
  TRANS,
  ROT_2D_ZAXIS,
};

struct vec2d 
{
  double x, y;
};

struct vec3d 
{
  double x, y, z;
};

struct vec4d 
{
  double x, y, z, w;
};

struct mat2d
{
  struct vec2d row1;
  struct vec2d row2;
};

struct mat3d
{
  struct vec3d row1;
  struct vec3d row2;
  struct vec3d row3;
};

struct mat4d
{
  struct vec4d row1;
  struct vec4d row2;
  struct vec4d row3;
  struct vec4d row4;
};

#endif // MATHS_TYPES_H
