#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "Token.h"

class Parser
{
public:
	Parser();
	~Parser();
	void ignoreComments(vector <Token>& tokens, int& it);
	//below are the functions that represent the grammar of the datalog Program
	void datalogProgram(vector <Token>& tokens, int& it);
	void scheme(vector <Token>& tokens, int& it);
	void schemeList(vector <Token>& tokens, int& it);
	void idList(vector <Token>& tokens, int& it);
	void fact(vector <Token>& tokens, int& it);
	void factList(vector <Token>& tokens, int& it);
	void rule(vector <Token>& tokens, int& it);
	void ruleList(vector <Token>& tokens, int& it);
	void headPredicate(vector <Token>& tokens, int& it);
	void predicate(vector <Token>& tokens, int& it);
	void predicateList(vector <Token>& tokens, int& it);
	void parameter(vector <Token>& tokens, int& it);
	void parameterList(vector <Token>& tokens, int& it);
	void expression(vector <Token>& tokens, int& it);
	void myOperator(vector <Token>& tokens, int& it);
	void query(vector <Token>& tokens, int& it);
	void queryList(vector <Token>& tokens, int& it);
	void stringList(vector <Token>& tokens, int& it);
	//this next method will determine if the input is valid
	string validate(vector <Token>& tokens);
	
};

