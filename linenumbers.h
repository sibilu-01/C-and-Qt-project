#ifndef LINENUMBERS_H
#define LINENUMBERS_H

#include <QMainWindow>

namespace Ui {
class LineNumbers;
}

class LineNumberArea : public QWidget
{
    Q_OBJECT

public:
    LineNumberArea(QTextEdit *editor);

    QSize sizeHint() const;

protected:
    void paintEvent(QPaintEvent *event);

private:
    QTextEdit *codeEditor;
};
#endif // LINENUMBERS_H
