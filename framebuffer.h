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

void init_framebuffer(fbuf *buf, int bufwidth, int bufheight);
void draw_pixel(fbuf *buf, int x, int y, color c);
void draw_line(fbuf *buf, int x1, int y1, int x2, int y2, color c);
void draw_triangle(fbuf *buf, int x1, int y1, int x2, int y2, int x3, int y3, color c);
void render(fbuf *buf);
void clear_framebuffer(fbuf *buf);
void quit_framebuffer(fbuf *buf);

#endif
