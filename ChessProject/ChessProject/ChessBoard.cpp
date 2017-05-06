#include "ChessBoard.h"
using namespace std;
using namespace IvanChessGame;

ChessBoard::ChessBoard(string strFileFullName) {

	_strFullFileName = "";
	_strFullFileName = strFileFullName;
	if (_strFullFileName == "")
	{
	   ChessBoardInitialization();
	}
	else{
		RestoreChessBoardFromFile();
	}
}

ChessBoard::~ChessBoard() {

	for (int i = 0; i < 64; i++)
	{
		if (_arrChessCell[i].GetChessPieceFromCell() != nullptr){
			delete _arrChessCell[i].GetChessPieceFromCell();
		}
	}

}

void ChessBoard::ChessBoardInitialization(){

	/*Creating all the ChessPieces and positioning them on the board*/

	// 1. Set ChessColor for each ChessCell on the ChessBoard
	for (int i = 0; i < 64; i++)
	{
		ChessColor cc = GetCellColorFromPos(i);
		_arrChessCell[i].SetCellColor(cc);
	}

	// 2. Set ChessPieces for each ChessCell on the ChessBoard:
	// 2.1. Set White ChessPieces:

	// Set Row 0 (WR WN	WB	WQ	WK	WB	WN	WR)
	Rook* WR1 = new Rook(WHITE, 0);
	_arrChessCell[0].SetChessPieceInCell(WR1);

	Knight* WN1 = new Knight(WHITE, 1);
	_arrChessCell[1].SetChessPieceInCell(WN1);

	Bishop* WB1 = new Bishop(WHITE, 2);
	_arrChessCell[2].SetChessPieceInCell(WB1);

	Queen* WQ = new Queen(WHITE, 3);
	_arrChessCell[3].SetChessPieceInCell(WQ);

	King* WK = new King(WHITE, 4);
	_arrChessCell[4].SetChessPieceInCell(WK);

	Bishop* WB2 = new Bishop(WHITE, 5);
	_arrChessCell[5].SetChessPieceInCell(WB2);

	Knight* WN2 = new Knight(WHITE, 6);
	_arrChessCell[6].SetChessPieceInCell(WN2);

	Rook* WR2 = new Rook(WHITE, 7);
	_arrChessCell[7].SetChessPieceInCell(WR2);

	// Set Row 1 (WP WP	WP	WP	WP	WP	WP	WP)
	for (int i = 8; i < 16; i++)
	{
		_arrChessCell[i].SetChessPieceInCell(new Pawn(WHITE, i));
	}

	// 2.2. Set Black ChessPieces:

	// Set Row 7 (BR BN	BB	BQ	BK	BB	BN	BR)

	Rook* BR1 = new Rook(BLACK, 56);
	_arrChessCell[56].SetChessPieceInCell(BR1);

	Knight* BN1 = new Knight(BLACK, 57);
	_arrChessCell[57].SetChessPieceInCell(BN1);

	Bishop* BB1 = new Bishop(BLACK, 58);
	_arrChessCell[58].SetChessPieceInCell(BB1);

	Queen* BQ = new Queen(BLACK, 59);
	_arrChessCell[59].SetChessPieceInCell(BQ);

	King* BK = new King(BLACK, 60);
	_arrChessCell[60].SetChessPieceInCell(BK);

	Bishop* BB2 = new Bishop(BLACK, 61);
	_arrChessCell[61].SetChessPieceInCell(BB2);

	Knight* BN2 = new Knight(BLACK, 62);
	_arrChessCell[62].SetChessPieceInCell(BN2);

	Rook* BR2 = new Rook(BLACK, 63);
	_arrChessCell[63].SetChessPieceInCell(BR2);

	// Set Row 6 (BP BP	BP	BP	BP	BP	BP	BP)
	for (int i = 48; i < 56; i++)
	{
		_arrChessCell[i].SetChessPieceInCell(new Pawn(BLACK, i));
	}

	_ccWhoMovesNext = WHITE;
}

void ChessBoard::RestoreChessBoardFromFile(){

	string line;
	ChessColor ccWhoMovesNextColor;
	ChessPiece* pChessPiece;
	string strChessPieceColor;
	ChessColor ccChessPiece;
	string strChessPieceShortName;
	string strRow;
	string strCol;
	int iRow;
	int iCol;
	int iPos;

	//Initialize empty board:
	// 1. Set ChessColor for each ChessCell of the ChessBoard
	for (int i = 0; i < 64; i++)
	{
		ChessColor cc = GetCellColorFromPos(i);
		_arrChessCell[i].SetCellColor(cc);
	}

	ifstream myfile(_strFullFileName);
	if (myfile.is_open()){
		while (getline(myfile, line))
		{
			// extract WhoMoveFirst Color
			if (line.substr(0, 11) == "Next move: "){
				if (line.substr(11) == "WHITE"){
					ccWhoMovesNextColor = WHITE;
				}
				else{
					ccWhoMovesNextColor = BLACK;
				}
				SetWhoMovesNext(ccWhoMovesNextColor);
				continue;
			}

			if (line.substr(0, 5) == "Empty"){
				// 2. Get ChessPiece short Name:
				strChessPieceShortName = line.substr(0, 5); // "Empty"
				// 3. Get ChessPiece position - row:
				strRow = line.substr(6, 1);
				// 3. Get ChessPiece position - col:
				strCol = line.substr(8, 1);
			}
			else{

				// 1. Get ChessPiece Color:
				strChessPieceColor = line.substr(0, 1); // W or B
				if (strChessPieceColor == "W"){
					ccChessPiece = WHITE;
				}
				else{
					ccChessPiece = BLACK;
				}

				// 2. Get ChessPiece short Name:
				strChessPieceShortName = line.substr(1, 1); // R, N, B, Q, K, P
				// 3. Get ChessPiece position - row:
				strRow = line.substr(3, 1);
				// 3. Get ChessPiece position - col:
				strCol = line.substr(5, 1);
			}

			iRow = stoi(strRow);
			iCol = stoi(strCol);
			iPos = iPos = GetPositionFromRowCol(iRow, iCol);
			if (strChessPieceShortName == "Empty") {
				_arrChessCell[iPos].SetChessPieceInCell(nullptr);
			}
			else if (strChessPieceShortName == "R"){
				_arrChessCell[iPos].SetChessPieceInCell(new Rook(ccChessPiece, iPos));
			}
			else if (strChessPieceShortName == "N"){
				_arrChessCell[iPos].SetChessPieceInCell(new Knight(ccChessPiece, iPos));
			}
			else if (strChessPieceShortName == "B"){
				_arrChessCell[iPos].SetChessPieceInCell(new Bishop(ccChessPiece, iPos));
			}
			else if (strChessPieceShortName == "Q"){
				_arrChessCell[iPos].SetChessPieceInCell(new Queen(ccChessPiece, iPos));
			}
			else if (strChessPieceShortName == "K"){
				_arrChessCell[iPos].SetChessPieceInCell(new King(ccChessPiece, iPos));
			}
			else if (strChessPieceShortName == "P"){
				_arrChessCell[iPos].SetChessPieceInCell(new Pawn(ccChessPiece, iPos));
			}
			else {
				// nothing
			}

			//cout << line << '\n';
		}
		myfile.close();
	}
	else {
		throw exception();
		//cout << "Unable to open file" << endl;
	}
}

void ChessBoard::SaveChessBoardToFile(string strFileName, ChessColor ccWhoMoves){

	ofstream myfile(strFileName);
	string strColor;
	if (ccWhoMoves == WHITE){
		strColor = "WHITE";
	}
	else {
		strColor = "BLACK";
	}

	if (myfile.is_open()) 	{
		
		myfile << "Next move: " + strColor << endl;
//		myfile << "This is another line.\n";
	}
	else{

		cout << "Unable to open file " +  strFileName << endl;
	}
	int iPos;
	string strChessPieceColor;
	string strChessPieceShortName;
	string strRow;
	string strCol;

	if (myfile.is_open()){
		for (int iRow = 7; iRow >= 0; iRow--){
			for (int iCol = 0; iCol < 8; iCol++){
				iPos = GetPositionFromRowCol(iRow, iCol);

				strRow = to_string(iRow);
				strCol = to_string(iCol);

				// set Chess Piece color;
				if (_arrChessCell[iPos].GetChessPieceFromCell() != nullptr){
					// Chess Cell is not empty
					if (_arrChessCell[iPos].GetChessPieceFromCell()->GetPieceColor() == WHITE){
						strChessPieceColor = "W";
					}
					else{
						strChessPieceColor = "B";
					}
					strChessPieceShortName = _arrChessCell[iPos].GetChessPieceFromCell()->GetShortPieceName();

					// print as a "WR 1,2" per line:
					myfile << strChessPieceColor + strChessPieceShortName << " " << strRow << "," << strCol << endl;
				}
				else {
					// Chess Cell is empty
					myfile << "Empty" << " " << strRow << "," << strCol << endl;
				}
			}
		}

		myfile.close();
	}
	else{
		cout << "Unable to open file " + strFileName + " again" << endl;
	}
}

int ChessBoard::GetPositionFromRowCol(int Row, int Col){

	return (Row*Dim + Col);
}


int ChessBoard::GetRowFromPos(int Pos) {

	return (Pos / Dim);
}
int ChessBoard::GetColFromPos(int Pos) {
	return Pos%Dim;
}

ChessColor ChessBoard::GetCellColorFromPos(int Position){
	
	int iRow = GetRowFromPos(Position);
	int iCol = GetColFromPos(Position);
	return GetCellColorFromRowCol (iRow, iCol);
}
ChessColor ChessBoard::GetCellColorFromRowCol(int Row, int Col)
{
	if (Row % 2 == 0) {

		if (Col % 2 == 0){
			return BLACK;
		}
		else {
			return WHITE;
		}
	}
	else {

		if (Col % 2 == 0){
			return WHITE;
		}
		else {
			return BLACK;
		}
	}
}


ChessCell* ChessBoard::GetBoard()
{
	return _arrChessCell;
}

ChessPiece* ChessBoard::GetPieceFromPos(int Position)
{
	return _arrChessCell[Position].GetChessPieceFromCell();
}

ChessPiece* ChessBoard::GetPieceFromRowCol(int Row, int Col)
{
	int iPos = GetPositionFromRowCol(Row, Col);
	return _arrChessCell[iPos].GetChessPieceFromCell();
}
int ChessBoard::GetPosFromInternationalNote(string strInternational){

	int iCol;
	int iRow;
	//int iPos;

	// convert strInternational
	switch (strInternational.at(0))
	{
	case 'a':
		iCol = 0;
		break;
	case 'b':
		iCol = 1;
		break;
	case 'c':
		iCol = 2;
		break;
	case 'd':
		iCol = 3;
		break;
	case 'e':
		iCol = 4;
		break;
	case 'f':
		iCol = 5;
		break;
	case 'g':
		iCol = 6;
		break;
	case 'h':
		iCol = 7;
		break;
	default:
		iCol = -1; // error
		break;
	}

	iRow = stoi(strInternational.substr(1, 1)) - 1;

	if (iCol == -1){
		return iCol; //error! Returning -1;
	}

	// convert (iRow, iCol) into iPos:

	return GetPositionFromRowCol(iRow, iCol);
}

ChessColor ChessBoard::GetWhoMovesNext() { return _ccWhoMovesNext; }
void ChessBoard::SetWhoMovesNext(ChessColor ccWhoMovesNext) { _ccWhoMovesNext = ccWhoMovesNext; }


