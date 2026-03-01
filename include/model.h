#ifndef MODEL_H
#define MODEL_H

#include "framebuffer.h"
#include "rmath.h"

typedef struct model {
	vec3 *vertices;
	vec3 *transformed_vertices;
	int vcount, vcap;
	int **faces;
	int fcount, fcap;
} model;

void load_model(model *m, char *file);
void render_model(fbuf *buf, model *m);
void rotate_transform(model *m, float c, float b, float a);
void scale_transform(model *m, float k);
void perspective_transform(model *m);
void viewport_transform(fbuf *buf, model *m);
void close_model(model *m);

#endif
