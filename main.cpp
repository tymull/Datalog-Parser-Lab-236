
#include <iostream>
#include "LexicalAnalyzer.h"
#include "Parser.h"
using namespace std;

int main(int argc, char* argv[])
{
	LexicalAnalyzer lexi(argv[1]);
	//cout << lexi.scan();
	//vector <Token> tokens = lexi.scan();
	Parser datalog_parser(lexi.scan());

	cout << datalog_parser.validate();

	return 0;
}
