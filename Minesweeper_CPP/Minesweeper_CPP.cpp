//#include "Renderer.h"
#include "MW_Game.h"
#include "Renderer.h"
//#include "Minesweeper_CPP.h"
#include <iostream>
//#include <string>
//#include <vector>
//#include <cstdlib>
//#include <ctime>
//#include <SDL.h>

int main(int argc, char* argv[]) {
    const int cell_size_px = 40;
    const int screen_h = 800;
    const int screen_w = 600;
    const int height = 10;
    const int width = 12;
    const int num_mines = 10;

    MW_Game mw_game(height, width, num_mines);
    Renderer rend(screen_h, screen_w, height, width, cell_size_px);
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

    mw_game.initializeBoard();
    mw_game.mineBoard();
    mw_game.countNeighbourMines();

    // test board functionality
    //mw_game.printBoard();

    // Main loop: Game play
    int status = 0;            // 0: active  1: failed  2: win  -1: Window closed
    while (status == 0) {
        SDL_Event e;

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                status = -1;
        }

        // Click: Defuse
        if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            int column = e.button.x / cell_size_px;
            int row = e.button.y / cell_size_px;

            status = mw_game.revealCell(row, column);
        }

        // Click: Flag
        if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_RIGHT) {
            int column = e.button.x / cell_size_px;
            int row = e.button.y / cell_size_px;

            mw_game.setFlag(row, column);
        }

        rend.render(mw_game.getBoard());

        if (status == 1) {
            std::cout << "Game over!" << std::endl;
            //SDL_DELAY();
        }

        if (status == 2) {
            std::cout << "You win!" << std::endl;
            //SDL_DELAY();
        }
    }

    //exitGameMassage(end);

    return 0;
}
