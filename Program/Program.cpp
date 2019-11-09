#include "Program.h"
using namespace std;

//Compiles the input json.
void Program::compile() {
    ifstream file;
    string line;
    cout << "Opening file " << filename << ".\n";
    file.open(filename);
    if(file.is_open()) {
        error_code = 0;
        int index = 0;
        int linenum = 0;
        QJsonObject jsonStats;

        cout << "File Opened.\n";
        while(getline(file, line)) {
            vector<string> arr = splitString(line);
            // Cuts the label out of the line and adds it to the list of identifiers as well as the line it exists at.
            if(arr[0].back() == ':') {
                line = line.erase(0, arr[0].length());
                arr[0].pop_back();
                this->addIdentifier(new Label(arr[0], index));
                arr.erase(arr.begin());
            }
            if(arr[0][0] == '#') {
                // Just a comment so skip the line.
                continue;
            }
            index++;
        }

        index = 0;
        file.clear();
        file.seekg(0, ios::beg);

        while(getline(file, line)) {
            cout << linenum << " : " << line << "\n";
            linenum++;

            vector<string> arr = splitString(line);

            // Cuts the label out of the line and adds it to the list of identifiers as well as the line it exists at.
            if(arr[0].back() == ':') {
                line = line.erase(0, arr[0].length());
                arr.erase(arr.begin());
            }

            Statement* stat;
            if(arr[0] == "dci") {
                stat = new DeclIntStmt(arr[1]);
            } else if(arr[0] == "rdi") {
                continue;
                //stat = new ReadStmt();
            } else if(arr[0] == "prt") {
                line = line.erase(0, arr[0].length());
                stat = new PrtStmt(line);
            } else if(arr[0] == "cmp") {
                continue;
                //stat = new DeclIntStmt(arr[1]);
            } else if(arr[0] == "jmr") {
                continue;
                //stat = new DeclIntStmt(arr[1]);
            } else if(arr[0] == "jmp") {
                continue;
                //stat = new DeclIntStmt(arr[1]);
            } else if(arr[0] == "end") {
                stat = new EndStmt();
            } else if(arr[0][0] == '#') {
                // Just a comment so skip the line.
                continue;
            } else {
                error_code = 1; // Syntax error
            }

            if(error_code != 0) {
                break;
            }

            this->addStatement(index, stat);
            jsonStats.insert(QString::number(index), stat->compile(&this->identifier, arr));
            index++;
        }

        if(error_code == 0) {
            QJsonObject compiled;
            QJsonObject identifiersJson;
            for(map<string, Identifier*>::iterator it = identifier.begin(); it!=identifier.end(); it++) {
                identifiersJson.insert(QString::fromStdString(it->first), it->second->getValue());
            }

            compiled.insert("identifiers", identifiersJson);
            compiled.insert("objects", jsonStats);
            compiled.insert("index", index);

            QJsonDocument doc(compiled);
            string name = filename.substr(0, filename.find(".")) + ".json";

            QFile jsonFile(QString::fromStdString(name));
            jsonFile.open(QFile::WriteOnly);
            jsonFile.write(doc.toJson(QJsonDocument::Indented));
        } else if(error_code == 1) {
            cout << "Syntax error on line: " << linenum << "\n";
            //Report syntax error
        } else if(error_code == 2) {
            cout << "Variable not found error on line: " << linenum << "\n";
            for(map<string, Identifier*>::iterator it = identifier.begin(); it!=identifier.end(); it++) {
                cout << it->first << "\n";
            }
            //Report VarNotFound error
        }
        file.close();
    }
}

void Program::execute() {

}

void Program::print() {

}

Identifier* Program::getIdentifier(string name) {
    return this->identifier.find(name)->second;
}

void Program::addIdentifier(Identifier* ident) {
    this->identifier.insert(pair<string, Identifier*>(ident->getName(), ident));
}

bool Program::identifierExists(string name) {
    return this->identifier.find(name) != identifier.end();
}


Statement* Program::getStatement(int index) {
    return this->statements.find(index)->second;
}

void Program::addStatement(int index, Statement* stat) {
    this->statements.insert(pair<int, Statement*>(index, stat));
}

vector<string> Program::splitString(string str) {
    stringstream ss(str);
    vector<string> args((istream_iterator<string>(ss)), istream_iterator<string>());
    return args;
}
