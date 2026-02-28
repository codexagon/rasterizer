#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <SDL2/SDL.h>

typedef struct framebuffer {
	int width, height;
	SDL_Window *window;
	SDL_Texture *texture;
	SDL_Renderer *renderer;
	float *zbuf;

	Uint32 *pixels;
} fbuf;

typedef union color {
	Uint32 value;
	struct {
		Uint8 b;
		Uint8 g;
		Uint8 r;
		Uint8 a;
	};
} color;

void init_framebuffer(fbuf *buf, int bufwidth, int bufheight);
void clear_framebuffer(fbuf *buf);
void draw_pixel(fbuf *buf, int x, int y, color c);
void render_framebuffer(fbuf *buf);
void quit_framebuffer(fbuf *buf);

#endif
