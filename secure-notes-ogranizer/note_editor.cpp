#include "note_editor.h"
#include "main_window.h"

NoteEditor::NoteEditor(QWidget *mainWindowRef, QWidget *parent) : QVBoxLayout(parent){
    this->mainWindowRef=mainWindowRef;

    tagsLayout = new TagsLayout(note);
    tagsLayout->setAlignment(Qt::AlignLeft);
    tagsLayout->setContentsMargins(50, 50, 0, 0);

    noteComponentsLayout = new CustomWidget();

    // Add the layouts to the right widget
    this->addLayout(createTimeAndButtonsLayout());
    this->addLayout(createTitleNoteLayout());
    this->addLayout(tagsLayout);
    this->addLayout(createTagLayout());
    this->addWidget(noteComponentsLayout);

}

NoteEditor::NoteEditor(QWidget *mainWindowRef, QStringList& lines, QString  title, QWidget *parent) : QVBoxLayout(parent)
{
    this->mainWindowRef=mainWindowRef;
    this->note=nullptr;
    this->title = title;

    tagsLayout = new TagsLayout(note);
    tagsLayout->setAlignment(Qt::AlignLeft);
    tagsLayout->setContentsMargins(50, 50, 0, 0);

    noteComponentsLayout = new CustomWidget(lines);
    this->addLayout(createTimeAndButtonsLayout());
    this->addLayout(createTitleNoteLayout());
    this->addLayout(tagsLayout);
    this->addLayout(createTagLayout() );
    this->addWidget(noteComponentsLayout);

}

NoteEditor::NoteEditor(QWidget *mainWindowRef, Note *note, std::vector<NoteComponent> noteComponents, QWidget *parent) : QVBoxLayout(parent)
{
    this->mainWindowRef=mainWindowRef;
    this->note=note;

    this->title = QString::fromStdString(note->gettitle());
    tagsLayout = new TagsLayout(note);
    tagsLayout->setAlignment(Qt::AlignLeft);
    tagsLayout->setContentsMargins(50, 50, 0, 0);

    noteComponentsLayout = new CustomWidget(note, noteComponents);
    this->addLayout(createTimeAndButtonsLayout());
    this->addLayout(createTitleNoteLayout());
    this->addLayout(tagsLayout);
    this->addLayout(createTagLayout());
    this->addWidget(noteComponentsLayout);

}

NoteEditor::NoteEditor(QWidget *mainWindowRef, Note *note, User *user, QWidget *parent)
{
    this->mainWindowRef=mainWindowRef;
    this->note=note;
    this->user=user;

    this->title = QString::fromStdString(note->gettitle());
    tagsLayout = new TagsLayout(note);
    tagsLayout->setAlignment(Qt::AlignLeft);
    tagsLayout->setContentsMargins(50, 50, 0, 0);

    noteComponentsLayout = new CustomWidget(note, user);
    this->addLayout(createTimeAndButtonsLayout());
    this->addLayout(createTitleNoteLayout());
    tagsLayout->loadTags();
    this->addLayout(tagsLayout);
    this->addLayout(createTagLayout() );
    this->addWidget(noteComponentsLayout);

}

QHBoxLayout* NoteEditor::createTimeAndButtonsLayout()
{
    // Create a horizontal layout for time, buttons, and labels
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(10);

    // Create and set up the time label
    timeAgoLabel = new QLabel("Edited 2h ago");
    timeAgoLabel->setAlignment(Qt::AlignRight);
    timeAgoLabel->setObjectName("timeAgoLabel");

    layout->addWidget(timeAgoLabel);


    // Initialize and set up the dots button with a lambda expression
    saveNoteButton = new button_icon_vlayout(":/res/img/saveNote.png", "horizontalButton", QSize(SIDEBAR_ICON_WIDTH, SIDEBAR_ICON_HEIGHT),
        Qt::AlignRight, [this]() {
            qDebug() << "save button clicked!";
            this->noteComponentsLayout->saveNote();
        });
    saveNoteButton->button->setCursor(Qt::PointingHandCursor);
    // Initialize and set up the share button with a lambda expression
    shareButton = new button_icon_vlayout(":/res/img/share.png", "horizontalButton", QSize(SIDEBAR_ICON_WIDTH, SIDEBAR_ICON_HEIGHT),
                                          Qt::AlignRight, [this]() {
                                              qDebug() << "Share button clicked!";
                                          });

    layout->addWidget(saveNoteButton->button);
    layout->addWidget(shareButton->button);

    return layout;
}

QHBoxLayout* NoteEditor::createTitleNoteLayout()
{
    // Create a horizontal layout for the title note
    QHBoxLayout *layout = new QHBoxLayout();

    // Create and set up the title note text edit
    QTextEdit *titleNote = new QTextEdit(title);
    titleNote->setAlignment(Qt::AlignLeft);
    titleNote->setProperty("class", "title");
    titleNote->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    layout->addWidget(titleNote);

    return layout;
}

QHBoxLayout * NoteEditor::createTagLayout() {
    // Create a horizontal layout for time, buttons, and labels
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(10);

    addButton = new button_icon_vlayout(":/res/img/plus.png", "createTagButton", QSize(SIDEBAR_ICON_WIDTH, SIDEBAR_ICON_HEIGHT),
                                        Qt::AlignRight, [this]() {createTagFromInput();});

    textInput = new QTextEdit();

    // Set a custom property for styling purposes
    textInput->setProperty("class", "textInput");

    // Disable the vertical scroll bar for the QTextEdit
    textInput->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Install an event filter to capture key events in the textInput
    // This allows handling the Enter key press event
    textInput->installEventFilter(this);

    layout->addWidget(textInput);
    layout->addWidget(addButton->button);

    return  layout;
}

void NoteEditor::createTagFromInput(){
    // Retrieve the entered text from the QTextEdit
    QString enteredText = textInput->toPlainText();

    // Check if there is text entered
    if (!enteredText.isEmpty()) {
        // Call the function to create a tag with the entered text
        tagsLayout->createTag(enteredText, false, -1);

        // Clear the text input after creating the tag
        textInput->clear();
    }
}

bool NoteEditor::eventFilter(QObject* obj, QEvent* event) {
    // Check if the event is associated with the textInput widget
    if (event->type() == QEvent::KeyPress) {
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
                tagsLayout->createTag(enteredText, false, -1);
                textInput->clear();;
                return true;  // Event handled
            }
        }
    }

    // Event is not related to textInput or not handled, return false
    return false;  // Event not handled
}

