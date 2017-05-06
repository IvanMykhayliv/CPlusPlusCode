#ifndef MOVESYNTAXVALIDATOR_H
#define MOVESYNTAXVALIDATOR_H

#include <string>
#include "ChessColor.h"

using namespace std;
namespace IvanChessGame
{
	// Global Constants for Move Syntax Validation:
	
	string const g_arrChessPieceName[12] = { "WK", "WQ", "WR", "WN", "WB", "WP", "BK", "BQ", "BR", "BN", "BB", "BP" };
	char const g_arr_Col[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
	char const  g_arrRow[8] = { '1', '2', '3', '4', '5', '6', '7', '8' };
	char const  g_undo{ 'U' };
	char const g_leftPr{ '(' };
	char const  g_rightPr{ ')' };
	char const g_separator{ '>' };
	int  const g_iLenghth{ 8 };
	
	//The expected syntax is like this: "WP e2>e4"
	//							index:	 01234567  
	class MoveSyntaxValidator{

		string _strMove;
		string _strChessPieceName;
		string _strFrom;
		string _strTo;
		ChessColor _gamerColor;

	public:
		MoveSyntaxValidator();
		~MoveSyntaxValidator();

		void ReSetMove(string strMove, ChessColor gamerColor);
		bool IsMoveSyntaxValid();
		string GetFrom() const;
		string GetTo() const;
		string GetChessPieceName() const;
		ChessColor GetGamerColor() const;
	};
}

#endif /*MOVESYNTAXVALIDATOR_H*/