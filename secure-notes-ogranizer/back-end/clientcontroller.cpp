#include "clientcontroller.h"


namespace GlobalClient{
    ClientController client("127.0.0.1", "12345");
}

ClientController::ClientController(const std::string& server_address, const std::string& server_port)
{
    clientConnection = new ClientConnection(server_address, server_port);
    msg_id = 0u;
}


bool ClientController::ClientSignUp(User *user, std::string* response)
{
    msg_id++;
    json send_message;
    json receive_message;
    send_message["ID"] = msg_id;
    send_message["Action"] = "signup";
    send_message["Data"] = user -> toJson();
    clientConnection -> Send(send_message);
    receive_message = clientConnection -> Receive();
    *response = receive_message["Response"];
    if(receive_message["Response"] == "signup successfully")
    {
        user -> setuserId(receive_message["user id"]);
        return true;
    }
    else {
        return false;
    }
}

bool ClientController::ClientLogIn(User *user, std::string* response)
{
    msg_id++;
    json send_message;
    json receive_message;
    send_message["ID"] = msg_id;
    send_message["Action"] = "login";
    send_message["Data"] = user -> toJson();
    clientConnection -> Send(send_message);
    receive_message = clientConnection -> Receive();
    *response = receive_message["Response"];
    if(receive_message["Response"] == "login successfully")
    {
        User temp_user = user -> fromJson(receive_message["Data"]);
        user -> setuserName(temp_user.getuserName());
        user -> setuserId(temp_user.getuserId());
        return true;
    }
    else {
        return false;
    }
}


bool ClientController::ClientCreateNote(Note *note, std::string* response)
{
    msg_id++;
    json send_message;
    json receive_message;
    send_message["ID"] = msg_id;
    send_message["Action"] = "create note";
    send_message["Data"] = note -> toJson();
    clientConnection -> Send(send_message);
    receive_message = clientConnection -> Receive();
    *response = receive_message["Response"];
    if(receive_message["Response"] == "note created successfully")
    {
        Note temp_note = note -> fromJson(receive_message["Data"]);
        note -> setnoteId(temp_note.getnoteId());
        note -> setcreatedAt(temp_note.getcreatedAt());
        return true;
    }
    else {
        return false;
    }
}


bool ClientController::ClientUpdateNoteTitle(Note *note, std::string* response)
{
    msg_id++;
    json send_message;
    json receive_message;
    send_message["ID"] = msg_id;
    send_message["Action"] = "update note title";
    send_message["Data"] = note -> toJson();
    clientConnection -> Send(send_message);
    receive_message = clientConnection -> Receive();
    *response = receive_message["Response"];
    if(receive_message["Response"] == "note updated successfully")
    {
        Note temp_note = note -> fromJson(receive_message["Data"]);
        note -> setupdatedAt(temp_note.getupdatedAt());
        return true;
    }
    else {
        return false;
    }
}


bool ClientController::ClientDeleteNote(Note *note, std::string* response)
{
    msg_id++;
    json send_message;
    json receive_message;
    send_message["ID"] = msg_id;
    send_message["Action"] = "delete note";
    send_message["Data"] = note -> toJson();
    clientConnection -> Send(send_message);
    receive_message = clientConnection -> Receive();
    *response = receive_message["Response"];
    if(receive_message["Response"] == "note deleted successfully")
    {
        return true;
    }
    else {
        return false;
    }
}

bool ClientController::ClientListNote(User *user, std::string* response, std::vector<Note>& NotesList)
{
    msg_id++;
    json send_message;
    json receive_message;
    std::vector<Note> notes;
    send_message["ID"] = msg_id;
    send_message["Action"] = "list notes";
    send_message["user id"] = user -> getuserId();
    clientConnection -> Send(send_message);
    receive_message = clientConnection -> Receive();
    *response = receive_message["Response"];
    if(receive_message["Response"] == "list notes successfully")
    {
        json notesArray = receive_message["Data"];
        std::vector<Note> notes = notesArray.get<std::vector<Note>>();
        for (Note& item : notes) {
            NotesList.push_back(item);
        }
        return true;
    }
    else {
        return false;
    }
}


bool ClientController::ClientSearchByNoteTitle(Note *note, std::string* response, std::vector<Note>& NotesList)
{
    msg_id++;
    json send_message;
    json receive_message;
    send_message["ID"] = msg_id;
    send_message["Action"] = "search by note title";
    send_message["Data"] = note -> toJson();
    clientConnection -> Send(send_message);
    receive_message = clientConnection -> Receive();
    *response = receive_message["Response"];
    if(receive_message["Response"] == "search by title successfully")
    {
        json notesArray = receive_message["Data"];
        std::vector<Note> notes = notesArray.get<std::vector<Note>>();
        for (Note& item : notes) {
            NotesList.push_back(item);
        }
        return true;
    }
    else {
        return false;
    }
}

bool ClientController::ClientCreateComponent(NoteComponent *noteComponent, User* user, std::string* response)
{
    msg_id++;
    json send_message;
    json receive_message;
    send_message["ID"] = msg_id;
    send_message["Action"] = "create component";
    send_message["user id"] = user -> getuserId();
    send_message["Data"] = noteComponent -> toJson();
    clientConnection -> Send(send_message);
    receive_message = clientConnection -> Receive();
    *response = receive_message["Response"];
    if(receive_message["Response"] == "component created successfully")
    {
        noteComponent -> setcomponentId(receive_message["component id"]);
        return true;
    }
    else {
        return false;
    }
}

bool ClientController::ClientUpdateComponent(NoteComponent *noteComponent, User* user, std::string* response)
{
    msg_id++;
    json send_message;
    json receive_message;
    send_message["ID"] = msg_id;
    send_message["Action"] = "update component";
    send_message["user id"] = user -> getuserId();
    send_message["Data"] = noteComponent -> toJson();
    clientConnection -> Send(send_message);
    receive_message = clientConnection -> Receive();
     *response = receive_message["Response"];
    if(receive_message["Response"] == "component updated successfully")
    {
        return true;
    }
    else {
        return false;
    }
}

bool ClientController::ClientDeleteComponent(NoteComponent *noteComponent, User* user, std::string* response)
{
    msg_id++;
    json send_message;
    json receive_message;
    send_message["ID"] = msg_id;
    send_message["Action"] = "delete component";
    send_message["user id"] = user -> getuserId();
    send_message["Data"] = noteComponent -> toJson();
    clientConnection -> Send(send_message);
    receive_message = clientConnection -> Receive();
    *response = receive_message["Response"];
    if(receive_message["Response"] == "component deleted successfully")
    {
        return true;
    }
    else {
        return false;
    }
}

 bool ClientController::ClientListComponents(Note *note, std::string* response, std::vector<NoteComponent>& ComponentsList){
    msg_id++;
    json send_message;
    json receive_message;
    send_message["ID"] = msg_id;
    send_message["Action"] = "list components";
    send_message["Data"] = note -> toJson();
    clientConnection -> Send(send_message);
    receive_message = clientConnection -> Receive();
    *response = receive_message["Response"];
    if(receive_message["Response"] == "list components successfully")
    {
        json componentsArray = receive_message["Data"];
        std::vector<NoteComponent> components = componentsArray.get<std::vector<NoteComponent>>();
        for (NoteComponent& item : components) {
            ComponentsList.push_back(item);
        }
        return true;
    }
    else {
        return false;
    }
}

bool ClientController::ClientAddTag(Tag *tag, User* user, std::string* response){
    msg_id++;
    json send_message;
    json receive_message;
    send_message["ID"] = msg_id;
    send_message["Action"] = "add tag";
    send_message["user id"] = user -> getuserId();
    send_message["Data"] = tag -> toJson();
    clientConnection -> Send(send_message);
    receive_message = clientConnection -> Receive();
    *response = receive_message["Response"];
    if(receive_message["Response"] == "tag added successfully")
    {
        Tag temp_tag = tag -> fromJson(receive_message["Data"]);
        tag -> settagId(temp_tag.gettagId());
        return true;
    }
    else {
        return false;
    }
}

bool ClientController::ClientUpdateTag(Tag *tag, User* user, std::string* response){
    msg_id++;
    json send_message;
    json receive_message;
    send_message["ID"] = msg_id;
    send_message["Action"] = "update tag";
    send_message["user id"] = user -> getuserId();
    send_message["Data"] = tag -> toJson();
    clientConnection -> Send(send_message);
    receive_message = clientConnection -> Receive();
    *response = receive_message["Response"];
    if(receive_message["Response"] == "tag updated successfully")
    {
        return true;
    }
    else {
        return false;
    }
}

bool ClientController::ClientDeleteTag(Tag *tag, User* user, std::string* response){
    msg_id++;
    json send_message;
    json receive_message;
    send_message["ID"] = msg_id;
    send_message["Action"] = "delete tag";
    send_message["user id"] = user -> getuserId();
    send_message["Data"] = tag -> toJson();
    clientConnection -> Send(send_message);
    receive_message = clientConnection -> Receive();
    *response = receive_message["Response"];
    if(receive_message["Response"] == "tag deleted successfully")
    {
        return true;
    }
    else {
        return false;
    }
}

bool ClientController::ClientFilterByTagName(Tag *tag, User* user, std::string* response, std::vector<Note>& NotesList){
    msg_id++;
    json send_message;
    json receive_message;
    send_message["ID"] = msg_id;
    send_message["Action"] = "filter by tag name";
    send_message["user id"] = user -> getuserId();
    send_message["tag name"] = tag -> gettagName();
    clientConnection -> Send(send_message);
    receive_message = clientConnection -> Receive();
    *response = receive_message["Response"];
    if(receive_message["Response"] == "filter by tag name successfully")
    {
        json notesArray = receive_message["Data"];
        std::vector<Note> notes = notesArray.get<std::vector<Note>>();
        for (Note& item : notes) {
            NotesList.push_back(item);
        }
        return true;
    }
    else {
        return false;
    }
}

bool ClientController::ClientListNoteTags(Note *note, std::string* response, std::vector<Tag>& TagsList)
{
    msg_id++;
    json send_message;
    json receive_message;
    send_message["ID"] = msg_id;
    send_message["Action"] = "list note tags";
    send_message["Data"] = note -> toJson();
    clientConnection -> Send(send_message);
    receive_message = clientConnection -> Receive();
    *response = receive_message["Response"];
    if(receive_message["Response"] == "list tags of note successfully")
    {
        json TagsArray = receive_message["Data"];
        std::vector<Tag> Tags = TagsArray.get<std::vector<Tag>>();
        for (Tag& item : Tags) {
            TagsList.push_back(item);
        }
        return true;
    }
    else {
        return false;
    }
}

bool ClientController::ClientUpdateUserData(User *user, std::string* response)
{
    msg_id++;
    json send_message;
    json receive_message;
    send_message["ID"] = msg_id;
    send_message["Action"] = "update user data";
    send_message["Data"] = user -> toJson();
    clientConnection -> Send(send_message);
    receive_message = clientConnection -> Receive();
    *response = receive_message["Response"];
    if(receive_message["Response"] == "update user data successfully")
    {
        return true;
    }
    else {
        return false;
    }
}

void ClientController::ClientLogout(){
    json endMessage;
    endMessage["Action"] = "close";
    clientConnection -> Send(endMessage);
    clientConnection -> closeConnection();
}
