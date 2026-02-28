#include "../include/framebuffer.h"
#include "../include/model.h"

fbuf buf;

color red = {255, 0, 0};
color green = {0, 255, 0};
color blue = {0, 0, 255};
color white = {255, 255, 255};

int main(int argc, char *argv[]) {
	if (argc != 2) return 1;
	init_framebuffer(&buf, 1000, 1000);

	model m;
	load_model(&m, argv[1]);
	float alpha = 0.0f, beta = 0.0f, gamma = 0.0f;

	SDL_Event e;
	int running = 1;
	while (running == 1) {
		clear_framebuffer(&buf);
		rotate_transform(&m, gamma, beta, alpha);
		viewport_transform(&buf, &m);
		render_model(&buf, &m);

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				running = 0;
			} else if (e.type == SDL_KEYDOWN) {
				switch(e.key.keysym.sym) {
					case SDLK_RIGHT: beta += 5; break;
					case SDLK_LEFT: beta -= 5; break;
					case SDLK_UP: gamma += 5; break;
					case SDLK_DOWN: gamma -= 5; break;
				}
			}
		}
		SDL_Delay(50);
	}
	close_model(&m);
	quit_framebuffer(&buf);
	return 0;
}
