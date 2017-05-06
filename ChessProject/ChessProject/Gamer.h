
#ifndef GAMER_H
#define GAMER_H

#include <string>
using namespace std;

#include "ChessColor.h"

namespace IvanChessGame
{
	class Gamer
	{
		string _strGamerName;
		ChessColor _gamerColor;
	public:
		//Gamer();
		Gamer(string strGamerName, ChessColor gamerColor);
		~Gamer();

		string GetGamerName();
		ChessColor GetGamerColor();
	};
}

#endif /* GAMER_H */