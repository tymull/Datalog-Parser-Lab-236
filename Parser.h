#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "Token.h"

class Parser
{
private:
	int it = 0; //initialize first iteration of Token vector
	vector <Token> tokens;
public:
	Parser(vector <Token> tokens);
	~Parser();
	int getIt();
	vector <Token> getTokens();
	void ignoreComments();
	//below are the functions that represent the grammar of the datalog Program
	void datalogProgram();
	void scheme();
	void schemeList();
	void idList();
	void fact();
	void factList();
	void rule();
	void ruleList();
	void headPredicate();
	void predicate();
	void predicateList();
	void parameter();
	void parameterList();
	void expression();
	void myOperator();
	void query();
	void queryList();
	void stringList();
	//this next method will determine if the input is valid
	string validate();

};
