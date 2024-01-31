#include "signin.h"
#include "signup.h"
#include "switcher_widget.h"
#include "main_window.h"
#include "add_note_dialog.h"

#include <QWidget>
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <iostream>

void load_style_sheet();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    load_style_sheet();

    // signin w;
    // w.show();

    // signup w;
    // w.show();
    // switcher_widget w;
    // w.show();


    main_window w;
    w.show();

    QWidget mainWindow;
    QVBoxLayout *mainLayout = new QVBoxLayout(&mainWindow);

    // Create a button to open the dialog
    QPushButton *openDialogButton = new QPushButton("Open Dialog");
    mainLayout->addWidget(openDialogButton);

    // Create the custom dialog
    add_note_dialog *addNoteDialog = new add_note_dialog(&mainWindow);

    // Connect the button click to show the dialog
    QObject::connect(openDialogButton, &QPushButton::clicked, addNoteDialog, &add_note_dialog::exec);

    // mainWindow.show();
    // type width and height
    // int initialWidth = w.width();
    // int initialHeight = w.height();
    // std::cout << "Initial: Width = " << initialWidth << ", Height = " << initialHeight << std::endl;
    return a.exec();
}


void load_style_sheet(){
    // use res to store and load any file
    // always use forward slash with qfile
    QFile styleFile(":/res/styles/styles.qss"); // Assuming the file is added as a resource
    styleFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream styleStream(&styleFile);
    QString style = styleStream.readAll();
    styleFile.close();
    qApp->setStyleSheet(style);
}
