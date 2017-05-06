#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <stack>
#include "Gamer.h"
#include "ChessBoard.h"
#include "MoveSemanticValidator.h"
#include "MoveSyntaxValidator.h"
#include "ChessPieceMoveEntry.h"
#include "StackAsLinkedList.h"

using namespace std;

namespace IvanChessGame
{	
	class ChessGame
	{
		Gamer* _pGamerOne;
		Gamer* _pGamerTwo;
		ChessBoard* _pChessBoard;
		MoveSyntaxValidator* _pMoveSyntaxValidator;
		MoveSemanticValidator* _pMoveSemanticValidator;
		stack<ChessPieceMoveEntry*> _stackMoves;
		StackAsLinkedList _stackMovesLL;

	public:
		ChessGame(Gamer* pGamerOne, Gamer* pGamerTwo, ChessBoard* pChessBoard, MoveSyntaxValidator* pMoveSyntaxValidator);
		~ChessGame();

		Gamer* GetGamerOne();
		Gamer* GetGamerTwo();
		ChessBoard* GetChessBoard();
		MoveSemanticValidator* GetMoveSemanticValidator();

		bool IsAvailablePosition(ChessColor chessColor);
		bool IsOpponentChessPieceCaptured();
		void ChessPieceMove();
		void ChessPieceUndo(ChessColor);
		stack<ChessPieceMoveEntry*> GetStackMoves();
		StackAsLinkedList GetStackMovesLL();
	private:
		void ChessPieceMovePos(int iFrom, int iTo, ChessColor chessColor);
		void ChessPieceMoveRowCol(int iRowFrom, int iColFrom, int iRowTo, int iColTo, ChessColor chessColor);
	};
}

#endif /*CHESSGAME_H*/