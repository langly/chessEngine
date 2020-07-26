#include "board.h"

#include <cstddef>
#include <iostream>

using namespace std;

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

Piece::Piece(Type t, bool w) :
	type(t), white(w){}

int Board::sum(){
	Piece *p;
	int sum = 0;

	for ( int y = 0; y < 8;y++){
		for ( int x = 0; x < 8;x++){
			if ( (p = board[y][x] )){
				sum += p->getValue();
			}
		}
	}

	return sum;
}

int main(int argc, char **argv){
	Board b;

	for ( int y = 0; y < 8;y++){
		for ( int x = 0; x < 8;x++){
			b.board[y][x] = nullptr;
		}
	}


	// Set up the initial board here.
	b.board[0][0] = new Piece(P_QUEEN, true);
	b.board[0][1] = new Piece(P_QUEEN, false);

	cout << b.sum() << endl;


	return 0;
}
