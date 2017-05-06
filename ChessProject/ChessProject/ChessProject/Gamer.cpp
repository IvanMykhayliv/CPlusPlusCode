#include "Gamer.h"
using namespace IvanChessGame;

//Gamer::Gamer() {}
Gamer::Gamer(string strGamerName, ChessColor gamerColor) {
	_strGamerName = strGamerName;
	_gamerColor = gamerColor;
}
Gamer::~Gamer(){}
string Gamer::GetGamerName() { return _strGamerName; }
ChessColor Gamer::GetGamerColor(){ return _gamerColor; }