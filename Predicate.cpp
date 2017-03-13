#include "Predicate.h"

Predicate::Predicate(string name, Parameter param)
{
  this->name = name;
  params.push_back(param);
}


Predicate::~Predicate()
{
}


string Predicate::getName()
{
  return name;
}


vector <Parameter> Predicate::getParams()
{
  return params;
}


void Predicate::addParameter(Parameter param)
{
  params.push_back(param);
}
