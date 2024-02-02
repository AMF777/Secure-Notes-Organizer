#ifndef COMPONENT_H
#define COMPONENT_H

#include <QWidget>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QKeyEvent>
#include "dropdown_label.h"
#include "textedit_template.h"
#include "constants.h"


class TextEditComponent : public QWidget
{
    Q_OBJECT
public:
    TextEditComponent(QWidget *parent = nullptr);
    TextEditComponent(int index, QWidget *parent = nullptr);
    textEdit *textEdit;
    int index;

signals:
    void createNewComponent(int index);
    void middleEnterKeyPressed(int index, const QString textToRight);
    void backspaceEmpty(int index);
    void backspaceNotEmpty(int index, const QString textToRight);
    void tabKeyPressed(int index);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    bool handleKeyPressEvent(QKeyEvent *keyEvent);

private slots:
    void updateHeight();
    void onFocusChanged(bool hasFocus);
    void handleFontOption();
    void handleBoldOption();
    void handleItalicOption();
    void handleUnderlinedOption();
    void handleFontColorOption();
    void handleBackgroundColorOption();
    void setupDropDownIcon();


private:
    DropdownLabel *selectColumnIcon;
    QHBoxLayout *layout;
    void setActions();
    void deleteRightText(const int cursorPostion);
    void handleDropdownItemSelected(const QString &itemText);
    void handleOptionSelected(const QString &selectedOption);

};

#endif // COMPONENT_H
