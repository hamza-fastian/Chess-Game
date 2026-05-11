#pragma once
#include <iostream>
#include "Game.h"
using namespace std;

void convert(string pos, int& r, int& c);

class Board {
public:
    Piece* board[8][8];

    Board();

    void initializeBoard();

    bool movePiece(int sr, int sc, int dr, int dc);

    bool isInside(int r, int c);

    ~Board();
};