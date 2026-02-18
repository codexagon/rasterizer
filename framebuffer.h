#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <SDL2/SDL.h>

#define u8 uint8_t

typedef struct framebuffer {
	int width, height;
	SDL_Window *window;
	SDL_Renderer *renderer;
} fbuf;

void init_framebuffer(fbuf *buf, int bufwidth, int bufheight);
void draw_pixel(fbuf *buf, int x, int y, u8 r, u8 g, u8 b);
void draw_line(fbuf *buf, int x1, int y1, int x2, int y2, u8 r, u8 g, u8 b);
void render(fbuf *buf);
void clear_framebuffer(fbuf *buf);
void quit_framebuffer(fbuf *buf);

#endif
