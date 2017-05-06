#ifndef STACKASLINKEDLIST_H
#define STACKASLINKEDLIST_H

#include "LLNode.h"

namespace IvanChessGame {
	class StackAsLinkedList{
		LLNode* _pLLNodeTop;	//Pointer on Top LLNode
		int _iCount;			//Number of LLNodes in the linked list
		//int _iMaxnum;
		//ChessPieceMoveEntry* _pStackData;
	public:
		StackAsLinkedList();
		~StackAsLinkedList();
		void Push(ChessPieceMoveEntry*);	//The core Data is actually added within a wrapped LLNode
		void Pop();
		ChessPieceMoveEntry* GetDataFromTop();
		void Print();
		int GetStackSize();
	};
}
#endif //STACKASLINKEDLIST_H