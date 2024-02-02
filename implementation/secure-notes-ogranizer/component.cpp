#include "component.h"
#include <QScrollBar>
#include <QFocusEvent>
#include <QFontDialog>
#include <QColorDialog>


TextEditComponent::TextEditComponent(QWidget *parent) : QWidget(parent)
{
    index = -1;
    // Create QTextEdit
    textEdit = new class textEdit(this);
    textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Disable vertical scrollbar
    textEdit->setProperty("class", "textComponents");  // Set the class name as a custom property

    setupDropDownIcon();

    // Set up layout
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(selectColumnIcon);
    layout->addWidget(textEdit);

    // Set minimum height
    setMinimumHeight(50);

    // Update height initially
    updateHeight();

    // Connect a slot to update height when text changes
    connect(textEdit->document(), &QTextDocument::contentsChanged, this, &TextEditComponent::updateHeight);
    textEdit->installEventFilter(this);

}

void TextEditComponent::setupDropDownIcon(){
    QPixmap selectColumnIconPixmap(":/res/img/select_column.png");
    QSize selectColumnIconSize(SIDEBAR_ICON_WIDTH, SIDEBAR_ICON_HEIGHT);
    selectColumnIcon = new DropdownLabel(selectColumnIconPixmap, selectColumnIconSize, this);

    selectColumnIcon->addActionToMenu("Bold");
    selectColumnIcon->addActionToMenu("Italic");
    selectColumnIcon->addActionToMenu("Underlined");
    selectColumnIcon->addActionToMenu("Font");
    selectColumnIcon->addActionToMenu("Font Color");
    selectColumnIcon->addActionToMenu("Background Color");

    connect(selectColumnIcon, &DropdownLabel::optionSelected, this, &TextEditComponent::handleOptionSelected);
}

void TextEditComponent::handleOptionSelected(const QString &selectedOption)
{
    if (selectedOption == "Font")
       handleFontOption();

    else if (selectedOption == "Bold")
        handleBoldOption();

    else if (selectedOption == "Italic")
        handleItalicOption();

    else if (selectedOption == "Underlined")
        handleUnderlinedOption();

    else if (selectedOption == "Font Color")
        handleFontColorOption();

    else if (selectedOption == "Background Color")
        handleBackgroundColorOption();
}

void TextEditComponent::handleFontOption()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, textEdit->font(), this);

    if (ok)
    {
        textEdit->setFontFamily(font.family());
        textEdit->setFontStyle(font.styleName());
        textEdit->setFontSize(font.pointSize());
    }
}

void TextEditComponent::handleBoldOption()
{
    // Toggle boldness
    bool isBold = !textEdit->isBold();
    textEdit->setBold(isBold);
}

void TextEditComponent::handleItalicOption()
{
    // Toggle italic
    bool isItalic = !textEdit->isItalic();
    textEdit->setItalic(isItalic);
}

void TextEditComponent::handleUnderlinedOption()
{
    // Toggle underlined
    bool isUnderlined = !textEdit->isUnderlined();
    textEdit->setUnderlined(isUnderlined);
}

void TextEditComponent::handleFontColorOption()
{
    // Get the current text content
    QString currentText = textEdit->toPlainText();

    // Prompt the user to choose a new font color
    QColor chosenFontColor = QColorDialog::getColor(textEdit->textColor(), this, "Choose Font Color");

    if (chosenFontColor.isValid())
    {
        // Set the new font color
        textEdit->setFontColor(chosenFontColor.name(QColor::HexRgb));

        // Set the text again after changing the font color
        textEdit->setText(currentText);
    }
}


void TextEditComponent::handleBackgroundColorOption()
{
    // Get the current text content
    QString currentText = textEdit->toPlainText();

    // Get the current background color
    QPalette palette = textEdit->palette();
    QColor backgroundColor = palette.color(QPalette::Window);

    // Prompt the user to choose a new background color
    QColor chosenBackgroundColor = QColorDialog::getColor(backgroundColor, this, "Choose Note Component Background color");

    if (chosenBackgroundColor.isValid())
    {
        // Set the new background color
        textEdit->setBackgroundColor(chosenBackgroundColor.name());
        textEdit->setTextBackgroundColor(chosenBackgroundColor);

        // Set the text again after changing the background color
        textEdit->setText(currentText);
    }
}


TextEditComponent::TextEditComponent(int index, QWidget *parent) : TextEditComponent(parent)
{
    this->index = index;
}

void TextEditComponent::onFocusChanged(bool hasFocus)
{
    if (hasFocus)
        textEdit->setStyleSheet("border: 2px solid black;");  // Change the border color when in focus
    else
        textEdit->setStyleSheet("border: none;");  // Change the border color when out of focus
}

bool TextEditComponent::handleKeyPressEvent(QKeyEvent *keyEvent)
{
    // Check if Tab key is pressed
    if (keyEvent->key() == Qt::Key_Tab)
    {
        // Emit a signal with the index when Tab is pressed
        emit tabKeyPressed(index);

        // Consume the event to prevent it from being processed further
        keyEvent->accept();
        return true;
    }
    // Check if Enter key is pressed without the Shift modifier
    else if ((keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) &&
        !(keyEvent->modifiers() & Qt::ShiftModifier))
    {
        // Get the cursor position
        int cursorPosition = textEdit->textCursor().position();

        // Check if the cursor is in the middle of the text
        if (cursorPosition > 0 && cursorPosition < textEdit->toPlainText().length())
        {
            // Extract text to the right of the cursor
            QString textToRight = textEdit->toPlainText().mid(cursorPosition);

            deleteRightText(cursorPosition);

            // Emit a signal with the extracted text
            emit middleEnterKeyPressed(index, textToRight);
        }
        else
            // Emit the createNewComponent signal with the updated index
            emit createNewComponent(index);

        // Consume the event to prevent it from being processed further
        keyEvent->accept();
        return true;
    }
    // Check if Backspace key is pressed and the text edit is empty
    else if (keyEvent->key() == Qt::Key_Backspace && textEdit->toPlainText().isEmpty() && index > 0)
    {
        // Emit the backspaceEmpty signal
        emit backspaceEmpty(index);

        // Consume the event to prevent it from being processed further
        keyEvent->accept();
        return true;
    }
    // Check if Backspace key is pressed and the text edit isn't empty to send it in the previous component
    else if (keyEvent->key() == Qt::Key_Backspace && textEdit->textCursor().position() == 0 && index > 0)
    {
        // Emit the backspaceNotEmpty signal
        emit backspaceNotEmpty(index, textEdit->toPlainText());

        // Consume the event to prevent it from being processed further
        keyEvent->accept();
        return true;
    }

    // If none of the conditions are met, return false
    return false;
}

bool TextEditComponent::eventFilter(QObject *obj, QEvent *event)
{
    // Check if the event is related to the textEdit object
    if (obj == textEdit)
    {
        // Handle the FocusIn event
        if (event->type() == QEvent::FocusIn)
            // Notify the onFocusChanged function that the text edit has gained focus
            onFocusChanged(true);

        // Handle the FocusOut event
        else if (event->type() == QEvent::FocusOut)
            // Notify the onFocusChanged function that the text edit has lost focus
            onFocusChanged(false);

        // Handle the KeyPress event
        else if (event->type() == QEvent::KeyPress)
        {
            // Cast the event to QKeyEvent to access key-specific information
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

            // Call the new function to handle the KeyPress event
            return handleKeyPressEvent(keyEvent);
        }
    }

    // Allow the event to be processed further by returning false
    return false;
}

void TextEditComponent::deleteRightText(const int cursorPosition){
    // Move the cursor to the desired index
    QTextCursor cursor = textEdit->textCursor();
    cursor.setPosition(cursorPosition);

    // Move the cursor to the end of the document
    cursor.movePosition(QTextCursor::End);

    // Set the cursor anchor to the desired index and remove the selected text
    cursor.setPosition(cursorPosition, QTextCursor::KeepAnchor);
    cursor.removeSelectedText();
}

void TextEditComponent::updateHeight()
{
    // Get the document height
    int docHeight = textEdit->document()->size().height() + 20;

    // Set the height based on the maximum of the document height and the minimum height
    setFixedHeight(qMax(docHeight, 50));
}
