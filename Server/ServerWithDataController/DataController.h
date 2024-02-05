#include <iostream>
#include <mysql_connection.h>
#include <exception>
#include <mysql_driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <string>
#include <vector>
#include "User.h"
#include "Note.h"
#include "NoteComponent.h"
#include "Tag.h"
#include <mutex>
using namespace sql;
class DataController{
    private:
        Driver *driver;
        Connection *con;
        Statement *stmt;
        ResultSet *res;
        PreparedStatement *pstmt;
        std::mutex mtx;
    public:
        ~DataController();
        void connect(std::string ip, std::string username, std::string password, std::string schema);
        bool Dc_signup(User& user);
        int Dc_getUserId(std::string email);
        bool Dc_login(User& user);
        bool Dc_CreateNote(int userId,std::string title);
        bool Dc_CreateNote(Note& note);
        // this is a helper function to get the current time in the format of YYYY-MM-DD HH:MM:SS to be used in the create and update note functions
        std::string Dc_getNoteCreatedAt(int noteId);
        std::string Dc_getNoteUpdatedAt(int noteId);
        int Dc_getNoteId(Note& note);
        bool Dc_UpdateNoteTitle(Note& note);
        //std::vector<Note> Dc_ListUserNotes(int userId);
        //std::vector<Note> Dc_SearchByTitle(int userId,std::string title);
        bool Dc_CreateNoteComponent(NoteComponent& noteComponent,int userId);
        bool Dc_UpdateNoteComponent(NoteComponent& noteComponent,int userId);
        bool Dc_DeleteNoteComponent(int componentId,int userId,int noteId);
        bool Dc_DeleteNote(int noteId,int userId);
        bool Dc_AddTag(Tag& tag,int userId);
        bool Dc_UpdateTag(Tag& tag,int userId);
        //std::vector<Note> Dc_FilterByTagName(std::string tagName,int userId);
        bool Dc_DeleteTag(Tag& tag,int userId);
        //std::vector<Tag>Dc_ListNoteTags(int noteId,int userId);
        bool Dc_UpdateUserData(User& user);
        /*modified apis to include response*/
        std::vector<Note> Dc_ListUserNotes(int userId,std::string& response);
        std::vector<Note> Dc_SearchByTitle(int userId,std::string title,std::string& response);
        std::vector<NoteComponent> Dc_ListNoteComponents(Note& note,std::string& response);
        std::vector<Note> Dc_FilterByTagName(std::string tagName,int userId,std::string& response);
        std::vector<Tag>Dc_ListNoteTags(int noteId,int userId,std::string& response);
};