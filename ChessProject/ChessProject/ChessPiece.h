#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <string>
#include <vector>
using namespace std;


#include "ChessColor.h"

namespace IvanChessGame
{
	class ChessPiece
	{
	protected:
		ChessColor _pieceColor;
		int _iCurrentPosition;
		string _strPieceName = "None";
		char _chrShortPieceName;

		vector<int> _availablePositionsToMove;
		vector<int> _availablePositionsForAttack;

	public:
		ChessPiece();
		//~ChessPiece();

// Getters:
		virtual ChessColor GetPieceColor();
		virtual string GetPieceName();
		virtual char GetShortPieceName();
		virtual int GetCurrentPosition();
		virtual void SetCurrentPosition(int);

		virtual vector<int>& GetAvailablePositionsToMove();
		virtual vector<int>& GetAvailablePositionsForAttack();

		virtual void MoveToPos(int iNewPosition);
		virtual void MoveToRowCol(int iNewRow, int iNewCol);

		virtual void ResetAllAvailablePositions();

	};

	class Pawn:public ChessPiece
	{

	  public:
		Pawn(ChessColor pieceColor, int startPosition);
		Pawn(ChessColor pieceColor, int startRow, int StartCol);
		~Pawn();

		vector<int>& GetAvailablePositionsToMove();
		vector<int>& GetAvailablePositionsForAttack();

		void MoveToPos(int iNewPosition);
		void MoveToRowCol(int Row, int Col);
		void ResetAllAvailablePositions();
	};

	class Bishop:public ChessPiece
	{

	public:

		Bishop(ChessColor pieceColor, int startPosition);
		Bishop(ChessColor pieceColor, int startRow, int StartCol);
		~Bishop();

		vector<int>& GetAvailablePositionsToMove();
		vector<int>& GetAvailablePositionsForAttack();

		void MoveToPos(int iNewPosition);
		void MoveToRowCol(int Row, int Col);
		void ResetAllAvailablePositions();
	};

	class Rook:public ChessPiece
	{

	public:
		Rook(ChessColor pieceColor, int startPosition);
		Rook(ChessColor pieceColor, int startRow, int StartCol);
		~Rook();

		vector<int>& GetAvailablePositionsToMove();
		vector<int>& GetAvailablePositionsForAttack();

		void MoveToPos(int iNewPosition);
		void MoveToRowCol(int Row, int Col);
		void ResetAllAvailablePositions();
	};

	class Knight:public ChessPiece
	{

	public:
		Knight(ChessColor pieceColor, int startPosition);
		Knight(ChessColor pieceColor, int startRow, int StartCol);
		~Knight();

		vector<int>& GetAvailablePositionsToMove();
		vector<int>& GetAvailablePositionsForAttack();

		void MoveToPos(int iNewPosition);
		void MoveToRowCol(int Row, int Col);
		void ResetAllAvailablePositions();
	};

	class Queen:public ChessPiece
	{
		
	public:
		Queen(ChessColor pieceColor, int startPosition);
		Queen(ChessColor pieceColor, int startRow, int StartCol);
		~Queen();

		vector<int>& GetAvailablePositionsToMove();
		vector<int>& GetAvailablePositionsForAttack();

		void MoveToPos(int iNewPosition);
		void MoveToRowCol(int Row, int Col);
		void ResetAllAvailablePositions();
	};

	class King:public ChessPiece
	{

	public:
		King(ChessColor pieceColor, int startPosition);
		King(ChessColor pieceColor, int startRow, int StartCol);
		~King();	

		vector<int>& GetAvailablePositionsToMove();
		vector<int>& GetAvailablePositionsForAttack();

		void MoveToPos(int iNewPosition);
		void MoveToRowCol(int Row, int Col);
		void ResetAllAvailablePositions();
	};
}

#endif /*CHESSPIECE_H*/