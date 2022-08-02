#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QObject>
#include <QSyntaxHighlighter>
class SyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
private:
    struct CXX{
    QList<QString> keywords;
    QList<QString> typeKeywords;
    //QList<QString> CustomtypeKeywords;
    };

public:
    SyntaxHighlighter(QTextDocument *parent);
protected:
    virtual void highlightBlock(const QString &)override;
};

#endif // SYNTAXHIGHLIGHTER_H
