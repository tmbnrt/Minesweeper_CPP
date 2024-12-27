#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <vector>
#include "MW_Game.h"

class Renderer
{
public:
	Renderer(int screen_w, int screen_h, int grid_rows, int grid_columns, int cell_size_px);
	~Renderer();

	void								render(const std::vector<std::vector<Cell>> board);

private:
	SDL_Window*							window;
	SDL_Renderer*						renderer;
	int									screen_w;
	int									screen_h;
	int									grid_rows;
	int									grid_columns;
	int									cell_size_px;
};

#endif