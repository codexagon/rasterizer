#include "framebuffer.h"
#include "helper.h"

void init_framebuffer(fbuf *buf, int bufwidth, int bufheight) {
	SDL_Init(SDL_INIT_VIDEO);

	buf->width = bufwidth;
	buf->height = bufheight;

	buf->window =
	    SDL_CreateWindow("rasterizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, buf->width, buf->height, 0);
	buf->renderer = SDL_CreateRenderer(buf->window, -1, SDL_RENDERER_SOFTWARE);

	clear_framebuffer(buf);
}

void draw_pixel(fbuf *buf, vertex v, color c) {
	if (v.x < 0 || v.x >= buf->width) {
		return;
	}
	if (v.y < 0 || v.y >= buf->height) {
		return;
	}

	SDL_SetRenderDrawColor(buf->renderer, c.r, c.g, c.b, 255);
	SDL_RenderDrawPoint(buf->renderer, v.x, v.y);
}

void draw_line(fbuf *buf, vertex v1, vertex v2, color c) {
	int dx = v2.x - v1.x, sx = 1;
	int dy = v2.y - v1.y, sy = 1;

	if (v2.x < v1.x) {
		dx = v1.x - v2.x;
		sx = -1;
	}
	if (v2.y < v1.y) {
		dy = v1.y - v2.y;
		sy = -1;
	}

	int e = 0;
	int base = (dy > dx) ? 1 : 0;
	int parl = (dy > dx) ? dy : dx;
	int perp = (dy > dx) ? dx : dy;

	int x = v1.x, y = v1.y;
	while (1) {
		draw_pixel(buf, (vertex){x, y, v1.z}, c);
		if (x == v2.x && y == v2.y)
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

void draw_triangle(fbuf *buf, vertex v1, vertex v2, vertex v3, color c) {
	int xbl = min3(v1.x, v2.x, v3.x);
	int xbm = max3(v1.x, v2.x, v3.x);
	int ybl = min3(v1.y, v2.y, v3.y);
	int ybm = max3(v1.y, v2.y, v3.y);

	int a1, a2, a3, a4 = signed_area(v1.x, v1.y, v2.x, v2.y, v3.x, v3.y);
	float alpha = 0, beta = 0, gamma = 0;

	int tz;
	for (int row = ybl; row <= ybm; row++) {
		for (int col = xbl; col <= xbm; col++) {
			a1 = signed_area(col, row, v2.x, v2.y, v3.x, v3.y);
			a2 = signed_area(col, row, v3.x, v3.y, v1.x, v1.y);
			a3 = signed_area(col, row, v1.x, v1.y, v2.x, v2.y);

			alpha = (float)a1 / a4;
			beta = (float)a2 / a4;
			gamma = (float)a3 / a4;
			if ((alpha >= 0 && beta >= 0 && gamma >= 0)) {
				tz = (int)(alpha * v1.z + beta * v2.z + gamma * v3.z);
				vertex p = {col, row, tz};
				draw_pixel(buf, p, (color){tz, tz, tz});
				// draw_pixel(buf, p, c);
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
