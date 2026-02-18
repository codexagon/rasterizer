#include "framebuffer.h"

fbuf buf;

int main() {
	init_framebuffer(&buf, 128, 96);

	int ax = 5, ay = 5;
	int bx = 120, by = 43;
	int cx = 48, cy = 90;
	draw_line(&buf, ax, ay, bx, by, 255, 0, 0);
	draw_line(&buf, bx, by, cx, cy, 0, 255, 0);
	draw_line(&buf, cx, cy, ax, ay, 0, 0, 255);
	draw_pixel(&buf, ax, ay, 255, 255, 255);
	draw_pixel(&buf, bx, by, 255, 255, 255);
	draw_pixel(&buf, cx, cy, 255, 255, 255);
	render(&buf);

	SDL_Event e;
	int running = 1;
	while (running == 1) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				running = 0;
			}
		}
		SDL_Delay(500);
	}
	quit_framebuffer(&buf);
	return 0;
}
