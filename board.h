#ifndef __BOARD_H
#define __BOARD_H

#define HEIGHT 	8
#define WIDTH 	8

#include <queue>
#include <iostream>

// Some forward declr.
struct Move;
struct Board;

typedef enum {
	P_KING,
	P_QUEEN,
	P_BISHOP,
	P_KNIGHT,
	P_ROOK,
	P_PAWN
} Type;

struct Position{
	int x,y;
	void print(){ std::cout << x << "x" << y;} 
};

class Piece {
	public:
	Piece(Type _t, bool _white);
	Type type;
	bool white;
	int getValue();
	Position pos;
	void print();
	void appendLegalMoves(std::queue<Move*> *m, Board *b, int y,int x);
};

struct Move{
	Position from;
	Position to;
	Piece *piece;
	void print(){ std::cout << "f: "; from.print();  std::cout << " t:"; to.print(); std::cout << std::endl;}
	Move(int fY, int fX, int toY, int toX);
	Move() {} 
};

struct Board {
	int sum();
	Piece* board[HEIGHT][WIDTH];
	std::queue<Move*> *findLegalMoves();
	void print();
};

#endif
