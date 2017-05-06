#ifndef CHESSPIECEMOVEENTRY_H
#define CHESSPIECEMOVEENTRY_H

#include <string>
#include "ChessPiece.h"
using namespace std;

namespace IvanChessGame
{
	class ChessPieceMoveEntry {

		string _strFrom;
		string _strTo;
		ChessPiece* _pChessPiece;
		ChessPiece* _pChessPieceCaptured;
		ChessColor _gamerColor;

	public:

		ChessPieceMoveEntry(string strFrom, string strTo, ChessPiece* pChessPiece, ChessPiece* pChessPieceCaptured, ChessColor gamerColor);
		~ChessPieceMoveEntry();
		string GetFrom();
		string GetTo();
		ChessColor GetGamerColor();
		ChessPiece* GetChessPiece();
		ChessPiece* GetChessPieceCaptured();
	};
}

#endif /*CHESSPIECEMOVEENTRY_H*/