#include "ChessPiece.h"
using namespace std;
using namespace IvanChessGame;

//SuperClass - ChessPiece definition:
ChessPiece::ChessPiece(){}
//ChessPiece::~ChessPiece(){}

//Getters
ChessColor ChessPiece::GetPieceColor() { return _pieceColor; }

int ChessPiece::GetCurrentPosition()   { return _iCurrentPosition; }
void ChessPiece::SetCurrentPosition(int iNewPos){ _iCurrentPosition = iNewPos; }

string ChessPiece::GetPieceName() { return _strPieceName; }
char ChessPiece::GetShortPieceName() { return _chrShortPieceName; }

vector<int>& ChessPiece::GetAvailablePositionsToMove() { return _availablePositionsToMove; }
vector<int>& ChessPiece::GetAvailablePositionsForAttack(){ return _availablePositionsForAttack; }

//Movers/Setters
void ChessPiece::MoveToPos(int iNewPosition) {}
void ChessPiece::MoveToRowCol(int iNewRow, int iNewCol) {}
void ChessPiece::ResetAllAvailablePositions() {}

//=====================================================================================

// Derived class - Pawn definition:

Pawn::Pawn(ChessColor pieceColor, int startPosition){
	_pieceColor = pieceColor; 
	_iCurrentPosition = startPosition; 
	_strPieceName = "Pawn";
	_chrShortPieceName = 'P';
}

Pawn::Pawn(ChessColor pieceColor, int startRow, int StartCol) {

}

Pawn::~Pawn(){}

vector<int>& Pawn::GetAvailablePositionsToMove() { return _availablePositionsToMove; }
vector<int>& Pawn::GetAvailablePositionsForAttack(){ return _availablePositionsForAttack; }

void Pawn::MoveToPos(int iNewPosition) {}
void Pawn::MoveToRowCol(int Row, int Col) {}
void Pawn::ResetAllAvailablePositions() {}

//=====================================================================================

// Derived class - Bishop definition:
Bishop::Bishop(ChessColor pieceColor, int startPosition){
	_pieceColor = pieceColor;
	_iCurrentPosition = startPosition;
	_strPieceName = "Bishop";
	_chrShortPieceName = 'B';
}

Bishop::Bishop(ChessColor pieceColor, int startRow, int StartCol) {

}

Bishop::~Bishop(){}

vector<int>& Bishop::GetAvailablePositionsToMove() { return _availablePositionsToMove; }
vector<int>& Bishop::GetAvailablePositionsForAttack(){ return _availablePositionsForAttack; }

void Bishop::MoveToPos(int iNewPosition) {}
void Bishop::MoveToRowCol(int Row, int Col) {}
void Bishop::ResetAllAvailablePositions() {}

//=====================================================================================

// Derived class - Rook definition:

Rook::Rook(ChessColor pieceColor, int startPosition){
	_pieceColor = pieceColor;
	_iCurrentPosition = startPosition;
	_strPieceName = "Rook";
	_chrShortPieceName = 'R';
}

Rook::Rook(ChessColor pieceColor, int startRow, int StartCol) {

}

Rook::~Rook(){}

vector<int>& Rook::GetAvailablePositionsToMove() { return _availablePositionsToMove; }
vector<int>& Rook::GetAvailablePositionsForAttack(){ return _availablePositionsForAttack; }

void Rook::MoveToPos(int iNewPosition) {}
void Rook::MoveToRowCol(int Row, int Col) {}
void Rook::ResetAllAvailablePositions() {}

//=====================================================================================

// Derived class - Knight definition:
Knight::Knight(ChessColor pieceColor, int startPosition){
	_pieceColor = pieceColor;
	_iCurrentPosition = startPosition;
	_strPieceName = "Knight";
	_chrShortPieceName = 'N';
}

Knight::Knight(ChessColor pieceColor, int startRow, int StartCol) {

}

Knight::~Knight(){}

vector<int>& Knight::GetAvailablePositionsToMove() { return _availablePositionsToMove; }
vector<int>& Knight::GetAvailablePositionsForAttack(){ return _availablePositionsForAttack; }

void Knight::MoveToPos(int iNewPosition) {}
void Knight::MoveToRowCol(int Row, int Col) {}
void Knight::ResetAllAvailablePositions() {}

//=====================================================================================

// Derived class - Queen definition:
Queen::Queen(ChessColor pieceColor, int startPosition){
	_pieceColor = pieceColor;
	_iCurrentPosition = startPosition; 
	_strPieceName = "Queen";
	_chrShortPieceName = 'Q';
}

Queen::Queen(ChessColor pieceColor, int startRow, int StartCol) {

}

Queen::~Queen(){}

vector<int>& Queen::GetAvailablePositionsToMove() { return _availablePositionsToMove; }
vector<int>& Queen::GetAvailablePositionsForAttack(){ return _availablePositionsForAttack; }


void Queen::MoveToPos(int iNewPosition) {}
void Queen::MoveToRowCol(int Row, int Col) {}
void Queen::ResetAllAvailablePositions() {}

//=====================================================================================

// Derived class - King definition:
King::King(ChessColor pieceColor, int startPosition){
	_pieceColor = pieceColor;
	_iCurrentPosition = startPosition;
	_strPieceName = "King";
	_chrShortPieceName = 'K';
}

King::King(ChessColor pieceColor, int startRow, int StartCol) {
}

King::~King(){}

vector<int>& King::GetAvailablePositionsToMove() { return _availablePositionsToMove; }
vector<int>& King::GetAvailablePositionsForAttack(){ return _availablePositionsForAttack; }

void King::MoveToPos(int iNewPosition) {}
void King::MoveToRowCol(int Row, int Col) {}
void King::ResetAllAvailablePositions() {}

//=====================================================================================