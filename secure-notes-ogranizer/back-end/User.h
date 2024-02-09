#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

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
        // Serialize the object to JSON
        json toJson() const;
        // Deserialize the object from JSON
        User fromJson(const json& json);
        ~User();
    private:
        std::string userName;
        std::string hashedPassword;
        std::string email;
        int userId;
};
#endif
