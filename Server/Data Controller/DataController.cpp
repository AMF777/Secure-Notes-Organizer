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
bool DataController::Dc_signup(User& user){
    try{
        pstmt=con->prepareStatement("INSERT INTO users (username,email,password_hash) VALUES (?,?,?)");
        pstmt->setString(1,user.getuserName());
        pstmt->setString(2,user.getemail());
        pstmt->setString(3,user.gethashedPassword());
        pstmt->execute();
        std::cout << "User added successfully" << std::endl;
        user.setuserId(Dc_getUserId(user.getemail()));
        return true;
    }
    catch(sql::SQLException &e){
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << "Error Code: " << e.getErrorCode() << std::endl;
        std::cout << "SQL State: " << e.getSQLState() << std::endl;
        return false;
    }
}
// This function returns the user_id of the user with the specified email to be used in the login function
int DataController::Dc_getUserId(std::string email){
    try{
        pstmt=con->prepareStatement("SELECT user_id FROM users WHERE email=?");
        pstmt->setString(1,email);
        res=pstmt->executeQuery();
        if(res->next()){
            return res->getInt("user_id");
        }
        else{
            std::cout << "User not found" << std::endl;
            return -1;
        }
    }
    catch(sql::SQLException &e){
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << "Error Code: " << e.getErrorCode() << std::endl;
        std::cout << "SQL State: " << e.getSQLState() << std::endl;
        return -1;
    }
}
bool DataController::Dc_login(User& user){
    try{
        pstmt=con->prepareStatement("SELECT * FROM users WHERE email=? AND password_hash=?");
        pstmt->setString(1,user.getemail());
        pstmt->setString(2,user.gethashedPassword());
        res=pstmt->executeQuery();
        if(res->next()){
            std::cout << "User logged in successfully" << std::endl;
            user.setuserId(res->getInt("user_id"));
             // Get the username from the database and set it in the user object
            std::string username = res->getString("username");
            user.setuserName(username);
            return true;
        }
        else{
            std::cout << "Email or Password provided is wrong" << std::endl;
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
std::vector<Note> DataController::Dc_ListUserNotes(int userId){
    try{
        // get all the notes of the user with the specified user_id
        pstmt=con->prepareStatement("SELECT * FROM notes WHERE user_id=?");
        pstmt->setInt(1,userId);
        res=pstmt->executeQuery();
        std::vector<Note> notes;
        // Iterate over the result set
        while(res->next()){
            Note note;
            note.setnoteId(res->getInt("note_id"));
            note.setuserId(res->getInt("user_id"));
            note.settitle(res->getString("title"));
            note.setcreatedAt(res->getString("created_at"));
            note.setupdatedAt(res->getString("updated_at"));
            notes.push_back(note);
        }
        return notes;
    }
    catch(sql::SQLException &e){
        std::cout << "Error: " << e.what() << std::endl;
        return {};
    }
}

std::string DataController::Dc_getNoteCreatedAt(int noteId){
    try{
        pstmt=con->prepareStatement("SELECT created_at FROM notes WHERE note_id=?");
        pstmt->setInt(1,noteId);
        res=pstmt->executeQuery();
        if(res->next()){
            return res->getString("created_at");
        }
        else{
            std::cout << "Note not found" << std::endl;
            return "Error";
        }
    }
    catch(sql::SQLException &e){
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << "Error Code: " << e.getErrorCode() << std::endl;
        std::cout << "SQL State: " << e.getSQLState() << std::endl;
        return "Error";
    }
}
std::string DataController::Dc_getNoteUpdatedAt(int noteId){
    try{
        pstmt=con->prepareStatement("SELECT updated_at FROM notes WHERE note_id=?");
        pstmt->setInt(1,noteId);
        res=pstmt->executeQuery();
        if(res->next()){
            return res->getString("updated_at");
        }
        else{
            std::cout << "Note not found" << std::endl;
            return "Error";
        }
    }
    catch(sql::SQLException &e){
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << "Error Code: " << e.getErrorCode() << std::endl;
        std::cout << "SQL State: " << e.getSQLState() << std::endl;
        return "Error";
    }
}
int DataController::Dc_getNoteId(Note& note){
    try{
        pstmt=con->prepareStatement("SELECT note_id FROM notes WHERE user_id=? AND title=? AND created_at=?");
        pstmt->setInt(1,note.getuserId());
        pstmt->setString(2,note.gettitle());
        pstmt->setString(3,note.getcreatedAt());
        res=pstmt->executeQuery();
        if(res->next()){
            return res->getInt("note_id");
        }
        else{
            std::cout << "Note not found" << std::endl;
            return -1;
        }
    }
    catch(sql::SQLException &e){
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << "Error Code: " << e.getErrorCode() << std::endl;
        std::cout << "SQL State: " << e.getSQLState() << std::endl;
        return -1;
    }
}

bool DataController::Dc_CreateNote(Note& note){
    try{
        // Check if the specified user_id exists in the users table
        pstmt = con->prepareStatement("SELECT 1 FROM users WHERE user_id = ?");
        pstmt->setInt(1, note.getuserId());

        res = pstmt->executeQuery();

        if (!res->next()) {
            std::cout << "Error: User with user_id " << note.getuserId() << " does not exist." << std::endl;
            return false;
        }
        // Prepare a SQL statement with placeholders and execute it
        pstmt=con->prepareStatement("INSERT INTO notes (user_id,title,created_at) VALUES (?,?,NOW())");
        pstmt->setInt(1,note.getuserId());
        pstmt->setString(2,note.gettitle());
        pstmt->execute();

        // Execute a new query to get the last inserted id
        pstmt = con->prepareStatement("SELECT LAST_INSERT_ID()");
        res = pstmt->executeQuery();
        if(res->next()){
            int noteId = res->getInt(1);
            note.setnoteId(noteId);
        }
        std::cout << "Note added successfully" << std::endl;
        // set the note id and created at and updated at fields of the note object
        
        note.setcreatedAt(Dc_getNoteCreatedAt(note.getnoteId()));
        note.setupdatedAt(Dc_getNoteUpdatedAt(note.getnoteId()));
        return true;
    }
    catch(sql::SQLException &e){
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << "Error Code: " << e.getErrorCode() << std::endl;
        std::cout << "SQL State: " << e.getSQLState() << std::endl;
        return false;
    }
}

bool DataController::Dc_UpdateNoteTitle(Note& note){
    try{
        // Check if the specified user_id exists in the users table
        pstmt = con->prepareStatement("SELECT 1 FROM users WHERE user_id = ?");
        pstmt->setInt(1, note.getuserId());

        res = pstmt->executeQuery();

        if (!res->next()) {
            std::cout << "Error: User with user_id " << note.getuserId() << " does not exist." << std::endl;
            return false;
        }
        // Check if the specified note_id exists in the notes table and belongs to the user
        pstmt = con->prepareStatement("SELECT 1 FROM notes WHERE note_id = ? AND user_id = ?");
        pstmt->setInt(1, note.getnoteId());
        pstmt->setInt(2, note.getuserId());

        res = pstmt->executeQuery();

        if (!res->next()) {
            std::cout << "Error: Note with note_id " << note.getnoteId() << " does not exist or does not belong to the user." << std::endl;
            return false;
        }
        // Prepare a SQL statement with placeholders and execute it
        pstmt=con->prepareStatement("UPDATE notes SET title=?,updated_at=NOW() WHERE note_id=?");
        pstmt->setString(1,note.gettitle());
        pstmt->setInt(2,note.getnoteId());
        pstmt->execute();
        std::cout << "Note updated successfully" << std::endl;
        // set the note id and created at and updated at fields of the note object
        note.setupdatedAt(Dc_getNoteUpdatedAt(note.getnoteId()));
        note.setcreatedAt(Dc_getNoteCreatedAt(note.getnoteId()));
        return true;
    }
    catch(sql::SQLException &e){
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << "Error Code: " << e.getErrorCode() << std::endl;
        std::cout << "SQL State: " << e.getSQLState() << std::endl;
        return false;
    }
}

std:: vector<Note> DataController::Dc_SearchByTitle(int userId,std::string title){
    try{
        // Check if the specified user_id exists in the users table
        pstmt=con->prepareStatement("SELECT * FROM notes WHERE user_id=? AND title LIKE ?");
        pstmt->setInt(1,userId);
        // to search for a string that contains a specific string we use %string%
        pstmt->setString(2,"%"+title+"%");
        res=pstmt->executeQuery();
        std::vector<Note> notes;
        // Iterate over the result set
        while(res->next()){
            Note note;
            note.setnoteId(res->getInt("note_id"));
            note.setuserId(res->getInt("user_id"));
            note.settitle(res->getString("title"));
            note.setcreatedAt(res->getString("created_at"));
            note.setupdatedAt(res->getString("updated_at"));
            notes.push_back(note);
        }
        return notes;
    }
    // Handle any exceptions that might occur during the Search note listing process
    catch(sql::SQLException &e){
        std::cout << "Error: " << e.what() << std::endl;
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
