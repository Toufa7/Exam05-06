#pragma once

#include <iostream>
#include <map>
#include "ASpell.hpp"
#include "ATarget.hpp"
#include "SpellBook.hpp"

class   Warlock
{
    private:
        std::string _name,_title;
        SpellBook   sbook;
    public:
        Warlock(const std::string &name, const std::string &title);
        ~Warlock();
        const   std::string &getName() const;
        const   std::string &getTitle() const;
        void    setTitle(const std::string &title);
        void    introduce() const;
        void    learnSpell(ASpell *spell);
        void    forgetSpell(std::string name);
        void    launchSpell(std::string name, ATarget const &target);
};
