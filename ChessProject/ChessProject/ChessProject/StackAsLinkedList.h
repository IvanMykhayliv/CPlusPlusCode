#ifndef STACKASLINKEDLIST_H
#define STACKASLINKEDLIST_H

#include "LLNode.h"

namespace IvanChessGame {
	class StackAsLinkedList{
		LLNode* _pLLNodeTop;	// pointer on Top LLNode
		int _iCount;			//number of LLNodes in the linked list
		//int _iMaxnum;
		//ChessPieceMoveEntry* _pStackData;
	public:
		StackAsLinkedList();
		~StackAsLinkedList();
		void Push(ChessPieceMoveEntry*);	// the core Data is actually added within a wrapped LLNode
		void Pop();
		ChessPieceMoveEntry* GetDataFromTop();
		void Print();
		int GetStackSize();
	};
}
#endif //STACKASLINKEDLIST_H