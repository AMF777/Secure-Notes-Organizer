#include "Note.h"
#include <iostream>
Note::Note(){
    std::cout << "Note object created" << std::endl;
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
Note::~Note(){
    std::cout << "Note object destroyed" << std::endl;
}