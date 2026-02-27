#include "../include/framebuffer.h"

void init_framebuffer(fbuf *buf, int bufwidth, int bufheight) {
	SDL_Init(SDL_INIT_VIDEO);

	buf->width = bufwidth;
	buf->height = bufheight;

	buf->zbuf = malloc(bufwidth * bufheight * sizeof(float));
	for (int i = 0; i < bufwidth * bufheight; i++) {
		(buf->zbuf)[i] = 0.0f;
	}

	buf->window =
	    SDL_CreateWindow("rasterizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, buf->width, buf->height, 0);
	buf->renderer = SDL_CreateRenderer(buf->window, -1, SDL_RENDERER_SOFTWARE);

	clear_framebuffer(buf);
}

void clear_framebuffer(fbuf *buf) {
	for (int i = 0; i < buf->width * buf->height; i++) {
		(buf->zbuf)[i] = 0.0f;
	}
	SDL_SetRenderDrawColor(buf->renderer, 0, 0, 0, 255);
	SDL_RenderClear(buf->renderer);
}

void quit_framebuffer(fbuf *buf) {
	free(buf->zbuf);
	SDL_DestroyRenderer(buf->renderer);
	SDL_DestroyWindow(buf->window);
	SDL_Quit();
}
