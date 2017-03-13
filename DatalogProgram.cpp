#include "DatalogProgram.h"

DatalogProgram::DatalogProgram()
{
}


DatalogProgram::~DatalogProgram()
{
}


vector <Predicate> DatalogProgram::getSchemes()
{
  return schemes;
}


vector <Predicate> DatalogProgram::getFacts()
{
  return facts;
}


vector <RuleDP> DatalogProgram::getRules()
{
  return rules;
}


vector <Predicate> DatalogProgram::getQueries()
{
  return queries;
}


void DatalogProgram::addScheme(Predicate pred)
{
  schemes.push_back(pred);
}


void DatalogProgram::addFact(Predicate pred)
{
  facts.push_back(pred);
}


void DatalogProgram::addRule(RuleDP rule)
{
  rules.push_back(rule);
}


void DatalogProgram::addQuery(Predicate pred)
{
  queries.push_back(pred);
}


string DatalogProgram::toString()
{

}
