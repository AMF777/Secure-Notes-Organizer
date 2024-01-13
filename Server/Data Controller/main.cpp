#include "DataController.h"
int main(){
    // the code will be refactored when Note class is implemented
    DataController* dc=new DataController();
    dc->connect("tcp://127.0.0.1","root","root","securenoteorganizertest");
    dc->Dc_signup("Ahmed","test@gmail.com","test");
    dc->Dc_login("test@gmail.com","test");
    //dc->Dc_CreateNote(1,"My fire note");
    std::vector<std::string> notes=dc->Dc_ListUsertNotes(1);
    std::cout << "User 1 notes:" << std::endl;
    for(int i=0;i<notes.size();i++){
        std::cout << notes[i] << std::endl;
    }
    std::vector<std::string> searchResults=dc->Dc_SearchByTitle(1,"My S");
    std::cout << "Search results:" << std::endl;
    for(int i=0;i<searchResults.size();i++){
        std::cout << searchResults[i] << std::endl;
    }
    delete dc;
    return 0;
}