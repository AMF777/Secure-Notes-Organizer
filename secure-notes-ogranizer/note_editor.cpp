#include "note_editor.h"
#include "main_window.h"
#include "qdialog.h"
#include <QTimer>
#include <QDialog>
#include <QLabel>
#include <QDialog>

void NoteEditor::initialize(QWidget *mainWindowRef, Note *note, CustomWidget *customWidget) {
    this->mainWindowRef = mainWindowRef;
    this->note = note;
    qDebug()<<title;

    if (title.isEmpty() )
        if (note)
            this->title = QString::fromStdString(note->gettitle());
        else
            this->title =  "title";

    tagsLayout = new TagsLayout(note);
    tagsLayout->setAlignment(Qt::AlignLeft);

    noteComponentsLayout = customWidget;

    savedMessageLabel = new QLabel("Saved");
    savedMessageLabel->setAlignment(Qt::AlignCenter);
    savedMessageLabel->setProperty("class", "savedMessageLabel");

    // Initialize saved message dialog
    savedMessageDialog = new QDialog();
    savedMessageDialog->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    QVBoxLayout *dialogLayout = new QVBoxLayout(savedMessageDialog);
    dialogLayout->addWidget(savedMessageLabel);
    savedMessageDialog->setLayout(dialogLayout);

    savedMessageDialog->setProperty("class", "savedMessageDialog");
    savedMessageDialog->hide();
    savedMessageDialog->setFixedSize(100, 30);

    // Initialize saved message timer
    savedMessageTimer = new QTimer(this);
    savedMessageTimer->setSingleShot(true);
    connect(savedMessageTimer, &QTimer::timeout, this, &NoteEditor::hideSavedMessage);

    this->addLayout(createTimeAndButtonsLayout());
    this->addLayout(createTitleNoteLayout());
    this->addLayout(tagsLayout);
    this->addLayout(createTagLayout());
    this->addWidget(noteComponentsLayout);
    this->addWidget(savedMessageDialog);
}

NoteEditor::NoteEditor(QWidget *mainWindowRef, QWidget *parent)
    : QVBoxLayout(parent) {
    this->initialize(mainWindowRef, nullptr, new CustomWidget());
}

NoteEditor::NoteEditor(QWidget *mainWindowRef, Note *note, std::vector<NoteComponent> noteComponents, QWidget *parent)
    : QVBoxLayout(parent) {
    this->initialize(mainWindowRef, note, new CustomWidget(note, noteComponents));
}

NoteEditor::NoteEditor(QWidget *mainWindowRef, Note *note, User *user, QWidget *parent)
    : QVBoxLayout(parent) {
    this->initialize(mainWindowRef, note, new CustomWidget(note, user));
    tagsLayout->loadTags();
}

NoteEditor::NoteEditor(QWidget *mainWindowRef, std::vector<NoteComponent> noteComponents,
                       QString title, User *user, QWidget *parent) : QVBoxLayout(parent)
{
    this->title=title;
    this->initialize(mainWindowRef, nullptr, new CustomWidget(noteComponents, user) );
}

QHBoxLayout* NoteEditor::createTimeAndButtonsLayout()
{
    // Create a horizontal layout for time, buttons, and labels
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(10);

    // Create and set up the time label
    std::string editedWhen="Local note";
    if(note){
        if((note->getupdatedAt() ).size()==0 ) editedWhen="Created at "+note->getcreatedAt().substr(0, note->getcreatedAt().find(' ') );
        else editedWhen="Updated at "+note->getupdatedAt().substr(0, note->getupdatedAt().find(' ') );
    }
    timeAgoLabel = new QLabel(QString::fromStdString(editedWhen) );
    timeAgoLabel->setAlignment(Qt::AlignRight);
    timeAgoLabel->setObjectName("timeAgoLabel");

    layout->addWidget(timeAgoLabel);


    // Initialize and set up the dots button with a lambda expression
    saveNoteButton = new button_icon_vlayout(":/res/img/saveNote.png", "horizontalButton", QSize(SIDEBAR_ICON_WIDTH, SIDEBAR_ICON_HEIGHT),
        Qt::AlignRight, [this]() {
            qDebug() << "save button clicked!";
//            savedMessageDialog->show();
            // Start the timer to hide the saved message after 2 seconds
//            savedMessageTimer->start(2000);
            this->note=this->noteComponentsLayout->saveNote(this->titleNote->toPlainText().toStdString() );
            QDialog *savedLabel=new QDialog(mainWindowRef);
            QLabel *label = new QLabel("Saved");

            // Set up the layout
            QVBoxLayout *layout = new QVBoxLayout(savedLabel);
            layout->addWidget(label);
            savedLabel->setLayout(layout);
            savedLabel->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
            // Center the dialog on the screen

            // Set a QTimer to close the dialog after 300 milliseconds
            savedLabel->show();
            QTimer::singleShot(2000, savedLabel, &QDialog::accept);
            if(!note){
                qDebug()<<"null ptr";
                return ;
            }
            ((main_window*)this->mainWindowRef)->refreshViewNotes(false);
            std::string editedWhen="Local note";
            if((this->note->getupdatedAt() ).size()==0 ) editedWhen="Created at "+this->note->getcreatedAt().substr(0, this->note->getcreatedAt().find(' ') );
            else editedWhen="Updated at "+this->note->getupdatedAt().substr(0, this->note->getupdatedAt().find(' ') );
            this->timeAgoLabel->setText(QString::fromStdString(editedWhen) );
            deleteNoteButton->button->setEnabled(true);
        });
    saveNoteButton->button->setCursor(Qt::PointingHandCursor);
    // Initialize and set up the share button with a lambda expression
    shareButton = new button_icon_vlayout(":/res/img/share.png", "horizontalButton", QSize(SIDEBAR_ICON_WIDTH, SIDEBAR_ICON_HEIGHT),
                                          Qt::AlignRight, [this]() {
                                              qDebug() << "Share button clicked!";
                                          });
    layout->addWidget(saveNoteButton->button);
    // layout->addWidget(shareButton->button);
    deleteNoteButton= new button_icon_vlayout(":/res/img/deleteNote.png", "horizontalButton", QSize(SIDEBAR_ICON_WIDTH, SIDEBAR_ICON_HEIGHT),
    Qt::AlignRight, [this]() {
        qDebug() << "delete button clicked!";
        std::string response="";
        if(!note){
            qDebug()<<"nullptr note";
            return;
        }
        GlobalClient::client.ClientDeleteNote(note,&response);
        ((main_window*)this->mainWindowRef)->refreshViewNotes();
    });
    deleteNoteButton->button->setCursor(Qt::PointingHandCursor);
    if(!note) deleteNoteButton->button->setEnabled(false);
    layout->addWidget(deleteNoteButton->button);
    return layout;
}

QHBoxLayout* NoteEditor::createTitleNoteLayout()
{
    // Create a horizontal layout for the title note
    QHBoxLayout *layout = new QHBoxLayout();

    // Create and set up the title note text edit
    titleNote = new QTextEdit(title);
    titleNote->setAlignment(Qt::AlignLeft);
    titleNote->setProperty("class", "title");
    titleNote->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    layout->addWidget(titleNote);
    layout->setAlignment(Qt::AlignLeft);
    return layout;
}

QHBoxLayout * NoteEditor::createTagLayout() {
    // Create a horizontal layout for time, buttons, and labels
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    // layout->setSpacing(10);

    addButton = new button_icon_vlayout(":/res/img/plus.png", "createTagButton", QSize(SIDEBAR_ICON_WIDTH, SIDEBAR_ICON_HEIGHT),
                                        Qt::AlignRight, [this]() {createTagFromInput();});

    textInput = new QTextEdit();
    textInput->setPlaceholderText("Enter a tag");
    // Set a custom property for styling purposes
    textInput->setProperty("class", "textInput");

    // Disable the vertical scroll bar for the QTextEdit
    textInput->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Install an event filter to capture key events in the textInput
    // This allows handling the Enter key press event
    textInput->installEventFilter(this);

    layout->addWidget(textInput);
    layout->addWidget(addButton->button);
    layout->setAlignment(Qt::AlignLeft);
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

void NoteEditor::hideSavedMessage()
{
    savedMessageDialog->hide();
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
