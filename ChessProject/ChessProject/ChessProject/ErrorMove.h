#ifndef ERRORMOVE_H
#define ERRORMOVE_H
#include <string>

using namespace std;
namespace IvanChessGame {

	class ErrorMove{
		string _strErrorMessage;
	public:
		ErrorMove(string);
		~ErrorMove();
		string GetErrorMessage();
	};

}
#endif /*ERRORMOVE_H*/