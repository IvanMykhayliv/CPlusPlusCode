#ifndef LLNODE_H
#define LLNODE_H
#include <iostream>
#include "ChessPieceMoveEntry.h"

namespace IvanChessGame {

	class LLNode {
	    ChessPieceMoveEntry* _pChessPieceMoveEntry; //core Data
		LLNode* _pLLNodeNext;
	public:
		LLNode();
		~LLNode();
		ChessPieceMoveEntry* GetPchessPieceMoveEntry();		// get core Data
		void SetPchessPieceMoveEntry(ChessPieceMoveEntry*); // set core Data. Can be set over constructor
		LLNode* GetPLLNodeNext();							// get pointer to Next Node
		void SetPLLNodeNext(LLNode*);						// set pointer to Next Node
	};
}
#endif //LLNODE_H