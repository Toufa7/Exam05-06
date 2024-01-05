#include "SpellBook.hpp"

SpellBook::SpellBook() {}

SpellBook::~SpellBook() {}

void    SpellBook::learnSpell(ASpell *spell)
{
	if (spell)
    	book[spell->getName()] = spell;
}

void    SpellBook::forgetSpell(std::string const &name)
{
    if (book.find(name) != book.end())
		book.erase(book.find(name));
}

ASpell    *SpellBook::createSpell(std::string const &name)
{
	ASpell* tmp = NULL;
	if (book.find(name) != book.end())
		tmp = book[name];
	return (tmp);
}