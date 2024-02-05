#include "mainwindow.h"
#include <QApplication>
#include <clientcontroller.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientController c1("127.0.0.1", "12345");

    /*User user;
    user.setuserName("user100");
    user.sethashedPassword("1234");
    user.setemail("user10@gmail.com");
    std::string response = "";
    bool flag = c1.ClientSignUp(&user, &response);
    std::cout<<response<<std::endl;
    if(flag){
        int id = user.getuserId();
        std::cout<<id<<std::endl;
    }*/

    /*User user;
    user.sethashedPassword("9876");
    user.setemail("user1@gmail.com");
    std::string response = "";
    bool flag = c1.ClientLogIn(&user, &response);
    std::cout<<response<<std::endl;
    if(flag){
        std::string name = user.getuserName();
        int id = user.getuserId();
        std::cout<<id<<std::endl<<name<<std::endl;
    }

    std::vector<Note> List;
    bool flag1 = c1.ClientListNote(&user, &response, List);
    std::cout<<response<<std::endl;
    if(flag1){
        for(int i=0;i<List.size();i++){
            List[i].print();
            std::cout << "/////////////////////////////"<<std::endl;
        }
    }*/

    /*Note note1;
    note1.setuserId(39);
    note1.settitle("note 1");
    std::string response1 = "";
    c1.ClientCreateNote(&note1, &response1);
    std::cout<<response1<<std::endl;
    std::cout<<note1.getnoteId();
    std::cout<<note1.getcreatedAt();

    response1 = "";
    note1.settitle("note 1 updated");
    c1.ClientUpdateNoteTitle(&note1, &response1);
    std::cout<<response1<<std::endl;
    std::cout<<note1.getupdatedAt();

    Note note2;
    note2.setuserId(39);
    note2.settitle("note 2");
    std::string response2 = "";
    c1.ClientCreateNote(&note2, &response2);
    std::cout<<response2<<std::endl;
    std::cout<<note1.getnoteId();
    std::cout<<note2.getcreatedAt();

    response2 = "";
    c1.ClientDeleteNote(&note2, &response2);
    std::cout<<response2<<std::endl;*/

    /*Note note;
    note.setuserId(31);
    note.settitle("Note");
    std::vector<Note> notes;
    std::string response2 = "";
    bool flag1 = c1.ClientSearchByNoteTitle(&note ,&response2 ,notes);
    if(flag1){
        for(int i=0;i<notes.size();i++){
            notes[i].print();
            std::cout << "/////////////////////////////"<<std::endl;
        }
    }*/

    /*User user;
    user.setuserId(39);

    NoteComponent component;
    component.setnoteId(20);
    component.setcomponentContent("QT");
    std::string response2 = "";
    c1.ClientCreateComponent(&component, &user, &response2);
    std::cout<<response2<<std::endl;
    std::cout<<component.getcomponentId()<<std::endl;

    component.setfontColor("red");
    response2 = "";
    c1.ClientUpdateComponent(&component, &user, &response2);
    std::cout<<response2<<std::endl;

    Note note;
    note.setnoteId(20);
    note.setuserId(39);
    response2 = "";
    std::vector<NoteComponent>  list;
    bool flag1 = c1.ClientListComponents(&note, &response2, list);
    if(flag1){
        for(int i=0;i<list.size();i++){
            list[i].print();
            std::cout << "/////////////////////////////"<<std::endl;
        }
    }

    response2 = "";
    c1.ClientDeleteComponent(&component, &user, &response2);
    std::cout<<response2<<std::endl;*/

    /*User user;
    user.setuserId(39);
    Tag tag;
    tag.setnoteId(20);
    tag.settagName("tag test");
    std::string response2 = "";
    c1.ClientAddTag(&tag, &user, &response2);
    std::cout<<response2<<std::endl;
    std::cout<<tag.gettagId()<<std::endl;

    tag.settagName("update tag test");
    response2 = "";
    c1.ClientUpdateTag(&tag, &user, &response2);
    std::cout<<response2<<std::endl;

    response2 = "";
    std::vector<Note> list;
    bool flag1 = c1.ClientFilterByTagName(&tag, &user, &response2, list);
    std::cout<<response2<<std::endl;
    if(flag1){
        for(int i=0;i<list.size();i++){
            list[i].print();
            std::cout << "/////////////////////////////"<<std::endl;
        }
    }

    response2 = "";
    c1.ClientDeleteTag(&tag, &user, &response2);
    std::cout<<response2<<std::endl;*/

    /*User user;
    user.setuserName("user1updated");
    user.sethashedPassword("1234");
    user.setemail("user1@gmail.com");
    std::string response = "";
    bool flag = c1.ClientUpdateUserData(&user, &response);
    std::cout<<response<<std::endl;*/

    /*Note note;
    note.setuserId(31);
    note.setnoteId(16);
    std::string response = "";
    std::vector<Tag> tags;
    c1.ClientListNoteTags(&note, &response, tags);
    for(int i=0;i<tags.size();i++){
        tags[i].print();
        std::cout << "/////////////////////////////"<<std::endl;
    }*/

    c1.ClientLogout();

    MainWindow w;
    w.show();
    return a.exec();
}
