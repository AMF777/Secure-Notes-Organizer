#include <string>
#include <iostream>
class User{
    public:
        User();
        std::string getuserName();
        std::string gethashedPassword();
        std::string getemail();
        int getuserId();
        void setuserName(std::string name);
        void sethashedPassword(std::string password);
        void setuserId(int id);
        void setemail(std::string email);
        ~User();
    private:
        std::string userName;
        std::string hashedPassword;
        std::string email;
        int userId;
};