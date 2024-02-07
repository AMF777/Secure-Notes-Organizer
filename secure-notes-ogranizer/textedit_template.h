#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>
#include "back-end/NoteComponent.h"
#include "back-end/Note.h"

class textEdit : public QTextEdit
{
    Q_OBJECT

public:
    textEdit(QWidget *parent = nullptr);
    textEdit(int fontSize, const QString &fontColor, const QString &backgroundColor,
             const QString &fontFamily, const QString &fontStyle, bool bold,
             bool italic, bool underlined, const QString &text, QWidget *parent = nullptr);

    void setAttributes(int fontSize, const QString &fontColor, const QString &backgroundColor,
                                 const QString &fontFamily, const QString &fontStyle, bool bold,
                                 bool italic, bool underlined);
    int getFontSize() const;
    void setFontSize(int size);

    QString getFontColor() const;
    void setFontColor(const QString &color);

    QString getBackgroundColor() const;
    void setBackgroundColor(const QString &color);

    QString getFontFamily() const;
    void setFontFamily(const QString &family);

    QString getFontStyle() const;
    void setFontStyle(const QString &style);

    bool isBold() const;
    void setBold(bool bold);

    bool isItalic() const;
    void setItalic(bool italic);

    bool isUnderlined() const;
    void setUnderlined(bool underlined);

    QString getText() const;
    void setText(const QString &text);
    void appendText(const QString &text);

    void focusAndMoveCursor(int position = -1);

private:
    int fontSize;
    QString fontColor;
    QString backgroundColor;
    QString fontFamily;
    QString fontStyle;
    bool bold;
    bool italic;
    bool underlined;
    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);

    std::string encodeCaesarCipher();
    void decodeCaesarCipher(std::string &encodedText) ;
};

#endif // TEXTEDIT_H
