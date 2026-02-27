#ifndef DRAWING_H
#define DRAWING_H

#include "framebuffer.h"
#include "model.h"

void draw_pixel(fbuf *buf, vertex v, color c);
void draw_line(fbuf *buf, vertex v1, vertex v2, color c);
void draw_triangle(fbuf *buf, vertex v1, vertex v2, vertex v3, color c);
void render_model(fbuf *buf, model *m);
void render(fbuf *buf);

#endif
