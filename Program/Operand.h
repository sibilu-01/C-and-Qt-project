#include "Program/Identifier.h"
#include <string>
#include <map>

class Operand {
    private:
        Identifier* identifier;
    public:
        Operand(Identifier* iden);
        Operand(string name);
        Operand(string name, int i);
        Operand(map<string, Identifier*> *identifiers, string name);
        Identifier* getIdentifier();
};
