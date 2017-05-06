#include "LLNode.h"

using namespace IvanChessGame;

LLNode::LLNode(){ _pChessPieceMoveEntry = nullptr;  _pLLNodeNext = nullptr; }
LLNode::~LLNode(){}
//Get core Data
ChessPieceMoveEntry* LLNode::GetPchessPieceMoveEntry(){ return _pChessPieceMoveEntry; }

//Set core Data. Can be set over constructor
void LLNode::SetPchessPieceMoveEntry(ChessPieceMoveEntry* pChessPieceMoveEntry) { _pChessPieceMoveEntry = pChessPieceMoveEntry; }

//Get pointer to Next Node
LLNode* LLNode::GetPLLNodeNext(){ return _pLLNodeNext; }

//Set pointer to Next Node
void LLNode::SetPLLNodeNext(LLNode* pLLNodeNext) { _pLLNodeNext = pLLNodeNext; }
