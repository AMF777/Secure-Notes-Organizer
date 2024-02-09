#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H
#include <vector>
#include "clientconnection.h"
#include "User.h"
#include "Note.h"
#include "NoteComponent.h"
#include "Tag.h"


class ClientController
{
public:
    ClientController(const std::string& server_address, const std::string& server_port);
    
    bool ClientSignUp(User *user, std::string* response); //client set (user email, user name, user hashedPassword) and get(user id)
    bool ClientLogIn(User *user, std::string* response); //client set (user email, user hashedPassword) and get(user id, user name)
    
    bool ClientCreateNote(Note *note, std::string* response); //client set (user id, note tilte) and get(note id, note created at)
    bool ClientUpdateNoteTitle(Note *note, std::string* response); //client set (user id, note id, note tilte) and get(note updated at)
    bool ClientDeleteNote(Note *note, std::string* response); //client set (user id, note id)
    
    bool ClientListNote(User *user, std::string* response, std::vector<Note>& NotesList); //client set (user id) and get (vector(NotesList))
    bool ClientSearchByNoteTitle(Note *note, std::string* response, std::vector<Note>& NotesList); //client set (user id, note tilte) and get (vector(NotesList))
    
    bool ClientCreateComponent(NoteComponent *noteComponent, User* user, std::string* response); //client set in user object (user id) and set in component object (note id, component content, Font(size, color, bold, italic, underlined, style, family, backgroundColor)) and get (component id)
    bool ClientUpdateComponent(NoteComponent *noteComponent, User* user, std::string* response); //client set in user object (user id) and set in component object (note id, component content, Font(size, color, bold, italic, underlined, style, family, backgroundColor)) and get (component id)
    bool ClientDeleteComponent(NoteComponent *noteComponenNotet, User* user, std::string* response); //client set in user object (user id) and set in component object (note id, component id)
    bool ClientListComponents(Note *note, std::string* response, std::vector<NoteComponent>& ComponentsList); //client set(user id, note id) and get vector(ComponentsList))

    bool ClientAddTag(Tag *tag, User* user, std::string* response); //client set in user object (user id) and set in tag object (note id, tag name) and get (tag id)
    bool ClientUpdateTag(Tag *tag, User* user, std::string* response); //client set in user object (user id) and set in tag object (note id, tag name, tag id)
    bool ClientDeleteTag(Tag *tag, User* user, std::string* response); //client set in user object (user id) and set in tag object (note id, tag name, tag id) 
    bool ClientFilterByTagName(Tag *tag, User* user, std::string* response, std::vector<Note>& NotesList); //client set in user object (user id) and set in tag object (ag name) and get (vector(NotesList))

    bool ClientListNoteTags(Note *note, std::string* response, std::vector<Tag>& TagsList);
    bool ClientUpdateUserData(User *user, std::string* response);

    void ClientLogout();

private:
    ClientConnection *clientConnection;
    unsigned int msg_id;
};


namespace GlobalClient{
    extern ClientController client;
    extern int notesCounter;
}

#endif // CLIENTCONTROLLER_H

