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

    /*User user;
    user.setuserName("user3");
    user.sethashedPassword("1234");
    user.setemail("user3@gmail.com");
    std::string response = "";
    bool flag = c1.ClientSignUp(&user, &response);
    std::cout<<response<<std::endl;
    if(flag){
        int id = user.getuserId();
        std::cout<<id<<std::endl;
    }*/
    ClientController c1("127.0.0.1", "12345");
    User user;
    user.sethashedPassword("2001");
    user.setemail("mo3@gmail.com");
    user.setuserId(1);
    std::string response = "";
    // bool flag = c1.ClientLogIn(&user, &response);
    // std::cout<<response<<std::endl;

    NoteComponent temp;
    temp.setnoteId(6);
    temp.setcomponentId(5);
    bool flag1 = c1.ClientDeleteComponent(&temp, &user, &response);
    std::cout<<response<<std::endl;
    if(flag1){
        std::cout<<response<<std::endl;
    }
    /*User user;
    user.setuserName("user3");
    user.sethashedPassword("1234");
    user.setemail("user3@gmail.com");
    std::string response = "";
    bool flag = c1.ClientSignUp(&user, &response);
    std::cout<<response<<std::endl;
    if(flag){
        int id = user.getuserId();
        std::cout<<id<<std::endl;
    }*/
    // User user;
    // user.sethashedPassword("2001");
    // user.setemail("mo3@gmail.com");
    // std::string response = "";
    // bool flag = c1.ClientLogIn(&user, &response);
    // std::cout<<response<<std::endl;
    // if(flag){
    //     std::string name = user.getuserName();
    //     int id = user.getuserId();
    //     std::cout<<id<<std::endl<<name<<std::endl;
    // }

    // std::vector<Note> List;
    // bool flag1 = c1.ClientListNote(&user, &response, List);
    // std::cout<<response<<std::endl;
    // if(flag1){
    //     for(int i=0;i<List.size();i++){
    //         List[i].print();
    //         std::cout << "/////////////////////////////"<<std::endl;
    //     }
    // }

    load_style_sheet();

    switcher_widget w;
    w.show();

    // signup w;
    // w.show();
    // switcher_widget w;
    // w.show();




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
