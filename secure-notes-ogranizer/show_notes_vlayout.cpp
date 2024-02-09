#include "show_notes_vlayout.h"
#include "note_widget.h"
#include "main_window.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QGridLayout>


#include "back-end/clientcontroller.h"

using namespace GlobalClient;


edit_notes_vlayout::edit_notes_vlayout(QWidget *parent)
{

}

edit_notes_vlayout::edit_notes_vlayout(QWidget *mainWindowRef, User *user, QWidget *parent)
{
    this->mainWindowRef=mainWindowRef;
    this->user=user;

    searchLineEdit= new QLineEdit();
    searchLineEdit->setPlaceholderText("Search note by Title");
    searchLineEdit->setProperty("class", "search-bar");
    connect(searchLineEdit, &QLineEdit::textChanged, this, &edit_notes_vlayout::preformSearch);
    addWidget(searchLineEdit);

    TagsLayout* tagsLayout = new TagsLayout();
    tagsLayout->setAlignment(Qt::AlignLeft);
    addLayout(tagsLayout);

    std::string username=user->getuserName();
    label1 = new QLabel("My notes("+QString::fromStdString(username)+")" );

    // Set a style class for the QLabel widgets
    label1->setProperty("class", "edit-notes-label");

    addWidget(label1);
    b1= new QGridLayout();

    std::vector<Note> notes;
    std::string response = "";
    // bool ClientListNote(User *user, std::string* response, std::vector<Note>& NotesList); //client set (user id) and get (vector(NotesList))
    bool flag = client.ClientListNote(user, &response, notes);
    if(!flag){
        qDebug()<<response;
    }

    notesCounter += notes.size();
    int cnt=0;
    for(auto& note:notes){
        // this memory is leaked
        // ccan use smart pointer
        Note* notePointer = new Note(note);
        note_widget *newNote = new note_widget(mainWindowRef, notePointer);
        for(std::string& tag : newNote->tagsVector){
            tagsLayout->createTag(QString::fromStdString(tag), true, -1, true);
            tagsPool[tag ]=false;
        }
        noteWidgets.push_back(newNote);
        b1->addLayout(newNote,cnt/5,cnt%5);
        // b1->addWidget(newNote,cnt/5,cnt%5);
        cnt++;
    }

    //connect(tag, &TagWidget::tagClicked, this, &edit_notes_vlayout::filteredNotesByTag);
    for(TagWidget* tag: tagsLayout->tags)
        connect(tag, &TagWidget::tagClicked, this, [this, tag](){
            bool prev=tagsPool[tag->getText().toStdString() ];
            this->tagsPool[tag->getText().toStdString() ]=!prev;
            this->preformSearch(this->searchLineEdit->text() );

//            qDebug()<<tag->getText().toStdString();
            if(!prev){
                tag->labelText->setStyleSheet(""
                                              "    font-size: 14px;"
                                              "    font-weight: 500;"
                                              "    letter-spacing: 0.025em;"
                                              "    font-style: normal;"
                                              "    color: black;"
                                              "    padding: 3px 8px;"
                                              "    border: 1px solid black;"
                                              "    border-radius: 7px;"
                                              "    background-color: #98FB98;"
                                              "");
                tag->labelText->update();
            }
            else{
                tag->labelText->setStyleSheet(""
                                              "    font-size: 14px;"
                                              "    font-weight: 500;"
                                              "    letter-spacing: 0.025em;"
                                              "    font-style: normal;"
                                              "    color: black;"
                                              "    padding: 3px 8px;"
                                              "    border: 1px solid black;"
                                              "    border-radius: 7px;"
                                              "");
                tag->labelText->update();
            }
        });


    b1->setAlignment(Qt::AlignLeft);
    addLayout(b1);
    setAlignment(Qt::AlignTop);
}

void edit_notes_vlayout::preformSearch(const QString &text)
{
    QString query= text.toLower();
//    qDebug() << text;
    for(note_widget* nw: this->noteWidgets){
        QString title=nw->title->text().toLower();

        bool ok=true;
        for(auto& en:tagsPool){
            if(en.second==false )continue;

            bool found=false;
            for(std::string& tag : nw->tagsVector){
//                QString temp = QString::fromStdString(tag);
                if(tag == en.first){
                    found= true;
                    break;
                }
            }
            ok&=found;
        }
        if(title.contains(query) && ok) nw->centralWidget->show();
        else nw->centralWidget->hide();
    }
    b1->invalidate();
    b1->update();
}

void edit_notes_vlayout::filteredNotesByTag(QString tagName)
{
    for(note_widget* nw: this->noteWidgets){
        bool found = false;
        for(std::string& tag : nw->tagsVector){
            QString temp = QString::fromStdString(tag);
            if(temp == tagName){
                found= true;
                break;
            }
        }
        if(found) nw->centralWidget->show();
        else nw->centralWidget->hide();
    }
    b1->invalidate();
    b1->update();
}
