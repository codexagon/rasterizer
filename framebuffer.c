#include "framebuffer.h"
#include "helper.h"

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

void draw_triangle(fbuf *buf, int x1, int y1, int x2, int y2, int x3, int y3, color c) {
	draw_line(buf, x1, y1, x2, y2, c);
	draw_line(buf, x2, y2, x3, y3, c);
	draw_line(buf, x3, y3, x1, y1, c);

	int xbl = min3(x1, x2, x3);
	int xbm = max3(x1, x2, x3);
	int ybl = min3(y1, y2, y3);
	int ybm = max3(y1, y2, y3);

	int d1 = 0, d2 = 0, d3 = 0;
	for (int row = ybl; row <= ybm; row++) {
		for (int col = xbl; col <= xbm; col++) {
			d1 = sign(x1, y1, x2, y2, col, row);
			d2 = sign(x2, y2, x3, y3, col, row);
			d3 = sign(x3, y3, x1, y1, col, row);
			if ((d1 > 0 && d2 > 0 && d3 > 0) || (d1 < 0 && d2 < 0 && d3 < 0)) {
				draw_pixel(buf, col, row, c);
			}
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
