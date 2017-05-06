#ifndef MOVESEMANTICVALIDATOR_H
#define MOVESEMANTICVALIDATOR_H

#include "MoveSyntaxValidator.h"
#include "ChessBoard.h"

namespace IvanChessGame
{
	class MoveSemanticValidator {

	public:
		MoveSemanticValidator(MoveSyntaxValidator* pMoveSyntaxValidator, ChessBoard* pChessBoard);
		~MoveSemanticValidator();
		bool IsMoveValid();
		int GetRowSource();
		int GetColSource();
		int GetRowDest();
		int GetColDest();

	private:
		MoveSyntaxValidator* _pMoveSyntaxValidator;
		ChessBoard* _pChessBoard;

		int _iSourcePos;
		int _iDestPos;

		int _iRowSource;
		int _iColSource;

		int _iRowDest;
		int _iColDest;

		bool IsDestinationPositionOccupiedByYourChessPiece();
		bool IsMoveOpponentChessPiece();
		bool IsTheChessPieceMoveLegitimate();
		bool IsAnyChessPieceInSoucePosition();
		bool IsMatchedChessPieceInSoucePosition();

		void ConvertInternationalNoteToRowCol();
	};
}
#endif /*MOVESEMANTICVALIDATOR_H*/