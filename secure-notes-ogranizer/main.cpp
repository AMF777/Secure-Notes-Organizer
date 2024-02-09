#include "signin.h"
#include "signup.h"
#include "switcher_widget.h"
#include "main_window.h"
#include "add_note_dialog.h"
#include <QWidget>
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include "back-end/clientcontroller.h"

void load_style_sheet();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    load_style_sheet();

    switcher_widget w;
    w.show();
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
