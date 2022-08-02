#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QTextBlock>
#include <QPainter>
#include <QFile>
#include <syntaxhighlighter.h>
class NumberLine;
class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    CodeEditor(QWidget *parent = nullptr);
    QString getErrorString();
private:
    NumberLine        *numberLine;
    QString            errorString;
    SyntaxHighlighter *syntax;
public slots:
    void numberLineUpdate       (const QRect& rect, int dy);
    void numberLineWidthUpdate  ();
    void numberLinePaintEvent   (QPaintEvent *e);
    void resizeEvent            (QResizeEvent *e)override;
    QString readTextFromFile    (const QString &name);
};


class NumberLine : public QWidget{

public:
    NumberLine(CodeEditor *parent, int widthAdd=0);
    int getLineWidth() const;
protected:
    void paintEvent(QPaintEvent *e) override;
    QSize sizeHint() const override;
    CodeEditor *codeEditor;
    int widthAddition;
    friend class CodeEditor;
};

#endif // CODEEDITOR_H

