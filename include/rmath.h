#ifndef RMATH_H
#define RMATH_H

typedef struct vector4d {
	float x, y, z, w;
} vec4;

typedef struct matrix4d {
	float vals[4][4];
} mat4;

vec4 scale(vec4 v, float scalar);
mat4 mprod4(mat4 m1, mat4 m2);
vec4 transform(vec4 v, mat4 mat);

#endif
