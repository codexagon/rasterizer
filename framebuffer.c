#include "framebuffer.h"

#define SCALE 10

void init_framebuffer(fbuf *buf, int bufwidth, int bufheight) {
	SDL_Init(SDL_INIT_VIDEO);

	buf->width = bufwidth * SCALE;
	buf->height = bufheight * SCALE;

	buf->window =
	    SDL_CreateWindow("rasterizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, buf->width, buf->height, 0);
	buf->renderer = SDL_CreateRenderer(buf->window, -1, 0);

	clear_framebuffer(buf);
}

void draw_pixel(fbuf *buf, int x, int y, color c) {
	if (x < 0 || x >= buf->width) {
		return;
	}
	if (y < 0 || y >= buf->height) {
		return;
	}

	SDL_SetRenderDrawColor(buf->renderer, c.r, c.g, c.b, 255);
	SDL_Rect rect = {x * SCALE, y * SCALE, SCALE, SCALE};
	SDL_RenderFillRect(buf->renderer, &rect);
}

void draw_line(fbuf *buf, int x1, int y1, int x2, int y2, color c) {
	int dx = x2 - x1, sx = 1;
	int dy = y2 - y1, sy = 1;

	if (x2 < x1) {
		dx = x1 - x2;
		sx = -1;
	}
	if (y2 < y1) {
		dy = y1 - y2;
		sy = -1;
	}

	int e = 0;
	int base = (dy > dx) ? 1 : 0;
	int parl = (dy > dx) ? dy : dx;
	int perp = (dy > dx) ? dx : dy;

	int x = x1, y = y1;
	while (1) {
		draw_pixel(buf, x, y, c);
		if (x == x2 && y == y2)
			break;
		if (base == 0) {
			x += sx;
		} else {
			y += sy;
		}

		e += perp << 1;
		if (e >= parl) {
			if (base == 0) {
				y += sy;
			} else {
				x += sx;
			}
			e -= parl << 1;
		}
	}
}

void render(fbuf *buf) { SDL_RenderPresent(buf->renderer); }

void clear_framebuffer(fbuf *buf) {
	SDL_SetRenderDrawColor(buf->renderer, 0, 0, 0, 255);
	SDL_RenderClear(buf->renderer);
}

void quit_framebuffer(fbuf *buf) {
	SDL_DestroyRenderer(buf->renderer);
	SDL_DestroyWindow(buf->window);
	SDL_Quit();
}
