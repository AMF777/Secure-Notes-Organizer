#include "User.h"

User::User(){
    userName = "null";
    email = "null";
    hashedPassword = "null";
    userId = -1;
}
void User::setuserName(std::string name){
    userName=name;
}
void User::sethashedPassword(std::string password){
    hashedPassword=password;
}
void User::setuserId(int id){
    userId=id;
}
void User::setemail(std::string email){
    this->email=email;
}
std::string User::getuserName(){
    return userName;
}
std::string User::gethashedPassword(){
    return hashedPassword;
}
std::string User::getemail(){
    return email;
}
int User::getuserId(){
    return userId;
}

// Method to hash a password using the stored salt
QString User::hashPassword(QString password) {
    QString  salt = "qIzbnqxn6ltPtEyi";
    // Concatenate the password and salt, then hash using SHA-256
    QByteArray dataToHash = password.toUtf8() + salt.toUtf8();
    QByteArray hashedData = QCryptographicHash::hash(dataToHash, QCryptographicHash::Sha256);

    // Convert the hashed data to a hexadecimal representation
    return QString::fromUtf8(hashedData.toHex());
}

// Method to verify a password by comparing hashed input with stored hashed password
bool User::verifyPassword(const QString &inputPassword, const QString &hashedPasswordToCheck) {
    // Hash the input password to compare with the provided hashed password
    QString hashedInputPassword = hashPassword(inputPassword);

    // Compare the hashed input password with the provided hashed password
    return (hashedInputPassword == hashedPasswordToCheck);
}


// Serialize the object to JSON
json User::toJson() const {
    return {
        {"user id", userId},
        {"user name", userName},
        {"user email", email},
        {"user hashed password", hashedPassword}
    };
}

// Deserialize the object from JSON
User User::fromJson(const json& json) {
    User obj;
    obj.userId = json["user id"];
    obj.userName = json["user name"];
    obj.email = json["user email"];
    obj.hashedPassword = json["user hashed password"];
    return obj;
}
User::~User(){
}
