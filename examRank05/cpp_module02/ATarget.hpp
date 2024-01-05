#pragma once

#include <iostream>
#include "ASpell.hpp"

class   ASpell;

class   ATarget
{
    protected:
        std::string _type;
    public:
        ATarget(std::string type);
        virtual ~ATarget();
        const std::string &getType() const;
        virtual ATarget *clone() const = 0;
        void    getHitBySpell(const ASpell &target) const;
};
