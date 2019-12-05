#include "Program.h"
#include "Program/Statements/AddStmt.h"
#include "Program/Statements/CmpStmt.h"
#include "Program/Statements/DeclIntStmt.h"
#include "Program/Statements/DeclArrayStmt.h"
#include "Program/Statements/EndStmt.h"
#include "Program/Statements/JEqualStmt.h"
#include "Program/Statements/JLessStmt.h"
#include "Program/Statements/JMoreStmt.h"
#include "Program/Statements/JumpStmt.h"
#include "Program/Statements/MovStmt.h"
#include "Program/Statements/PrtStmt.h"
#include "Program/Statements/ReadStmt.h"

#include "Program/Variable.h"
#include "Program/Label.h"
#include "Program/Array.h"

Program::Program(std::string fn): filename(fn) {}

Program::~Program() {
    for(std::map<std::string, Identifier*>::iterator it = identifier.begin(); it!=identifier.end(); it++) {
        delete it->second;
    }

    for(std::map<int, Statement*>::iterator it = statements.begin(); it!=statements.end(); it++) {
        delete it->second;
    }
}

//Compiles the input json.
std::string Program::compile() {
    std::ifstream file;
    std::string line;
    file.open(filename);
    if(file.is_open()) {
        this->error_code = 0;
        int index = 0;
        int linenum = 0;
        QJsonObject jsonStats;
        while(getline(file, line)) {
            if(line == "" || line[0] == '#') {
                continue;
            }

            std::vector<std::string> arr = splitString(line);
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
        file.seekg(0, std::ios::beg);

        while(getline(file, line)) {
            if(line == "" || line[0] == '#') {
                continue;
            }
            linenum++;

            std::vector<std::string> arr = splitString(line);

            // Cuts the label out of the line and adds it to the list of identifiers as well as the line it exists at.
            if(arr[0].back() == ':') {
                line = line.erase(0, arr[0].length()+1);
                arr.erase(arr.begin());
            }

            Statement* stat;
            if(arr[0] == "dci") {
                if(!is_number(arr[1])) {
                    stat = new DeclIntStmt(new Variable(arr[1]));
                } else {
                    this->error_code = 1;
                    break;
                }
            } else if(arr[0] == "dca") {
                if(!is_number(arr[1]) && is_number(arr[2])) {
                    stat = new DeclArrayStmt(new Array(arr[1], stoi(arr[2])));
                } else if(!is_number(arr[1]) && this->identifierExists(arr[2])) {
                    stat = new DeclArrayStmt(new Array(arr[1], this->getIdentifier(arr[2])));
                } else {
                    this->error_code = 1;
                    break;
                }
            } else if(arr[0] == "rdi") {
                if(this->identifierExists(arr[1])) {
                    stat = new ReadStmt(this->getIdentifier(arr[1]));
                } else {
                    this->error_code = 2;
                    break;
                }
            } else if(arr[0] == "prt") {
                std::string text = line.substr(arr[0].length() + 1, line.length());
                if(this->identifierExists(text)) {
                    stat = new PrtStmt(this->getIdentifier(text));
                } else {
                    stat = new PrtStmt(text);
                }
            } else if(arr[0] == "mov") {
                if(this->identifierExists(arr[1]) && this->identifierExists(arr[2])) {
                    stat = new MovStmt(this->getIdentifier(arr[1]), this->getIdentifier(arr[2]));
                } else if(this->is_number(arr[1]) && this->identifierExists(arr[2])) {
                    stat = new MovStmt(new Variable(arr[1], stoi(arr[1])), this->getIdentifier(arr[2]));
                } else {
                    this->error_code = 2;
                    break;
                }
            } else if(arr[0] == "add") {
                if(this->identifierExists(arr[1]) && this->identifierExists(arr[2])) {
                    stat = new AddStmt(this->getIdentifier(arr[1]), this->getIdentifier(arr[2]));
                } else if(is_number(arr[1]) && this->identifierExists(arr[2])) {
                    stat = new AddStmt(new Variable(arr[1], stoi(arr[1])), this->getIdentifier(arr[2]));
                } else {
                    this->error_code = 2;
                    break;
                }
            } else if(arr[0] == "cmp") {
                if(this->identifierExists(arr[1]) && this->identifierExists(arr[2])) {
                    stat = new CmpStmt(this->getIdentifier(arr[1]), this->getIdentifier(arr[2]));
                } else if(is_number(arr[1]) && this->identifierExists(arr[2])) {
                    stat = new CmpStmt(new Variable(arr[1], stoi(arr[1])), this->getIdentifier(arr[2]));
                } else if(is_number(arr[2]) && this->identifierExists(arr[1])) {
                    stat = new CmpStmt(this->getIdentifier(arr[1]), new Variable(arr[2], stoi(arr[2])));
                } else if(is_number(arr[1]) && is_number(arr[2])) {
                    stat = new CmpStmt(new Variable(arr[1], stoi(arr[1])), new Variable(arr[2], stoi(arr[2])));
                } else {
                    this->error_code = 2;
                    break;
                }
            } else if(arr[0] == "jls") {
                if(this->identifierExists(arr[1])) {
                    stat = new JLessStmt(this->getIdentifier(arr[1]));
                } else {
                    this->error_code = 2;
                    break;
                }
            } else if(arr[0] == "jmr") {
                if(this->identifierExists(arr[1])) {
                    stat = new JMoreStmt(this->getIdentifier(arr[1]));
                } else {
                    this->error_code = 2;
                    break;
                }
            } else if(arr[0] == "jeq") {
                if(this->identifierExists(arr[1])) {
                    stat = new JEqualStmt(this->getIdentifier(arr[1]));
                } else {
                    this->error_code = 2;
                    break;
                }
            }else if(arr[0] == "jmp") {
                if(this->identifierExists(arr[1])) {
                    stat = new JumpStmt(this->getIdentifier(arr[1]));
                } else {
                    this->error_code = 2;
                    break;
                }
            } else if(arr[0] == "end") {
                stat = new EndStmt();
            } else {
                this->error_code = 1; // Syntax error
                break;
            }
            QJsonObject statementObj = stat->compile(this, arr);
            if(this->error_code != 0 || statementObj.empty()) {
                this->error_code = 1;
                break;
            }

            this->addStatement(index, stat);
            jsonStats.insert(QString::number(index), statementObj);
            index++;
        }

        if(this->error_code == 0) {
            QJsonObject compiled;
            QJsonObject identifiersJson;
            QJsonObject labelsJson;
            for(std::map<std::string, Identifier*>::iterator it = identifier.begin(); it!=identifier.end(); it++) {
                if(dynamic_cast<Label*>(it->second)) {
                    identifiersJson.insert(QString::fromStdString(it->first), it->second->getValue());
                }
            }
            compiled.insert("identifiers", identifiersJson);
            compiled.insert("objects", jsonStats);
            compiled.insert("index", index);

            QJsonDocument doc(compiled);
            std::string name = filename.substr(0, filename.find(".")) + ".json";

            QFile jsonFile(QString::fromStdString(name));
            jsonFile.open(QFile::WriteOnly);
            jsonFile.write(doc.toJson(QJsonDocument::Indented));
            file.close();
            return "File compiled successfully to: " + name;
        } else if(this->error_code == 1) {
            file.close();
            return "Syntax error on line: " + std::to_string(linenum);
            //Report syntax error
        } else if(this->error_code == 2) {
            file.close();
            return "Identifier Not Found error on line: " + std::to_string(linenum);
        } else {
            file.close();
            return "Unknown error encountered, please check your code and try again.";
        }
    }
    file.close();
    return "Unknown error encountered, please check your code and try again.";
}

void Program::execute() {
    QEventLoop loop;
    connect(this, &Program::inputRecieved, &loop, &QEventLoop::quit);

    QFile file;
    file.setFileName(QString::fromStdString(filename));
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QString val;
    val = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject object = document.object();
    QJsonValue indexVal = object.value("index");
    int index = indexVal.toInt();

    QJsonValue identifierVal = object.value("identifiers");
    QJsonObject idents = identifierVal.toObject();
    QJsonObject::iterator it;
    for(it = idents.begin(); it != idents.end(); ++it) {
        this->addIdentifier(new Label(it.key().toStdString(), it.value().toInt()));
    }

    QJsonValue statementVal = object.value("objects");
    QJsonObject statements = statementVal.toObject();
    this->setExecuting(true);
    for(this->index = 0; this->index < index && this->getExecuting(); this->index++) {
        QJsonValue val = statements.value(QString::number(this->index));
        QJsonObject statement = val.toObject();
        QString stmt = statement.value("stmt").toString();

        Statement* stat;
        if(stmt == "dci") {
            stat = new DeclIntStmt(new Variable(statement.value("var").toString().toStdString()));
        } else if(stmt == "dca") {
            if(is_number(statement.value("size").toString().toStdString())) {
                stat = new DeclArrayStmt(new Array(statement.value("name").toString().toStdString(), statement.value("size").toInt()));
            } else {
                stat = new DeclArrayStmt(new Array(statement.value("name").toString().toStdString(), this->getIdentifier(statement.value("size").toString().toStdString())));
            }
        } else if(stmt == "rdi") {
            loop.exec();
            stat = new ReadStmt(this->getIdentifier(statement.value("var").toString().toStdString()));
        } else if(stmt == "prt") {
            if(this->identifierExists(statement.value("print").toString().toStdString())) {
                stat = new PrtStmt(this->getIdentifier(statement.value("print").toString().toStdString()));
            } else {
                stat = new PrtStmt(statement.value("print").toString().toStdString());
            }
        } else if(stmt == "mov") {
            std::string lvar = statement.value("lvar").toString().toStdString();
            std::string rvar = statement.value("rvar").toString().toStdString();
            if(this->identifierExists(lvar) && this->identifierExists(rvar)) {
                stat = new MovStmt(this->getIdentifier(lvar), this->getIdentifier(rvar));
            } else if(this->is_number(lvar) && this->identifierExists(rvar)) {
                stat = new MovStmt(new Variable(lvar, stoi(lvar)), this->getIdentifier(rvar));
            } else {
                this->error_code = 1; // Syntax error
                break;
            }
        } else if(stmt == "add") {
            std::string lvar = statement.value("lvar").toString().toStdString();
            std::string rvar = statement.value("rvar").toString().toStdString();
            if(this->identifierExists(lvar) && this->identifierExists(rvar)) {
                stat = new AddStmt(this->getIdentifier(lvar), this->getIdentifier(rvar));
            } else if(is_number(lvar) && this->identifierExists(rvar)) {
                stat = new AddStmt(new Variable(lvar, stoi(lvar)), this->getIdentifier(rvar));
            } else {
                this->error_code = 1; // Syntax error
                break;
            }
        } else if(stmt == "cmp") {
            std::string lvar = statement.value("lvar").toString().toStdString();
            std::string rvar = statement.value("rvar").toString().toStdString();
            if(this->identifierExists(lvar) && this->identifierExists(rvar)) {
                stat = new CmpStmt(this->getIdentifier(lvar), this->getIdentifier(rvar));
            } else if(this->is_number(lvar) && this->identifierExists(rvar)) {
                stat = new CmpStmt(new Variable(lvar, stoi(lvar)), this->getIdentifier(rvar));
            } else if(this->is_number(rvar) && this->identifierExists(lvar)) {
                stat = new CmpStmt(this->getIdentifier(lvar), new Variable(rvar, stoi(rvar)));
            } else if(this->is_number(rvar) && this->is_number(lvar)) {
                stat = new CmpStmt(new Variable(lvar, stoi(lvar)), new Variable(rvar, stoi(rvar)));
            } else {
                this->error_code = 1; // Syntax error
                break;
            }
        } else if(stmt == "jls") {
            stat = new JLessStmt(this->getIdentifier(statement.value("jump_pos").toString().toStdString()));
        } else if(stmt == "jmr") {
            stat = new JMoreStmt(this->getIdentifier(statement.value("jump_pos").toString().toStdString()));
        } else if(stmt == "jeq") {
            stat = new JEqualStmt(this->getIdentifier(statement.value("jump_pos").toString().toStdString()));
        }else if(stmt == "jmp") {
            stat = new JumpStmt(this->getIdentifier(statement.value("jump_pos").toString().toStdString()));
        } else if(stmt == "end") {
            stat = new EndStmt();
        } else {
            this->error_code = 1; // Syntax error
            break;
        }
        stat->run(this);
    }
    this->setExecuting(false);
}

void Program::input(QString s) {
    this->lastinput = s.toStdString();
    if(is_number(this->lastinput)) {
        emit inputRecieved();
    }
}

std::string Program::getInput() {
    return this->lastinput;
}

Identifier* Program::getIdentifier(std::string name) {
    if(name.at(0) == '$') {
        std::size_t plus_pos = name.find('+');
        std::string index = name.substr(plus_pos+1);
        std::string array = name.substr(1, plus_pos-1);
        if((!is_number(index) && this->identifierExists(index) && this->identifierExists(array))) {
            if(this->executing) {
                int val = this->getIdentifier(index)->getValue();
                return this->identifier.find("$" + array + "+" + std::to_string(val))->second;
            } else {
                return new Variable(name);
            }
        } else if((is_number(index) && this->identifierExists(array))) {
            return this->identifier.find(name)->second;
        } else {
            return nullptr;
        }
    }
    return this->identifier.find(name)->second;
}

void Program::addIdentifier(Identifier* ident) {
    this->identifier.insert(std::pair<std::string, Identifier*>(ident->getName(), ident));
}

bool Program::identifierExists(std::string name) {
    if(name.at(0) == '$') {
        std::size_t plus_pos = name.find('+');
        std::string array = name.substr(1, plus_pos-1);
        std::string index = name.substr(plus_pos+1);
        if((!is_number(index) && identifierExists(index) && identifierExists(array)) || (is_number(index) && identifierExists(array))) {
            return true;
        } else {
            return false;
        }
    }
    return this->identifier.find(name) != identifier.end();
}


Statement* Program::getStatement(int index) {
    return this->statements.find(index)->second;
}

void Program::addStatement(int index, Statement* stat) {
    this->statements.insert(std::pair<int, Statement*>(index, stat));
}

void Program::setIndex(int index) {
    this->index = index;
}

int Program::getComparison() {
    return this->comparisonFlag;
}

void Program::setComparison(int i) {
    this->comparisonFlag = i;
}

bool Program::getExecuting() {
    return this->executing;
}

void Program::setExecuting(bool ex) {
    this->executing = ex;
}

bool Program::is_number(std::string s) {
    if(s[0] == '-') {
        s.erase(0);
    }
    return std::all_of(s.begin(), s.end(), ::isdigit);
}

std::vector<std::string> Program::splitString(std::string str) {
    std::stringstream ss(str);
    std::vector<std::string> args((std::istream_iterator<std::string>(ss)), std::istream_iterator<std::string>());
    return args;
}
