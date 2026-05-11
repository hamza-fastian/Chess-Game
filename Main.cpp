#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"
using namespace std;

void getValidMoves(Board& b, int sr, int sc, int validMoves[64][2], int& moveCount)
{
    moveCount = 0;

    Piece* p = b.board[sr][sc];

    if (p == NULL)
        return;

    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            if (p->isValidMove(r, c, &b))
            {
                validMoves[moveCount][0] = r;
                validMoves[moveCount][1] = c;

                moveCount++;
            }
        }
    }
}

struct TextureManager
{
    sf::Texture wp, bp;
    sf::Texture wr, br;
    sf::Texture wn, bn;
    sf::Texture wb, bb;
    sf::Texture wq, bq;
    sf::Texture wk, bk;

    void load()
    {
        wp.loadFromFile("C:/Users/HP/Desktop/ChessGame/x64/Debug/images/w_pawn.png");
        bp.loadFromFile("C:/Users/HP/Desktop/ChessGame/x64/Debug/images/b_pawn.png");

        wr.loadFromFile("C:/Users/HP/Desktop/ChessGame/x64/Debug/images/w_rook.png");
        br.loadFromFile("C:/Users/HP/Desktop/ChessGame/x64/Debug/images/b_rook.png");

        wn.loadFromFile("C:/Users/HP/Desktop/ChessGame/x64/Debug/images/w_knight.png");
        bn.loadFromFile("C:/Users/HP/Desktop/ChessGame/x64/Debug/images/b_knight.png");

        wb.loadFromFile("C:/Users/HP/Desktop/ChessGame/x64/Debug/images/w_bishop.png");
        bb.loadFromFile("C:/Users/HP/Desktop/ChessGame/x64/Debug/images/b_bishop.png");

        wq.loadFromFile("C:/Users/HP/Desktop/ChessGame/x64/Debug/images/w_queen.png");
        bq.loadFromFile("C:/Users/HP/Desktop/ChessGame/x64/Debug/images/b_queen.png");

        wk.loadFromFile("C:/Users/HP/Desktop/ChessGame/x64/Debug/images/w_king.png");
        bk.loadFromFile("C:/Users/HP/Desktop/ChessGame/x64/Debug/images/b_king.png");
    }
};

int main()
{
    const int tileSize = 100;

    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess Game");

    Board b;
    b.initializeBoard();

    TextureManager tex;
    tex.load();

    bool selected = false;

    int sr = -1;
    int sc = -1;

    color turn = white;

    int validMoves[64][2];
    int moveCount = 0;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                int col = event.mouseButton.x / tileSize;
                int row = event.mouseButton.y / tileSize;

                if (!selected)
                {
                    if (b.board[row][col] != NULL &&
                        b.board[row][col]->getcolor() == turn)
                    {
                        sr = row;
                        sc = col;

                        selected = true;

                        getValidMoves(b, sr, sc, validMoves, moveCount);
                    }
                }
                
                else
                {
                    if (b.movePiece(sr, sc, row, col))
                    {
                        turn = (turn == white)
                            ? black
                            : white;
                    }

                    selected = false;

                    moveCount = 0;
                }
            }
        }

        window.clear();

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                sf::RectangleShape square(sf::Vector2f(tileSize, tileSize));

                square.setPosition(
                    j * tileSize,
                    i * tileSize
                );

                if ((i + j) % 2 == 0)
                {
                    square.setFillColor(sf::Color::White);
                }
                else
                {
                    square.setFillColor(sf::Color::Black);
                }

                window.draw(square);

                for (int k = 0; k < moveCount; k++)
                {
                    if (validMoves[k][0] == i &&
                        validMoves[k][1] == j)
                    {
                        sf::CircleShape highlight(18);

                        highlight.setFillColor(
                            sf::Color(80, 200, 255, 170)
                        );

                        highlight.setPosition(
                            j * tileSize + 25,
                            i * tileSize + 25
                        );

                        window.draw(highlight);
                    }
                }

                Piece* p = b.board[i][j];

                if (p == NULL)
                    continue;

                sf::Sprite sprite;

                if (dynamic_cast<Pawn*>(p))
                {
                    sprite.setTexture(
                        p->getcolor() == white
                        ? tex.wp
                        : tex.bp
                    );
                }

                else if (dynamic_cast<Rook*>(p))
                {
                    sprite.setTexture(
                        p->getcolor() == white
                        ? tex.wr
                        : tex.br
                    );
                }

                else if (dynamic_cast<Knight*>(p))
                {
                    sprite.setTexture(
                        p->getcolor() == white
                        ? tex.wn
                        : tex.bn
                    );
                }

                else if (dynamic_cast<Bishap*>(p))
                {
                    sprite.setTexture(
                        p->getcolor() == white
                        ? tex.wb
                        : tex.bb
                    );
                }

                else if (dynamic_cast<Queen*>(p))
                {
                    sprite.setTexture(
                        p->getcolor() == white
                        ? tex.wq
                        : tex.bq
                    );
                }

                else if (dynamic_cast<King*>(p))
                {
                    sprite.setTexture(
                        p->getcolor() == white
                        ? tex.wk
                        : tex.bk
                    );
                }

                sprite.setPosition(
                    j * tileSize,
                    i * tileSize
                );

                sprite.setScale(
                    tileSize /
                    (float)sprite.getTexture()->getSize().x,

                    tileSize /
                    (float)sprite.getTexture()->getSize().y
                );

                window.draw(sprite);
            }
        }

        window.display();
    }

    return 0;
}