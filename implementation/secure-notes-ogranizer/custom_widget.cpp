// custom_widget.cpp
#include "custom_widget.h"
#include "text_edit_component.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>

CustomWidget::CustomWidget(QWidget *parent) : QVBoxLayout(parent),
    shareButton(new button_icon_vlayout(":/res/img/share.png", "horizontalButton", QSize(20, 20),
                                         Qt::AlignRight, [this]() {
                                             qDebug() << "Share button clicked!";
                                         })),
    dotsButton(new button_icon_vlayout(":/res/img/dots.png", "horizontalButton", QSize(20, 20),
                                        Qt::AlignRight, [this]() {
                                            qDebug() << "Dots button clicked!";
                                        }))

{
    setContentsMargins(0, 0, 0, 0);
    setSpacing(10);

    QHBoxLayout *horizontalLayout1 = new QHBoxLayout();
    horizontalLayout1->setContentsMargins(0, 0, 0, 0);
    horizontalLayout1->setSpacing(10);

    timeAgoLabel = new QLabel("Edited 2h ago");
    timeAgoLabel->setAlignment(Qt::AlignRight);
    timeAgoLabel->setObjectName("timeAgoLabel");

    horizontalLayout1->addWidget(timeAgoLabel);
    horizontalLayout1->addWidget(shareButton->button);
    horizontalLayout1->addWidget(dotsButton->button);

    QHBoxLayout *horizontalLayout2 = new QHBoxLayout();
    horizontalLayout2->setContentsMargins(0, 0, 0, 0);
    horizontalLayout2->setSpacing(10);

    QTextEdit *titleNote = new QTextEdit("Untitled");
    titleNote->setAlignment(Qt::AlignLeft);
    titleNote->setProperty("class", "title");
    titleNote->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    horizontalLayout2->addWidget(titleNote);

    verticalLayoutTextEdits = new QVBoxLayout();

    createComponent(parent);
    createComponent(parent);
    createComponent(parent);
    createComponent(parent);

    // Set up the overall layout
    addLayout(horizontalLayout1);
    addLayout(horizontalLayout2);
    addLayout(verticalLayoutTextEdits);
}

void CustomWidget::createComponent(QWidget *parent)
{
    // Create a new TextEditComponent
    TextEditComponent *newComponent = new TextEditComponent(parent);

    // Add the new component to the vector
    componentVector.push_back(newComponent);

    // Add the new component to the layout
    verticalLayoutTextEdits->addWidget(newComponent);
}
