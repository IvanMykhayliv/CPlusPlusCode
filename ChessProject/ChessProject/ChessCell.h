#ifndef CHESSCELL_H
#define CHESSCELL_H

#include "ChessPiece.h"

namespace IvanChessGame
{

	class ChessCell
	{
		ChessColor _cellColor;
		ChessPiece* _pChessPiece = nullptr;

	public:
		ChessCell();
		ChessCell(ChessColor cellColor);
		~ChessCell();

		ChessPiece* GetChessPieceFromCell();
		void SetChessPieceInCell(ChessPiece* pChessPiece);
		void RemoveChessPieceFromTheCell();

		ChessColor GetCellColor();
		void SetCellColor(ChessColor chessColor);
	};
}

#endif /*CHESSCELL_H*/