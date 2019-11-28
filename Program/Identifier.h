#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <string>
#include "vector"

class Identifier {
    private:
        std::string name;
    public:
        Identifier(std::string name);
        virtual ~Identifier() {}

        virtual int getValue() {
            return 0;
        }

        std::string getName();
};

#endif
