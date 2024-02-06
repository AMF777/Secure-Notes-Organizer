#include <iostream>
#include <string>
#include "json.hpp"

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

// Provide a specialization of nlohmann::adl_serializer for Tag
namespace nlohmann {
template <>
struct adl_serializer<Tag> {
        static void to_json(json& j, const Tag& obj) {
            j = obj.toJson();
        }

        static void from_json(const json& j, Tag& obj) {
            Tag temp;
            obj = temp.fromJson(j);
        }
};
}  // namespace nlohmann
