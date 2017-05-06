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

	if (!IsAnyChessPieceInSoucePosition()){ //Found no ChessPiece in the Source position
		throw ErrorMove("MoveSemanticValidator: Found no Chess Piece in the Source position");
		//return false;
	}

	if (!IsMatchedChessPieceInSoucePosition()) { //The ChessPiece in the Source position doesn't match the declared one
		throw ErrorMove("MoveSemanticValidator: the Chess Piece in the Source position doesn't match the declared one");
		//return false;
	}

	if (IsDestinationPositionOccupiedByYourChessPiece()){ //Are you hitting your own ChessPiece?
		throw ErrorMove("MoveSemanticValidator: You are trying to capture your own ChessPiece");
		//return false;
	}

	if (IsMoveOpponentChessPiece()){ //You tried to move an opponent's ChessPiece
		throw ErrorMove("MoveSemanticValidator: You are trying to move an opponent's ChessPiece");
		//return false;
	}

	if (!IsTheChessPieceMoveLegitimate()){ //TBD - You tried to move the ChessPiece incorrectly, like a Rook diagonally
		throw ErrorMove("MoveSemanticValidator: You tried to move the ChessPiece incorrectly");
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
		//cout << endl << "You moved the opponent's chess piece.";
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

	//Convert From
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
	
	//Convert To
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