#include "DataController.h"
int main(){
    // the code will be refactored when Note class is implemented
    DataController* dc=new DataController();
    dc->connect("tcp://127.0.0.1","root","root","securenoteorganizertest");
    User* user=new User();
    Note* note=new Note(29,"Note 5");
    user->setuserName("Ahmed");
    user->setemail("ahmedmegz@gmail.com");
    user->sethashedPassword("1234");
    dc->Dc_signup(*user);
    std::cout << "User id: " << user->getuserId() << std::endl;
    dc->Dc_login(*user);
    std::cout << "User id of logged in user: " << user->getuserId() << std::endl;
    dc->Dc_CreateNote(*note);
    note->print();
    delete dc;
    delete user;
    delete note;
    return 0;
}