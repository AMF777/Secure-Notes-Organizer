#include <string>
#include "json.hpp"

using json = nlohmann::json;

class Note{
    private:
        int noteId;
        int userId;
        std::string title;
        std::string createdAt;
        std::string updatedAt;
    public:
        Note();
        Note(int userId,std::string title);
        int getnoteId();
        int getuserId();
        std::string gettitle();
        std::string getcreatedAt();
        std::string getupdatedAt();
        void setnoteId(int noteId);
        void setuserId(int userId);
        void settitle(std::string title);
        void setcreatedAt(std::string createdAt);
        void setupdatedAt(std::string updatedAt);
        // for debugging purposes
        void print();
        // Serialize the object to JSON
        json toJson() const;
        // Deserialize the object from JSON
        Note fromJson(const json& json);
        ~Note();
};

// Provide a specialization of nlohmann::adl_serializer for Note
namespace nlohmann {
template <>
struct adl_serializer<Note> {
    static void to_json(json& j, const Note& obj) {
        j = obj.toJson();
    }

    static void from_json(const json& j, Note& obj) {
        Note temp;
        obj = temp.fromJson(j);
    }
};
}  // namespace nlohmann
