#include"Board.h"

Board::Board()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			board[i][j] = NULL;
}

void Board::initializeBoard()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			board[i][j] = NULL;

	for (int i = 0; i < 8; i++)
	{
		board[1][i] = new Pawn(black, 1, i, true);
		board[6][i] = new Pawn(white, 6, i, true);
	}

	board[0][0] = new Rook(black, 0, 0, true);
	board[0][7] = new Rook(black, 0, 7, true);
	board[7][0] = new Rook(white, 7, 0, true);
	board[7][7] = new Rook(white, 7, 7, true);

	board[0][1] = new Knight(black, 0, 1, true);
	board[0][6] = new Knight(black, 0, 6, true);
	board[7][1] = new Knight(white, 7, 1, true);
	board[7][6] = new Knight(white, 7, 6, true);

	board[0][2] = new Bishap(black, 0, 2, true);
	board[0][5] = new Bishap(black, 0, 5, true);
	board[7][2] = new Bishap(white, 7, 2, true);
	board[7][5] = new Bishap(white, 7, 5, true);

	board[0][3] = new Queen(black, 0, 3, true);
	board[7][3] = new Queen(white, 7, 3, true);

	board[0][4] = new King(black, 0, 4, true);
	board[7][4] = new King(white, 7, 4, true);
}

bool Board::isInside(int r, int c)
{
	return (r >= 0 && r < 8 && c >= 0 && c < 8);
}

bool Board::movePiece(int sr, int sc, int dr, int dc)
{
	if (!isInside(sr, sc) || !isInside(dr, dc))
		return false;

	Piece* p = board[sr][sc];
	if (!p) return false;

	if (!p->isValidMove(dr, dc, this))
		return false;

	if (board[dr][dc] && board[dr][dc]->getcolor() == p->getcolor())
		return false;

	if (board[dr][dc])
		delete board[dr][dc];

	board[dr][dc] = p;
	board[sr][sc] = NULL;

	p->setposition(dr, dc);

	return true;
}

Board::~Board()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			delete board[i][j];
}
