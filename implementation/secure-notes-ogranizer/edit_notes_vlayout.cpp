#include "edit_notes_vlayout.h"
#include "note_widget.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QPushButton>

edit_notes_vlayout::edit_notes_vlayout(QWidget *parent)
    : QVBoxLayout{parent}
{
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
    setAlignment(Qt::AlignCenter);
}
