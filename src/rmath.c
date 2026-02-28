#include "../include/rmath.h"

#include <math.h>

vec3 vrot3(vec3 v, float c, float b, float a) {
	// c: x axis, b: y axis, a: z axis
	vec3 new;
	float ar = 0.01745329 * a;
	float br = 0.01745329 * b;
	float cr = 0.01745329 * c;
	new.x = v.x * (cos(br) * cos(cr)) - v.y * (cos(br) * sin(ar)) + v.z * (sin(br));
	new.y = v.x * (sin(cr) * sin(br) * cos(ar) + cos(cr) * sin(ar)) + v.y * (cos(cr) * cos(ar) - sin(cr) * sin(br) * sin(ar)) - v.z * (sin(cr) * cos(br));
	new.z = v.x * (sin(cr) * sin(ar) - cos(cr) * sin(br) * cos(ar)) + v.y * (cos(cr) * sin(br) * sin(ar) + sin(cr) * cos(ar)) + v.z * (cos(cr) * cos(br));
	return new;
}
