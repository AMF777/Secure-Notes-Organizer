#include <iostream>
#include <string>
#include <json.hpp>

using json = nlohmann::json;

class Tag{
    public:
        Tag();
        Tag(std::string tagName,int noteId);
        void settagName(std::string tagName);
        void setnoteId(int noteId);
        void settagId(int tagId);
        std::string gettagName();
        int getnoteId();
        int gettagId();
        void print();
        // Serialize the object to JSON
        json toJson() const;
        // Deserialize the object from JSON
        Tag fromJson(const json& json);
        ~Tag();
    private:
        std::string tagName;
        int noteId;
        int tagId;
};