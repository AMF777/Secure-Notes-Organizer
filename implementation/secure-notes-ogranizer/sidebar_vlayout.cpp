// sidebar_layout.cpp
#include "sidebar_vlayout.h"
#include "button_icon_vlayout.h"
#include "constants.h"
#include "add_note_dialog.h"

const QSize sidebar_vlayout::iconSize = QSize(SIDEBAR_ICON_WIDTH, SIDEBAR_ICON_HEIGHT);

sidebar_vlayout::sidebar_vlayout(QWidget *parent) : QVBoxLayout(parent)
{

    button_icon_vlayout* profileButton = new button_icon_vlayout(":/res/img/profile.png", "sidebar-button", iconSize,
                                                             Qt::AlignLeft, [this](){profileButtonClicked();} );
    button_icon_vlayout* plusButton = new button_icon_vlayout(":/res/img/plus.png", "sidebar-button", iconSize,
                                                                 Qt::AlignLeft, [this](){addNewNoteButtonClicked();} );
    button_icon_vlayout* editButton = new button_icon_vlayout(":/res/img/edit.png", "sidebar-button", iconSize,
                                                                 Qt::AlignLeft, [this](){editNoteButtonClicked();} );
    button_icon_vlayout* logoutButton = new button_icon_vlayout(":/res/img/logout.png", "sidebar-button", iconSize,
                                                                Qt::AlignLeft, [this](){logoutButtonClicked();} );
    setButtonSizePolicy(profileButton->button);
    setButtonSizePolicy(plusButton->button);
    setButtonSizePolicy(editButton->button);
    setButtonSizePolicy(logoutButton->button);

    addLayout(profileButton);
    addLayout(plusButton);
    addLayout(editButton);
    addLayout(logoutButton);
}

void sidebar_vlayout::setButtonSizePolicy(QPushButton *button)
{
    QSizePolicy buttonSizePolicy = button->sizePolicy();
    buttonSizePolicy.setHorizontalPolicy(QSizePolicy::Fixed);
    buttonSizePolicy.setVerticalPolicy(QSizePolicy::Minimum);
    button->setSizePolicy(buttonSizePolicy);
}
void sidebar_vlayout::profileButtonClicked()
{
    qDebug() << "Profile Button clicked";
}

void sidebar_vlayout::addNewNoteButtonClicked()
{
    qDebug() << "Add New Note Button clicked";
    add_note_dialog *addNoteDialog = new add_note_dialog(parentWidget() );
    addNoteDialog->show();
}

void sidebar_vlayout::editNoteButtonClicked()
{
    qDebug() << "Edit Note Button clicked";
}

void sidebar_vlayout::logoutButtonClicked()
{
    qDebug() << "Logout Button clicked";
}
