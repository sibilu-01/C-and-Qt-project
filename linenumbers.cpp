#include "linenumbers.h"
#include "ui_linenumbers.h"

LineNumberArea::LineNumberArea(QTextEdit *editor) : QWidget(editor) {
    codeEditor = editor;
}

QSize LineNumberArea::sizeHint() const {
    return QSize(((QTextEditHighlighter *)codeEditor)->lineNumberAreaWidth(), 0);
}

void LineNumberArea::paintEvent(QPaintEvent *event) {
    ((QTextEditHighlighter *)codeEditor)->lineNumberAreaPaintEvent(event);
}
