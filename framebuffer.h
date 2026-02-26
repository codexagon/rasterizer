#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <SDL2/SDL.h>

typedef struct framebuffer {
	int width, height;
	SDL_Window *window;
	SDL_Renderer *renderer;
} fbuf;

typedef struct color {
	uint8_t r, g, b;
} color;

typedef struct vertex {
	float x, y, z;
} vertex;

void init_framebuffer(fbuf *buf, int bufwidth, int bufheight);
void draw_pixel(fbuf *buf, vertex v, color c);
void draw_line(fbuf *buf, vertex v1, vertex v2, color c);
void draw_triangle(fbuf *buf, vertex v1, vertex v2, vertex v3, color c);
void render(fbuf *buf);
void clear_framebuffer(fbuf *buf);
void quit_framebuffer(fbuf *buf);

#endif
