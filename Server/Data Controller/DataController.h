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
using namespace sql;
class DataController{
    private:
        Driver *driver;
        Connection *con;
        Statement *stmt;
        ResultSet *res;
        PreparedStatement *pstmt;
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
        std::vector<Note> Dc_ListUserNotes(int userId);
        std::vector<Note> Dc_SearchByTitle(int userId,std::string title);
        std::vector<std::string> Dc_ListUsertNotes(int userId);
        bool Dc_CreateNoteComponent(NoteComponent& noteComponent,int userId);
        
};