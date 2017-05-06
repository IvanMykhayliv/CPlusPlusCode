#include "ChessPieceMoveEntry.h"
using namespace IvanChessGame;

ChessPieceMoveEntry::ChessPieceMoveEntry(string strFrom, string strTo, ChessPiece* pChessPiece, ChessPiece* pChessPieceCaptured, ChessColor gamerColor){
	_strFrom = strFrom;
	_strTo = strTo;
	_pChessPiece = pChessPiece;
	_pChessPieceCaptured = pChessPieceCaptured;
	_gamerColor = gamerColor;
}

ChessPieceMoveEntry::~ChessPieceMoveEntry(){

}

string ChessPieceMoveEntry::GetFrom() {
	return _strFrom;
}
string ChessPieceMoveEntry::GetTo() {
	return _strTo;
}
ChessColor ChessPieceMoveEntry::GetGamerColor() {
	return _gamerColor;
}
ChessPiece* ChessPieceMoveEntry::GetChessPiece(){
	return _pChessPiece;
}
ChessPiece* ChessPieceMoveEntry::GetChessPieceCaptured(){
	return _pChessPieceCaptured;
}