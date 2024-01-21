#include "Tag.h"
Tag::Tag(){
    std::cout << "Tag object created" << std::endl;
}
Tag::Tag(std::string tagName,int noteId){
    this->tagName=tagName;
    this->noteId=noteId;
}
void Tag::settagName(std::string tagName){
    this->tagName=tagName;
}
void Tag::setnoteId(int noteId){
    this->noteId=noteId;
}
void Tag::settagId(int tagId){
    this->tagId=tagId;
}
std::string Tag::gettagName(){
    return this->tagName;
}
int Tag::getnoteId(){
    return this->noteId;
}
int Tag::gettagId(){
    return this->tagId;
}
void Tag::print(){
    std::cout << "Tag name: " << this->tagName << std::endl;
    std::cout << "Note id: " << this->noteId << std::endl;
    std::cout << "Tag id: " << this->tagId << std::endl;
}
Tag::~Tag(){
    std::cout << "Tag object destroyed" << std::endl;
}
