#include <string>
using namespace std;

class Identifier {
    private:
        string name;
};

class Variable: public Identifier {
    private:
        int value;
};

class Label: public Identifier {
};
