#ifndef MODEL_H
#define MODEL_H

#include "framebuffer.h"

typedef struct model {
	vertex *vertices;
	int vcount, vcap;
	int **faces;
	int fcount, fcap;
} model;

void load_model(model *m, char *file, int w, int h);
void render_model(fbuf *buf, model *m);
void close_model(model *m);

#endif
