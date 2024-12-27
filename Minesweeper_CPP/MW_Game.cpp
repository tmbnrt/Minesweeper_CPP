#include "MW_Game.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <SDL.h>

MW_Game::MW_Game(int height, int width, int num_mines) : height(height), width(width), num_mines(num_mines) {
	std::vector<std::vector<Cell>> board(height, std::vector<Cell>(width));
    this->board = board;
}

void MW_Game::initializeBoard() {
    for (int i = 0; i < board.size(); i++)
        for (int j = 0; j < board[0].size(); j++) {
            board[i][j].visible = false;
            board[i][j].isMine = false;
            board[i][j].isFlagged = false;
            board[i][j].isDefused = false;
            board[i][j].neighbourMines = 0;
        }
}

void MW_Game::printBoard() {
    for (int i = 0; i < board.size(); i++)
        std::cout << "_";
    std::cout << std::endl;

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            if (!board[i][j].visible)
                std::cout << "#";
            else
                if (board[i][j].neighbourMines > 0)
                    std::cout << board[i][j].neighbourMines;
                else
                    std::cout << " ";
        }

        std::cout << " | " << (i + 1) << std::endl;
    }
}

void MW_Game::mineBoard() {
    srand(time(0));

    int placed = 0;
    while (placed < num_mines) {
        int rand_h = rand() % board.size();
        int rand_w = rand() % board[0].size();
        if (!board[rand_h][rand_w].isMine) {
            board[rand_h][rand_w].isMine = true;
            placed++;
        }
    }
}

void MW_Game::countNeighbourMines() {
    for (int i = 0; i < board.size(); i++)
        for (int j = 0; j < board[i].size(); j++)
            if (!board[i][j].isMine) {
                board[i][j].neighbourMines = checkNeighbours(board, i, j);
            }                
}

int MW_Game::checkNeighbours(std::vector<std::vector<Cell>> board, int x, int y) {
    int mines = 0;
    int rows = board.size();
    int columns = board[0].size();

    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
        {
            int check_x = x + i;
            int check_y = y + j;
            if (check_x >= 0 && check_y >= 0 && check_x < rows && check_y < columns)
                if (board[check_x][check_y].isMine)
                    mines++;
        }

    return mines;
}

bool MW_Game::outOfRange(int row, int column) {
    if (row < 1 || row > board.size())
        return true;
    if (column < 1 || column > board[0].size())
        return true;

    return false;
}

static void gameOver(std::vector<std::vector<Cell>> board) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            if (board[i][j].isMine)
                std::cout << "*";
            else
                std::cout << " ";
        }
        std::cout << std::endl;
    }
}

static int checkAllRevealed(std::vector<std::vector<Cell>> board, int num_mines) {
    int num_visible = 0;
    int num_flagged = 0;
    for (int i = 0; i < board.size(); i++)
        for (int j = 0; j < board[0].size(); j++) {
            if (board[i][j].visible)
                num_visible++;
            if (board[i][j].isFlagged)
                num_flagged++;
        }

    if ((num_visible + num_mines) == (board.size() * board[0].size()) && num_mines == num_flagged)
        return 2;

    for (int i = 0; i < board.size(); i++)
        for (int j = 0; j < board[0].size(); j++)
            if (!board[i][j].visible)
                return 0;

    return 2;
}

static void rek_reveal(std::vector<std::vector<Cell>>& board, int row, int column) {
    if (row < 0 || column < 0 || row >= board.size() || column >= board[0].size())
        return;
    if (board[row][column].visible)
        return;
    if (board[row][column].neighbourMines > 0) {
        board[row][column].visible = true;
        return;
    }

    board[row][column].visible = true;

    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if (i == 0 || j == 0)
                rek_reveal(board, row + i, column + j);

    return;
}

int MW_Game::revealCell(int row, int column) {
    if (board[row][column].isFlagged)
        return 0;

    if (board[row][column].isMine) {
        gameOver(board);
        return 1;       // 1: mine exploded, game over
    }

    rek_reveal(board, row, column);

    return checkAllRevealed(board, num_mines);
}

void MW_Game::setFlag(int row, int column) {
    if (!board[row][column].visible) {
        if (board[row][column].isFlagged)
            board[row][column].isFlagged = false;
        else
            board[row][column].isFlagged = true;
    }
}

std::vector<std::vector<Cell>> MW_Game::getBoard() {
    return board;
}


