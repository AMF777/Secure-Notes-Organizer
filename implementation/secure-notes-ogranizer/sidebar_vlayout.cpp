// sidebar_layout.cpp
#include "sidebar_vlayout.h"
#include "button_icon_vlayout.h"
#include "constants.h"
#include "add_note_dialog.h"
#include "signout.h"
#include "profile_dialog.h"

const QSize sidebar_vlayout::iconSize = QSize(SIDEBAR_ICON_WIDTH, SIDEBAR_ICON_HEIGHT);

sidebar_vlayout::sidebar_vlayout(QWidget *parent) : QVBoxLayout(parent)
{
    createButton(":/res/img/profile.png", SIDEBAR_ICON_CLASSNAME, iconSize,
                                                            Qt::AlignLeft, [this](){profileButtonClicked();} );
    createButton(":/res/img/plus.png", SIDEBAR_ICON_CLASSNAME, iconSize,
                                                            Qt::AlignLeft, [this](){addNewNoteButtonClicked();} );
    createButton(":/res/img/edit.png", SIDEBAR_ICON_CLASSNAME, iconSize,
                                                            Qt::AlignLeft, [this](){editNoteButtonClicked();} );
    createButton(":/res/img/logout.png", SIDEBAR_ICON_CLASSNAME, iconSize,
                                                            Qt::AlignLeft, [this](){logoutButtonClicked();} );
}

void sidebar_vlayout::createButton(const QString &iconPath, const QString &className, const QSize iconSize,
                                   Qt::Alignment alignment, const std::function<void()> &onClick)
{
    button_icon_vlayout* button = new button_icon_vlayout(iconPath, className, iconSize, alignment, onClick);
    button->setButtonSizePolicy();
    buttons.push_back(button);
    addLayout(button);
}

void sidebar_vlayout::profileButtonClicked()
{
    qDebug() << "Profile Button clicked";
    profile_dialog *profileDialog= new profile_dialog(parentWidget() );
    profileDialog->show();
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
    signout *signoutbutton = new signout(parentWidget());
    signoutbutton->show();
    signoutbutton->setGraphicsEffect(nullptr);

    qDebug() << "Logout Button clicked";
}
