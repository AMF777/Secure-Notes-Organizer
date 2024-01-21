#include "DataController.h"
int main(){
    // the code will be refactored when Note class is implemented
    DataController* dc=new DataController();
    dc->connect("tcp://127.0.0.1","root","root","securenoteorganizertest");
    User* user=new User();
    user->setuserName("Ahmed");
    user->setemail("ahmedmegz864@gmail.com");
    user->sethashedPassword("1234");
    //dc->Dc_signup(*user);
    dc->Dc_login(*user);
    std::cout << "User id of logged in user: " << user->getuserId() << std::endl;
    Tag *tag=new Tag();
    tag->setnoteId(6);
    tag->settagId(1);
    dc->Dc_DeleteTag(*tag,user->getuserId());
    /*Tag *tag=new Tag("History updated",2);
    tag->settagId(10);
    dc->Dc_UpdateTag(*tag,user->getuserId());
    tag->print();*/
    /*std::vector<Note> notes=dc->Dc_FilterByTagName("Art",user->getuserId());
    for(int i=0;i<notes.size();i++){
        notes[i].print();
        std::cout << "/////////////////////////////"<<std::endl;
    }*/
    /*Note* note=new Note();
    note->setuserId(user->getuserId());
    note->settitle("Note 1 for mary updated");
    note->setnoteId(9);*/
    //note->setnoteId(7);
    //dc->Dc_UpdateNoteTitle(*note);
    //dc->Dc_CreateNote(*note);
    /*std::vector<Note> notes=dc->Dc_ListUserNotes(user->getuserId());
    for(int i=0;i<notes.size();i++){
        notes[i].print();
        std::cout << "/////////////////////////////"<<std::endl;
    }*/
    /*Note *note=new Note();
    note->setuserId(user->getuserId());
    note->setnoteId(7);*/
    /*NoteComponent *noteComponent=new NoteComponent(note->getnoteId(),"This is a test to update note component",20,"#0afffss","#ffffff","Arial","normal",true,true,false);
    noteComponent->setcomponentId(3);
    dc->Dc_UpdateNoteComponent(*noteComponent,user->getuserId());
    std::vector<NoteComponent> noteComponents=dc->Dc_ListNoteComponents(*note);
    for(int i=0;i<noteComponents.size();i++){
        noteComponents[i].print();
        std::cout << "/////////////////////////////"<<std::endl;
    }*/
    //dc->Dc_DeleteNoteComponent(3,user->getuserId(),note->getnoteId());
    //dc->Dc_DeleteNote(7,user->getuserId());

    delete dc;
    delete user;
    //delete note;
    //delete noteComponent;
    return 0;
}