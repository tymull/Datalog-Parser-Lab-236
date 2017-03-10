#include "Parser.h"


Parser::Parser(vector <Token> tokens)
{
	this->tokens = tokens;
}


Parser::~Parser()
{
}


int Parser::getIt()
{
	return it;
}


vector <Token> Parser::getTokens()
{
	return tokens;
}


void Parser::ignoreComments() //this should be called every time it is incremented
{
	//cout << "\n\nHERE ARE THE TOKENS:" << tokens[it] << endl << endl;
	while (tokens[it].getName() == "COMMENT")
	//will ensure that "COMMENT" is effectively ignored and not compared to other token
	{
		it++;
	}
}


void Parser::datalogProgram()
{
	ignoreComments();
	if (tokens[it].getName() != "SCHEMES") //input must start with token name SCHEMES
	{
		throw tokens[it]; //bad input throw to output the token
	}
	else
	{
		it++; //input is good so far, move to next token
		ignoreComments();
	}
	if (tokens[it].getName() != "COLON") //COLON should follow SCHEMES
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}
	scheme(); //recurse to a different part of grammar
	schemeList(); //since it is passed by reference, it will continue to increment through the vector through recursions

	if (tokens[it].getName() != "FACTS")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}
	if (tokens[it].getName() != "COLON")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}
	factList();

	if (tokens[it].getName() != "RULES")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}
	if (tokens[it].getName() != "COLON")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}
	ruleList();

	if (tokens[it].getName() != "QUERIES")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}
	if (tokens[it].getName() != "COLON")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}
	query();
	queryList();
}


void Parser::scheme()
{
	if (tokens[it].getName() != "ID")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}
	if (tokens[it].getName() != "LEFT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}
	if (tokens[it].getName() != "ID")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}
	idList();

	if (tokens[it].getName() != "RIGHT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}
}


void Parser::schemeList()
{
	if (tokens[it].getName() == "ID")
	{
		scheme();
		schemeList();
	}
	else if (tokens[it].getName() != "FACTS") //if next token is FACTS, move on. Otherwise throw
	{
		throw tokens[it];
	}
}


void Parser::idList()
{
	if (tokens[it].getName() == "COMMA")
	{
		it++;
		ignoreComments();

		if (tokens[it].getName() != "ID")
		{
			throw tokens[it];
		}
		else
		{
			it++;
			ignoreComments();
			idList();
		}
	}
	else if (tokens[it].getName() != "RIGHT_PAREN") //if next token is RIGHT_PAREN, move on. Otherwise throw
	{
		throw tokens[it];
	}
}


void Parser::fact()
{
	if (tokens[it].getName() != "ID")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}
	if (tokens[it].getName() != "LEFT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}
	if (tokens[it].getName() != "STRING")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}
	stringList();

	if (tokens[it].getName() != "RIGHT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}
	if (tokens[it].getName() != "PERIOD")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}
}


void Parser::factList()
{
	if (tokens[it].getName() == "ID")
	{
		fact();
		factList();
	}
	else if (tokens[it].getName() != "RULES") //if next token is RULES, move on. Otherwise throw
	{
		throw tokens[it];
	}
}


void Parser::rule()
{
	headPredicate();

	if (tokens[it].getName() != "COLON_DASH")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}

	predicate();
	predicateList();

	if (tokens[it].getName() != "PERIOD")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}
}


void Parser::ruleList()
{
	if (tokens[it].getName() == "ID")
	{
		rule();
		ruleList();
	}
	else if (tokens[it].getName() != "QUERIES") //if next token is QUERIES, move on. Otherwise throw
	{
		throw tokens[it];
	}
}


void Parser::headPredicate()
{
	if (tokens[it].getName() != "ID")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}
	if (tokens[it].getName() != "LEFT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}
	if (tokens[it].getName() != "ID")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}
	idList();

	if (tokens[it].getName() != "RIGHT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}
}


void Parser::predicate()
{
	if (tokens[it].getName() != "ID")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}
	if (tokens[it].getName() != "LEFT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}

	parameter();
	parameterList();

	if (tokens[it].getName() != "RIGHT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}
}


void Parser::predicateList()
{
	if (tokens[it].getName() == "COMMA")
	{
		it++;
		ignoreComments();
		predicate();
		predicateList();
	}
	else if (tokens[it].getName() != "PERIOD") //if next token is RIGHT_PAREN, move on. Otherwise throw
	{
		throw tokens[it];
	}
}


void Parser::parameter()
{
	if (tokens[it].getName() == "ID")
	{
		it++;
		ignoreComments();
	}
	else if (tokens[it].getName() == "LEFT_PAREN")
	{
		expression();
	}
	else if (tokens[it].getName() == "STRING")
	{
		it++;
		ignoreComments();
	}
	else
	{
		throw tokens[it];
	}
}


void Parser::parameterList()
{
	if (tokens[it].getName() == "COMMA")
	{
		it++;
		ignoreComments();
		parameter();
		parameterList();
	}
	else if (tokens[it].getName() != "RIGHT_PAREN") //if next token is RIGHT_PAREN, move on. Otherwise throw
	{
		throw tokens[it];
	}
}


void Parser::expression()
{
	if (tokens[it].getName() != "LEFT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}

	parameter();
	myOperator();
	parameter();

	if (tokens[it].getName() != "RIGHT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}
}


void Parser::myOperator()
{
	if (tokens[it].getName() == "ADD")
	{
		it++;
		ignoreComments();
	}
	else if (tokens[it].getName() == "MULTIPLY")
	{
		it++;
		ignoreComments();
	}
	else
	{
		throw tokens[it];
	}
}


void Parser::query()
{
	if (tokens[it].getName() == "ID")
	{
		predicate();
	}
	else
	{
		throw tokens[it];
	}
	if (tokens[it].getName() == "Q_MARK")
	{
		it++;
		ignoreComments();
	}
	else
	{
		throw tokens[it];
	}
}


void Parser::queryList()
{
	if (tokens[it].getName() == "ID")
	{
		query();
		queryList();
	}
	else if (tokens[it].getName() != "EOF") //if next token is EOF, move on and finish. Otherwise throw
	{
		throw tokens[it];
	}
}


void Parser::stringList()
{
	if (tokens[it].getName() == "COMMA")
	{
		it++;
		ignoreComments();

		if (tokens[it].getName() == "STRING")
		{
			it++;
			ignoreComments();
			stringList();
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


string Parser::validate()
{
	try
	{
		datalogProgram(); //this will run through each production in grammar to validate
	}
	catch (Token t)
	{
		stringstream output;
		output << "Failure!\n  " << t.getToken(); //two spaces instead of \t
		return output.str();
	}
	return "Success!";
}
