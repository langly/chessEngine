

#include <cstddef>
#include <iostream>

using namespace std;

// Fix the configuration variables somehow better
#define HEIGHT 8
#define WIDTH 8

#include "piece.h"
#include "board.h"

Piece::Piece(Type t, bool w) :
	type(t), white(w){}


int Piece::getValue(){
	int a;
	switch(type){
		case P_KING: 	a = 10;
		case P_QUEEN: 	a = 9;
		case P_ROOK: 	a = 5;
		case P_BISHOP: 	a = 3;
		case P_KNIGHT: 	a = 3;
		case P_PAWN: 	a = 3;
	}

	return a * (white?1:-1);
}

void Piece::print(){
	char c = '\0';
	switch(type){
		case P_KING: 	c = 'k'; break;
		case P_QUEEN: 	c = 'q'; break;
		case P_ROOK: 	c = 'r'; break;
		case P_BISHOP: 	c = 'b'; break;
		case P_KNIGHT: 	c = 'h'; break;
		case P_PAWN: 	c = 'p'; break;
	}

	cout << char(white ? c : c + 'A' - 'a');
}

void Piece::appendLegalMoves(std::queue<Move*> *moves, Board *b, int y,int x){
	// Some logic for the different types of Pieces here.. 
	// Could possibly be solved more elegantly using sub classes..

	Move *m = nullptr;
	
	if ( type == P_ROOK ) {
		// Do the 4 directions individually. Makes it easier to 
		// handle the intersect case.

		// Up
		for ( int i = y+1; i < HEIGHT; i++ ){
			m = new Move(y,x,i,x);
			m->piece = this;

			moves->push(m);

			m->print();

			if ( b->board[i][x] ) break;
		}

		// Down
		for ( int i = y-1; i >= 0; i-- ){
			m = new Move(y,x,i,x);
			m->piece = this;

			moves->push(m);

			m->print();

			if ( b->board[i][x] ) break;
		}

		// Right
		for ( int i = x+1; i < WIDTH; i++ ){
			m = new Move(y,x,y,i);
			m->piece = this;

			moves->push(m);

			m->print();

			if ( b->board[y][i] ) break;
		}

		// Left
		for ( int i = x-1; i >= 0; i-- ){
			m = new Move(y,x,y,i);
			m->piece = this;

			moves->push(m);

			m->print();

			if ( b->board[y][i] ) break;
		}
	}
}
