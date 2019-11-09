#include "Program/Identifier.h"
#include <string>

class Operand {
    private:
        Identifier* identifier;
    public:
        Operand(string in);
        Identifier* getIdentifier();
};
