#include "User.h"

User::User(){
    userName = "null";
    email = "null";
    hashedPassword = "null";
    userId = -1;
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
// Serialize the object to JSON
json User::toJson() const {
    return {
        {"user id", userId},
        {"user name", userName},
        {"user email", email},
        {"user hashed password", hashedPassword}
    };
}

// Deserialize the object from JSON
User User::fromJson(const json& json) {
    User obj;
    obj.userId = json["user id"];
    obj.userName = json["user name"];
    obj.email = json["user email"];
    obj.hashedPassword = json["user hashed password"];
    return obj;
}
User::~User(){}
