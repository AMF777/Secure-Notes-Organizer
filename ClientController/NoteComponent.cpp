#include "NoteComponent.h"

NoteComponent::NoteComponent(){
    componentId = -1;
    noteId = -1;
    componentContent = "null";
    fontSize = -1;
    fontColor = "null";
    backgroundColor = "null";
    fontFamily = "null";
    fontStyle = "null";
    isBold = false;
    isItalic = false;
    isUnderlined = false;
}
NoteComponent::NoteComponent(int noteId,std::string componentContent,int fontSize,std::string fontColor,std::string backgroundColor,std::string fontFamily,std::string fontStyle,bool isBold,bool isItalic,bool isUnderlined){
    this->noteId=noteId;
    this->componentContent=componentContent;
    this->fontSize=fontSize;
    this->fontColor=fontColor;
    this->backgroundColor=backgroundColor;
    this->fontFamily=fontFamily;
    this->fontStyle=fontStyle;
    this->isBold=isBold;
    this->isItalic=isItalic;
    this->isUnderlined=isUnderlined;
}
void NoteComponent::setcomponentId(int id){
    componentId=id;
}
void NoteComponent::setnoteId(int id){
    noteId=id;
}
void NoteComponent::setcomponentContent(std::string content){
    componentContent=content;
}
void NoteComponent::setfontSize(int size){
    fontSize=size;
}
void NoteComponent::setfontColor(std::string color){
    fontColor=color;
}
void NoteComponent::setbackgroundColor(std::string color){
    backgroundColor=color;
}
void NoteComponent::setfontFamily(std::string family){
    fontFamily=family;
}
void NoteComponent::setfontStyle(std::string style){
    fontStyle=style;
}
void NoteComponent::setisBold(bool bold){
    isBold=bold;
}
void NoteComponent::setisItalic(bool italic){
    isItalic=italic;
}
void NoteComponent::setisUnderlined(bool underlined){
    isUnderlined=underlined;
}
int NoteComponent::getcomponentId(){
    return componentId;
}
int NoteComponent::getnoteId(){
    return noteId;
}
std::string NoteComponent::getcomponentContent(){
    return componentContent;
}
int NoteComponent::getfontSize(){
    return fontSize;
}
std::string NoteComponent::getfontColor(){
    return fontColor;
}
std::string NoteComponent::getbackgroundColor(){
    return backgroundColor;
}
std::string NoteComponent::getfontFamily(){
    return fontFamily;
}
std::string NoteComponent::getfontStyle(){
    return fontStyle;
}
bool NoteComponent::getisBold(){
    return isBold;
}
bool NoteComponent::getisItalic(){
    return isItalic;
}
bool NoteComponent::getisUnderlined(){
    return isUnderlined;
}
void NoteComponent::print(){
    std::cout << "Component id: " << componentId << std::endl;
    std::cout << "Note id: " << noteId << std::endl;
    std::cout << "Component content: " << componentContent << std::endl;
    std::cout << "Font size: " << fontSize << std::endl;
    std::cout << "Font color: " << fontColor << std::endl;
    std::cout << "Background color: " << backgroundColor << std::endl;
    std::cout << "Font family: " << fontFamily << std::endl;
    std::cout << "Font style: " << fontStyle << std::endl;
    std::cout << "Is bold: " << isBold << std::endl;
    std::cout << "Is italic: " << isItalic << std::endl;
    std::cout << "Is underlined: " << isUnderlined << std::endl;
}
// Serialize the object to JSON
json NoteComponent::toJson() const {
    return {
        {"component id", componentId},
        {"note id", noteId},
        {"component content", componentContent},
        {"font size", fontSize},
        {"font color", fontColor},
        {"background color", backgroundColor},
        {"font family", fontFamily},
        {"font style", fontStyle},
        {"font bold", isBold},
        {"font italic", isItalic},
        {"font underlined", isUnderlined}
    };
}

// Deserialize the object from JSON
NoteComponent NoteComponent::fromJson(const json& json) {
    NoteComponent obj;
    obj.componentId = json["component id"];
    obj.noteId = json["note id"];
    obj.componentContent = json["component content"];
    obj.fontSize = json["font size"];
    obj.fontColor = json["font color"];
    obj.backgroundColor = json["background color"];
    obj.fontFamily = json["font family"];
    obj.fontStyle = json["font style"];
    obj.isBold = json["font bold"];
    obj.isItalic = json["font italic"];
    obj.isUnderlined = json["font underlined"];
    return obj;
}
NoteComponent::~NoteComponent(){}