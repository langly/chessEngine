#ifndef __PIECE_H
#define __PIECE_H

#include <iostream>
#include <queue>

struct Move;
struct Board;

struct Position{
	int x,y;
	void print(){ std::cout << x << "x" << y;} 
};

typedef enum {
	P_KING,
	P_QUEEN,
	P_BISHOP,
	P_KNIGHT,
	P_ROOK,
	P_PAWN
} Type;

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


#endif
