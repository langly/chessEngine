#ifndef __BOARD_H
#define __BOARD_H

typedef enum {
	P_KING,
	P_QUEEN,
	P_BISHOP,
	P_KNIGHT,
	P_ROOK,
	P_PAWN
} Type;

struct Move{
	short x,y;
};

struct Piece {
	Piece(Type _t, bool _white);
	Type type;
	bool white;
	int getValue();
	Move move(int x, int y);
};


struct Board {
	int sum();
	Piece* board[8][8];


};

#endif
