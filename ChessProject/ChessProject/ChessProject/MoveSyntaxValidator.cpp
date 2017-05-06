#include "MoveSyntaxValidator.h"
#include "ErrorMove.h"

using namespace IvanChessGame;

// the expected syntax is like that "WP e2>e4"
//							index:	 01234567  

MoveSyntaxValidator::MoveSyntaxValidator() {
	_strMove = "";
	_strFrom = "";
	_strTo = "";
	_strChessPieceName = "";
}
MoveSyntaxValidator::~MoveSyntaxValidator() {

}

void MoveSyntaxValidator::ReSetMove(string strMove, ChessColor gamerColor) {
	_strMove = strMove;
	_strFrom = "";
	_strTo = "";
	_gamerColor = gamerColor;
}
bool MoveSyntaxValidator::IsMoveSyntaxValid() {
	if (_strMove == ""){
		throw ErrorMove("MoveSyntaxValidator: nothing was entered...");
		//return false;
	}

	if (_strMove == "U"){
		return true;
	}

	if (_strMove.length() != g_iLenghth){
		throw ErrorMove("MoveSyntaxValidator: The lenght of the entered command is not 8");
		//return false;
	}

	if (_strMove.at(2) != ' ') {
		throw ErrorMove("MoveSyntaxValidator: In the entered command must be space in the 3rd position");
		//return false;
	}


	if (_strMove.at(5) != g_separator) {
		throw ErrorMove("MoveSyntaxValidator: In the entered command must be separator '>' in the 6th position");
		//return false;
	}
	
	string strChessPieceName = _strMove.substr(0, 2);
	bool bFound = false;

	// checking entered Chess Pices Name...
	for (int i = 0; i < 12; i++) {
		if (g_arrChessPieceName[i] == strChessPieceName)
		{
			bFound = true;
			break;
		}
	}

	if (!bFound){
		throw ErrorMove("MoveSyntaxValidator: In the entered command is unknown Chess Piece name");
		//return false;
	}

	// checking entered chessboard's column name if it is one of out 'a', 'b', 'c', 'd', ...etc.
	bFound = false;

	// source column should be from a to h
	for (int i = 0; i < 8; i++){
		if (_strMove.at(3) == g_arr_Col[i]){
			bFound = true;
			break;
		}
	}

	if (!bFound){
		throw ErrorMove("MoveSyntaxValidator: In the entered command is the source column is NOT from 'a' to 'h'");
		//return false;
	}

	bFound = false;

	// destination column should be from a to h
	for (int i = 0; i < 8; i++){
		if (_strMove.at(6) == g_arr_Col[i]){
			bFound = true;
			break;
		}
	}

	if (!bFound){
		throw ErrorMove("MoveSyntaxValidator: In the entered command is the destination column is NOT from 'a' to 'h'");
		//return false;
	}

	bFound = false;

	// checking entered chessboard's row number if it is one of out '1', '2', '3', '4', ...etc.
	// source:
	for (int i = 0; i < 8; i++){
		if (_strMove.at(4) == g_arrRow[i]){
			bFound = true;
			break;
		}
	}

	if (!bFound){
		throw ErrorMove("MoveSyntaxValidator: In the entered command is the source row is NOT from '1' to '8'");
		//return false;
	}

	bFound = false;

	// Destination Row should be from 1 to 8
	for (int i = 0; i < 8; i++){
		if (_strMove.at(7) == g_arrRow[i]){
			bFound = true;
			break;
		}
	}
	if (!bFound){
		throw ErrorMove("MoveSyntaxValidator: In the entered command is the destination row is NOT from '1' to '8'");
		//return false;
	}

	// You should not to move an opponent's ChessPiece
	if ((_gamerColor == WHITE) && (_strMove.at(0) == 'B')) {
		throw ErrorMove("MoveSyntaxValidator: In the entered command you declared the opponent's color");
		//return false;
	}

	if ((_gamerColor == BLACK) && (_strMove.at(0) == 'W')) {
		throw ErrorMove("MoveSyntaxValidator: In the entered command you declared the opponent's color");
		//return false;
	}

	// Destination and Source positions should be different
	if (_strMove.substr(3, 2) == _strMove.substr(6, 2)){
		throw ErrorMove("MoveSyntaxValidator: In the entered command the Destination and Source positions must be different");
		//return false;
	}

	_strFrom = _strMove.substr(3, 2);
	_strTo = _strMove.substr(6,2);
	_strChessPieceName = _strMove.substr(0, 2);

	return true;
}
string MoveSyntaxValidator::GetFrom() const {
	
	return _strFrom;

}
string MoveSyntaxValidator::GetTo() const {
	
	return _strTo;
}

string MoveSyntaxValidator::GetChessPieceName() const {
	return _strChessPieceName;
}

ChessColor MoveSyntaxValidator::GetGamerColor() const {
	return _gamerColor;
}