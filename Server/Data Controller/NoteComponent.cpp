#include "NoteComponent.h"
NoteComponent::NoteComponent(){
    std::cout << "NoteComponent object created" << std::endl;
}
NoteComponent::NoteComponent(int noteId,std::string componentContent,int fontSize,std::string fontColor,std::string backgroundColor,bool isBold,bool isItalic,bool isUnderlined){
    this->noteId=noteId;
    this->componentContent=componentContent;
    this->fontSize=fontSize;
    this->fontColor=fontColor;
    this->backgroundColor=backgroundColor;
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
    std::cout << "Is bold: " << isBold << std::endl;
    std::cout << "Is italic: " << isItalic << std::endl;
    std::cout << "Is underlined: " << isUnderlined << std::endl;
}
NoteComponent::~NoteComponent(){
    std::cout << "NoteComponent object destroyed" << std::endl;
}