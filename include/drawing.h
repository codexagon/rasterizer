#ifndef DRAWING_H
#define DRAWING_H

#include "framebuffer.h"
#include "model.h"

void draw_line(fbuf *buf, vec4 v1, vec4 v2, color c);
void draw_triangle(fbuf *buf, vec4 v1, vec4 v2, vec4 v3, color c);
void render_model(fbuf *buf, model *m);

#endif
