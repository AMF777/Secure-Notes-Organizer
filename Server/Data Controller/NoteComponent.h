#include <iostream>
#include <string>
class NoteComponent{
    private:
        int componentId;
        int noteId;
        std::string componentContent;
        int fontSize;
        std::string fontColor;
        std::string backgroundColor;
        bool isBold;
        bool isItalic;
        bool isUnderlined;
    public:
        NoteComponent();
        NoteComponent(int noteId,std::string componentContent,int fontSize,std::string fontColor,std::string backgroundColor,bool isBold,bool isItalic,bool isUnderlined);
        void setcomponentId(int id);
        void setnoteId(int id);
        void setcomponentContent(std::string content);
        void setfontSize(int size);
        void setfontColor(std::string color);
        void setbackgroundColor(std::string color);
        void setisBold(bool bold);
        void setisItalic(bool italic);
        void setisUnderlined(bool underlined);
        int getcomponentId();
        int getnoteId();
        std::string getcomponentContent();
        int getfontSize();
        std::string getfontColor();
        std::string getbackgroundColor();
        bool getisBold();
        bool getisItalic();
        bool getisUnderlined();
        ~NoteComponent();    
};