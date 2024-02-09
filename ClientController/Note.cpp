#include "Note.h"
#include <iostream>
Note::Note(){
    title = "null";
    updatedAt = "null";
    createdAt = "null";
    userId = -1;
    noteId = -1;
}
Note::Note(int userId,std::string title){
    this->userId=userId;
    this->title=title;
}
int Note::getnoteId(){
    return noteId;
}
int Note::getuserId(){
    return userId;
}
std::string Note::gettitle(){
    return title;
}
std::string Note::getcreatedAt(){
    return createdAt;
}
std::string Note::getupdatedAt(){
    return updatedAt;
}
void Note::setnoteId(int noteId){
    this->noteId=noteId;
}
void Note::setuserId(int userId){
    this->userId=userId;
}
void Note::settitle(std::string title){
    this->title=title;
}
void Note::setcreatedAt(std::string createdAt){
    this->createdAt=createdAt;
}
void Note::setupdatedAt(std::string updatedAt){
    this->updatedAt=updatedAt;
}
void Note::print(){
    std::cout << "Note id: " << noteId << std::endl;
    std::cout << "User id: " << userId << std::endl;
    std::cout << "Title: " << title << std::endl;
    std::cout << "Created at: " << createdAt << std::endl;
    std::cout << "Updated at: " << updatedAt << std::endl;
}
// Serialize the object to JSON
json Note::toJson() const {
    return {
        {"user id", userId},
        {"note id", noteId},
        {"note title", title},
        {"created at", createdAt},
        {"updated at", updatedAt}
    };
}

// Deserialize the object from JSON
Note Note::fromJson(const json& json) {
    Note obj;
    obj.userId = json["user id"];
    obj.noteId = json["note id"];
    obj.title = json["note title"];
    obj.createdAt = json["created at"];
    obj.updatedAt = json["updated at"];
    return obj;
}
Note::~Note(){}

