#include <iostream>
#include <string>
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
        ~Tag();
    private:
        std::string tagName;
        int noteId;
        int tagId;
};