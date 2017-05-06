#ifndef CHESSBOARD_H
#define CHESSBOARD_H

/*
Our internal ChessBoard topology:

Row:
|
V

7...W B W B W B W B  
6...B W B W B W B W
5...W B W B W B W B
4...B W B W B W B W 
3...W B W B W B W B 
2...B W B W B W B W
1...W B W B W B W B
0...B W B W B W B W
    . . . . . . . .
    0 1 2 3 4 5 6 7  <- Col:


Our external ChessBoard topology is:

8...W B W B W B W B
7...B W B W B W B W
6...W B W B W B W B
5...B W B W B W B W
4...W B W B W B W B
3...B W B W B W B W
2...W B W B W B W B
1...B W B W B W B W
    . . . . . . . .
    a b c d e f g h

Our one-dimentional indexing for ChessCells is like that:
    

	56 57 58 59 60 61 62 63
	48 49 50 51 52 53 54 55
	40 41 42 43 44 45 46 47
	32 33 34 35 36 37 38 39
	24 25 26 27 28 29 30 31
    16 17 18 19 20 21 22 23
	08 09 10 11 12 13 14 15
	00 01 02 03 04 05 06 07

*/

#include <fstream>
#include <string>
#include <iostream>
#include "ChessCell.h"

namespace IvanChessGame
{
	class ChessBoard
	{		
		const int Dim = 8;

		int _iRow, iCol, iPos;
		ChessCell _arrChessCell[64];
		ChessColor _ccWhoMovesNext;
		string _strFullFileName;

	public:
		ChessBoard(string strFullFileName="");
		~ChessBoard();

		int GetPositionFromRowCol(int Row, int Col);
		int GetRowFromPos(int Pos);
		int GetColFromPos(int Pos);
		int GetPosFromInternationalNote(string);

		ChessColor GetCellColorFromPos(int Position);
		ChessColor GetCellColorFromRowCol(int Row, int Col);
		ChessColor GetWhoMovesNext();
		void SetWhoMovesNext(ChessColor);
		
		ChessCell* GetBoard();
		ChessPiece* GetPieceFromPos(int Position);
		ChessPiece* GetPieceFromRowCol(int Row, int Col);

		void SaveChessBoardToFile(string, ChessColor);

	private:
		void SetColorForEachCell();
		void ChessBoardInitialization();
		void RestoreChessBoardFromFile();
	};
}

#endif //CHESSBOARD_H
