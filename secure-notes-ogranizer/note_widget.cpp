#include "note_widget.h"

#include <QWidget>
#include <algorithm>
#include "main_window.h"


const int w=80;
const int h=80;
note_widget::note_widget(QWidget *parent)
    : QVBoxLayout{parent}
{

    QWidget *centralWidget= new QWidget();
    centralWidget->installEventFilter(this);

    centralWidget->setFixedSize(200,140);
    centralWidget->setProperty("class","note-widget black-border");
    centralWidget->setCursor(Qt::PointingHandCursor);
    // connect(centralWidget, &clickable_widget::clicked, this, &note_widget::handleButtonClick);
    // imageLabel = new QLabel();
    title = new QLabel("Title: Note Title....");
    title->setProperty("class","note-widget-title");
    tags = new QLabel("Tags: Sports, School, Work, ...");
    tags->setProperty("class","note-widget-tags");
    preview = new QLabel("this is how content look like this is how content look likethis \nis how content look likethis is how content look likethis is how content look like");
    preview->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    preview->setWordWrap(true);

    tags->setProperty("class","note-widget-preview");
    // Load the image

    // QPixmap image(":/res/img/note-icon.png");
    // image = image.scaled(w,h,Qt::KeepAspectRatio);
    // imageLabel->setPixmap(image);
    // imageLabel->setProperty("class","note-widget");

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->setAlignment(Qt::AlignTop);

    // layout->setSpacing(0);
    // layout->setContentsMargins(0,0,0,0);
    // layout->addWidget(imageLabel);
    layout->addWidget(title);
    layout->addWidget(tags);
    layout->addWidget(preview);

    addWidget(centralWidget);

}

note_widget::note_widget(Note *note, QWidget *parent)
{
    this->note = note;
    QWidget *centralWidget= new QWidget();
    centralWidget->installEventFilter(this);

    centralWidget->setFixedSize(200,140);
    centralWidget->setProperty("class","note-widget black-border");
    centralWidget->setCursor(Qt::PointingHandCursor);

    std::string noteTitle=note->gettitle();
    // noteTitle.substr(std::min(10,(int)(noteTitle.size()) )noteTitle.substr(std::min(10,(int)(noteTitle.size()) )+"..."
    title = new QLabel(QString::fromStdString(noteTitle) );
    title->setProperty("class","note-widget-title");

    // to do: tags
    std::string concatTags="";
    // concat ttags together
    // concatTags.substr(std::min(14,(int)concatTags.size() ) )+"..."
    tags = new QLabel(QString::fromStdString(concatTags) );
    tags->setProperty("class","note-widget-tags");

    // to doo: get some coponents
    std::string concatComponents="";
    // concatComponents.substr(std::min(40,(int)concatComponents.size() ) )
    preview = new QLabel(QString::fromStdString(concatComponents) );
    preview->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    preview->setWordWrap(true);

    tags->setProperty("class","note-widget-preview");

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->setAlignment(Qt::AlignTop);

    // layout->setSpacing(0);
    // layout->setContentsMargins(0,0,0,0);
    // layout->addWidget(imageLabel);
    layout->addWidget(title);
    layout->addWidget(tags);
    layout->addWidget(preview);

    addWidget(centralWidget);
}

note_widget::note_widget(QWidget *mainWindowRef, Note *note, QWidget *parent): note_widget(note,parent)
{
    this->mainWindowRef=mainWindowRef;
}

bool note_widget::eventFilter(QObject *obj, QEvent *event)
{
    // qDebug() << "Event filter called for object of type:" << typeid(*obj).name();
    if (event->type() == QEvent::MouseButtonPress) {

        qDebug() << "clicked on widget";
        main_window *ref=(main_window*)mainWindowRef;
        ref->initEditorFromNote(this->note);

    }

    // // Continue with default event handling
    // return QWidget::eventFilter(obj, event);
    return true;
}

void note_widget::widgetClicked()
{
    qDebug()<<"widget clicked";
}
