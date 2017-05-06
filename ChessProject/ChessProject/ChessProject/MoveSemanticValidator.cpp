#include "MoveSemanticValidator.h"
#include "ErrorMove.h"

using namespace IvanChessGame;

MoveSemanticValidator::MoveSemanticValidator(MoveSyntaxValidator* pMoveSyntaxValidator, ChessBoard* pChessBoard){

	_pMoveSyntaxValidator = pMoveSyntaxValidator;
	_pChessBoard = pChessBoard;
}
MoveSemanticValidator::~MoveSemanticValidator() {

}
int MoveSemanticValidator::GetRowSource() {
	return _iRowSource;
}
int MoveSemanticValidator::GetColSource() {
	return _iColSource;
}
int MoveSemanticValidator::GetRowDest() {
	return _iRowDest;
}
int MoveSemanticValidator::GetColDest() {
	return _iColDest;
}


bool MoveSemanticValidator::IsMoveValid() {

	ConvertInternationalNoteToRowCol();

	if (!IsAnyChessPieceInSoucePosition()){ // found no ChessPiece in the Source position
		throw ErrorMove("MoveSemanticValidator: found no Chess Piece in the Source position");
		//return false;
	}

	if (!IsMatchedChessPieceInSoucePosition()) { // the ChessPiece in the Source position is not matched to the one you declared (entered)
		throw ErrorMove("MoveSemanticValidator: the Chess Piece in the Source position is not matched to the one you declared (entered)");
		//return false;
	}

	if (IsDestinationPositionOccupiedByYourChessPiece()){ // are you hitting your own Chess Piece?
		throw ErrorMove("MoveSemanticValidator: You are trying to capture your own ChessPiece");
		//return false;
	}

	if (IsMoveOpponentChessPiece()){ // you tried to move an opponen't ChessPiece
		throw ErrorMove("MoveSemanticValidator: You are moving an opponent's Chess Piece");
		//return false;
	}

	if (!IsTheChessPieceMoveLegitimate()){ // TBD - you tried to move the ChessPiece into incorrect direction like Rook along diagoanal 
		throw ErrorMove("MoveSemanticValidator: You tried to move the ChessPiece into incorrect direction like Rook along diagoanal");
		//return false;
	}

	return true;
}

bool MoveSemanticValidator::IsDestinationPositionOccupiedByYourChessPiece(){

	if (
		(_pChessBoard->GetPieceFromRowCol(_iRowDest, _iColDest) != nullptr) &&
		_pChessBoard->GetPieceFromRowCol(_iRowSource, _iColSource)->GetPieceColor() == _pChessBoard->GetPieceFromRowCol(_iRowDest, _iColDest)->GetPieceColor()
		) {
		//cout << endl << "Hit your own chess piece on the destination position.";
		return true;
	}

	return false;
}
bool MoveSemanticValidator::IsMoveOpponentChessPiece(){

	if (_pChessBoard->GetPieceFromRowCol(_iRowSource, _iColSource)->GetPieceColor() != _pMoveSyntaxValidator->GetGamerColor()){
		//cout << endl << "You moved opponent's chess piece...";
		return true;
	}
	return false;
}

bool MoveSemanticValidator::IsAnyChessPieceInSoucePosition(){

	if (_pChessBoard->GetPieceFromRowCol(_iRowSource, _iColSource) == nullptr) {
		//cout << endl << "Found no chess piece in the entered source position.";
		return false;
	}
	return true;
}

bool MoveSemanticValidator::IsMatchedChessPieceInSoucePosition(){

	ChessPiece* pChessPiece = _pChessBoard->GetPieceFromRowCol(_iRowSource, _iColSource);
	char chrChessPieceName = _pMoveSyntaxValidator->GetChessPieceName().at(1);
	if (pChessPiece->GetShortPieceName() != chrChessPieceName){
		return false;
	}
	return true;
}


bool MoveSemanticValidator::IsTheChessPieceMoveLegitimate(){

	// TBD

	return true;

}

void MoveSemanticValidator::ConvertInternationalNoteToRowCol(){

	string strFrom{ _pMoveSyntaxValidator->GetFrom() };
	string strTo{ _pMoveSyntaxValidator->GetTo() };

	// convert From
	switch (strFrom.at(0))
	{
	case 'a':
		_iColSource = 0;
		break;
	case 'b':
		_iColSource = 1;
		break;
	case 'c':
		_iColSource = 2;
		break;
	case 'd':
		_iColSource = 3;
		break;
	case 'e':
		_iColSource = 4;
		break;
	case 'f':
		_iColSource = 5;
		break;
	case 'g':
		_iColSource = 6;
		break;
	case 'h':
		_iColSource = 7;
		break;
	default:
		_iColSource = -1;
		break;
	}


	_iRowSource = stoi(strFrom.substr(1, 1)) - 1;
	
	// convert To
	switch (strTo.at(0))
	{
	case 'a':
		_iColDest = 0;
		break;
	case 'b':
		_iColDest = 1;
		break;
	case 'c':
		_iColDest = 2;
		break;
	case 'd':
		_iColDest = 3;
		break;
	case 'e':
		_iColDest = 4;
		break;
	case 'f':
		_iColSource = 5;
		break;
	case 'g':
		_iColSource = 6;
		break;
	case 'h':
		_iColDest = 7;
		break;
	default:
		_iColDest = -1;
		break;
	}

	_iRowDest = stoi(strTo.substr(1, 1)) - 1;
}