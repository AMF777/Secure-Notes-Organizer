#include "DataController.h"
void DataController::connect(std::string ip, std::string username, std::string password, std::string schema){
    std::lock_guard<std::mutex> lock(mtx);
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
/*bool DataController::Dc_signup(User& user){
    std::lock_guard<std::mutex> lock(mtx);
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
}*/
bool DataController::Dc_signup(User& user){
    std::lock_guard<std::mutex> lock(mtx);
    try{
        // Check if the email is already in use
        std::unique_ptr<sql::PreparedStatement> checkStmt(con->prepareStatement("SELECT * FROM users WHERE email = ?"));
        checkStmt->setString(1, user.getemail());
        std::unique_ptr<sql::ResultSet> res(checkStmt->executeQuery());
        if (res->next()) {
            std::cout << "Email is already in use" << std::endl;
            return false;
        }

        // If the email is not in use, insert the new user
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
    std::lock_guard<std::mutex> lock(mtx);
    
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
    std::lock_guard<std::mutex> lock(mtx);
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
    std::lock_guard<std::mutex> lock(mtx);
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
    std::lock_guard<std::mutex> lock(mtx);
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
    std::lock_guard<std::mutex> lock(mtx);
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
    std::lock_guard<std::mutex> lock(mtx);
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
    std::lock_guard<std::mutex> lock(mtx);
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
        // Release the mutex before calling Dc_getNoteCreatedAt and Dc_getNoteUpdatedAt
        mtx.unlock();

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
    std::lock_guard<std::mutex> lock(mtx);
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
        // Release the mutex before calling Dc_getNoteCreatedAt and Dc_getNoteUpdatedAt
        mtx.unlock();
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
    std::lock_guard<std::mutex> lock(mtx);
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
bool DataController::Dc_CreateNoteComponent(NoteComponent& noteComponent,int userId){
    std::lock_guard<std::mutex> lock(mtx);
    try{
        // Check if the specified user_id exists in the users table
        pstmt = con->prepareStatement("SELECT 1 FROM users WHERE user_id = ?");
        pstmt->setInt(1, userId);

        res = pstmt->executeQuery();

        if (!res->next()) {
            std::cout << "Error: User with user_id " << userId << " does not exist." << std::endl;
            return false;
        }
        // Check if the specified note_id exists in the notes table and belongs to the user
        pstmt = con->prepareStatement("SELECT 1 FROM notes WHERE note_id = ? AND user_id = ?");
        pstmt->setInt(1, noteComponent.getnoteId());
        pstmt->setInt(2, userId);

        res = pstmt->executeQuery();

        if (!res->next()) {
            std::cout << "Error: Note with note_id " << noteComponent.getnoteId() << " does not exist or does not belong to the user." << std::endl;
            return false;
        }
        // Prepare a SQL statement with placeholders and execute it
        pstmt=con->prepareStatement("INSERT INTO Component_note (note_id,Component_content,Font_size,Font_color,Background_color,Font_family,Font_style,Font_bold,Font_italic,Font_underlined) VALUES (?,?,?,?,?,?,?,?,?,?)");
        pstmt->setInt(1,noteComponent.getnoteId());
        pstmt->setString(2,noteComponent.getcomponentContent());
        pstmt->setInt(3,noteComponent.getfontSize());
        pstmt->setString(4,noteComponent.getfontColor());
        pstmt->setString(5,noteComponent.getbackgroundColor());
        pstmt->setString(6,noteComponent.getfontFamily());
        pstmt->setString(7,noteComponent.getfontStyle());
        pstmt->setBoolean(8,noteComponent.getisBold());
        pstmt->setBoolean(9,noteComponent.getisItalic());
        pstmt->setBoolean(10,noteComponent.getisUnderlined());
        pstmt->execute();
        std::cout << "Note component added successfully" << std::endl;
        // Execute a new query to get the last inserted id
        pstmt = con->prepareStatement("SELECT LAST_INSERT_ID()");
        res = pstmt->executeQuery();
        if(res->next()){
            int componentId = res->getInt(1);
            noteComponent.setcomponentId(componentId);
        }
        // Update the updated_at field in the notes table
        pstmt = con->prepareStatement("UPDATE notes SET updated_at = NOW() WHERE note_id = ?");
        pstmt->setInt(1, noteComponent.getnoteId());
        pstmt->execute();
        return true;
    }
    catch(sql::SQLException &e){
        std::cout << "Error: " << e.what() << std::endl;
        return false;
    }
}
bool DataController::Dc_UpdateNoteComponent(NoteComponent& noteComponent,int userId){
    std::lock_guard<std::mutex> lock(mtx);
    try{
        // Check if the specified note_id exists in the notes table and belongs to the user
        pstmt = con->prepareStatement("SELECT 1 FROM notes WHERE note_id = ? AND user_id = ?");
        pstmt->setInt(1, noteComponent.getnoteId());
        pstmt->setInt(2, userId);

        res = pstmt->executeQuery();

        if (!res->next()) {
            std::cout << "Error: Note with note_id " << noteComponent.getnoteId() << " does not exist or does not belong to the user." << std::endl;
            return false;
        }
        // Prepare a SQL statement with placeholders and execute it
        pstmt=con->prepareStatement("UPDATE Component_note SET Component_content=?,Font_size=?,Font_color=?,Background_color=?,Font_family=?,Font_style=?,Font_bold=?,Font_italic=?,Font_underlined=? WHERE Component_id=?");
        pstmt->setString(1,noteComponent.getcomponentContent());
        pstmt->setInt(2,noteComponent.getfontSize());
        pstmt->setString(3,noteComponent.getfontColor());
        pstmt->setString(4,noteComponent.getbackgroundColor());
        pstmt->setString(5,noteComponent.getfontFamily());
        pstmt->setString(6,noteComponent.getfontStyle());
        pstmt->setBoolean(7,noteComponent.getisBold());
        pstmt->setBoolean(8,noteComponent.getisItalic());
        pstmt->setBoolean(9,noteComponent.getisUnderlined());
        pstmt->setInt(10,noteComponent.getcomponentId());
        pstmt->execute();
        std::cout << "Note component updated successfully" << std::endl;
        // Update the updated_at field in the notes table
        pstmt = con->prepareStatement("UPDATE notes SET updated_at = NOW() WHERE note_id = ?");
        pstmt->setInt(1, noteComponent.getnoteId());
        pstmt->execute();
        return true;
    }
    catch(sql::SQLException &e){
        std::cout << "Error: " << e.what() << std::endl;
        return false;
    }
}
std::vector<NoteComponent> DataController::Dc_ListNoteComponents(Note& note){
    std::lock_guard<std::mutex> lock(mtx);
    try{
        // Check if the specified note_id exists in the notes table and belongs to the user
        pstmt = con->prepareStatement("SELECT 1 FROM notes WHERE note_id = ? AND user_id = ?");
        pstmt->setInt(1, note.getnoteId());
        pstmt->setInt(2, note.getuserId());

        res = pstmt->executeQuery();

        if (!res->next()) {
            std::cout << "Error: Note with note_id " << note.getnoteId() << " does not exist or does not belong to the user." << std::endl;
            return {};
        }
        // Prepare a SQL statement with placeholders and execute it
        pstmt=con->prepareStatement("SELECT * FROM Component_note WHERE note_id=?");
        pstmt->setInt(1,note.getnoteId());
        res=pstmt->executeQuery();
        std::vector<NoteComponent> noteComponents;
        // Iterate over the result set
        while(res->next()){
            NoteComponent noteComponent;
            noteComponent.setcomponentId(res->getInt("Component_id"));
            noteComponent.setnoteId(res->getInt("note_id"));
            noteComponent.setcomponentContent(res->getString("Component_content"));
            noteComponent.setfontSize(res->getInt("Font_size"));
            noteComponent.setfontColor(res->getString("Font_color"));
            noteComponent.setbackgroundColor(res->getString("Background_color"));
            noteComponent.setfontFamily(res->getString("Font_family"));
            noteComponent.setfontStyle(res->getString("Font_style"));
            noteComponent.setisBold(res->getBoolean("Font_bold"));
            noteComponent.setisItalic(res->getBoolean("Font_italic"));
            noteComponent.setisUnderlined(res->getBoolean("Font_underlined"));
            noteComponents.push_back(noteComponent);
        }
        return noteComponents;
    }
    // Handle any exceptions that might occur during the Search note listing process
    catch(sql::SQLException &e){
        std::cout << "Error: " << e.what() << std::endl;
        return {};
    }
}
bool DataController::Dc_DeleteNoteComponent(int componentId,int userId,int noteId){
    std::lock_guard<std::mutex> lock(mtx);
    try{
        // Check if the specified note_id exists in the notes table and belongs to the user
        pstmt = con->prepareStatement("SELECT 1 FROM notes WHERE note_id = ? AND user_id = ?");
        pstmt->setInt(1, noteId);
        pstmt->setInt(2, userId);

        res = pstmt->executeQuery();

        if (!res->next()) {
            std::cout << "Error: Note with note_id " << componentId << " does not exist or does not belong to the user." << std::endl;
            return false;
        }
        // Prepare a SQL statement with placeholders and execute it
        pstmt=con->prepareStatement("DELETE FROM Component_note WHERE Component_id=? AND note_id=?");
        pstmt->setInt(1,componentId);
        pstmt->setInt(2,noteId);
        pstmt->execute();
        std::cout << "Note component deleted successfully" << std::endl;
        // Update the updated_at field in the notes table
        pstmt = con->prepareStatement("UPDATE notes SET updated_at = NOW() WHERE note_id = ?");
        pstmt->setInt(1, noteId);
        pstmt->execute();
        return true;
    }
    catch(sql::SQLException &e){
        std::cout << "Error: " << e.what() << std::endl;
        return false;
    }
}
bool DataController::Dc_DeleteNote(int noteId,int userId){
    std::lock_guard<std::mutex> lock(mtx);
    try{
        // Check if the specified note_id exists in the notes table and belongs to the user
        pstmt = con->prepareStatement("SELECT 1 FROM notes WHERE note_id = ? AND user_id = ?");
        pstmt->setInt(1, noteId);
        pstmt->setInt(2, userId);

        res = pstmt->executeQuery();

        if (!res->next()) {
            std::cout << "Error: Note with note_id " << noteId << " does not exist or does not belong to the user." << std::endl;
            return false;
        }
        // Prepare a SQL statement with placeholders and execute it
        pstmt=con->prepareStatement("DELETE FROM Component_note WHERE note_id=?");
        pstmt->setInt(1,noteId);
        pstmt->execute();
        std::cout << "Note components deleted successfully" << std::endl;
        // Delete the note from the notes table
        pstmt = con->prepareStatement("DELETE FROM notes WHERE note_id = ? AND user_id = ?");
        pstmt->setInt(1, noteId);
        pstmt->setInt(2, userId);
        pstmt->execute();
        std::cout << "Note deleted successfully" << std::endl;
        return true;
    }
    catch(sql::SQLException &e){
        std::cout << "Error: " << e.what() << std::endl;
        return false;
    }
}
bool DataController::Dc_AddTag(Tag& tag,int userId){
    std::lock_guard<std::mutex> lock(mtx);
    try{
        // Check if the specified user_id exists in the users table
        pstmt = con->prepareStatement("SELECT 1 FROM users WHERE user_id = ?");
        pstmt->setInt(1, userId);

        res = pstmt->executeQuery();

        if (!res->next()) {
            std::cout << "Error: User with user_id " << userId << " does not exist." << std::endl;
            return false;
        }
        // Check if the specified note_id exists in the notes table and belongs to the user
        pstmt = con->prepareStatement("SELECT 1 FROM notes WHERE note_id = ? AND user_id = ?");
        pstmt->setInt(1, tag.getnoteId());
        pstmt->setInt(2, userId);

        res = pstmt->executeQuery();

        if (!res->next()) {
            std::cout << "Error: Note with note_id " << tag.getnoteId() << " does not exist or does not belong to the user." << std::endl;
            return false;
        }
        // Prepare a SQL statement with placeholders and execute it
        pstmt=con->prepareStatement("INSERT INTO tags (tag_name) VALUES (?)");
        pstmt->setString(1,tag.gettagName());
        pstmt->execute();
        std::cout << "Tag added successfully" << std::endl;
        // Execute a new query to get the last inserted id
        pstmt = con->prepareStatement("SELECT LAST_INSERT_ID()");
        res = pstmt->executeQuery();
        if(res->next()){
            int tagId = res->getInt(1);
            tag.settagId(tagId);
        }
        // Update the updated_at field in the notes table
        pstmt = con->prepareStatement("UPDATE notes SET updated_at = NOW() WHERE note_id = ?");
        pstmt->setInt(1, tag.getnoteId());
        pstmt->execute();
        // Insert the note_id and tag_id into the note_tags table
        pstmt = con->prepareStatement("INSERT INTO note_tags (note_id, tag_id) VALUES (?, ?)");
        pstmt->setInt(1, tag.getnoteId());
        pstmt->setInt(2, tag.gettagId());
        pstmt->execute();
        std::cout << "Note tag added successfully" << std::endl;
        return true;
    }
    catch(sql::SQLException &e){
        std::cout << "Error: " << e.what() << std::endl;
        return false;
    }
}
bool DataController::Dc_UpdateTag(Tag& tag,int userId){
    std::lock_guard<std::mutex> lock(mtx);
    try{
        // Check if the specified user_id exists in the users table
        pstmt = con->prepareStatement("SELECT 1 FROM users WHERE user_id = ?");
        pstmt->setInt(1, userId);

        res = pstmt->executeQuery();

        if (!res->next()) {
            std::cout << "Error: User with user_id " << userId << " does not exist." << std::endl;
            return false;
        }
        // Check if the specified note_id exists in the notes table and belongs to the user
        pstmt = con->prepareStatement("SELECT 1 FROM notes WHERE note_id = ? AND user_id = ?");
        pstmt->setInt(1, tag.getnoteId());
        pstmt->setInt(2, userId);

        res = pstmt->executeQuery();

        if (!res->next()) {
            std::cout << "Error: Note with note_id " << tag.getnoteId() << " does not exist or does not belong to the user." << std::endl;
            return false;
        }
        // Check if the specified tag_id exists in the tags table
        pstmt = con->prepareStatement("SELECT 1 FROM tags WHERE tag_id = ?");
        pstmt->setInt(1, tag.gettagId());

        res = pstmt->executeQuery();

        if (!res->next()) {
            std::cout << "Error: Tag with tag_id " << tag.gettagId() << " does not exist." << std::endl;
            return false;
        }
        // Prepare a SQL statement with placeholders and execute it
        pstmt=con->prepareStatement("UPDATE tags SET tag_name=? WHERE tag_id=?");
        pstmt->setString(1,tag.gettagName());
        pstmt->setInt(2,tag.gettagId());
        pstmt->execute();
        std::cout << "Tag updated successfully" << std::endl;
        // Update the updated_at field in the notes table
        pstmt = con->prepareStatement("UPDATE notes SET updated_at = NOW() WHERE note_id = ?");
        pstmt->setInt(1, tag.getnoteId());
        pstmt->execute();
        return true;
    }
    catch(sql::SQLException &e){
        std::cout << "Error: " << e.what() << std::endl;
        return false;
    }
}
std::vector<Note> DataController::Dc_FilterByTagName(std::string tagName,int userId){
    std::lock_guard<std::mutex> lock(mtx);
    try{
        // Check if the specified user_id exists in the users table
        pstmt = con->prepareStatement("SELECT 1 FROM users WHERE user_id = ?");
        pstmt->setInt(1, userId);

        res = pstmt->executeQuery();

        if (!res->next()) {
            std::cout << "Error: User with user_id " << userId << " does not exist." << std::endl;
            return {};
        }
        // Prepare a SQL statement with placeholders and execute it
        pstmt=con->prepareStatement("SELECT * FROM notes WHERE note_id IN (SELECT note_id FROM note_tags WHERE tag_id IN (SELECT tag_id FROM tags WHERE tag_name=?)) AND user_id=?");
        pstmt->setString(1,tagName);
        pstmt->setInt(2,userId);
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
bool DataController::Dc_DeleteTag(Tag &tag,int userId){
    std::lock_guard<std::mutex> lock(mtx);
    try{
        // Check if the specified user_id exists in the users table
        pstmt = con->prepareStatement("SELECT 1 FROM users WHERE user_id = ?");
        pstmt->setInt(1, userId);

        res = pstmt->executeQuery();

        if (!res->next()) {
            std::cout << "Error: User with user_id " << userId << " does not exist." << std::endl;
            return false;
        }
        // Check if the specified note_id exists in the notes table and belongs to the user
        pstmt = con->prepareStatement("SELECT 1 FROM notes WHERE note_id = ? AND user_id = ?");
        pstmt->setInt(1, tag.getnoteId());
        pstmt->setInt(2, userId);

        res = pstmt->executeQuery();

        if (!res->next()) {
            std::cout << "Error: Note with note_id " << tag.getnoteId() << " does not exist or does not belong to the user." << std::endl;
            return false;
        }
        // Check if the specified tag_id exists in the tags table
        pstmt = con->prepareStatement("SELECT 1 FROM tags WHERE tag_id = ?");
        pstmt->setInt(1, tag.gettagId());

        res = pstmt->executeQuery();

        if (!res->next()) {
            std::cout << "Error: Tag with tag_id " << tag.gettagId() << " does not exist." << std::endl;
            return false;
        }
        // Delete the note_id and tag_id from the note_tags table
        pstmt = con->prepareStatement("DELETE FROM note_tags WHERE note_id = ? AND tag_id = ?");
        pstmt->setInt(1, tag.getnoteId());
        pstmt->setInt(2, tag.gettagId());
        pstmt->execute();
        // Prepare a SQL statement with placeholders and execute it
        pstmt=con->prepareStatement("DELETE FROM tags WHERE tag_id=?");
        pstmt->setInt(1,tag.gettagId());
        pstmt->execute();
        std::cout << "Tag deleted successfully" << std::endl;
        // Update the updated_at field in the notes table
        pstmt = con->prepareStatement("UPDATE notes SET updated_at = NOW() WHERE note_id = ?");
        pstmt->setInt(1, tag.getnoteId());
        pstmt->execute();
        return true;

    }
catch(sql::SQLException &e){
        std::cout << "Error: " << e.what() << std::endl;
        return false;
    }
}
std::vector<Tag> DataController::Dc_ListNoteTags(int noteId,int userId){
    std::lock_guard<std::mutex> lock(mtx);
    try{
        // Check if the specified user_id exists in the users table
        pstmt = con->prepareStatement("SELECT 1 FROM users WHERE user_id = ?");
        pstmt->setInt(1, userId);

        res = pstmt->executeQuery();

        if (!res->next()) {
            std::cout << "Error: User with user_id " << userId << " does not exist." << std::endl;
            return {};
        }
        // Check if the specified note_id exists in the notes table and belongs to the user
        pstmt = con->prepareStatement("SELECT 1 FROM notes WHERE note_id = ? AND user_id = ?");
        pstmt->setInt(1, noteId);
        pstmt->setInt(2, userId);

        res = pstmt->executeQuery();

        if (!res->next()) {
            std::cout << "Error: Note with note_id " << noteId << " does not exist or does not belong to the user." << std::endl;
            return {};
        }
        // Prepare a SQL statement with placeholders and execute it
        pstmt=con->prepareStatement("SELECT * FROM tags WHERE tag_id IN (SELECT tag_id FROM note_tags WHERE note_id=?)");
        pstmt->setInt(1,noteId);
        res=pstmt->executeQuery();
        std::vector<Tag> tags;
        // Iterate over the result set
        while(res->next()){
            Tag tag;
            tag.settagId(res->getInt("tag_id"));
            tag.settagName(res->getString("tag_name"));
            tag.setnoteId(noteId);
            tags.push_back(tag);
        }
        return tags;
    }
    // Handle any exceptions that might occur during the Search note listing process
    catch(sql::SQLException &e){
        std::cout << "Error: " << e.what() << std::endl;
        return {};
    }
}
bool DataController::Dc_UpdateUserData(User& user){
    std::lock_guard<std::mutex> lock(mtx);
    try{
        // Check if the specified email exists in the users table
        pstmt = con->prepareStatement("SELECT 1 FROM users WHERE email = ?");
        pstmt->setString(1, user.getemail());

        res = pstmt->executeQuery();

        if (!res->next()) {
            std::cout << "Error: User with email " << user.getemail() << " does not exist." << std::endl;
            return false;
        }
        // Prepare a SQL statement with placeholders and execute it
        pstmt=con->prepareStatement("UPDATE users SET username=?,password_hash=? WHERE email=?");
        pstmt->setString(1,user.getuserName());
        pstmt->setString(2,user.gethashedPassword());
        pstmt->setString(3,user.getemail());
        pstmt->execute();
        std::cout << "User data updated successfully" << std::endl;
        return true;
    }
    catch(sql::SQLException &e){
        std::cout << "Error: " << e.what() << std::endl;
        return false;
    }
}
DataController::~DataController(){
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Destructor called" << std::endl;
    delete res;
    delete stmt;
    delete con;
    delete pstmt;
}
