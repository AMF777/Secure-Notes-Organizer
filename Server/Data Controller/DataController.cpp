#include "DataController.h"
void DataController::connect(std::string ip, std::string username, std::string password, std::string schema){
    try{
        driver = get_driver_instance();
        con = driver->connect(ip,username,password);
        con->setSchema(schema);
        stmt=con->createStatement();
        std::cout << "Connected to database Successfully" << std::endl;
    }
    catch(sql::SQLException &e){
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << "Error Code: " << e.getErrorCode() << std::endl;
        std::cout << "SQL State: " << e.getSQLState() << std::endl;
    }
}
bool DataController::Dc_signup(std::string username,std::string email ,std::string hashedPassword){
    try{
        pstmt=con->prepareStatement("INSERT INTO users (username,email,password_hash) VALUES (?,?,?)");
        pstmt->setString(1,username);
        pstmt->setString(2,email);
        pstmt->setString(3,hashedPassword);
        pstmt->execute();
        std::cout << "User added successfully" << std::endl;
        return true;
    }
    catch(sql::SQLException &e){
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << "Error Code: " << e.getErrorCode() << std::endl;
        std::cout << "SQL State: " << e.getSQLState() << std::endl;
        return false;
    }
}
bool DataController::Dc_login(std::string email,std::string hashedPassword){
        try{
            pstmt=con->prepareStatement("SELECT * FROM users WHERE email=? AND password_hash=?");
            pstmt->setString(1,email);
            pstmt->setString(2,hashedPassword);
            res=pstmt->executeQuery();
            if(res->next()){
                std::cout << "User logged in successfully" << std::endl;
                return true;
            }
            else{
                std::cout << "User not found" << std::endl;
                return false;
            }
        }
        catch(sql::SQLException &e){
            std::cout << "Error: " << e.what() << std::endl;
            std::cout << "Error Code: " << e.getErrorCode() << std::endl;
            std::cout << "SQL State: " << e.getSQLState() << std::endl;
            return false;
        }
    }
bool DataController::Dc_CreateNote(int userId, std::string title) {
    try {
        // Check if the specified user_id exists in the users table
        pstmt = con->prepareStatement("SELECT 1 FROM users WHERE user_id = ?");
        pstmt->setInt(1, userId);

        res = pstmt->executeQuery();

        if (!res->next()) {
            std::cout << "Error: User with user_id " << userId << " does not exist." << std::endl;
            return false;
        }

        // Prepare a SQL statement with placeholders
        pstmt = con->prepareStatement("INSERT INTO notes (user_id, title, created_at) VALUES (?, ?, NOW())");

        // Set the values for the placeholders
        pstmt->setInt(1, userId);
        pstmt->setString(2, title);

        // Execute the prepared statement
        pstmt->execute();

        std::cout << "Note added successfully" << std::endl;
        return true;
    } catch (sql::SQLException &e) {
        // Handle any exceptions that might occur during the note creation process

        // Output error details to the console
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << "Error Code: " << e.getErrorCode() << std::endl;
        std::cout << "SQL State: " << e.getSQLState() << std::endl;

        return false;
    }
}
std::vector<std::string> DataController::Dc_ListUsertNotes(int userId) {
    try {
        // Check if the specified user_id exists in the users table
        pstmt = con->prepareStatement("SELECT 1 FROM users WHERE user_id = ?");
        pstmt->setInt(1, userId);

        res = pstmt->executeQuery();

        if (!res->next()) {
            std::cout << "Error: User with user_id " << userId << " does not exist." << std::endl;
            return {};
        }

        // Prepare a SQL statement with placeholders
        pstmt = con->prepareStatement("SELECT * FROM notes WHERE user_id = ?");

        // Set the values for the placeholders
        pstmt->setInt(1, userId);

        // Execute the prepared statement
        res = pstmt->executeQuery();

        // Create a vector to store the note titles
        std::vector<std::string> noteTitles;

        // Iterate over the result set
        while (res->next()) {
            // Get the title of the current note
            std::string title = res->getString("title");

            // Add the title to the vector
            noteTitles.push_back(title);
        }

        // Return the vector
        return noteTitles;
    } catch (sql::SQLException &e) {
        // Handle any exceptions that might occur during the note listing process

        // Output error details to the console
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << "Error Code: " << e.getErrorCode() << std::endl;
        std::cout << "SQL State: " << e.getSQLState() << std::endl;

        return {};
    }
}
std::vector<std::string> DataController::Dc_SearchByTitle(int userId,std::string title){
    try{
        // Check if the specified user_id exists in the users table
        pstmt=con->prepareStatement("SELECT * FROM notes WHERE user_id=? AND title LIKE ?");
        pstmt->setInt(1,userId);
        // to search for a string that contains a specific string we use %string%
        pstmt->setString(2,"%"+title+"%");
        res=pstmt->executeQuery();
        std::vector<std::string> noteTitles;
        // Iterate over the result set
        while(res->next()){
            std::string title=res->getString("title");
            noteTitles.push_back(title);
        }
        return noteTitles;
    }
    // Handle any exceptions that might occur during the Search note listing process
    catch(sql::SQLException &e){
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << "Error Code: " << e.getErrorCode() << std::endl;
        std::cout << "SQL State: " << e.getSQLState() << std::endl;
        return {};
    }
}

DataController::~DataController(){
    std::cout << "Destructor called" << std::endl;
    delete res;
    delete stmt;
    delete con;
    delete pstmt;
}
