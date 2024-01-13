#include <iostream>
#include <mysql_connection.h>
#include <exception>
#include <mysql_driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <string>
#include <vector>
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
        bool Dc_signup(std::string username,std::string email,std::string hashedPassword);
        bool Dc_login(std::string email,std::string hashedPassword);
        bool Dc_CreateNote(int userId,std::string title);
        std::vector<std::string> Dc_ListUsertNotes(int userId);
        std::vector<std::string> Dc_SearchByTitle(int userId,std::string title);
};