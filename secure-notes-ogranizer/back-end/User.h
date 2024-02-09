#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include <QString>
#include <QCryptographicHash>
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
        // For hashing Password
        QString hashPassword(QString password);
        bool verifyPassword(const QString &inputPassword, const QString &hashedPasswordToCheck);
        // Serialize the object to JSON
        json toJson() const;
        // Deserialize the object from JSON
        User fromJson(const json& json);
        ~User();
        static QString getSALT();

    private:
        std::string userName;
        std::string hashedPassword;
        std::string email;
        int userId;
};

#endif
