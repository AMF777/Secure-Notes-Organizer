#include "Tag.h"
Tag::Tag(){
    tagName = "null";
    noteId = -1;
    tagId = -1;
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
// Serialize the object to JSON
json Tag::toJson() const {
    return {
        {"tag name", tagName},
        {"note id", noteId},
        {"tag id", tagId}
    };
}

// Deserialize the object from JSON
Tag Tag::fromJson(const json& json) {
    Tag obj;
    obj.tagName = json["tag name"];
    obj.noteId = json["note id"];
    obj.tagId = json["tag id"];
    return obj;
}
Tag::~Tag(){}
