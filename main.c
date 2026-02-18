#include "framebuffer.h"

fbuf buf;

color red = {255, 0, 0};
color green = {0, 255, 0};
color blue = {0, 0, 255};
color white = {255, 255, 255};

int main() {
	init_framebuffer(&buf, 128, 96);

	int ax = 5, ay = 5;
	int bx = 120, by = 43;
	int cx = 48, cy = 90;
	draw_line(&buf, ax, ay, bx, by, red);
	draw_line(&buf, bx, by, cx, cy, green);
	draw_line(&buf, cx, cy, ax, ay, blue);
	draw_pixel(&buf, ax, ay, white);
	draw_pixel(&buf, bx, by, white);
	draw_pixel(&buf, cx, cy, white);
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
