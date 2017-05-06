#include "StackAsLinkedList.h"
using namespace std;
using namespace IvanChessGame;

StackAsLinkedList::StackAsLinkedList(){ _iCount = 0; _pLLNodeTop = nullptr; }
StackAsLinkedList::~StackAsLinkedList(){}
void StackAsLinkedList::Push(ChessPieceMoveEntry* pChessPieceMoveEntry) {
	LLNode* pNewTopLLNode = new LLNode();
	if (_pLLNodeTop == nullptr)
	{
		pNewTopLLNode->SetPchessPieceMoveEntry(pChessPieceMoveEntry);	// set core Data within new Node
		pNewTopLLNode->SetPLLNodeNext(nullptr);
		_pLLNodeTop = pNewTopLLNode;
		_iCount++;
	}
	else
	{
		pNewTopLLNode->SetPchessPieceMoveEntry(pChessPieceMoveEntry);	// set core Data within new Node
		pNewTopLLNode->SetPLLNodeNext(_pLLNodeTop); 
		_pLLNodeTop = pNewTopLLNode;
		_iCount++;
	}
}

ChessPieceMoveEntry* StackAsLinkedList::GetDataFromTop(){
	if (_pLLNodeTop == nullptr){
		//cout << "Stack is empty";
		return nullptr;
	}
	return _pLLNodeTop->GetPchessPieceMoveEntry();
}

void StackAsLinkedList::Pop(){
	if (_pLLNodeTop == nullptr)
		cout << "nothing to pop";
	else
	{
		LLNode* old = _pLLNodeTop;
		_pLLNodeTop = _pLLNodeTop->GetPLLNodeNext();
		_iCount--;
		delete(old);
	}
}
void StackAsLinkedList::Print(){
	ChessPiece* chp;
	LLNode* temp;
	temp = _pLLNodeTop;

	while (temp != nullptr)
	{
		chp = temp->GetPchessPieceMoveEntry()->GetChessPiece();
		if (chp != nullptr){
		   cout << chp->GetShortPieceName() << ",";
		}
		else{
		   cout << "." << ",";
		}
		temp = temp->GetPLLNodeNext();
	}
	cout << endl;
}

int StackAsLinkedList::GetStackSize() { return _iCount; }