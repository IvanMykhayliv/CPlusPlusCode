#include "ChessGame.h"
#include "ChessBoard.h"
#include "ErrorMove.h"
#include <iostream>

using namespace std;
using namespace IvanChessGame;

ChessGame::ChessGame(Gamer* pGamerOne, Gamer* pGamerTwo, ChessBoard* pChessBoard, MoveSyntaxValidator* pMoveSyntaxValidator) {
	_pGamerOne = pGamerOne;
	_pGamerTwo = pGamerTwo;
	_pChessBoard = pChessBoard;
	_pMoveSyntaxValidator = pMoveSyntaxValidator;
	_pMoveSemanticValidator = new MoveSemanticValidator(_pMoveSyntaxValidator, _pChessBoard);
}
ChessGame::~ChessGame()  {
	if (_pMoveSemanticValidator != nullptr) {
		delete _pMoveSemanticValidator;
	}
	// TBD: remove ChessPieceMoveEntries from the stack...
}
Gamer* ChessGame::GetGamerOne() { return _pGamerOne; }
Gamer* ChessGame::GetGamerTwo() { return _pGamerTwo; }
ChessBoard* ChessGame::GetChessBoard() { return _pChessBoard; }
MoveSemanticValidator* ChessGame::GetMoveSemanticValidator() { return _pMoveSemanticValidator; }

stack<ChessPieceMoveEntry*> ChessGame::GetStackMoves(){
	return _stackMoves;
}

StackAsLinkedList ChessGame::GetStackMovesLL(){
	return _stackMovesLL;
}

bool ChessGame::IsAvailablePosition(ChessColor chessColor) {
	
	//TBD:
	// 1) scan all ChessPieces of the given chessColor within  ChessBoard through each ChessCell;
	// 2) if the list<int> (either _availablePositionsToMove or _availablePositionsForAttack)
	//     contains Positions, then return true
	//    otherwise - false   

	return true; // just for compiler satisfaction;
}

bool ChessGame::IsOpponentChessPieceCaptured(){
	if (
		(_pChessBoard->GetPieceFromRowCol(_pMoveSemanticValidator->GetRowDest(), _pMoveSemanticValidator->GetColDest()) != nullptr) &&
		_pChessBoard->GetPieceFromRowCol(_pMoveSemanticValidator->GetRowSource(), _pMoveSemanticValidator->GetColSource())->GetPieceColor() != _pChessBoard->GetPieceFromRowCol(_pMoveSemanticValidator->GetRowDest(), _pMoveSemanticValidator->GetColDest())->GetPieceColor()
		) {
		//cout << endl << "Hit opponent's chess piece on the destination position.";
		return true;
	}
	return false;
}

void ChessGame::ChessPieceMove() {
	int iRowSource{ _pMoveSemanticValidator->GetRowSource() };
	int iColSource{ _pMoveSemanticValidator->GetColSource() };

	int iRowDest{ _pMoveSemanticValidator->GetRowDest() };
	int iColDest{ _pMoveSemanticValidator->GetColDest() };
	ChessColor chessColor = _pChessBoard->GetPieceFromRowCol(iRowSource, iColSource)->GetPieceColor();
	ChessPieceMoveRowCol(iRowSource, iColSource, iRowDest, iColDest, chessColor);
}

void ChessGame::ChessPieceMoveRowCol(int iRowFrom, int iColFrom, int iRowTo, int iColTo, ChessColor chessColor)
{
	ChessPieceMovePos(_pChessBoard->GetPositionFromRowCol(iRowFrom, iColFrom), _pChessBoard->GetPositionFromRowCol(iRowTo, iColTo), chessColor);
}

void ChessGame::ChessPieceMovePos(int iFrom, int iTo, ChessColor chessColor){

	string strFrom = _pMoveSyntaxValidator->GetFrom();
	string strTo = _pMoveSyntaxValidator->GetTo();
	ChessColor gamerColor = _pMoveSyntaxValidator->GetGamerColor();
	ChessPiece* pChessPiece = _pChessBoard->GetPieceFromPos(iFrom);
	ChessPiece* pChessPieceCaptured = _pChessBoard->GetPieceFromPos(iTo);
	
	pChessPiece->SetCurrentPosition(iTo);
	if (pChessPieceCaptured != nullptr){
		pChessPieceCaptured->SetCurrentPosition(-1); // no current position for a captured ChessPiece... 
		ChessColor ccCaptured = pChessPieceCaptured->GetPieceColor();
		string strCapturedColor;
		if (ccCaptured == WHITE){
			strCapturedColor = "WHITE";
		}
		else {
			strCapturedColor = "BLACK";
		}
		cout << strCapturedColor + " " + pChessPieceCaptured->GetPieceName() + " captured!" << endl;
	}

	ChessPieceMoveEntry* pChessPieceMoveEntry = new ChessPieceMoveEntry(strFrom, strTo, pChessPiece, pChessPieceCaptured, gamerColor);
	//_stackMoves.push(pChessPieceMoveEntry);
	_stackMovesLL.Push(pChessPieceMoveEntry);

	_pChessBoard->GetBoard()[iTo].SetChessPieceInCell(pChessPiece);
	_pChessBoard->GetBoard()[iFrom].SetChessPieceInCell(nullptr);

	//set Who Moves Next (it needs for restoring Game from file)  
	if (gamerColor == WHITE) {
		_pChessBoard->SetWhoMovesNext(BLACK);
	}
	else{
		_pChessBoard->SetWhoMovesNext(WHITE);
	}
}
void ChessGame::ChessPieceUndo(ChessColor ccRequestor){

	int iPos;

	//if (_stackMoves.empty()) {
	//	throw ErrorMove("ChessPieceUndo: Undo stack is empty");
	//	//return;
	//}
	if (_stackMovesLL.GetStackSize() == 0 ) {
		throw ErrorMove("ChessPieceUndo: Undo stack is empty");
		//return;
	}
	//if (_stackMoves.size() % 2 != 0) {
	//	// something is wrong! The size must be always even
	//	throw ErrorMove("ChessPieceUndo: The size must be always even. You can Undo only if you made any move in this game before...");
	//	//return;
	//}
	//ChessPieceMoveEntry* pUndo1 = _stackMoves.top();
	//_stackMoves.pop();

	ChessPieceMoveEntry* pUndo1 = _stackMovesLL.GetDataFromTop();
	_stackMovesLL.Pop();

	//1. Restoring previous opponent's position per pUndo1
	string strFrom = pUndo1->GetFrom();
	string strTo = pUndo1->GetTo();
	ChessColor color = pUndo1->GetGamerColor();
	ChessPiece* pChessPiece = pUndo1->GetChessPiece();
	ChessPiece* pChessPieceCaptured = pUndo1->GetChessPieceCaptured();

	if (pChessPieceCaptured != nullptr){
		// return the captured ChessPiece to its previous positon:
		// 1. Get internal position from external strTo
		iPos = _pChessBoard->GetPosFromInternationalNote(strTo);
		if (iPos != -1) {
			// 2. Update the captured ChessPiece's internal position
			pChessPieceCaptured->SetCurrentPosition(iPos);
			// 3. Set the ChessBoard's cell for captured ChessPiece
			_pChessBoard->GetBoard()[iPos].SetChessPieceInCell(pChessPieceCaptured);
		}
		else {
			//error!
		}
	}
	// return the ChessPiece to  its previous positon
	// 1. Get internal position from external strFrom
	iPos = _pChessBoard->GetPosFromInternationalNote(strFrom);
	if (iPos != -1) {
		// 2. Update the captured ChessPiece's internal position
		pChessPiece->SetCurrentPosition(iPos);
		// 3. Set the ChessBoard's cell for ChessPiece
		_pChessBoard->GetBoard()[iPos].SetChessPieceInCell(pChessPiece);
	}
	else {
		//error!
	}

	if (pChessPieceCaptured == nullptr){
		// clean-up To cell
		iPos = _pChessBoard->GetPosFromInternationalNote(strTo);
		_pChessBoard->GetBoard()[iPos].SetChessPieceInCell(nullptr);

	}

	//if (_stackMoves.empty()) {
	//	//throw ErrorMove("ChessPieceUndo: Undo stack is empty");
	//	return;
	//}
	if (_stackMovesLL.GetStackSize() == 0) {
		//throw ErrorMove("ChessPieceUndo: Undo stack is empty");
		return;
	}
	//ChessPieceMoveEntry* pUndo2 = _stackMoves.top();
	//_stackMoves.pop();

	ChessPieceMoveEntry* pUndo2 = _stackMovesLL.GetDataFromTop();
	_stackMovesLL.Pop();

	// 2. Restoring your own previous position per pUndo2
	strFrom = pUndo2->GetFrom();
	strTo = pUndo2->GetTo();
	color = pUndo2->GetGamerColor();
	pChessPiece = pUndo2->GetChessPiece();
	pChessPieceCaptured = pUndo2->GetChessPieceCaptured();

	if (pChessPieceCaptured != nullptr){
		// return the captured ChessPiece to its previous positon:
		// 1. Get internal position from external strTo
		iPos = _pChessBoard->GetPosFromInternationalNote(strTo);
		if (iPos != -1) {
			// 2. Update the captured ChessPiece's internal position
			pChessPieceCaptured->SetCurrentPosition(iPos);
			// 3. Set the ChessBoard's cell for captured ChessPiece
			_pChessBoard->GetBoard()[iPos].SetChessPieceInCell(pChessPieceCaptured);
		}
		else {
			//error!
		}
	}
	// return the ChessPiece to  its previous positon
	// 1. Get internal position from external strFrom
	iPos = _pChessBoard->GetPosFromInternationalNote(strFrom);
	if (iPos != -1) {
		// 2. Update the captured ChessPiece's internal position
		pChessPiece->SetCurrentPosition(iPos);
		// 3. Set the ChessBoard's cell for ChessPiece
		_pChessBoard->GetBoard()[iPos].SetChessPieceInCell(pChessPiece);
	}
	else {
		//error!
	}

	if (pChessPieceCaptured == nullptr){
		// clean-up To cell
		iPos = _pChessBoard->GetPosFromInternationalNote(strTo);
		_pChessBoard->GetBoard()[iPos].SetChessPieceInCell(nullptr);
	}
}