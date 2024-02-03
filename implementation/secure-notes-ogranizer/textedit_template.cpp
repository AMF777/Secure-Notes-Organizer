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
    // Retrieve the current font size
    return fontSize;
}

void textEdit::setFontSize(int size)
{
    // Set the font size and update the font of the textEdit
    fontSize = size;
    QFont currentFont = this->font();
    currentFont.setPointSize(fontSize);
    this->setFont(currentFont);
}

QString textEdit::getFontColor() const
{
    // Retrieve the current font color as a string
    return fontColor;
}

void textEdit::setFontColor(const QString &color)
{
    // Set the font color and update the text color of the textEdit
    fontColor = color;
    this->setTextColor(QColor(fontColor));
}

QString textEdit::getBackgroundColor() const
{
    // Retrieve the current background color as a string
    return backgroundColor;
}

void textEdit::setBackgroundColor(const QString &color)
{
    // Set the background color and update the text background color of the textEdit
    backgroundColor = color;
    this->setTextBackgroundColor(QColor(backgroundColor));
}

QString textEdit::getFontFamily() const
{
    // Retrieve the current font family as a string
    return fontFamily;
}

void textEdit::setFontFamily(const QString &family)
{
    // Set the font family and update the font of the textEdit
    fontFamily = family;
    QFont currentFont = this->font();
    currentFont.setFamily(fontFamily);
    this->setFont(currentFont);
}

QString textEdit::getFontStyle() const
{
    // Retrieve the current font style as a string
    return fontStyle;
}

void textEdit::setFontStyle(const QString &style)
{
    // Set the font style and update the font of the textEdit
    fontStyle = style;
    QFont currentFont = this->font();
    currentFont.setStyleName(fontStyle);
    this->setFont(currentFont);
}

bool textEdit::isBold() const
{
    // Check if the text is currently bold
    return bold;
}

void textEdit::setBold(bool isBold)
{
    // Set or unset bold style and update the font of the textEdit
    bold = isBold;
    QFont currentFont = this->font();
    currentFont.setBold(bold);
    this->setFont(currentFont);
}

bool textEdit::isItalic() const
{
    // Check if the text is currently italic
    return italic;
}

void textEdit::setItalic(bool isItalic)
{
    // Set or unset italic style and update the font of the textEdit
    italic = isItalic;
    QFont currentFont = this->font();
    currentFont.setItalic(italic);
    this->setFont(currentFont);
}

bool textEdit::isUnderlined() const
{
    // Check if the text is currently underlined
    return underlined;
}

void textEdit::setUnderlined(bool isUnderlined)
{
    // Set or unset underline style and update the font of the textEdit
    underlined = isUnderlined;
    QFont currentFont = this->font();
    currentFont.setUnderline(underlined);
    this->setFont(currentFont);
}

QString textEdit::getText() const
{
    // Retrieve the plain text content of the textEdit
    return toPlainText();
}

void textEdit::setText(const QString &text)
{
    // Set the plain text content of the textEdit
    setPlainText(text);
}

void textEdit::appendText(const QString &text)
{
    // Append the specified text to the existing text in the textEdit
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
