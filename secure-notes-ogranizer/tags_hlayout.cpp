#include "tags_hlayout.h"
#include <QDebug>
#include <QTextEdit>
#include <QKeyEvent>

TagsLayout::TagsLayout(QWidget* parent) : QHBoxLayout(parent) {
    // Initialize the tags vector to an empty QVector
    tags = QVector<TagWidget*>();

    // Create a QPushButton for adding new tags
    addButton = new QPushButton();

    // Set the icon for the addButton from a resource file
    addButton->setIcon(QIcon(":/res/img/plus.png"));

    // Set a custom property for styling purposes
    addButton->setProperty("class", "tagButtons");

    // Connect the clicked signal of addButton to the addButtonPressed slot
    connect(addButton, &QPushButton::clicked, this, &TagsLayout::addButtonPressed);

    // Add the addButton to the layout
    addWidget(addButton);
}


TagsLayout::~TagsLayout() {
    // Clean up tags vector
    for (TagWidget* tag : tags)
        delete tag;
}

void TagsLayout::addButtonPressed() {
    // Check if textInput is not already created
    if (!textInput) {
        // Create a new QTextEdit for user input
        textInput = new QTextEdit();  // Assuming textEdit is your custom QTextEdit class

        // Set a custom property for styling purposes
        textInput->setProperty("class", "textInput");

        // Disable the vertical scroll bar for the QTextEdit
        textInput->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        // Add the textInput, deleteButton, and addButton to the layout
        addWidget(textInput);
        addWidget(addButton);

        // Install an event filter to capture key events in the textInput
        // This allows handling the Enter key press event
        textInput->installEventFilter(this);

        // Set focus to the newly created QTextEdit
        textInput->setFocus();
    }
}


void TagsLayout::createTag(const QString &text) {
    // Call the function to create a tag with the entered text
    if(tagExists(text))
        return;

    // Create a new Tag widget with the provided text and set TagsLayout as its parent
    TagWidget* newTag = new TagWidget(text, this);

    // Connect the tag's remove signal to the TagsLayout removeTag slot
    connect(newTag, &TagWidget::tagRemoved, this, &TagsLayout::removeTag);

    // Add the new tag to the Tags Vector
    tags.push_back(newTag);

    // Add the new tag at the end of the layout
    addWidget(newTag);

    // Move the "+" button to the end of the layout
    addWidget(addButton);

    // Check if the number of tags is now 10 or more, and hide the "+" button
    if (tags.size() >= 10)
        addButton->hide();
}

void TagsLayout::removeTag(TagWidget* tag) {
    // Remove tag from the layout and vector

    // Retrieve the button and tagText widgets associated with the tag
    QWidget* button = takeAt(indexOf(tag) - 2)->widget();
    QWidget* tagText = takeAt(indexOf(tag) - 1)->widget();

    // Schedule the deletion of the button and tagText widgets
    button->deleteLater();
    tagText->deleteLater();

    // Explicitly delete the button and tagText objects
    delete button;
    delete tagText;

    // Remove the tag from the vector

    // Find the tag in the vector and move it to the end
    auto it = std::remove(tags.begin(), tags.end(), tag);

    // Erase the elements that were moved to the end
    tags.erase(it, tags.end());

    // Check if the number of tags is less than 10, and show the "+" button
    if (tags.size() < 10)
        addButton->show();
}

bool TagsLayout::tagExists(const QString& tagText) const {
    // Iterate through all widgets in the layout
    for (int i = 0; i < tags.size(); ++i)
        // If it is a QTextEdit, compare its text with the provided tagText
        if (tags[i]->getText() == tagText)
            // Tag with the specified text already exists
            return true;

    // Tag with the specified text does not exist
    return false;
}

bool TagsLayout::eventFilter(QObject* obj, QEvent* event) {
    // Check if the event is associated with the textInput widget
    if (obj == textInput && event->type() == QEvent::KeyPress) {
        // Cast the event to QKeyEvent for key-related information
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        // Check if the pressed key is Enter or Return
        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
            // Handle Enter key press event

            // Retrieve the entered text from the QTextEdit
            QString enteredText = textInput->toPlainText();

            // Check if there is text entered
            if (enteredText.size() > 0) {
                // Call the function to create a tag with the entered text
                createTag(enteredText);

                // Remove the QTextEdit from the layout
                removeWidget(textInput);

                // Delete the textInput widget and set it to nullptr
                textInput->deleteLater();
                textInput = nullptr;

                // Event is handled, return true
                return true;  // Event handled
            }
        } else if (keyEvent->key() == Qt::Key_Backspace) {
            // Handle Backspace key press event

            // Check if the textInput is empty
            if (textInput->toPlainText().isEmpty()) {
                // Remove the QTextEdit from the layout
                removeWidget(textInput);

                // Delete the textInput widget and set it to nullptr
                textInput->deleteLater();
                textInput = nullptr;

                // Event is handled, return true
                return true;  // Event handled
            }
        }
    }

    // Event is not related to textInput or not handled, return false
    return false;  // Event not handled
}


