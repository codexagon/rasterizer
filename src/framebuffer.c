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

	buf->texture =
	    SDL_CreateTexture(buf->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, buf->width, buf->height);

	buf->pixels = malloc(bufwidth * bufheight * sizeof(Uint32));

	clear_framebuffer(buf);
}

void clear_framebuffer(fbuf *buf) {
	color c = { .value = 0xFF000000 };
	for (int i = 0; i < buf->width * buf->height; i++) {
		(buf->zbuf)[i] = 0.0f;
		(buf->pixels)[i] = c.value;
	}
}

void draw_pixel(fbuf *buf, int x, int y, color c) {
	if (x < 0 || x >= buf->width) return;
	if (y < 0 || y >= buf->height) return;
	(buf->pixels)[y * buf->width + x] = c.value;
}

void render_framebuffer(fbuf *buf) {
	SDL_UpdateTexture(buf->texture, NULL, buf->pixels, buf->width * sizeof(Uint32));
	SDL_RenderCopy(buf->renderer, buf->texture, NULL, NULL);
	SDL_RenderPresent(buf->renderer);
}

void quit_framebuffer(fbuf *buf) {
	free(buf->zbuf);
	free(buf->pixels);
	SDL_DestroyRenderer(buf->renderer);
	SDL_DestroyTexture(buf->texture);
	SDL_DestroyWindow(buf->window);
	SDL_Quit();
}
