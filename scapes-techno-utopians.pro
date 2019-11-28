QT += core gui
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Program/Program.cpp \
        Program/Identifier.cpp \
        Program/Array.cpp \
        Program/Label.cpp \
        Program/Operand.cpp \
        Program/Variable.cpp \
        Program/Statements/AddStmt.cpp \
        Program/Statements/CmpStmt.cpp \
        Program/Statements/DeclArrayStmt.cpp \
        Program/Statements/DeclIntStmt.cpp \
        Program/Statements/EndStmt.cpp \
        Program/Statements/JEqualStmt.cpp \
        Program/Statements/JLessStmt.cpp \
        Program/Statements/JMoreStmt.cpp \
        Program/Statements/JumpStmt.cpp \
        Program/Statements/MovStmt.cpp \
        Program/Statements/PrtStmt.cpp \
        Program/Statements/ReadStmt.cpp \
        main.cpp \
        mainwindow.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Program/Program.h \
    Program/Statements/Statement.h \
    Program/Identifier.h \
    Program/Array.h \
    Program/Variable.h \
    Program/Label.h \
    Program/Operand.h \
    Program/Statements/AddStmt.h \
    Program/Statements/CmpStmt.h \
    Program/Statements/DeclArrayStmt.h \
    Program/Statements/DeclIntStmt.h \
    Program/Statements/EndStmt.h \
    Program/Statements/JEqualStmt.h \
    Program/Statements/JLessStmt.h \
    Program/Statements/JMoreStmt.h \
    Program/Statements/JumpStmt.h \
    Program/Statements/MovStmt.h \
    Program/Statements/PrtStmt.h \
    Program/Statements/ReadStmt.h \
    mainwindow.h

DISTFILES += \
    example.txt

FORMS += \
    mainwindow.ui
