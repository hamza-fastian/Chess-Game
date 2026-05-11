#pragma once
#include<iostream>
using namespace std;
class Board;
enum color{white=1,black};

class Piece {
protected:
	color c;
	int row;
	int col;
	bool alive;
public:
	Piece();
	Piece(color co, int r, int c);
	int getrow();
	int getcol();
	color getcolor();
	bool isAlive();
	void setposition(int r,int c);
	virtual bool isValidMove(int row,int col,Board* b) = 0;
};

class Rook:public Piece {
public:
	Rook();
	Rook(color co, int r, int c, bool a);
	bool isValidMove(int row, int col, Board* b);
	
};

class Pawn :public Piece {
public:
	Pawn(color co, int r, int c, bool a);
	bool isValidMove(int row, int col, Board* b);
};

class Bishap:public Piece {
public:
	Bishap();
	Bishap(color co, int r, int c, bool a);
	bool isValidMove(int row, int col, Board* b);
};

class Knight:public Piece {
public:
	Knight(color co, int r, int c, bool a);
	bool isValidMove(int row, int col, Board* b);
};

class Queen:public Piece {
public:
	Queen(color co, int r, int c, bool a);
	bool isValidMove(int row, int col, Board* b);
};

class King :public Piece {
public:
	King(color co, int r, int c, bool a);
	bool isValidMove(int row, int col, Board* b);
};