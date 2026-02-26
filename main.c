#include "framebuffer.h"
#include "model.h"

fbuf buf;

color red = {255, 0, 0};
color green = {0, 255, 0};
color blue = {0, 0, 255};
color white = {255, 255, 255};

int main(int argc, char *argv[]) {
	if (argc != 2) return 1;
	init_framebuffer(&buf, 1280, 1100);

	model m;
	load_model(&m, argv[1], buf.width, buf.height);
	clear_framebuffer(&buf);
	render_model(&buf, &m);
	close_model(&m);

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
