#include "../include/rmath.h"

vec4 scale(vec4 v, float scalar) {
	vec4 new;
	new.x = v.x * scalar;
	new.y = v.y * scalar;
	new.z = v.z * scalar;
	new.w = v.w * scalar;
	return new;
}

mat4 mprod4(mat4 m1, mat4 m2) {
	mat4 product = {0};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				(product.vals)[i][j] += (m1.vals)[i][k] * (m2.vals)[k][j];
			}
		}
	}

	return product;
}

vec4 transform(vec4 v, mat4 m) {
	return (vec4){(m.vals)[0][0] * v.x + (m.vals)[0][1] * v.y + (m.vals)[0][2] * v.z + (m.vals)[0][3] * v.w,
	              (m.vals)[1][0] * v.x + (m.vals)[1][1] * v.y + (m.vals)[1][2] * v.z + (m.vals)[1][3] * v.w,
	              (m.vals)[2][0] * v.x + (m.vals)[2][1] * v.y + (m.vals)[2][2] * v.z + (m.vals)[2][3] * v.w,
	              (m.vals)[3][0] * v.x + (m.vals)[3][1] * v.y + (m.vals)[3][2] * v.z + (m.vals)[3][3] * v.w};
}
