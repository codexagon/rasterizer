#include "../include/framebuffer.h"
#include "../include/model.h"

fbuf buf;

int main(int argc, char *argv[]) {
	if (argc != 2) return 1;
	init_framebuffer(&buf, 1000, 1000);

	model m;
	load_model(&m, argv[1]);
	float alpha = 0.0f, beta = 0.0f, gamma = 0.0f;
	float zoom = 1.0f;

	SDL_Event e;
	int running = 1;
	while (running == 1) {
		clear_framebuffer(&buf);
		rotate_transform(&m, gamma, beta, alpha);
		scale_transform(&m, zoom);
		perspective_transform(&m);
		viewport_transform(&buf, &m);
		render_model(&buf, &m);
		render_framebuffer(&buf);

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				running = 0;
			} else if (e.type == SDL_KEYDOWN) {
				switch(e.key.keysym.sym) {
					case SDLK_RIGHT: beta += 5; break;
					case SDLK_LEFT: beta -= 5; break;
					case SDLK_UP: gamma += 5; break;
					case SDLK_DOWN: gamma -= 5; break;
					case SDLK_KP_PLUS:
					case SDLK_EQUALS: zoom += 0.05; break; // plus key
					case SDLK_KP_MINUS:
					case SDLK_MINUS: {
						if (zoom > 0) {
							zoom -= 0.05;
						}
						break;
					}
					case SDLK_q: running = 0;
				}
			}
		}
		SDL_Delay(50);
	}
	close_model(&m);
	quit_framebuffer(&buf);
	return 0;
}
