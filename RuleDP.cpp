#include "RuleDP.h"

RuleDP::RuleDP(Predicate headPred, Predicate pred)
{
  this->headPred = headPred;
  predicates.push_back(pred);
}


RuleDP::~RuleDP()
{
}


Predicate RuleDP::getHeadPred()
{
  return headPred;
}
vector <Predicate> RuleDP::getPredicates()
{
  return predicates;
}


void RuleDP::addPredicate(Predicate pred)
{
  predicates.push_back(pred);
}
