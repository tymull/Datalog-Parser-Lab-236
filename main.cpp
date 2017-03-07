
#include <iostream>
#include "LexicalAnalyzer.h"
#include "Parser.h"
using namespace std;

int main(int argc, char* argv[])
{
	LexicalAnalyzer lexi(argv[1]);
	//cout << lexi.scan();

	Parser datalog_parser;
	cout << datalog_parser.validate(lexi.scan());

	return 0;
}
