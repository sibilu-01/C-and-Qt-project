#include <string>
using namespace std;

class Statement {
    public:
    virtual void run() {}
    virtual void compile(string instr) {}
};

class ReadStmt: public Statement {
    public:
        void run();
        void compile(string instr);
};
