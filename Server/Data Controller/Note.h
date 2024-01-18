#include <string>
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
        ~Note();
};