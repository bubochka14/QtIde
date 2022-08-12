#include "syntaxhighlighter.h"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent)
    :QSyntaxHighlighter(parent)

{
    initCXX_Keywords();
    initFormats();

    //highlighting rule for numbers:
    syntaxRule digRule;
    digRule.pattern = QRegularExpression("[0-9]");
    digRule.format  = digitsFormat;
    rules.append(digRule);

    //highlighting rule for cxx_keywords:
    foreach (QString str, cxx_keywords) {
        syntaxRule rule;
        rule.pattern = QRegularExpression(str);
        rule.format = keywordFormat;
        rules.append(rule);
    }

    //highlighting rule for macros:









}
void SyntaxHighlighter::highlightBlock(const QString &str){
    int state = previousBlockState();
    int startIndex=0, endIndex;

    setFormat(startIndex,str.length(),normalFormat);
    if(state == CStyleCommentState) startIndex = commHighlight  (str);
    if(state == CStringState)       startIndex = cstringHiglight(str);

    if(startIndex==-1)return; // not find end




}
int SyntaxHighlighter::commHighlight  (const QString &str,int startIndex){
    int endIndex = str.indexOf("*/", startIndex);
    if(endIndex==-1){
        setFormat(startIndex, str.length()-startIndex, CStyleCommentFormat);
        setCurrentBlockState(CStyleCommentState);
    }else{
        endIndex+=2;
        setFormat(startIndex, endIndex-startIndex, CStyleCommentFormat);

    }
    return endIndex;
}
int SyntaxHighlighter::cstringHiglight(const QString &str, int startIndex){
    int endIndex = str.indexOf("[\"][\']", startIndex);
    if(endIndex==-1){
        setFormat(startIndex, str.length()-startIndex, CStringFormat);
        setCurrentBlockState(CStringState);
    }else{
        endIndex++;
        setFormat(startIndex, endIndex-startIndex, CStringFormat);

    }
    return endIndex;
}
void SyntaxHighlighter::initCXX_Keywords(){
   QFile file(QDir::currentPath()+"\\keywords\\cxx_keywords.txt");
   if(!file.open(QIODevice::ReadOnly| QIODevice::Text)){
       QMessageBox *msg = new QMessageBox;
       msg->setIcon(QMessageBox::Warning);
       msg->setText("Cannot open cxx keyword file");
       msg->exec();
       return;
   }
   QString tmp = file.readAll();
   cxx_keywords = tmp.split(" ");
   file.close();

}

void SyntaxHighlighter::initFormats(){

    normalFormat.setForeground(Qt::gray);

    CStyleCommentFormat.setForeground(Qt::darkCyan);
    CStyleCommentFormat.setFontItalic(true);

    CStringFormat.setForeground(Qt::darkMagenta);

    macroFormat.setForeground(Qt::darkCyan);

    keywordFormat.setForeground(Qt::yellow);

    digitsFormat.setForeground(Qt::darkMagenta);

    variableFormat.setForeground(Qt::gray);
    variableFormat.setFontWeight(QFont::Bold);

}
