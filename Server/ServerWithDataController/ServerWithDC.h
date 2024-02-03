#ifndef ServerWithDC_H
#define ServerWithDC_H

#include <iostream>
#include <string>
#include <vector>

#include "DataController.h"

using namespace std;

class ServerWithDC{
private:
	DataController* dataController = new DataController();
	//std::mutex S_mtx;
public:
	ServerWithDC();

	bool ServerSendtoDC_Signup(User& receivedObject, int& userIdFromDC);
	bool ServerSendtoDC_Login(User& receivedObject, User& responseObject);

	bool ServerSendtoDC_CreateNote(Note& receivedObject, Note& responseObject);
	bool ServerSendtoDC_UpdateNoteTitle(Note& receivedObject, Note& responseObject);
	bool ServerSendtoDC_DeleteNote(Note& receivedObject);

	bool ServerSendtoDC_ListNotes(int userIDFromCC, vector<Note>& notes);
	bool ServerSendtoDC_SearchByTitle(Note& receivedObject, vector<Note>& notes);

	bool ServerSendtoDC_CreateComponent(NoteComponent& receivedObject, int userIdFromCC, int& componentIdFromDC);
	bool ServerSendtoDC_UpdateComponent(NoteComponent& receivedObject, int userIdFromCC);
	bool ServerSendtoDC_DeleteComponent(NoteComponent& receivedObject, int userIdFromCC);
	bool ServerSendtoDC_ListComponents(Note& receivedObject, vector<NoteComponent>& components);

	bool ServerSendtoDC_AddTag(Tag& receivedObject, int userIdFromCC);
	bool ServerSendtoDC_UpdateTag(Tag& receivedObject, int userIdFromCC);
	bool ServerSendtoDC_DeleteTag(Tag& receivedObject, int userIdFromCC);
	bool ServerSendtoDC_FilterByTagName(int& userIdFromCC, string& tagNameFromCC, vector<Note>& notes);

	~ServerWithDC();
};

#endif //ServerWithDC_H