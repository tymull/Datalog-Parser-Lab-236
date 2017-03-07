#include "Parser.h"


Parser::Parser()
{
}


Parser::~Parser()
{
}


void ignoreComments(vector <Token>& tokens, int& it) //this should be called every time it is incremented
{
	while (tokens[it].getName() == "COMMENT") 
	//will ensure that "COMMENT" is effectively ignored and not compared to other token
	{
		it++;
	}
}


void Parser::datalogProgram(vector <Token>& tokens, int& it)
{
	ignoreComments(tokens, it);
	if (tokens[it].getName() != "SCHEMES") //input must start with token name SCHEMES
	{
		throw tokens[it]; //bad input throw to output the token
	}
	else
	{
		it++; //input is good so far, move to next token
		ignoreComments(tokens, it);
	}
	if (tokens[it].getName() != "COLON") //COLON should follow SCHEMES
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments(tokens, it);
	}
	scheme(tokens, it); //recurse to a different part of grammar
	schemeList(tokens, it); //since it is passed by reference, it will continue to increment through the vector through recursions
	
	if (tokens[it].getName() != "FACTS")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments(tokens, it);
	}
	if (tokens[it].getName() != "COLON")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments(tokens, it);
	}
	factList(tokens, it);

	if (tokens[it].getName() != "RULES")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments(tokens, it);
	}
	if (tokens[it].getName() != "COLON")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments(tokens, it);
	}
	ruleList(tokens, it);

	if (tokens[it].getName() != "QUERIES")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments(tokens, it);
	}
	if (tokens[it].getName() != "COLON")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments(tokens, it);
	}
	query(tokens, it);
	queryList(tokens, it);
}


void Parser::scheme(vector <Token>& tokens, int& it)
{
	if (tokens[it].getName() != "ID")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments(tokens, it);
	}
	if (tokens[it].getName() != "LEFT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments(tokens, it);
	}
	if (tokens[it].getName() != "ID")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments(tokens, it);
	}
	idList(tokens, it);

	if (tokens[it].getName() != "RIGHT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments(tokens, it);
	}
}


void Parser::schemeList(vector <Token>& tokens, int& it)
{
	if (tokens[it].getName() == "ID")
	{
		scheme(tokens, it);
		schemeList(tokens, it);
	}
	else if (tokens[it].getName() != "FACTS") //if next token is FACTS, move on. Otherwise throw
	{
		throw tokens[it];
	}
}


void Parser::idList(vector <Token>& tokens, int& it)
{
	if (tokens[it].getName() == "COMMA")
	{
		it++;
		ignoreComments(tokens, it);

		if (tokens[it].getName() != "ID")
		{
			throw tokens[it];
		}
		else
		{
			it++;
			ignoreComments(tokens, it);
			idList(tokens, it);
		}
	}
	else if (tokens[it].getName() != "RIGHT_PAREN") //if next token is RIGHT_PAREN, move on. Otherwise throw
	{
		throw tokens[it];
	}
}


void Parser::fact(vector <Token>& tokens, int& it)
{
	if (tokens[it].getName() != "ID")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments(tokens, it);
	}
	if (tokens[it].getName() != "LEFT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments(tokens, it);
	}
	if (tokens[it].getName() != "STRING")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments(tokens, it);
	}
	stringList(tokens, it);

	if (tokens[it].getName() != "RIGHT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments(tokens, it);
	}
	if (tokens[it].getName() != "PERIOD")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments(tokens, it);
	}
}


void Parser::factList(vector <Token>& tokens, int& it)
{
	if (tokens[it].getName() == "ID")
	{
		fact(tokens, it);
		factList(tokens, it);
	}
	else if (tokens[it].getName() != "RULES") //if next token is RULES, move on. Otherwise throw
	{
		throw tokens[it];
	}
}


void Parser::rule(vector <Token>& tokens, int& it)
{
	headPredicate(tokens, it);

	if (tokens[it].getName() != "COLON_DASH")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments(tokens, it);
	}

	predicate(tokens, it);
	predicateList(tokens, it);

	if (tokens[it].getName() != "PERIOD")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments(tokens, it);
	}
}


void Parser::ruleList(vector <Token>& tokens, int& it)
{
	if (tokens[it].getName() == "ID")
	{
		rule(tokens, it);
		ruleList(tokens, it);
	}
	else if (tokens[it].getName() != "QUERIES") //if next token is QUERIES, move on. Otherwise throw
	{
		throw tokens[it];
	}
}


void Parser::headPredicate(vector <Token>& tokens, int& it)
{
	if (tokens[it].getName() != "ID")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments(tokens, it);
	}
	if (tokens[it].getName() != "LEFT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments(tokens, it);
	}
	if (tokens[it].getName() != "ID")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments(tokens, it);
	}
	idList(tokens, it);

	if (tokens[it].getName() != "RIGHT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments(tokens, it);
	}
}


void Parser::predicate(vector <Token>& tokens, int& it)
{
	if (tokens[it].getName() != "ID")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments(tokens, it);
	}
	if (tokens[it].getName() != "LEFT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments(tokens, it);
	}

	parameter(tokens, it);
	parameterList(tokens, it);

	if (tokens[it].getName() != "RIGHT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments(tokens, it);
	}
}


void Parser::predicateList(vector <Token>& tokens, int& it)
{
	if (tokens[it].getName() == "COMMA")
	{
		it++;
		ignoreComments(tokens, it);
		predicate(tokens, it);
		predicateList(tokens, it);
	}
	else if (tokens[it].getName() != "PERIOD") //if next token is RIGHT_PAREN, move on. Otherwise throw
	{
		throw tokens[it];
	}
}


void Parser::parameter(vector <Token>& tokens, int& it)
{
	if (tokens[it].getName() == "ID")
	{
		it++;
		ignoreComments(tokens, it);
	}
	else if (tokens[it].getName() == "LEFT_PAREN")
	{
		expression(tokens, it);
	}
	else if (tokens[it].getName() == "STRING")
	{
		it++;
		ignoreComments(tokens, it);
	}
	else
	{
		throw tokens[it];
	}
}


void Parser::parameterList(vector <Token>& tokens, int& it)
{
	if (tokens[it].getName() == "COMMA")
	{
		it++;
		ignoreComments(tokens, it);
		parameter(tokens, it);
		parameterList(tokens, it);
	}
	else if (tokens[it].getName() != "RIGHT_PAREN") //if next token is RIGHT_PAREN, move on. Otherwise throw
	{
		throw tokens[it];
	}
}


void Parser::expression(vector <Token>& tokens, int& it)
{
	if (tokens[it].getName() != "LEFT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments(tokens, it);
	}

	parameter(tokens, it);
	myOperator(tokens, it);
	parameter(tokens, it);

	if (tokens[it].getName() != "RIGHT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments(tokens, it);
	}
}


void Parser::myOperator(vector <Token>& tokens, int& it)
{
	if (tokens[it].getName() == "ADD")
	{
		it++;
		ignoreComments(tokens, it);
	}
	else if (tokens[it].getName() == "MULTIPLY")
	{
		it++;
		ignoreComments(tokens, it);
	}
	else
	{
		throw tokens[it];
	}
}


void Parser::query(vector <Token>& tokens, int& it)
{
	if (tokens[it].getName() == "ID")
	{
		predicate(tokens, it);
	}
	else
	{
		throw tokens[it];
	}
	if (tokens[it].getName() == "Q_MARK")
	{
		it++;
		ignoreComments(tokens, it);
	}
	else
	{
		throw tokens[it];
	}
}


void Parser::queryList(vector <Token>& tokens, int& it)
{
	if (tokens[it].getName() == "ID")
	{
		query(tokens, it);
		queryList(tokens, it);
	}
	else if (tokens[it].getName() != "EOF") //if next token is EOF, move on and finish. Otherwise throw
	{
		throw tokens[it];
	}
}


void Parser::stringList(vector <Token>& tokens, int& it)
{
	if (tokens[it].getName() == "COMMA")
	{
		it++;
		ignoreComments(tokens, it);

		if (tokens[it].getName() == "STRING")
		{
			it++;
			ignoreComments(tokens, it);
			stringList(tokens, it);
		}
		else
		{
			throw tokens[it];
		}
	}
	else if (tokens[it].getName() != "RIGHT_PAREN") //if next token is RIGHT_PAREN, move on. Otherwise throw
	{
		throw tokens[it];
	}
}


string Parser::validate(vector <Token>& tokens)
{
	int it = 0; //initialize first iteration of Token vector
	try
	{
		datalogProgram(tokens, it); //this will run through each production in grammar to validate
	}
	catch (Token t)
	{
		stringstream output;
		output << "Failure!\n\t" << t.getToken;
		return output.str();
	}
	return "Success!";
}
