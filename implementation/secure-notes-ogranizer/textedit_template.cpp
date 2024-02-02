#include "textEdit_template.h"

textEdit::textEdit(QWidget *parent)
    : QTextEdit(parent),
    fontSize(12),
    fontColor("black"),
    backgroundColor("white"),
    fontFamily("Arial"),
    fontStyle("Normal"),
    bold(false),
    italic(false),
    underlined(false)
{
    // Set initial font properties
    QFont defaultFont = this->font();
    defaultFont.setPointSize(fontSize);
    defaultFont.setFamily(fontFamily);
    defaultFont.setStyleName(fontStyle);
    defaultFont.setBold(bold);
    defaultFont.setItalic(italic);
    defaultFont.setUnderline(underlined);
    this->setFont(defaultFont);

    // Set initial text color and background color
    this->setTextColor(QColor(fontColor));
    this->setTextBackgroundColor(QColor(backgroundColor));
}

textEdit::textEdit(int fontSize, const QString &fontColor, const QString &backgroundColor,
                   const QString &fontFamily, const QString &fontStyle, bool bold,
                   bool italic, bool underlined, const QString &text, QWidget *parent)
    : QTextEdit(text, parent)
{
    // Constructor with parameters
    // Use the setter functions to set the properties based on the provided parameters
    setFontSize(fontSize);
    setFontColor(fontColor);
    setBackgroundColor(backgroundColor);
    setFontFamily(fontFamily);
    setFontStyle(fontStyle);
    setBold(bold);
    setItalic(italic);
    setUnderlined(underlined);
}


int textEdit::getFontSize() const
{
    return fontSize;
}

void textEdit::setFontSize(int size)
{
    fontSize = size;
    QFont currentFont = this->font();
    currentFont.setPointSize(fontSize);
    this->setFont(currentFont);
}

QString textEdit::getFontColor() const
{
    return fontColor;
}

void textEdit::setFontColor(const QString &color)
{
    fontColor = color;
    this->setTextColor(QColor(fontColor));
}

QString textEdit::getBackgroundColor() const
{
    return backgroundColor;
}

void textEdit::setBackgroundColor(const QString &color)
{
    backgroundColor = color;
    this->setTextBackgroundColor(QColor(backgroundColor));
}

QString textEdit::getFontFamily() const
{
    return fontFamily;
}

void textEdit::setFontFamily(const QString &family)
{
    fontFamily = family;
    QFont currentFont = this->font();
    currentFont.setFamily(fontFamily);
    this->setFont(currentFont);
}

QString textEdit::getFontStyle() const
{
    return fontStyle;
}

void textEdit::setFontStyle(const QString &style)
{
    fontStyle = style;
    QFont currentFont = this->font();
    currentFont.setStyleName(fontStyle);
    this->setFont(currentFont);
}

bool textEdit::isBold() const
{
    return bold;
}

void textEdit::setBold(bool isBold)
{
    bold = isBold;
    QFont currentFont = this->font();
    currentFont.setBold(bold);
    this->setFont(currentFont);
}

bool textEdit::isItalic() const
{
    return italic;
}

void textEdit::setItalic(bool isItalic)
{
    italic = isItalic;
    QFont currentFont = this->font();
    currentFont.setItalic(italic);
    this->setFont(currentFont);
}

bool textEdit::isUnderlined() const
{
    return underlined;
}

void textEdit::setUnderlined(bool isUnderlined)
{
    underlined = isUnderlined;
    QFont currentFont = this->font();
    currentFont.setUnderline(underlined);
    this->setFont(currentFont);
}

QString textEdit::getText() const
{
    return toPlainText();
}

void textEdit::setText(const QString &text)
{
    setPlainText(text);
}

void textEdit::appendText(const QString &text)
{
    setPlainText(getText() + text);
}

void textEdit::focusAndMoveCursor(int position)
{
    // Set focus to the textEdit
    setFocus();

    // Move the cursor to the specified position or the end if position is -1
    QTextCursor cursor = textCursor();

    if (position >= 0)
        cursor.setPosition(position);
    else
        cursor.movePosition(QTextCursor::End);


    setTextCursor(cursor);
}
