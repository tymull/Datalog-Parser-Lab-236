#include "LexicalAnalyzer.h"


LexicalAnalyzer::LexicalAnalyzer(char* input_file)
{
	char character;
	ifstream file_to_read(input_file);
	if (file_to_read.is_open())
	{
		/*
		while (file_to_read.peek() != EOF)
		{

			//character = file_to_read.get();
			//cout << "from file: " << character <<endl;
			input_file.push_back(file_to_read.get()); //reads the file into the data member
			how AJ made it-- he also put input_file_in */
		while (!file_to_read.eof())
		{
			file_to_read >> character;
			this->input_file.push_back(character); //reads the file into the data member
		}
		file_to_read.close();
	}
	else
	{
		cout << "unable to read file";
	}
}


LexicalAnalyzer::~LexicalAnalyzer()
{
}

vector <char> LexicalAnalyzer::getInputFile()
{
	return input_file;
}

void LexicalAnalyzer::analyze(char* input_file)
{
	char character;
	ifstream file_to_read(input_file);
	if (file_to_read.is_open())
	{
		while (!file_to_read.eof())
		{
			file_to_read >> character;
			this->input_file.push_back(character); //reads the file into the data member
		}
		file_to_read.close();
	}
	else
	{
		cout << "unable to read file";
	}
}

char LexicalAnalyzer::getChar(int it)
{
	return input_file[it]; //returns character at given iteration.
}

/*
void LexicalAnalyzer::reset()
{

}
*/

vector <Token> LexicalAnalyzer::scan()
{


	//the following vectors order automata by precidence
	vector <Automaton*> automata;
	vector <int> automata_readings;
	vector <Token> tokens;
	
	unsigned int current_iteration = 0; //this is first iteration for iterating through file. Can increment after tokens made
	unsigned int current_line = 1; //current line in file starts at 1

	automata.push_back(new Comma());
	automata.push_back(new Period());
	automata.push_back(new QMark());
	automata.push_back(new LeftParen());
	automata.push_back(new RightParen());
	automata.push_back(new Colon());
	automata.push_back(new ColonDash());
	automata.push_back(new Multiply());
	automata.push_back(new Add());
	automata.push_back(new Schemes());
	automata.push_back(new Facts());
	automata.push_back(new Rules());
	automata.push_back(new Queries());
	automata.push_back(new ID());
	automata.push_back(new MyString());
	automata.push_back(new LineComment());
	automata.push_back(new BlockComment());
	automata.push_back(new WhiteSpace());

	while (current_iteration < input_file.size()-1) //for some reason need -1 this loop iterates through file
	{
		int max_readings = 0;
		int new_max_readings = 0;
		int it_of_max_readings = -1; //current iteration of max readings. initialized to -1 in case none read.
		cout << "file size is " << input_file.size() << endl;
		if (input_file[current_iteration] == '\n')
		{
			current_line++;
			current_iteration++;
		}
		else
		{
			for (unsigned int i = 0; i < automata.size(); i++)//this loop lets each automata read from current iteration
			{
				automata[i]->read(current_iteration, input_file);
				//finds which automata has most readings and highest precidence.
				new_max_readings = max(max_readings, automata[i]->getReadings());
				/*this will change it_of_max_readings to match the automata with max readings while keeping
				precidence by only changing if it exceeds the previous max.*/
				if (new_max_readings > max_readings)
				{
					cout << "\n max reading change c_i=" << current_iteration << " i=" << i << endl;
					it_of_max_readings = i;
					max_readings = new_max_readings;
				}
				
			}
			if (it_of_max_readings != automata.size()) //because this would be a white space
			{
				tokens.push_back(automata[it_of_max_readings]->tokenize(current_line, current_iteration, input_file));
				//this will set readings back to 0 for each automata before it moves forward in file
				automata[it_of_max_readings]->resetReadings();
				cout << "here " << current_iteration << "then ";
				current_iteration += max_readings; //move iteration to point beyond end of last token made
				cout << current_iteration << "\nComma readings = " << automata[it_of_max_readings]->getReadings() << endl;
			}
			else
			{
				automata[it_of_max_readings]->resetReadings();
				current_iteration += max_readings; //this way it just skips over white space and doesn't make a token
			}
		}
	}
	string name_EOF = "EOF";
	string content_EOF = "";
	Token token_EOF(name_EOF, content_EOF, current_line);
	tokens.push_back(token_EOF);
	/*
	stringstream token_list; //maybe take this out to optimize
	for (unsigned int i = 0; i < tokens.size(); i++)
	{
		token_list << tokens[i].getToken();
		if (i < tokens.size())//if i is not on the last token (EOF)
		{
			token_list << endl;
		}
	}
	*/
	return tokens;
}
