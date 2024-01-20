#include "DataController.h"
int main(){
    // the code will be refactored when Note class is implemented
    DataController* dc=new DataController();
    dc->connect("tcp://127.0.0.1","root","root","securenoteorganizertest");
    User* user=new User();
    /*Note* note=new Note();
    note->setuserId(29);
    note->setnoteId(10);
    note->settitle("Note 1 updated3");*/
    user->setuserName("Ahmed");
    user->setemail("ahmedmegz@gmail.com");
    user->sethashedPassword("1234");
    dc->Dc_signup(*user);
    std::cout << "User id: " << user->getuserId() << std::endl;
    dc->Dc_login(*user);
    std::cout << "User id of logged in user: " << user->getuserId() << std::endl;
    std::cout << "User name of logged in user: " << user->getuserName() << std::endl;
    //dc->Dc_CreateNote(*note);
    //dc->Dc_UpdateNoteTitle(*note);
    //note->print();
    //std::vector<Note> notes=dc->Dc_ListUserNotes(user->getuserId());
    NoteComponent *noteComponent=new NoteComponent(10,"I am writing my updated Note Component for Note 1 Updated3",20,"black","white",true,true,false);
    noteComponent->setcomponentId(1);
    //dc->Dc_CreateNoteComponent(*noteComponent,user->getuserId());
    dc->Dc_UpdateNoteComponent(*noteComponent,user->getuserId());
    noteComponent->print();
    std::vector<Note> notes=dc->Dc_SearchByTitle(user->getuserId(),"not");
    for(int i=0;i<notes.size();i++){
        notes[i].print();
        std::cout << "/////////////////////////////"<<std::endl;
    }
    delete dc;
    delete user;
    //delete note;
    delete noteComponent;
    return 0;
}