#include "text_edit_component.h"
#include <QScrollBar>
#include <QFocusEvent>

TextEditComponent::TextEditComponent(QWidget *parent) : QWidget(parent)
{
    // Create QTextEdit
    textEdit = new QTextEdit(this);
    textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Disable vertical scrollbar
    textEdit->setProperty("class", "textComponents");  // Set the class name as a custom property

    selectColumnIcon = new QLabel(this);
    QPixmap icon(":/res/img/select_column.png");
    selectColumnIcon->setPixmap(icon);
    selectColumnIcon->setFixedSize(20, 20);

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

void TextEditComponent::onFocusChanged(bool hasFocus)
{
    if (hasFocus)
        textEdit->setStyleSheet("border: 2px solid black;");  // Change the border color when in focus
    else
        textEdit->setStyleSheet("border: none;");  // Change the border color when out of focus
}

bool TextEditComponent::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == textEdit && event->type() == QEvent::FocusIn)
        onFocusChanged(true);
    else if (obj == textEdit && event->type() == QEvent::FocusOut)
        onFocusChanged(false);

    return false;
}

void TextEditComponent::keyPressEvent(QKeyEvent *event)
{
    // Handle key events here
    // For example, you can check for a specific key and perform an action
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {

        // Emit the createNewComponent signal
        emit createNewComponent();

        // Consume the event to prevent it from being processed further
        event->accept();
        return;
    }

    // Call the base class implementation to handle other key events
    QWidget::keyPressEvent(event);
}

void TextEditComponent::updateHeight()
{
    // Get the document height
    int docHeight = textEdit->document()->size().height() + 20;

    // Set the height based on the maximum of the document height and the minimum height
    setFixedHeight(qMax(docHeight, 50));
}
