#ifndef RMATH_H
#define RMATH_H

typedef struct vector3d {
	float x, y, z;
} vec3;

vec3 vrot3(vec3 v, float c, float b, float a);
vec3 scale(vec3 v, float scalar);

#endif
