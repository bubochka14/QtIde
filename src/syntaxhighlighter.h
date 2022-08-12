#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QObject>
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QDir>
#include <QMessageBox>
#include <QCoreApplication>
class SyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
private:
    QStringList cxx_keywords;
    //QList<QString> CustomtypeKeywords;
    enum state{
        normalState =-1,
        CStyleCommentState=0,
        CStringState=1
    };
    struct syntaxRule{
        QTextCharFormat format;
        QRegularExpression pattern;
    };
    QList<syntaxRule> rules;


    QTextCharFormat CStringFormat,CStyleCommentFormat,
        normalFormat,digitsFormat,macroFormat,keywordFormat,
        variableFormat;

public:
    SyntaxHighlighter(QTextDocument *parent);
protected:
    virtual void highlightBlock(const QString &)override;
    int commHighlight  (const QString &str,int startIndex=0);
    int cstringHiglight(const QString &str,int startIndex=0);
    void initCXX_Keywords();
    void initFormats();


};

#endif // SYNTAXHIGHLIGHTER_H
