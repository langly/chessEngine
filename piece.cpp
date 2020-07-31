

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

void Piece::rookMoves(std::deque<Move*> *moves, Board *b, int y,int x){
	// Do the 4 directions individually. Makes it easier to 
	// handle the intersect case.

		// Up
	Move *m = nullptr;
	for ( int i = y+1; i < HEIGHT; i++ ){
		m = new Move(y,x,i,x);
		m->piece = this;
		moves->push_back(m);
		if ( b->board[i][x] ) break;
	}

	// Down
	for ( int i = y-1; i >= 0; i-- ){
		m = new Move(y,x,i,x);
		m->piece = this;
		moves->push_back(m);
		if ( b->board[i][x] ) break;
	}

	// Right
	for ( int i = x+1; i < WIDTH; i++ ){
		m = new Move(y,x,y,i);
		m->piece = this;
		moves->push_back(m);
		if ( b->board[y][i] ) break;
	}

	// Left
	for ( int i = x-1; i >= 0; i-- ){
		m = new Move(y,x,y,i);
		m->piece = this;
		moves->push_back(m);
		if ( b->board[y][i] ) break;
	}
}

void Piece::bishopMoves(std::deque<Move*> *moves, Board *b, int y,int x){
	Move *m = nullptr;
	for ( int i = y+1,j = x+1; i < HEIGHT && j < WIDTH; i++,j++) {
		m = new Move(y,x,i,j);
		m->piece = this;
		moves->push_back(m);
		if ( b->board[i][j] ) break;
	}
	for ( int i = y-1,j = x-1; i >= 0 && j >= 0; i--,j--) {
		m = new Move(y,x,i,j);
		m->piece = this;
		moves->push_back(m);
		if ( b->board[i][j] ) break;
	}
	for ( int i = y+1,j = x-1; i < HEIGHT && j >= 0; i++,j--) {
		m = new Move(y,x,i,j);
		m->piece = this;
		moves->push_back(m);
		if ( b->board[i][j] ) break;
	}
	for ( int i = y-1,j = x+1; i >= 0 && j >= WIDTH; i--,j++){
		m = new Move(y,x,i,j);
		m->piece = this;
		moves->push_back(m);
		if ( b->board[i][j] ) break;
	}
}

bool Piece::pawnUpgrade(int y){
	return ( y == 0 && white ) || ( y == HEIGHT-1 && !white);
}

void Piece::appendLegalMoves(std::deque<Move*> *moves, Board *b, int y,int x){
	// Some logic for the different types of Pieces here.. 
	// Could possibly be solved more elegantly using sub classes..
	//
	// TODO: I think we can capture ourselves now.. Should be fixed

	Move *m = nullptr;
	
	if ( type == P_ROOK ) {
		rookMoves(moves,b,y,x);
	} else  if ( type == P_BISHOP ) { 
		bishopMoves(moves,b,y,x);
	} else if ( type == P_KNIGHT) { 
		// Knight pieces should be just rotational around the L though
	} else if ( type == P_KING ){

		// This move is legal though only if nobody else can reach it. 
		for ( int i = -1; i < 2; i++ ){
			for ( int j = -1; j < 2; j++ ){
				if ( y+i >= 0 && y+i < HEIGHT && 
				     x+j >= 0 && x+j < WIDTH ){
					m = new Move(y,x,y+i,x+j);	
					moves->push_back(m);
				}
			}
		}
	} else if ( type == P_PAWN ) {
		// If we are white, we go up the table
		int direction = white ? -1 : 1;
		int next = y + direction;

		// Cannot capture a piece infront of us.
		if ( next >= 0 && next < HEIGHT ){
			if ( !b->board[next][x] ) { 
				m = new Move(y,x,next,x);

				// TODO: Upgrade

				if ( pawnUpgrade(next) ){
					// Have to upgrade pieces.
				} else {
					moves->push_back(m);
				}
			}

			if ( x+1 < WIDTH && b->board[next][x+1] ) { 
				m = new Move(y,x,next,x+1);	
				moves->push_back(m);
			}

			if ( x-1 >= 0 && b->board[next][x-1] ) { 
				m = new Move(y,x,next,x-1);	
				moves->push_back(m);
			}
		}

		// TOOD: Implement en passant. 
		// We probably need to introduce some state to the pawns for doing this.


	} else if ( type == P_QUEEN) { 
		// This is just Bishop and Rook combined.
		rookMoves(moves,b,y,x);
		bishopMoves(moves,b,y,x);
	} else {
		cout << "Type not supported" << endl;
	}
}
