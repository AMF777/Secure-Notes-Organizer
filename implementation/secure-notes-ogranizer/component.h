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
    int index;

signals:
    void createNewComponent(int index);
    void backspaceEmpty(int index);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

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
    textEdit *textEdit;
    DropdownLabel *selectColumnIcon;
    QHBoxLayout *layout;
    void handleDropdownItemSelected(const QString &itemText);
    void setActions();
    void handleOptionSelected(const QString &selectedOption);

};

#endif // COMPONENT_H
