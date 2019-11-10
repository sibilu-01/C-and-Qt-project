#include "Program/Identifier.h"
#include <string>
#include <map>

class Operand {
    private:
        Identifier* identifier;
    public:
        Operand(Identifier* iden);
        Operand(std::string name);
        Operand(std::string name, int i);
        Operand(std::map<std::string, Identifier*> *identifiers, std::string name);
        Identifier* getIdentifier();
};
