#include "main_window.h"
#include "sidebar_vlayout.h"

main_window::main_window(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *central_widget = new QWidget(this);

    SidebarLayout *layout = new SidebarLayout(central_widget);
    QString className = "sidebar-button";

    layout->createButton(":/res/img/profile.png", className, Qt::AlignLeft, [this](){ profileButtonClicked();});

    layout->createButton(":/res/img/plus.png", className, Qt::AlignLeft, [this](){ addNewNoteButtonClicked();});

    layout->createButton(":/res/img/edit.png", className, Qt::AlignLeft, [this](){ editNoteButtonClicked();});

    layout->createButton(":/res/img/logout.png", className, Qt::AlignLeft, [this](){ logoutButtonClicked();});

    setCentralWidget(central_widget);
}

void main_window::profileButtonClicked()
{
    qDebug() << "Profile Button clicked";
}

void main_window::addNewNoteButtonClicked()
{
    qDebug() << "Add New Note Button clicked";
}

void main_window::editNoteButtonClicked()
{
    qDebug() << "Edit Note Button clicked";
}

void main_window::logoutButtonClicked()
{
    qDebug() << "Logout Button clicked";
}
