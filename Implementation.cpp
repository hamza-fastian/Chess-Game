#include"game.h"
#include"Board2.h"

Piece::Piece()
{
	row = 0;
	col = 0;
	alive = false;
}

Piece::Piece(color co, int r, int c) :c(co), row(r), col(c), alive(true)
{
	
}

int Piece::getrow()
{
	return row;
}

int Piece::getcol()
{
	return col;
}

color Piece::getcolor()
{
	return c;
}

bool Piece::isAlive()
{
	return alive;
}

void Piece::setposition(int r, int c)
{
	row = r;
	col = c;
}

Rook::Rook()
{

}

Rook::Rook(color co, int r, int c, bool a) :Piece(co, r, c)
{

}

bool Rook::isValidMove(int row, int col, Board* b)
{
	if ((row >= 0 && row < 8) && (col >= 0 && col < 8))
	{
		if (b == NULL)
		{
			return false;
		}
		if (row == this->row && col == this->col)
		{
			return false;
		}
		else
		{
			if (row == this->row)
			{
				if (col > this->col)
				{
					for (int i = this->col + 1; i < col; i++)
					{
						if (b->board[this->row][i] != NULL)
							return false;
					}
				}
				else
				{
					for (int i = this->col-1; i > col; i--)
					{
						if (b->board[this->row][i] != NULL)
							return false;
					}
				}
			}
			if (col == this->col)
			{
				if (row > this->row)
				{
					for (int i = this->row + 1; i < row; i++)
					{
						if (b->board[i][this->col] != NULL)
							return false;
					}
				}
				else
				{
					for (int i = this->row-1; i > row; i--)
					{
						if (b->board[i][this->col] != NULL)
							return false;
					}
				}
			}
		}
	}
	else
	{
		return false;
	}
	if (b->board[row][col] != NULL)
	{
		if (b->board[row][col]->getcolor() == this->c)
			return false;
	}

	return true;
}

Pawn::Pawn(color co, int r, int c, bool a) :Piece(co, r, c)
{

}

bool Pawn::isValidMove(int row, int col, Board* b)
{
	if ((row >= 0 && row < 8) && (col >= 0 && col < 8))
	{
		if (b == NULL)
		{
			return false;
		}

		int r = row - this->row;
		int c = col - this->col;
		if (this->c == white)
		{
			if (c == 0)
			{
				if (this->row == 6)
				{
					if (r == -2)
					{
						if (b->board[this->row - 1][col] != NULL ||
							b->board[row][col] != NULL)
						{
							return false;
						}

						return true;
					}
				}
				if (r == -1)
				{
					if (b->board[row][col] == NULL)
					{
						return true;
					}
				}
			}
			if ((c == 1 || c == -1) && r == -1)
			{
				if (b->board[row][col] != NULL)
				{
					if (b->board[row][col]->getcolor() != this->c)
					{
						return true;
					}
				}
			}
		}
		else
		{
			if (c == 0)
			{
				if (this->row == 1)
				{
					if (r == 2)
					{
						if (b->board[this->row + 1][col] != NULL ||
							b->board[row][col] != NULL)
						{
							return false;
						}

						return true;
					}
				}
				if (r == 1)
				{
					if (b->board[row][col] == NULL)
					{
						return true;
					}
				}
			}
			if ((c == 1 || c == -1) && r == 1)
			{
				if (b->board[row][col] != NULL)
				{
					if (b->board[row][col]->getcolor() != this->c)
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

Bishap::Bishap()
{
	// Default Constructor for Bishap
}

Bishap::Bishap(color co, int r, int c, bool a) :Piece(co, r, c)
{

}

bool Bishap::isValidMove(int row, int col, Board* b)
{
	if ((row >= 0 && row < 8) && (col >= 0 && col < 8))
	{
		if (b == NULL)
		{
			return false;
		}
		int newr = row - this->row;
		int newc = col - this->col;
		if (newr < 0)
		{
			newr *= -1;
		}
		if (newc < 0)
		{
			newc *= -1;
		}
		if (newr != newc)
		{
			return false;
		}

		int nextr = (row > this->row) ? 1 : -1;
		int nextc = (col > this->col) ? 1 : -1;

		int r = this->row + nextr;
		int c = this->col + nextc;
		while (r != row)
		{
			if (b->board[r][c] != NULL)
			{
				return false;
			}
			r += nextr;
			c += nextc;
		}
		
	}
	else
	{
		return false;
	}
	if (b->board[row][col] != NULL)
	{
		if (b->board[row][col]->getcolor() == this->c)
			return false;
	}
	return true;
}

Knight::Knight(color co, int r, int c, bool a):Piece(co, r, c)
{

}

bool Knight::isValidMove(int row, int col, Board* b)
{
	if ((row >= 0 && row < 8) && (col >= 0 && col < 8))
	{
		if (b == NULL)
		{
			return false;
		}
		int r = row - this->row;
		int c = col - this->col;
		if (r < 0)
		{
			r *= -1;
		}
		if (c < 0)
		{
			c *= -1;
		}
		if ((r == 2 && c == 1) || (r == 1 && c == 2))
		{
			
		}
		else
		{
			return false;
		}

	}
	else
	{
		return false;
	}
	if (b->board[row][col] != NULL)
	{
		if (b->board[row][col]->getcolor() == this->c)
			return false;
	}
	return true;
}

Queen::Queen(color co, int r, int c, bool a):Piece(co, r, c)
{

}

bool Queen::isValidMove(int row, int col, Board* b)
{
	if (b == NULL)
	{
		return false;
	}
	if (row < 0 || row >= 8 || col < 0 || col >= 8)
	{
		return false;
	}
	if (row == this->row && col == this->col)
		return false;
	int dx = row - this->row;
	int dy = col - this->col;
	if (b->board[row][col] != NULL)
	{
		if (b->board[row][col]->getcolor() == this->c)
			return false;
	}
	if (row == this->row || col == this->col)
	{
		if (row == this->row)
		{
			int step = (col > this->col) ? 1 : -1;

			for (int i = this->col + step; i != col; i += step)
			{
				if (b->board[row][i] != NULL)
					return false;
			}
		}
		else
		{
			int step = (row > this->row) ? 1 : -1;

			for (int i = this->row + step; i != row; i += step)
			{
				if (b->board[i][col] != NULL)
					return false;
			}
		}

		return true;
	}
	if (dx < 0)
	{
		dx *= -1;
	}
	if (dy < 0)
	{
		dy *= -1;
	}
	if (dx == dy)
	{
		int stepX = (dx > 0) ? 1 : -1;
		int stepY = (dy > 0) ? 1 : -1;

		int r = this->row + stepX;
		int c = this->col + stepY;

		while (r != row && c != col)
		{
			if (b->board[r][c] != NULL)
				return false;

			r += stepX;
			c += stepY;
		}
		return true;
	}
	return false;
}

King::King(color co, int r, int c, bool a):Piece(co,r,c)
{

}

bool King::isValidMove(int row, int col, Board* b)
{
	if ((row >= 0 && row < 8) && (col >= 0 && col < 8))
	{
		if (b == NULL)
		{
			return false;
		}
		int r = row - this->row;
		int c = col - this->col;
		if (r < 0)
		{
			r *= -1;
		}
		if (c < 0)
		{
			c *= -1;
		}
		if (r > 1 || c > 1)
		{
			return false;
		}
		if (r == 0 && c == 0)
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	if (b->board[row][col] != NULL)
	{
		if (b->board[row][col]->getcolor() == this->c)
			return false;
	}
	return true;
}