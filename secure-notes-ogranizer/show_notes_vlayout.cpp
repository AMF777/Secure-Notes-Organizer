#include "show_notes_vlayout.h"
#include "note_widget.h"
#include "main_window.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include "back-end/clientcontroller.h"

edit_notes_vlayout::edit_notes_vlayout(QWidget *parent)
    : QVBoxLayout{parent}
{
    this->user=nullptr;
    this->mainWindowRef=nullptr;
    // Create QLabel widgets
    QLabel *label1 = new QLabel("My notes");
    QLabel *label2 = new QLabel("Shared with me");
    QLabel *label3 = new QLabel("Shared with others");

    // Set a style class for the QLabel widgets
    label1->setProperty("class", "edit-notes-label");
    label2->setProperty("class", "edit-notes-label");
    label3->setProperty("class", "edit-notes-label");

    addWidget(label1);
    QHBoxLayout* b1= new QHBoxLayout();
    b1->addLayout(new note_widget() );
    b1->addLayout(new note_widget() );
    b1->addLayout(new note_widget() );
    // b1->setAlignment(Qt::AlignCenter);
    // QScrollArea *scroll= new QScrollArea();
    // QWidget *b1Widget = new QWidget();
    // b1Widget->setLayout(b1);
    // scroll->setWidget(b1Widget);
    // scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // scroll->setMaximumHeight(140);
    addLayout(b1);
    // addWidget(scroll);

    addWidget(label2);
    QHBoxLayout* b2= new QHBoxLayout();
    b2->addLayout(new note_widget() );
    b2->addLayout(new note_widget() );
    b2->addLayout(new note_widget() );
    // b2->setAlignment(Qt::AlignCenter);
    addLayout(b2);

    addWidget(label3);
    QHBoxLayout* b3= new QHBoxLayout();
    b3->addLayout(new note_widget() );
    b3->addLayout(new note_widget() );
    b3->addLayout(new note_widget() );
    // b3->setAlignment(Qt::AlignCenter);
    addLayout(b3);
    setAlignment(Qt::AlignTop);
}

edit_notes_vlayout::edit_notes_vlayout(User* user, QWidget *parent) : QVBoxLayout{parent}
{
    this->user=user;
    this->mainWindowRef=nullptr;this->mainWindowRef=nullptr;
    std::string username=user->getuserName();
    QLabel *label1 = new QLabel("My notes("+QString::fromStdString(username)+")" );
    QLabel *label2 = new QLabel("Shared with me");
    QLabel *label3 = new QLabel("Shared with others");

    // Set a style class for the QLabel widgets
    label1->setProperty("class", "edit-notes-label");
    label2->setProperty("class", "edit-notes-label");
    label3->setProperty("class", "edit-notes-label");

    addWidget(label1);
    QHBoxLayout* b1= new QHBoxLayout();

    std::vector<Note> notes;
    std::string response = "";
    // bool ClientListNote(User *user, std::string* response, std::vector<Note>& NotesList); //client set (user id) and get (vector(NotesList))
    bool flag = client.ClientListNote(user, &response, notes);
    if(!flag){
        qDebug()<<response;
    }
    for(auto& note:notes){
        // b1->addLayout(new note_widget(&note) );

        Note* tmp=new Note(note.getuserId(), note.gettitle() );
        b1->addLayout(new note_widget(tmp ) );
    }
    b1->setAlignment(Qt::AlignLeft);
    addLayout(b1);

    addWidget(label2);
    // QHBoxLayout* b2= new QHBoxLayout();
    // b2->addLayout(new note_widget() );
    // b2->addLayout(new note_widget() );
    // b2->addLayout(new note_widget() );
    // addLayout(b2);

    addWidget(label3);
    // QHBoxLayout* b3= new QHBoxLayout();
    // b3->addLayout(new note_widget() );
    // b3->addLayout(new note_widget() );
    // b3->addLayout(new note_widget() );
    // addLayout(b3);
    setAlignment(Qt::AlignTop);
}

edit_notes_vlayout::edit_notes_vlayout(QWidget *mainWindowRef, User *user, QWidget *parent)
{
    this->mainWindowRef=mainWindowRef;
    this->user=user;

    std::string username=user->getuserName();
    QLabel *label1 = new QLabel("My notes("+QString::fromStdString(username)+")" );
    QLabel *label2 = new QLabel("Shared with me");
    QLabel *label3 = new QLabel("Shared with others");

    // Set a style class for the QLabel widgets
    label1->setProperty("class", "edit-notes-label");
    label2->setProperty("class", "edit-notes-label");
    label3->setProperty("class", "edit-notes-label");

    addWidget(label1);
    QHBoxLayout* b1= new QHBoxLayout();

    std::vector<Note> notes;
    std::string response = "";
    // bool ClientListNote(User *user, std::string* response, std::vector<Note>& NotesList); //client set (user id) and get (vector(NotesList))
    bool flag = client.ClientListNote(user, &response, notes);
    if(!flag){
        qDebug()<<response;
    }

    for(auto& note:notes){
        // this memory is leaked
        // ccan use smart pointer
        Note* notePointer = new Note(note);
        b1->addLayout(new note_widget(mainWindowRef, notePointer));
    }


    b1->setAlignment(Qt::AlignLeft);
    addLayout(b1);
    addWidget(label2);
    addWidget(label3);
    setAlignment(Qt::AlignTop);
}
