#pragma once
#include "Automaton.h"
//class LexicalAnalyzer;
class Comma :
	public Automaton
{
private:
	int readings = 0; //number of characters read by this machine
public:
	Comma();
	~Comma();
	int getReadings();
	bool read(int it, const vector <char>& input_file);
	void resetReadings();
	Token tokenize(unsigned int& current_line, int it, const vector <char>& input_file);
};
