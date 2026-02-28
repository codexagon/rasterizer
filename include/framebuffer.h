#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <SDL2/SDL.h>

typedef struct framebuffer {
	int width, height;
	SDL_Window *window;
	SDL_Renderer *renderer;
	float *zbuf;
} fbuf;

typedef struct color {
	uint8_t r, g, b;
} color;

void init_framebuffer(fbuf *buf, int bufwidth, int bufheight);
void clear_framebuffer(fbuf *buf);
void quit_framebuffer(fbuf *buf);

#endif
