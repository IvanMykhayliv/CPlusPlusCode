#include "ChessCell.h"
using namespace IvanChessGame;

ChessCell::ChessCell(){}
ChessCell::ChessCell(ChessColor cellColor){ 
	_cellColor = cellColor; 
}

ChessCell::~ChessCell() {

}

// Getter & Setter for a ChessPiece
ChessPiece* ChessCell::GetChessPieceFromCell(){ return _pChessPiece; };
void ChessCell::SetChessPieceInCell(ChessPiece* pChessPiece) { _pChessPiece = pChessPiece; };
void ChessCell::RemoveChessPieceFromTheCell(){
	if (_pChessPiece != nullptr){
		delete _pChessPiece;
		_pChessPiece = nullptr;
	}
}

// Getter & Setter for a Cell's Color
ChessColor ChessCell::GetCellColor(){ return _cellColor; };
void ChessCell::SetCellColor(ChessColor chessColor) { _cellColor = chessColor; }
