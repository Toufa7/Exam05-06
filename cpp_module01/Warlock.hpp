#pragma once
#include <iostream>
#include <map>
#include "ASpell.hpp"
#include "ATarget.hpp"

class   Warlock {
    private:
        std::string _name;
        std::string _title;
        std::map<std::string, ASpell*> book;

    public:
        Warlock(const std::string &name, const std::string &title);
		~Warlock();

		std::string const &getName() const;
		std::string const &getTitle() const;
		void setTitle(std::string const &title);
		void introduce() const;
	
		void learnSpell(ASpell* spell);
		void forgetSpell(std::string name);
		void launchSpell(std::string name, ATarget const& target);
};