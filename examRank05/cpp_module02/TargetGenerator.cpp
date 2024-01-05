#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator() {}

TargetGenerator::~TargetGenerator() {}

void    TargetGenerator::learnTargetType(ATarget *target)
{
	if (target)
    	book[target->getType()] = target;
}

void    TargetGenerator::forgetTargetType(std::string const &name)
{
    if (book.find(name) != book.end())
		book.erase(book.find(name));
}

ATarget    *TargetGenerator::createTarget(std::string const &name)
{
	ATarget* tmp = NULL;
	if (book.find(name) != book.end())
		tmp = book[name];
	return (tmp);
}