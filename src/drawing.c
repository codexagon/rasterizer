#include "../include/drawing.h"
#include "../include/helper.h"

void draw_line(fbuf *buf, vec4 v1, vec4 v2, color c) {
	float dx = v2.x - v1.x, sx = 1;
	float dy = v2.y - v1.y, sy = 1;

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
	float parl = (dy > dx) ? dy : dx;
	float perp = (dy > dx) ? dx : dy;

	float x = v1.x, y = v1.y;
	while (1) {
		draw_pixel(buf, x, y, c);
		if (x == v2.x && y == v2.y)
			break;
		if (base == 0) {
			x += sx;
		} else {
			y += sy;
		}

		e += perp / 2;
		if (e >= parl) {
			if (base == 0) {
				y += sy;
			} else {
				x += sx;
			}
			e -= parl / 2;
		}
	}
}

void draw_triangle(fbuf *buf, vec4 v1, vec4 v2, vec4 v3, color c) {
	float xbl = min3(v1.x, v2.x, v3.x);
	float xbm = max3(v1.x, v2.x, v3.x);
	float ybl = min3(v1.y, v2.y, v3.y);
	float ybm = max3(v1.y, v2.y, v3.y);

	if (xbl < 0) xbl = 0;
	if (ybl < 0) ybl = 0;
	if (xbm > buf->width) xbm = buf->width - 1;
	if (ybm > buf->height) ybm = buf->height - 1;

	float a1, a2, a3;
	float a4 = signed_area(v1.x, v1.y, v2.x, v2.y, v3.x, v3.y);
	float alpha = 0, beta = 0, gamma = 0;

	float z;
	int idx;
	for (int y = (int)ybl; y <= (int)ybm; y++) {
		for (int x = (int)xbl; x <= (int)xbm; x++) {
			a1 = signed_area((float)x, (float)y, v2.x, v2.y, v3.x, v3.y);
			a2 = signed_area((float)x, (float)y, v3.x, v3.y, v1.x, v1.y);
			a3 = signed_area((float)x, (float)y, v1.x, v1.y, v2.x, v2.y);

			alpha = a1 / a4;
			beta = a2 / a4;
			gamma = a3 / a4;
			if ((alpha >= 0 && beta >= 0 && gamma >= 0)) {
				z = alpha * v1.z + beta * v2.z + gamma * v3.z;
				if (z > 0xFF) z = 0xFF; // only for depth visualization, remove otherwise
				idx = (int)(y * buf->width + x);
				if (z > (buf->zbuf)[idx]) {
					(buf->zbuf)[idx] = z;
					draw_pixel(buf, x, y, (color){ .a = 0xFF, .r = z, .g = z, .b = z});
				}
			}
		}
	}
}

void render_model(fbuf *buf, model *m) {
	for (int i = 0; i < m->fcount; i++) {
		vec4 v1 = m->transformed_vertices[m->faces[i][0] - 1];
		vec4 v2 = m->transformed_vertices[m->faces[i][1] - 1];
		vec4 v3 = m->transformed_vertices[m->faces[i][2] - 1];

		int facing_towards = ((v3.x - v1.x) * (v2.y - v1.y)) - ((v2.x - v1.x) * (v3.y - v1.y));
		if (facing_towards < 0) {
			continue;
		}
		draw_triangle(buf, v1, v2, v3, (color){0xFFFFFFFF});
	}
}
