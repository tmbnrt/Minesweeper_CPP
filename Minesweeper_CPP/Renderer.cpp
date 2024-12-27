#include "Renderer.h"
#include "MW_Game.h"
#include <SDL.h>
#include <iostream>

Renderer::Renderer(int screen_w, int screen_h, int grid_rows, int grid_columns, int cell_size_px)
	: screen_w(screen_w), screen_h(screen_h), grid_rows(grid_rows), grid_columns(grid_columns), cell_size_px(cell_size_px) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw std::runtime_error("SDL cannot be initialized!");
		std::cerr << "SDL could not initialize! Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	window = SDL_CreateWindow("Minesweeper",
							  SDL_WINDOWPOS_CENTERED,
							  SDL_WINDOWPOS_CENTERED,
							  grid_columns * cell_size_px,
							  grid_rows * cell_size_px,
							  SDL_WINDOW_SHOWN);

	if (!window) {
		SDL_Quit();
		throw std::runtime_error("Cannot create window!");
		std::cerr << "Window cannot be created! Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (!renderer) {
		throw std::runtime_error("Renderer cannot be created!");
		std::cerr << "Renderer cannot be created! Error: " << SDL_GetError() << std::endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		exit(1);
	}
}

Renderer::~Renderer() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

/*
void Renderer::clear() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}*/

void Renderer::render(const std::vector<std::vector<Cell>> board) {
	// Background
	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

	// Clear back buffer
	SDL_RenderClear(renderer);

	// Play board
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[0].size(); j++) {
			SDL_Rect rect = { j * cell_size_px, i * cell_size_px, cell_size_px, cell_size_px };

			if (!board[i][j].visible)
				SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
			if (board[i][j].visible && board[i][j].isMine)
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			if (board[i][j].visible && board[i][j].neighbourMines == 0)
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			if (!board[i][j].visible && board[i][j].isFlagged)
				SDL_SetRenderDrawColor(renderer, 200, 150, 150, 150);
			if (board[i][j].visible && board[i][j].neighbourMines == 1)
				SDL_SetRenderDrawColor(renderer, 173, 216, 230, 255);	// light blue
			if (board[i][j].visible && board[i][j].neighbourMines == 2)
				SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);	// blue
			if (board[i][j].visible && board[i][j].neighbourMines == 3)
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);	// green
			if (board[i][j].visible && board[i][j].neighbourMines == 4)
				SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);	// yellow
			if (board[i][j].visible && board[i][j].neighbourMines == 5)
				SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);	// orange
			if (board[i][j].visible && board[i][j].neighbourMines == 6)
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);	// red
			if (board[i][j].visible && board[i][j].neighbourMines == 7)
				SDL_SetRenderDrawColor(renderer, 255, 105, 180, 255);	// pink
			if (board[i][j].visible && board[i][j].neighbourMines == 8)
				SDL_SetRenderDrawColor(renderer, 219, 112, 219, 255);	// lila

			SDL_RenderFillRect(renderer, &rect);

			// Frame
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderDrawRect(renderer, &rect);
		}

		// Switch to front buffer
		SDL_RenderPresent(renderer);
	}
}
