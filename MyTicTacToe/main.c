#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <stdlib.h>
#include<SDL.h>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#include "game.h"
#include "logic.h"
#include "rendering.h"
int main(int argc, char* argv[])
{
	printf("Hello world!\n");
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Could not initilze sdl2: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_Window *window = SDL_CreateWindow("Procedural", 100, 100, MAX_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		SDL_DestroyWindow(window);
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	game_t game = {
		.board = {
		PLAYER_O, PLAYER_X, EMPTY,
		EMPTY, PLAYER_X, EMPTY,
		EMPTY, EMPTY, PLAYER_O
	},
		.player = PLAYER_X,
		.state = TIE_STATE
	};

	SDL_Event e;
	while (game.state != QUIT_STATE) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				game.state = QUIT_STATE;
				break;
			case SDL_MOUSEBUTTONDOWN:
				click_on_cell(&game, (e.button.y / CELL_HEIGHT), (e.button.x / CELL_WIDTH));
				break;
			default:
			{}

			}
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
			render_game(renderer, &game);
			SDL_RenderPresent(renderer);
		}
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}
