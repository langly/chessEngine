#ifndef __BOARD_H
#define __BOARD_H

#define HEIGHT 	8
#define WIDTH 	8

#include <deque>
#include <iostream>

#include "piece.h" 

// Some forward declr.
struct Move;
struct Board;


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
	std::deque<Move*> *findLegalMoves();
	void print();
};

#endif
