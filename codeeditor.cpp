#include "codeeditor.h"

CodeEditor::CodeEditor(QWidget *parent)
    :QPlainTextEdit(parent)
    ,syntax(new SyntaxHighlighter(document()))


{
    numberLine = new NumberLine(this,20);
    setLineWrapMode(QPlainTextEdit::LineWrapMode::NoWrap);
    connect(this, &QPlainTextEdit::blockCountChanged,
            this, &CodeEditor::numberLineWidthUpdate);
    connect(this, &QPlainTextEdit::updateRequest,
            this, &CodeEditor::numberLineUpdate);
    QFont font("Monospace");
    font.setStyleHint(QFont::TypeWriter);
    font.setPointSize(15);
    setFont(font);

    numberLineWidthUpdate();

}
void CodeEditor::numberLineUpdate(const QRect &rect,int dy) {
    if(dy)
        numberLine->scroll(0,dy);
    else
        numberLine->update(0,rect.y(),numberLine->width(),rect.height());

}
void CodeEditor::numberLineWidthUpdate(){
    setViewportMargins(numberLine->getLineWidth(),0,0,0);
}

void CodeEditor::resizeEvent(QResizeEvent *e){
    QPlainTextEdit::resizeEvent(e);
    QRect r = contentsRect();
    numberLine->setGeometry(r.x(),r.y(),numberLine->getLineWidth(),r.height());
}

void CodeEditor::numberLinePaintEvent(QPaintEvent *e){
    QPainter painter(numberLine);
    QColor darkGray("#4C4E52");
    painter.fillRect(e->rect(),darkGray);
    QTextBlock block = firstVisibleBlock();
    int num = block.blockNumber();
    int top =qRound( blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = blockBoundingRect(block).height() + top;
    painter.setPen(Qt::cyan);
    while( top <= e->rect().bottom() && block.isValid()){
        painter.drawText(0,top,numberLine->width(),fontMetrics().height(),
                         Qt::AlignCenter,QString::number(num+1));
        block = block.next();
        num++;
        top = bottom;
        bottom = blockBoundingRect(block).height() + top;

    }
}
QString CodeEditor::readTextFromFile(const QString &name){
    QFile file(name);
    if(file.open(QIODevice::ReadWrite|QIODevice::Text)){
        setPlainText(file.readAll());
    }
    else
    {
       errorString = file.errorString();
       setPlainText(QString("Cannot open file: %1\nError: %2").arg(name,errorString));
       return errorString;
    }
    return QString();

}

//NumberLine class:
NumberLine::NumberLine(CodeEditor *parent, int widthAdd/*=0*/)
    :QWidget(parent)
    ,codeEditor(parent)
    ,widthAddition(widthAdd)
{
    QFont numFont("Monospace");
    numFont.setStyleHint(QFont::TypeWriter);
    setFont(numFont);
}
int NumberLine::getLineWidth() const
{    return widthAddition + fontMetrics().horizontalAdvance(
                QString::number(codeEditor->blockCount()));
}
QSize NumberLine::sizeHint() const {
    return QSize(getLineWidth(),-1);
}
void NumberLine::paintEvent(QPaintEvent *e){
    codeEditor->numberLinePaintEvent(e);
}
