#include "User.h"
User::User(){
    std::cout << "User object created" << std::endl;
}
void User::setuserName(std::string name){
    userName=name;
}
void User::sethashedPassword(std::string password){
    hashedPassword=password;
}
void User::setuserId(int id){
    userId=id;
}
void User::setemail(std::string email){
    this->email=email;
}
std::string User::getuserName(){
    return userName;
}
std::string User::gethashedPassword(){
    return hashedPassword;
}
std::string User::getemail(){
    return email;
}
int User::getuserId(){
    return userId;
}
User::~User(){
    std::cout << "User object destroyed" << std::endl;
}