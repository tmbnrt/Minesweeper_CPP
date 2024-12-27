#ifndef GAME_H
#define GAME_H

#include <vector>

struct Cell {
	bool visible;
	bool isMine;
	bool isFlagged;
	bool isDefused;
	int neighbourMines;
};

class MW_Game
{
public:
	MW_Game(int height, int width, int num_mines);	

	bool							outOfRange(int row, int column);
	void							initializeBoard();
	void							mineBoard();
	void							printBoard();
	void							countNeighbourMines();
	void							setFlag(int row, int column);
	
	int								revealCell(int row, int column);
	std::vector<std::vector<Cell>>	getBoard();

private:
	int								width;
	int								height;
	int								num_mines;
	std::vector<std::vector<Cell>>	board;
	static int						checkNeighbours(std::vector<std::vector<Cell>> board, int x, int y);
};

#endif