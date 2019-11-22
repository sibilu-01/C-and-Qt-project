#include "Program.h"

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
    std::cout << "Opening file " << filename << ".\n";
    file.open(filename);
    if(file.is_open()) {
        error_code = 0;
        int index = 0;
        int linenum = 0;
        QJsonObject jsonStats;

        std::cout << "File Opened.\n";
        while(getline(file, line)) {
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
            std::cout << linenum << " : " << line << "\n";
            linenum++;

            std::vector<std::string> arr = splitString(line);

            // Cuts the label out of the line and adds it to the list of identifiers as well as the line it exists at.
            if(arr[0].back() == ':') {
                line = line.erase(0, arr[0].length()+1);
                arr.erase(arr.begin());
            }

            Statement* stat;
            if(arr[0] == "dci") {
                if(arr[1].find_first_not_of("0123456789") != std::string::npos) {
                    stat = new DeclIntStmt(&this->identifier, arr[1]);
                } else {
                    error_code = 1;
                    break;
                }
            } else if(arr[0] == "rdi") {
                if(this->identifierExists(arr[1])) {
                    stat = new ReadStmt(this->getIdentifier(arr[1]));
                } else {
                    error_code = 2;
                    break;
                }
            } else if(arr[0] == "prt") {
                std::string text = line.substr(arr[0].length() + 1, line.length());
                if(this->identifierExists(text)) {
                    stat = new PrtStmt(this->getIdentifier(text));
                } else {
                    stat = new PrtStmt(text);
                }
            } else if(arr[0] == "cmp") {
                if(this->identifierExists(arr[1]) && this->identifierExists(arr[2])) {
                    stat = new CmpStmt(this->getIdentifier(arr[1]), this->getIdentifier(arr[2]));
                } else if(arr[1].find_first_not_of("0123456789") == std::string::npos && this->identifierExists(arr[2])) {
                    stat = new CmpStmt(new Variable(arr[1], stoi(arr[1])), this->getIdentifier(arr[2]));
                } else if(arr[2].find_first_not_of("0123456789") == std::string::npos && this->identifierExists(arr[1])) {
                    stat = new CmpStmt(this->getIdentifier(arr[1]), new Variable(arr[2], stoi(arr[2])));
                } else if(arr[1].find_first_not_of("0123456789") == std::string::npos && arr[2].find_first_not_of("0123456789") == std::string::npos) {
                    stat = new CmpStmt(new Variable(arr[1], stoi(arr[1])), new Variable(arr[2], stoi(arr[2])));
                } else {
                    error_code = 2;
                    break;
                }
            } else if(arr[0] == "jmr") {
                if(this->identifierExists(arr[1])) {
                    stat = new JMoreStmt(this->getIdentifier(arr[1]));
                } else {
                    error_code = 2;
                    break;
                }
            } else if(arr[0] == "jmp") {
                if(this->identifierExists(arr[1])) {
                    stat = new JumpStmt(this->getIdentifier(arr[1]));
                } else {
                    error_code = 2;
                    break;
                }
            } else if(arr[0] == "end") {
                stat = new EndStmt();
            } else if(arr[0][0] == '#') {
                continue;
            } else {
                error_code = 1; // Syntax error
                break;
            }

            QJsonObject statementObj = stat->compile(arr);
            if(error_code != 0 || statementObj.empty()) {
                error_code = 1;
                break;
            }

            this->addStatement(index, stat);
            jsonStats.insert(QString::number(index), statementObj);
            index++;
        }

        if(error_code == 0) {
            QJsonObject compiled;
            QJsonObject identifiersJson;
            QJsonObject labelsJson;
            QJsonObject variablesJson;
            for(std::map<std::string, Identifier*>::iterator it = identifier.begin(); it!=identifier.end(); it++) {
                if(dynamic_cast<Label*>(it->second)) {
                    labelsJson.insert(QString::fromStdString(it->first), it->second->getValue());
                } else {
                    variablesJson.insert(QString::fromStdString(it->first), it->second->getValue());
                }
            }
            identifiersJson.insert("variables", variablesJson);
            identifiersJson.insert("labels", labelsJson);
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
        } else if(error_code == 1) {
            file.close();
            return "Syntax error on line: " + std::to_string(linenum);
            //Report syntax error
        } else if(error_code == 2) {
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

    QJsonValue statementVal = object.value("objects");
    QJsonObject statements = statementVal.toObject();
    for(int i = 0; i < index; i++) {
        QJsonObject statement = statements.value(QString(i)).toObject();
        QString stmt = statement.value("stmt").toString();
        Statement* stat;
        if(stmt == "dci") {
            stat = new DeclIntStmt(&this->identifier, statement.value("var").toString().toStdString());
        }

        stat->run();
    }
}

void Program::print() {

}

Identifier* Program::getIdentifier(std::string name) {
    return this->identifier.find(name)->second;
}

void Program::addIdentifier(Identifier* ident) {
    this->identifier.insert(std::pair<std::string, Identifier*>(ident->getName(), ident));
}

bool Program::identifierExists(std::string name) {
    return this->identifier.find(name) != identifier.end();
}


Statement* Program::getStatement(int index) {
    return this->statements.find(index)->second;
}

void Program::addStatement(int index, Statement* stat) {
    this->statements.insert(std::pair<int, Statement*>(index, stat));
}

std::vector<std::string> Program::splitString(std::string str) {
    std::stringstream ss(str);
    std::vector<std::string> args((std::istream_iterator<std::string>(ss)), std::istream_iterator<std::string>());
    return args;
}
