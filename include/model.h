#ifndef MODEL_H
#define MODEL_H

#include "framebuffer.h"
#include "rmath.h"

typedef struct model {
	vec4 *vertices;
	vec4 *transformed_vertices;
	int vcount, vcap;
	int **faces;
	int fcount, fcap;
} model;

void load_model(model *m, char *file);
void apply_transforms(model *m, mat4 *matrices, int n, mat4 viewport);
mat4 get_rotation_matrix(float c, float b, float a);
mat4 get_scale_matrix(float k);
mat4 get_perspective_matrix(float fov);
mat4 get_viewport_matrix(fbuf *buf);
void close_model(model *m);

#endif
