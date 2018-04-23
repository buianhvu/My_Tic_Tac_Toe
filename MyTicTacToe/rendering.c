#include <SDL.h>
#include "game.h"
#include "rendering.h"
#include <math.h>

const SDL_Color GRID_COLOR = { .r = 255,.g = 255,.b = 255 };
const SDL_Color PLAYER_X_COLOR = { .r = 255,.g = 50,.b = 50 };
const SDL_Color PLAYER_O_COLOR = { .r = 50,.g = 100,.b = 255 };
const SDL_Color TIE_COLOR = { .r = 100,.g = 100,.b = 100 };

void render_grid(SDL_Renderer *renderer, const SDL_Color *color) {
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);
	for (int i = 1; i <= N; i++) {
		SDL_RenderDrawLine(renderer, i*CELL_WIDTH, 0, i*CELL_WIDTH, SCREEN_HEIGHT);
		SDL_RenderDrawLine(renderer, 0, i*CELL_HEIGHT, SCREEN_WIDTH, i*CELL_HEIGHT);
	}
}

void render_x(SDL_Renderer *renderer, int row, int column, const SDL_Color *player_x_color) {
	const float half_box_size = fmin(CELL_HEIGHT, CELL_WIDTH) / 4;
	const float center_x = column * CELL_WIDTH + CELL_WIDTH * 0.5;
	const float center_y = row * CELL_HEIGHT + CELL_HEIGHT * 0.5;
	SDL_SetRenderDrawColor(renderer, player_x_color->r, player_x_color->g, player_x_color->b, 255);

	// instead of install gfx lib, we only use this algorithm instead
	//    thickLineColor(renderer, 0, 0, 123, 123, 20, 0xFF00FFFF) ;

	SDL_RenderDrawLine(renderer, center_x - half_box_size, center_y - half_box_size, center_x + half_box_size, center_y + half_box_size);
	SDL_RenderDrawLine(renderer, center_x - half_box_size + 1, center_y - half_box_size, center_x + half_box_size + 1, center_y + half_box_size);
	SDL_RenderDrawLine(renderer, center_x - half_box_size, center_y - half_box_size + 1, center_x + half_box_size, center_y + half_box_size + 1);

	SDL_RenderDrawLine(renderer, center_x + half_box_size, center_y - half_box_size, center_x - half_box_size, center_y + half_box_size);
	SDL_RenderDrawLine(renderer, center_x + half_box_size - 1, center_y - half_box_size, center_x - half_box_size - 1, center_y + half_box_size);
	SDL_RenderDrawLine(renderer, center_x + half_box_size, center_y - half_box_size + 1, center_x - half_box_size, center_y + half_box_size + 1);
}
void render_o(SDL_Renderer *renderer, int row, int column, const SDL_Color *player_o_color) {
	const float half_box_size = fmin(CELL_HEIGHT, CELL_WIDTH) / 4;
	const float center_x = column * CELL_WIDTH + CELL_WIDTH * 0.5;
	const float center_y = row * CELL_HEIGHT + CELL_HEIGHT * 0.5;
	/*SDL_Rect sourceRect;
	SDL_Rect desRect;
	SDL_Surface * tempSurface = SDL_LoadBMP("circle.bmp");
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	SDL_QueryTexture(texture, NULL, NULL, &sourceRect.w, &sourceRect.h);

	sourceRect.x = desRect.x = 0;
	sourceRect.y = desRect.y = 0;
	desRect.w = sourceRect.w;
	desRect.h = sourceRect.h;
	SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
*/

	

	SDL_Rect r;
	SDL_SetRenderDrawColor(renderer, player_o_color->r, player_o_color->g, player_o_color->b, 255);
	r.x = center_x - half_box_size;
	r.y = center_y - half_box_size;
	r.h = half_box_size*2;
	r.w = half_box_size*2;
	SDL_RenderDrawRect(renderer, &r);

}


void render_board(SDL_Renderer *renderer, const int *board, const SDL_Color *player_x_color, const SDL_Color *player_o_color) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			switch (board[i*N + j]) {
			case PLAYER_X:
				render_x(renderer, i, j, player_x_color);
				break;
			case PLAYER_O:
				render_o(renderer, i, j, player_o_color);
				break;
			default:
			{}
			}
		}
	}

}

void render_running_state(SDL_Renderer *renderer, const game_t *game) {
	render_grid(renderer, &GRID_COLOR);
	render_board(renderer, game->board, &PLAYER_X_COLOR, &PLAYER_O_COLOR);

}
void render_game_over_state(SDL_Renderer *renderer, const game_t *game, const SDL_Color *color) {
	render_grid(renderer, color);
	render_board(renderer, game->board, color, color);
}
void render_game(SDL_Renderer *renderer, const game_t *game) {
	switch (game->state) {
	case RUNNING_STATE:
		render_running_state(renderer, game);
		break;
	case PLAYER_X_WON_STATE:
		render_game_over_state(renderer, game, &PLAYER_X_COLOR);
		break;
	case PLAYER_O_WON_STATE:
		render_game_over_state(renderer, game, &PLAYER_O_COLOR);
		break;
	case TIE_STATE:
		render_game_over_state(renderer, game, &TIE_COLOR);
		break;
	default: {}
			 break;

	}
}

