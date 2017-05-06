#include "ErrorMove.h"
using namespace std;
using namespace IvanChessGame;

ErrorMove::ErrorMove(string strErrorMessage) { _strErrorMessage = strErrorMessage; }
ErrorMove::~ErrorMove(){}
string ErrorMove::GetErrorMessage (){ return _strErrorMessage; }
