#include "board.h"

#include <cstddef>
#include <iostream>

using namespace std;


Move::Move(int fY, int fX, int toY, int toX){
	from.x = fX;
	from.y = fY;
	to.x = toX;
	to.y = toY;
	piece = nullptr;
}

// Find all of the legal moves on the board.
// TODO: We might want to make this into a queue or similar for performance reasons
std::deque<Move*> *Board::findLegalMoves(bool turn_white){
	Piece *p = nullptr;
	deque<Move*> *moves = new deque<Move*>();

	for ( int y = 0; y < HEIGHT;y++){
		for ( int x = 0; x < WIDTH;x++){
			if ( (p = board[y][x] ) && p->white == turn_white){
				cout << "new piece" << endl;
				p->appendLegalMoves(moves,this, y,x);			
			}
		}
	}

	return moves;
}

// TODO: This has to become better... Find a smarter way of scoring the board
int Board::sum(){
	Piece *p;
	int sum = 0;

	for ( int y = 0; y < HEIGHT;y++){
		for ( int x = 0; x < WIDTH;x++){
			if ( (p = board[y][x] )){
				sum += p->getValue();
			}
		}
	}

	return sum;
}

void Board::print(){
	for ( int y = 0; y < HEIGHT;y++){
		for ( int x = 0; x < WIDTH;x++){
			Piece *p = board[y][x];
			if ( p ) p->print();
			else cout << '.' ;
		}
		cout <<  endl;
	}
}

std::deque<Board*> Board::mutate(){
	deque<Move*> *moves = findLegalMoves(true);

	deque<Board*> new_boards;

	// Calculate all the permutations for the boards here
	for ( auto iter = moves->begin(); iter < moves->end(); iter++){
		Move *m = *iter; 

		Board *b = new Board();
		*b = *this;

		b->board[m->from.y][m->from.x] = nullptr;
		b->board[m->to.y][m->to.x] = m->piece;

		new_boards.push_back(b);
	}

	return new_boards;
}

int main(int argc, char **argv){
	Board b;

	for ( int y = 0; y < 8;y++){
		for ( int x = 0; x < 8;x++){
			b.board[y][x] = nullptr;
		}
	}


	// Set up the initial board here.
	b.board[4][4] = new Piece(P_BISHOP, true);
	b.board[6][6] = new Piece(P_ROOK, false);

	b.print();

	auto i = b.mutate();
	for ( auto iter = i.begin(); iter != i.end(); iter++){
		(*iter)->print();
		cout << endl;
	}


	return 0;
}
