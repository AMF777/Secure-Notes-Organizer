#include "note_editor.h"
#include "main_window.h"

NoteEditor::NoteEditor(QWidget *mainWindowRef, QWidget *parent) : QVBoxLayout(parent){
    this->note=nullptr;
    this->mainWindowRef=mainWindowRef;

    tagsLayout = new TagsLayout(note);
    tagsLayout->setAlignment(Qt::AlignLeft);
    tagsLayout->setContentsMargins(50, 50, 0, 0);

    noteComponentsLayout = new CustomWidget();

    // Add the layouts to the right widget
    this->addLayout(createTimeAndButtonsLayout());
    this->addLayout(createTitleNoteLayout());
    this->addLayout(tagsLayout);
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
    this->addWidget(noteComponentsLayout);
}

NoteEditor::NoteEditor(QWidget *mainWindowRef, Note *note, std::vector<NoteComponent> noteComponents, QWidget *parent) : QVBoxLayout(parent)
{
    this->mainWindowRef=mainWindowRef;
    this->note=note;

    // qDebug()  << note->getnoteId();
    // qDebug()  << note->getuserId();

    this->title = QString::fromStdString(note->gettitle());
    tagsLayout = new TagsLayout(note);
    tagsLayout->setAlignment(Qt::AlignLeft);
    tagsLayout->setContentsMargins(50, 50, 0, 0);

    noteComponentsLayout = new CustomWidget(note, noteComponents);
    this->addLayout(createTimeAndButtonsLayout());
    this->addLayout(createTitleNoteLayout());
    this->addLayout(tagsLayout);
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
                                                 qDebug() << "Dots button clicked!";
                                             });

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

