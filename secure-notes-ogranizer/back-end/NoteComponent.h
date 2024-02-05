#include <iostream>
#include <string>
#include "json.hpp"

using json = nlohmann::json;

class NoteComponent{
    private:
        int componentId;
        int noteId;
        std::string componentContent;
        int fontSize;
        std::string fontColor;
        std::string backgroundColor;
        std:: string fontFamily;
        std:: string fontStyle;
        bool isBold;
        bool isItalic;
        bool isUnderlined;
    public:
        NoteComponent();
        NoteComponent(int noteId,std::string componentContent,int fontSize,std::string fontColor,std::string backgroundColor,std::string fontFamily,std::string fontStyle,bool isBold,bool isItalic,bool isUnderlined);
        void setcomponentId(int id);
        void setnoteId(int id);
        void setcomponentContent(std::string content);
        void setfontSize(int size);
        void setfontColor(std::string color);
        void setbackgroundColor(std::string color);
        void setfontFamily(std::string family);
        void setfontStyle(std::string style);
        void setisBold(bool bold);
        void setisItalic(bool italic);
        void setisUnderlined(bool underlined);
        int getcomponentId();
        int getnoteId();
        std::string getcomponentContent();
        int getfontSize();
        std::string getfontColor();
        std::string getbackgroundColor();
        std::string getfontFamily();
        std::string getfontStyle();
        bool getisBold();
        bool getisItalic();
        bool getisUnderlined();
        // for debugging purposes
        void print();
        // Serialize the object to JSON
        json toJson() const;
        // Deserialize the object from JSON
        NoteComponent fromJson(const json& json);
        ~NoteComponent();    
};

// Provide a specialization of nlohmann::adl_serializer for NoteComponent
namespace nlohmann {
template <>
struct adl_serializer<NoteComponent> {
    static void to_json(json& j, const NoteComponent& obj) {
        j = obj.toJson();
    }

    static void from_json(const json& j, NoteComponent& obj) {
        NoteComponent temp;
        obj = temp.fromJson(j);
    }
};
}  // namespace nlohmann
