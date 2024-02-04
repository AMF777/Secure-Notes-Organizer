#include "note_widget.h"

#include <QWidget>
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
    preview = new QLabel("this is how content look like");
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

bool note_widget::eventFilter(QObject *obj, QEvent *event)
{
    // qDebug() << "Event filter called for object of type:" << typeid(*obj).name();
    if (event->type() == QEvent::MouseButtonPress) {
        qDebug() << "Event filter called for object of type:" << typeid(*obj).name();

    }

    // // Continue with default event handling
    // return QWidget::eventFilter(obj, event);
    return true;
}

void note_widget::widgetClicked()
{
    qDebug()<<"widget clicked";
}
