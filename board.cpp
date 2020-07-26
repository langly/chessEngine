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

Move::Move(int fY, int fX, int toY, int toX){
	from.x = fX;
	from.y = fY;
	to.x = toX;
	to.y = toY;
}

Piece::Piece(Type t, bool w) :
	type(t), white(w){}

// Find all of the legal moves on the board.
// TODO: We might want to make this into a queue or similar for performance reasons
std::queue<Move*> *Board::findLegalMoves(){
	Piece *p = nullptr;
	queue<Move*> *moves = new queue<Move*>();

	for ( int y = 0; y < HEIGHT;y++){
		for ( int x = 0; x < WIDTH;x++){
			if ( (p = board[y][x] )){
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

int main(int argc, char **argv){
	Board b;

	for ( int y = 0; y < 8;y++){
		for ( int x = 0; x < 8;x++){
			b.board[y][x] = nullptr;
		}
	}


	// Set up the initial board here.
	b.board[0][0] = new Piece(P_ROOK, true);
	b.board[4][0] = new Piece(P_ROOK, false);

	b.print();

	queue<Move*> *q = b.findLegalMoves();

	cout << q->size() << endl;

	cout << b.sum() << endl;


	return 0;
}
