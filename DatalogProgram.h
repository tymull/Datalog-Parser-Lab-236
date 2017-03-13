#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Token.h"
#include "RuleDP.h"
#include "Predicate.h"
#include "Parameter.h"

class DatalogProgram
{
protected:
  vector <Predicate> schemes;
  vector <Predicate> facts;
  vector <RuleDP> rules;
  vector <Predicate> queries;
public:
  DatalogProgram();
  ~DatalogProgram();
  vector <Predicate> getSchemes();
  vector <Predicate> getFacts();
  vector <RuleDP> getRules();
  vector <Predicate> getQueries();
  void addScheme(Predicate pred);
  void addFact(Predicate pred);
  void addRule(RuleDP rule);
  void addQuery(Predicate pred);
  string toString();

};
