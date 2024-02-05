// sidebar_layout.cpp
#include "sidebar_vlayout.h"
#include "button_icon_vlayout.h"
#include "constants.h"
#include "add_note_dialog.h"
#include "signout.h"
#include "profile_dialog.h"

// Set the default icon size for the sidebar buttons
const QSize sidebar_vlayout::iconSize = QSize(SIDEBAR_ICON_WIDTH, SIDEBAR_ICON_HEIGHT);

// Constructor for the sidebar layout
sidebar_vlayout::sidebar_vlayout(QWidget *parent) : QVBoxLayout(parent)
{
    // Create profile button
    createButton(":/res/img/profile.png", SIDEBAR_ICON_CLASSNAME, iconSize,
                 Qt::AlignLeft, [this](){profileButtonClicked();});
    // Create add new note button
    createButton(":/res/img/plus.png", SIDEBAR_ICON_CLASSNAME, iconSize,
                 Qt::AlignLeft, [this](){addNewNoteButtonClicked();});
    // Create view note button
    createButton(":/res/img/note-icon.png", SIDEBAR_ICON_CLASSNAME, iconSize,
                 Qt::AlignLeft, nullptr);
    createButton(":/res/img/edit.png", SIDEBAR_ICON_CLASSNAME, iconSize,
                 Qt::AlignLeft, nullptr);
    // Create logout button
    createButton(":/res/img/logout.png", SIDEBAR_ICON_CLASSNAME, iconSize,
                 Qt::AlignLeft, [this](){logoutButtonClicked();});
}

sidebar_vlayout::sidebar_vlayout(std::function<void ()> swapToEdit, std::function<void ()> swapToShow, QWidget *parent)
    : sidebar_vlayout(parent)
{
    buttons[2]->setClickHandler(swapToEdit);
    buttons[3]->setClickHandler(swapToShow);
}

sidebar_vlayout::sidebar_vlayout(const std::function<void ()> swapToEdit, const std::function<void ()> swapToShow,
                                 const std::function<void (QString)> initEditorFromFile, QWidget *parent) : sidebar_vlayout(parent)
{
    // buttons[1]->setClickHandler(initEditorFromFile);
    this->initEditorFromFile=initEditorFromFile;
    buttons[2]->setClickHandler(swapToEdit);
    buttons[3]->setClickHandler(swapToShow);
}

// Function to create a button and add it to the layout
void sidebar_vlayout::createButton(const QString &iconPath, const QString &className, const QSize iconSize,
                                   Qt::Alignment alignment, const std::function<void()> &onClick)
{
    // Create a button with the specified properties
    button_icon_vlayout* button = new button_icon_vlayout(iconPath, className, iconSize, alignment, onClick);
    button->button->setCursor(Qt::PointingHandCursor);
    // Set the button size policy
    button->setButtonSizePolicy();

    // Add the button to the layout and store it in the buttons vector
    buttons.push_back(button);
    addLayout(button);
}

void sidebar_vlayout::setUser(User *user)
{
    qDebug() <<  "1";
    qDebug() <<  user->getemail();
    this->user = user;
}

// Function to handle profile button click
void sidebar_vlayout::profileButtonClicked()
{
    qDebug() << "Profile Button clicked";

    // Create and show the profile dialog
    profile_dialog *profileDialog = new profile_dialog(user, parentWidget());
    profileDialog->show();
}

// Function to handle add new note button click
void sidebar_vlayout::addNewNoteButtonClicked()
{
    qDebug() << "Add New Note Button clicked";

    // Create and show the add note dialog
    // add_note_dialog *addNoteDialog = new add_note_dialog(parentWidget());
    add_note_dialog *addNoteDialog = new add_note_dialog(initEditorFromFile, parentWidget());
    addNoteDialog->show();
}

// // Function to handle edit note button click
// void sidebar_vlayout::editNoteButtonClicked()
// {
//     qDebug() << "Edit Note Button clicked";
//     // Add the implementation for editing a note here
// }

// Function to handle logout button click
void sidebar_vlayout::logoutButtonClicked()
{
    // Create and show the signout dialog
    signout *signoutbutton = new signout(parentWidget());
    signoutbutton->show();
    signoutbutton->setGraphicsEffect(nullptr);

    qDebug() << "Logout Button clicked";
}

// void sidebar_vlayout::viewNotesClicked()
// {
//     qDebug() << "View notes clicked";
// }
