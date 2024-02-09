#include "note_widget.h"

#include <QWidget>
#include <algorithm>
#include <vector>
#include <QFontMetrics>

#include "main_window.h"
#include "back-end/Tag.h"
#include "back-end/NoteComponent.h"


const int w=80;
const int h=80;

note_widget::note_widget(QWidget *parent)
    : QVBoxLayout{parent}
{

    centralWidget= new QWidget();
    centralWidget->setProperty("class","note-widget");
    centralWidget->installEventFilter(this);
    centralWidget->setFixedSize(200,140);
    centralWidget->setCursor(Qt::PointingHandCursor);

    title = new QLabel("Title: Note Title....");
    title->setProperty("class","note-widget-title");
    tags = new QLabel("Tags: Sports, School, Work, ...");
    tags->setProperty("class","note-widget-tags");
    preview = new QLabel("this is how content look like this is how content look likethis \nis how content look likethis is how content look likethis is how content look like");
    preview->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    preview->setWordWrap(true);

    tags->setProperty("class","note-widget-preview");

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->setAlignment(Qt::AlignTop);

    layout->addWidget(title);
    layout->addWidget(tags);
    layout->addWidget(preview);

    addWidget(centralWidget);

}

note_widget::note_widget(Note *note, QWidget *parent) : QVBoxLayout{parent}
{
    this->note = note;
    centralWidget= new QWidget();
    centralWidget->installEventFilter(this);

    centralWidget->setFixedSize(200,140);

    centralWidget->setAttribute(Qt::WA_StyleSheet, true);
    // centralWidget->setProperty("class","note-widget");
    centralWidget->setCursor(Qt::PointingHandCursor);

    std::string noteTitle=note->gettitle();
    noteTitle=noteTitle.substr(0, std::min(15,(int)noteTitle.size() ) );

    title = new QLabel(QString::fromStdString(noteTitle) );
    title->setProperty("class","note-widget-title note-widget");

    std::vector<Tag> tagsList;
    std::string response;

    GlobalClient::client.ClientListNoteTags(note,&response,tagsList);
    // to do: tags
    std::string concatTags="";

    for(int i=0,tagsN=tagsList.size();i<tagsN;i++){
        tagsVector.push_back(tagsList[i].gettagName());
        concatTags+=tagsList[i].gettagName();
        if(i!=tagsN-1)concatTags+=", ";
    }
    concatTags=concatTags.substr(0, std::min(20,(int)concatTags.size() ) );
    tags = new QLabel(QString::fromStdString(concatTags) );
    tags->setProperty("class","note-widget-tags");
    // to doo: get some coponents

    std::vector<NoteComponent> noteComponents;
    GlobalClient::client.ClientListComponents(note,&response,noteComponents);

    std::string concatComponents="";
    for(int i=0,compsN=noteComponents.size();i<compsN;i++){
        std::string line = textEdit::decodeCaesarCipher(noteComponents[i].getcomponentContent());
        concatComponents += line;
        if(i!=compsN-1)concatComponents+=" ";
    }

    concatComponents=concatComponents.substr(0, std::min(40,(int)concatComponents.size() ) );
    preview = new QLabel(QString::fromStdString(concatComponents) );
    preview->setMaximumWidth(170);
    preview->setWordWrap(true);
    preview->setAlignment(Qt::AlignLeft);

    tags->setProperty("class","note-widget-preview");

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    centralWidget->setLayout(layout);


    layout->setAlignment(Qt::AlignTop);


    layout->addWidget(title);
    layout->addWidget(tags);
    layout->addWidget(preview);

    addWidget(centralWidget);
    setAlignment(Qt::AlignCenter);
    setContentsMargins(10,10,10,10);
}

note_widget::note_widget(QWidget *mainWindowRef, Note *note, QWidget *parent): note_widget(note,parent)
{
    this->mainWindowRef=mainWindowRef;
}

bool note_widget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        main_window *ref=(main_window*)mainWindowRef;
        ref->initEditorFromNote(this->note);
    }

    return true;
}

void note_widget::widgetClicked()
{
    qDebug()<<"widget clicked";
}
