// ChessProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Gamer.h"
#include "ChessBoard.h"
#include "ChessGame.h"
#include "MoveSyntaxValidator.h"
#include "ErrorMove.h"

bool IsFullFileNameValid(string);

//using namespace std;
using namespace IvanChessGame;

int _tmain(int argc, _TCHAR* argv[])
{
	
	// Greeting:
	string strSE = "";
	string strFullFileName = "";
	bool bCorrectAnswer = false;

	cout << "Welcome to Ivan Mykhayliv's CHESS GAME !" << endl << endl;
	cout << "Enter S to start the game from begining or" << endl 
		 << "Enter S <full name of a Chessboard's state saved file> or" << endl
		 << "Enter E to Exit...: ";
    
	while (!bCorrectAnswer)
	{
	   getline(cin, strSE);

	   if ((strSE.substr(0,1) == "S") || (strSE == "E")) {
		   bCorrectAnswer = true;
        }
		else {
		   cout << endl << "Wrong answer. Again..." << endl 
			   << "Enter S to start the game from begining or" << endl
			   << "Enter S <full name of a Chessboard's state saved file> or" << endl
			   << "Enter E to Exit...: ";
		   strSE = "";
		   continue;
		};
		if ((strSE == "E") || (strSE == "S")){
			break;
		}
		
		if ((strSE.substr(0, 1) == "S") && (strSE.length() > 2) && (strSE.substr(1, 1) == " ") ){
			strFullFileName = strSE.substr(2);
			bCorrectAnswer = IsFullFileNameValid(strFullFileName);
		}
		else{
			cout << endl << "Wrong answer. Again..." << endl
				<< "Enter S to start the game from begining or" << endl
				<< "Enter S <full name of a Chessboard's state saved file> or" << endl
				<< "Enter E to Exit...: ";
			strSE = "";
			bCorrectAnswer = false;
		}

	}

	cout << endl;

	if (strSE == "E")
	{
		cout << "You requested the Exit. Press Enter key and Good Bye! " << endl;
		getline(cin, strSE);
		return 0;
	}

	cout << "The Ivan's CHESS GAME is about to start..." << endl;
	cout << "There are 2 players:" << endl;
	cout << "1. Peter White who always plays by white chess pieces" << endl;
	cout << "2. Joe Black who always plays by black chess pieces" << endl;

	cout << "Press Enter key to start!" << endl;
	getline(cin, strSE);

	//<TBD>
	
	// initializing Gamers:
	Gamer* pPeterWhite = new Gamer("Peter White", WHITE);
	Gamer* pJoeBlack = new Gamer("Joe Black", BLACK);
	string strGamerNameWhoMovesFirst = pPeterWhite->GetGamerName();
	string strGamerNameWhoMovesNext = pJoeBlack->GetGamerName();

	// initializing the ChessBoard
	ChessBoard* pChessBoard;
	ChessColor ccMoveFirst;
	ChessColor ccMoveNext;
	try{

		pChessBoard = new ChessBoard(strFullFileName);
		ccMoveFirst = pChessBoard->GetWhoMovesNext();
		if (ccMoveFirst == WHITE){
			strGamerNameWhoMovesFirst = pPeterWhite->GetGamerName();
			ccMoveNext = BLACK;
			strGamerNameWhoMovesNext = pJoeBlack->GetGamerName();
		}
		else {
			strGamerNameWhoMovesFirst = pJoeBlack->GetGamerName();
			ccMoveNext = WHITE;
			strGamerNameWhoMovesNext = pPeterWhite->GetGamerName();
		}
	}
	catch (exception e)
	{
		cout << "It looks the file " + strFullFileName + " can't be opened. It may not exist..." << endl;
		cout << "The Chess Game is terminated. You need to restart it. Press Enter to end the game." << endl;
		getline(cin, strSE);
		return 0;
	}

	// initializing ChessGame
	MoveSyntaxValidator MoveSntxVld;

	ChessGame* pChessGame = new ChessGame (pPeterWhite, pJoeBlack, pChessBoard, &MoveSntxVld);

	bool bGameIsOn = true;
	bool bWhoMovesFirstWon = false;
	bool bWhoMovesNextWon = false;
	bool bValidMove = false;

	int iRowSrc = 0;
	int iColSrc = 0;

	int iRowDst = 0;
	int iColDst = 0;

	string line = "";
	vector<int> vIntFromInput;

	//Start Game
	//====================================================================

	while (bGameIsOn)
	{
		if (pChessGame->IsAvailablePosition(ccMoveFirst)){ //aka... is any available position to make a move... If not, then Peter White lost the game
			
			do{
				//First Move (if no saved chessboard's state file, then always Peter White's Move) :
				bValidMove = true;
				line = "";
				// ask to enter a command E, U or <Color><ChessPieceName> source>destination, where source and destination are in FIDE notation
				iRowSrc = 0;
				iColSrc = 0;
				cout << endl << strGamerNameWhoMovesFirst + "'s move:" << endl
					 << "Enter a command 'E' for game exiting or" << endl
					 << "Enter a command 'U' for Undo your last move or" << endl
					 << "Enter a command 'W' <file full name> for saving the current chessboard's state in the file or " << endl
					 << "Enter a move like '<Color><ChessPieceName> source>destination' ";
				getline(cin, line);

				if (line == "E"){
					cout << "Then " + strGamerNameWhoMovesNext + " wins." << endl;
					bGameIsOn = false;
					bWhoMovesNextWon = true;
					continue;
				}

				// Validation the correctess of the strGamerNameWhoMovesFirst's entered command (syntax validation):

				if (line == "U"){
					bValidMove = false;
					cout << strGamerNameWhoMovesFirst + " started the Undo of his last move..." << endl;
					try{
						pChessGame->ChessPieceUndo();
					}
					catch (ErrorMove em)  {
						cout << em.GetErrorMessage() << endl;
					}
					continue;
				}

				MoveSntxVld.ReSetMove(line, ccMoveFirst);
				
				try {
					if (!MoveSntxVld.IsMoveSyntaxValid())
					{
						//bValidMove = false;
						//cout << strGamerNameWhoMovesFirst + ", the syntax validation of your move fails. You entered wrong command. Try it again..." << endl;
						//continue;
					}
				}
				catch (ErrorMove em) {
					cout << em.GetErrorMessage() << endl;
					cout << strGamerNameWhoMovesFirst + ", the syntax validation of your move fails. You entered wrong command. Try it again..." << endl;
					bValidMove = false;
					continue;
				}
			
				// Semantic validationpChessGame now
				try {
					if (!pChessGame->GetMoveSemanticValidator()->IsMoveValid()) {
						//bValidMove = false;
						//cout << strGamerNameWhoMovesFirst + ", the semantic validation of your move fails. You entered wrong command. Try it again..." << endl;
						//continue;
					}
				}
				catch (ErrorMove em) {
					cout << em.GetErrorMessage() << endl;
					cout << strGamerNameWhoMovesFirst + ", the semantic validation of your move fails. You entered wrong command. Try it again..." << endl;
					bValidMove = false;
					continue;
				}
				// Actual move now
				pChessGame->ChessPieceMove();

			} while (!bValidMove && bGameIsOn);
			// Verification of eneterd Source Position (Row, Col) and Destination Positio (Row, Col)
			// call like chessGame->ChessPieceMove(iSourceRow, iSourceCol, iDestRow, iDestCol, WHITE);
		}
		else {
			bGameIsOn = false;
			bWhoMovesNextWon = true;
		}

		if (!bGameIsOn)	{
			continue;
		}

		if (pChessGame->IsAvailablePosition(ccMoveNext)){ //aka... is there any available position to make a move... If not, then Joe Black lost the game
			// JoeBlackMove():
			do{
				//Joe Black's Move :
				bValidMove = true;
				line = "";

				// ask to enter a command E, U or <Color><ChessPieceName> source>destination, where source and destination are in FIDE notation
				iRowSrc = 0;
				iColSrc = 0;
				cout << endl << strGamerNameWhoMovesNext + "'s move:" << endl
					<< "Enter a command 'E' for game exiting or" << endl
					<< "Enter a command 'U' for Undo your last move or" << endl
					<< "Enter a command 'W' <file full name> for saving the current chessboard's state in the file or " << endl
					<< "Enter a move like '<Color><ChessPieceName> source>destination' ";
				getline(cin, line);

				if (line == "E"){
					cout << "Then " + strGamerNameWhoMovesFirst + " wins." << endl;
					bGameIsOn = false;
					bWhoMovesFirstWon = true;
					continue;
				}

				// Validation the correctess of the strGamerNameWhoMovesNext's entered command:

				if (line == "U"){
					bValidMove = false;
					cout << strGamerNameWhoMovesNext + " started the Undo of his last move..." << endl;
					try{
						pChessGame->ChessPieceUndo();
					}
					catch (ErrorMove em)  {
						cout << em.GetErrorMessage() << endl;
					}
					continue;
				}

				MoveSntxVld.ReSetMove(line, ccMoveNext);
				try {
					if (!MoveSntxVld.IsMoveSyntaxValid())
					{
						//bValidMove = false;
						//cout << strGamerNameWhoMovesNext " ", the syntax validation of your move fails. You entered wrong command. Try it again..." << endl;
						//continue;
					}
				}
				catch (ErrorMove em) {
					cout << em.GetErrorMessage() << endl;
					cout << strGamerNameWhoMovesNext  + ", the syntax validation of your move fails.You entered wrong command.Try it again..." << endl;
					bValidMove = false;
					continue;
				}

				// Semantic validationpChessGame now
				try{
					if (!pChessGame->GetMoveSemanticValidator()->IsMoveValid()) {
						//bValidMove = false;
						//cout << strGamerNameWhoMovesNext  + ", the semantic validation of your move fails.You entered wrong command.Try it again..." << endl;
						//continue;
					}
				}
				catch (ErrorMove em) {
					cout << em.GetErrorMessage() << endl;
					cout << strGamerNameWhoMovesNext + ", the semantic validation of your move fails.You entered wrong command.Try it again..." << endl;
					bValidMove = false;
					continue;
				}

				// Actual move now
				try{
					pChessGame->ChessPieceMove();
				}
				catch (ErrorMove em) {
					cout << em.GetErrorMessage() << endl;
				}

			} while (!bValidMove);

			// Verification of eneterd Source Position (Row, Col) and Destination Positio (Row, Col)
			// call like chessGame->ChessPieceMove(iSourceRow, iSourceCol, iDestRow, iDestCol, WHITE);
		}
		else {
			bGameIsOn = false;
			bWhoMovesFirstWon = true;
		}
		// switching first and next moves and Gamers:

		if (ccMoveFirst == WHITE){
			ccMoveFirst = BLACK;
			ccMoveNext = WHITE;
		}
		else
		{
			ccMoveFirst = WHITE;
			ccMoveNext = BLACK;
		}
		string strTemp;
		strTemp = strGamerNameWhoMovesFirst;
		strGamerNameWhoMovesFirst = strGamerNameWhoMovesNext;
		strGamerNameWhoMovesNext = strTemp;
	}

	if (bWhoMovesFirstWon){
		cout << endl << strGamerNameWhoMovesFirst + " won!" << endl;
	}

	if (bWhoMovesNextWon){
		cout << endl << strGamerNameWhoMovesNext + " won!" << endl;
	}

	cout << "Exiting... Press any key and Good Bye! ";
	getline(cin, strSE);

   //======================================================================
	delete pPeterWhite;
	delete pJoeBlack;
	delete pChessBoard;
	delete pChessGame;

	return 0;
}

bool IsFullFileNameValid(string strLogFileName) {
	return true;
}

