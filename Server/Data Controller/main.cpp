#include <thread>
#include <vector>
#include "DataController.h"


int main(){
    // Number of threads
    const int numThreads = 3;

    // Create a vector to hold the threads
    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; i++) {
        // Create a new thread
        threads.push_back(std::thread([i]() {
            // Create a new DataController instance for this thread
            DataController* dc = new DataController();

            // Connect to the database
            dc->connect("tcp://127.0.0.1", "root", "root", "securenoteorganizertest");

            // Create a new User instance for this thread
            User* user = new User();
            user->setuserName("Ahmed");
            user->setemail("ahmedmegz864@gmail.com");
            user->sethashedPassword("1234");

            // Log in the user
            dc->Dc_login(*user);
            std::cout << "User id of logged in user: " << user->getuserId() << std::endl;

            // Create a new Tag instance for this thread
            Tag* tag = new Tag();
            tag->settagName("Tag multithreading test upated " + std::to_string(i));
            tag->setnoteId(36);
            tag->settagId(8);

            // Add the tag
            dc->Dc_DeleteTag(*tag, 1);
            /*std::vector<Note> notes = dc->Dc_FilterByTagName("Art", 5);
            for (int i = 0; i < notes.size(); i++) {
                notes[i].print();
                std::cout << "/////////////////////////////" << std::endl;
            }*/
            // Clean up
            std::cout << "Cleaning up thread " << i << std::endl;
            delete tag;
            delete user;
            delete dc;
        }));
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
    // the code will be refactored when Note class is implemented
    //DataController* dc=new DataController();
    //dc->connect("tcp://127.0.0.1","root","root","securenoteorganizertest");
    /*User* user=new User();
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

    //delete dc;
    //delete user;
    //delete note;
    //delete noteComponent;
    //return 0;
    /*DataController* dc=new DataController();
    dc->connect("tcp://127.0.0.1","root","root","securenoteorganizertest");
    User* user=new User();
    user->setuserName("Ahmed");
    user->setemail("ahmedmegz864@gmail.com ");
    user->sethashedPassword("1234");
    dc->Dc_login(*user);
    std::cout << "User id of logged in user: " << user->getuserId() << std::endl;
    Note* note=new Note();
    note->setuserId(user->getuserId());
    note->settitle("Note 1 for Ahmed");
    dc->Dc_CreateNote(*note);
    delete dc;
    delete user;
    delete note;*/
}