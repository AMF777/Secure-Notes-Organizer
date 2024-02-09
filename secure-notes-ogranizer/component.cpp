#include "component.h"
#include <QScrollBar>
#include <QFocusEvent>
#include <QFontDialog>
#include <QColorDialog>


TextEditComponent::TextEditComponent(QWidget *parent) : QWidget(parent)
{
    index = -1;
    // Create QTextEdit
    text = new class textEdit(this);
    text->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Disable vertical scrollbar
    text->setProperty("class", "textComponents");  // Set the class name as a custom property

    setupDropDownIcon();

    // Set up layout
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(selectColumnIcon);
    layout->addWidget(text);

    // Set minimum height
    setMinimumHeight(50);

    // Update height initially
    updateHeight();

    // Connect a slot to update height when text changes
    connect(text->document(), &QTextDocument::contentsChanged, this, &TextEditComponent::updateHeight);
    text->installEventFilter(this);

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
    QFont font = QFontDialog::getFont(&ok, text->font(), this);

    if (ok)
    {
        text->setFontFamily(font.family());
        text->setFontStyle(font.styleName());
        text->setFontSize(font.pointSize());
    }
}

void TextEditComponent::handleBoldOption()
{
    // Toggle boldness
    bool isBold = !text->isBold();
    text->setBold(isBold);
}

void TextEditComponent::handleItalicOption()
{
    // Toggle italic
    bool isItalic = !text->isItalic();
    text->setItalic(isItalic);
}

void TextEditComponent::handleUnderlinedOption()
{
    // Toggle underlined
    bool isUnderlined = !text->isUnderlined();
    text->setUnderlined(isUnderlined);
}

void TextEditComponent::handleFontColorOption()
{
    // Get the current text content
    QString currentText = text->toPlainText();

    // Prompt the user to choose a new font color
    QColor chosenFontColor = QColorDialog::getColor(text->textColor(), this, "Choose Font Color");

    if (chosenFontColor.isValid())
    {
        // Set the new font color
        text->setFontColor(chosenFontColor.name(QColor::HexRgb));

        // Set the text again after changing the font color
        text->setText(currentText);
    }
}


void TextEditComponent::handleBackgroundColorOption()
{
    // Get the current text content
    QString currentText = text->toPlainText();

    // Get the current background color
    QPalette palette = text->palette();
    QColor backgroundColor = palette.color(QPalette::Window);

    // Prompt the user to choose a new background color
    QColor chosenBackgroundColor = QColorDialog::getColor(backgroundColor, this, "Choose Note Component Background color");

    if (chosenBackgroundColor.isValid())
    {
        // Set the new background color
        text->setBackgroundColor(chosenBackgroundColor.name());
        text->setTextBackgroundColor(chosenBackgroundColor);

        // Set the text again after changing the background color
        text->setText(currentText);
    }
}


TextEditComponent::TextEditComponent(int index, QWidget *parent) : TextEditComponent(parent)
{
    this->index = index;
}

NoteComponent TextEditComponent::toNoteComponent(Note *note, TextEditComponent& tec)
{
    textEdit *tEdit=tec.text;
    // qDebug()<<tEdit->isItalic();
    // qDebug()<<tEdit->isBold();
    // NoteComponent::NoteComponent(int noteId,std::string componentContent,int fontSize,std::string fontColor,std::string backgroundColor,std::string fontFamily,std::string fontStyle,bool isBold,bool isItalic,bool isUnderlined)
    NoteComponent cmp(note->getnoteId(), tEdit->getText().toStdString(), tEdit->getFontSize(),  tEdit->getFontColor().toStdString(), tEdit->getBackgroundColor().toStdString(), tEdit->getFontFamily().toStdString(),
                      tEdit->getFontStyle().toStdString(),tEdit->isBold(), tEdit->isItalic(), tEdit->isUnderlined() );;
    return cmp;
}

void TextEditComponent::onFocusChanged(bool hasFocus)
{
    if (hasFocus)
        text->setStyleSheet("border: 2px solid black;");  // Change the border color when in focus
    else
        text->setStyleSheet("border: none;");  // Change the border color when out of focus
}

bool TextEditComponent::handleKeyPressEvent(QKeyEvent *keyEvent)
{
    // Check if Tab key is pressed
    if (keyEvent->key() == Qt::Key_Tab || keyEvent->key() == Qt::Key_Down)
    {
        // Emit a signal with the index when Tab is pressed
        emit tabKeyPressed(index, true);

        // Consume the event to prevent it from being processed further
        keyEvent->accept();
        return true;
    }else if(keyEvent->key() == Qt::Key_Up){
        // Emit a signal with the index when Tab is pressed
        emit tabKeyPressed(index, false);
    }
    // Check if Enter key is pressed without the Shift modifier
    else if ((keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) &&
        !(keyEvent->modifiers() & Qt::ShiftModifier))
    {
        // Get the cursor position
        int cursorPosition = text->textCursor().position();

        // Check if the cursor is in the middle of the text
        if (cursorPosition > 0 && cursorPosition < text->toPlainText().length())
        {
            // Extract text to the right of the cursor
            QString textToRight = text->toPlainText().mid(cursorPosition);

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
    else if (keyEvent->key() == Qt::Key_Backspace && text->toPlainText().isEmpty() && index > 0)
    {
        // Emit the backspaceEmpty signal
        emit backspaceEmpty(index);

        // Consume the event to prevent it from being processed further
        keyEvent->accept();
        return true;
    }
    // Check if Backspace key is pressed and the text edit isn't empty to send it in the previous component
    else if (keyEvent->key() == Qt::Key_Backspace && text->textCursor().position() == 0 && index > 0)
    {
        // Emit the backspaceNotEmpty signal
        emit backspaceNotEmpty(index, text->toPlainText());

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
    if (obj == text)
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
    QTextCursor cursor = text->textCursor();
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
    int docHeight = text->document()->size().height() + 20;

    // Set the height based on the maximum of the document height and the minimum height
    setFixedHeight(qMax(docHeight, 50));
}
