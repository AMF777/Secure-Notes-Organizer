
#include "ServerWithDC.h"

ServerWithDC::ServerWithDC(){
	// connect with database
	dataController->connect("tcp://127.0.0.1","root","databaseRoot","SecureNoteOrganizer");
}

bool ServerWithDC::ServerSendtoDC_Signup(User& receivedObject, int& userIdFromDC){
	string name = receivedObject.getuserName();
	string email = receivedObject.getemail();
	string password = receivedObject.gethashedPassword();

	bool flag = false;
	if(name != "null" && email != "null", password != "null"){
		//call appropriate function in Data Controller to handle signup request
		flag = dataController->Dc_signup(receivedObject);     
		userIdFromDC = receivedObject.getuserId();
	}
	return flag;
}

bool ServerWithDC::ServerSendtoDC_Login(User& receivedObject, User& responseObject){
	string email = receivedObject.getemail();
	string password = receivedObject.gethashedPassword();

	bool flag = false;
	if(email != "null" && password != "null"){
		//call appropriate function in Data Controller to handle login request
		flag = dataController->Dc_login(receivedObject);
		int userIdFromDC = receivedObject.getuserId();
		string userNameFromDC = receivedObject.getuserName();
		responseObject.setuserId(userIdFromDC);
		responseObject.setuserName(userNameFromDC);
	}
	return flag;
}

bool ServerWithDC::ServerSendtoDC_CreateNote(Note& receivedObject, Note& responseObject){
	int id = receivedObject.getuserId();
	string title = receivedObject.gettitle();

	bool flag = false;
	if(id != -1 && title != "null"){
		//call appropriate function in Data Controller to handle create note request
		flag = dataController->Dc_CreateNote(receivedObject);
		int noteIdFromDC = receivedObject.getnoteId();
		string createdAtFromDC = receivedObject.getcreatedAt();
		responseObject.setnoteId(noteIdFromDC);
		responseObject.setcreatedAt(createdAtFromDC);
	}
	return flag;
}

bool ServerWithDC::ServerSendtoDC_UpdateNoteTitle(Note& receivedObject, Note& responseObject){
	int idOfUser = receivedObject.getuserId();
	int idOfNote = receivedObject.getnoteId();
	string title = receivedObject.gettitle();

	bool flag = false;
	if(idOfUser != -1 && idOfNote != -1 && title != "null"){
		//call appropriate function in Data Controller to handle create note request
		flag = dataController->Dc_UpdateNoteTitle(receivedObject);
		string updatedAtFromDC = receivedObject.getcreatedAt();
		responseObject.setupdatedAt(updatedAtFromDC);
	}
	return flag;
}
bool ServerWithDC::ServerSendtoDC_DeleteNote(Note& receivedObject){
	int idOfUser = receivedObject.getuserId();
	int idOfNote = receivedObject.getnoteId();

	bool flag = false;
	if(idOfUser != -1 && idOfNote != -1){
		//call appropriate function in Data Controller to handle create note request
		flag = dataController->Dc_DeleteNote(idOfNote, idOfUser);
	}
	return flag;
}

bool ServerWithDC::ServerSendtoDC_ListNotes(int userIDFromCC, vector<Note>& notes, string& responseFromDC){
	if(userIDFromCC != -1){
		//call appropriate function in Data Controller to handle create note request
		vector<Note> notesFromDC = dataController->Dc_ListUserNotes(userIDFromCC, responseFromDC);
		if(responseFromDC == "Success"){
			for (Note& item : notesFromDC) {
				notes.push_back(item);
			}
			return true;
		}
	}
	return false;
}

bool ServerWithDC::ServerSendtoDC_SearchByTitle(Note& receivedObject, vector<Note>& notes, string& responseFromDC){
	int idOfUser = receivedObject.getuserId();
	string title = receivedObject.gettitle();
	if(idOfUser != -1 && title != "null"){
		//call appropriate function in Data Controller to handle create note request
		vector<Note> notesFromDC = dataController->Dc_SearchByTitle(idOfUser, title, responseFromDC);
		if(responseFromDC == "Success"){
			for (Note& item : notesFromDC) {
				notes.push_back(item);
			}
			return true;
		}
	}
	return false;
}

bool ServerWithDC::ServerSendtoDC_CreateComponent(NoteComponent& receivedObject, int userIdFromCC, int& componentIdFromDC){
	int noteID = receivedObject.getnoteId();
	string content = receivedObject.getcomponentContent();

	bool flag = false;
	if(userIdFromCC != -1 && noteID != -1, content != "null"){
		//call appropriate function in Data Controller to handle signup request
		flag = dataController->Dc_CreateNoteComponent(receivedObject, userIdFromCC);     
		componentIdFromDC = receivedObject.getcomponentId();
	}
	return flag;
}

bool ServerWithDC::ServerSendtoDC_UpdateComponent(NoteComponent& receivedObject, int userIdFromCC){
	int noteID = receivedObject.getnoteId();
	int componentID = receivedObject.getcomponentId();
	string content = receivedObject.getcomponentContent();

	bool flag = false;
	if(userIdFromCC != -1 && noteID != -1 && componentID != -1 && content != "null"){
		//call appropriate function in Data Controller to handle signup request
		flag = dataController->Dc_UpdateNoteComponent(receivedObject, userIdFromCC);     
	}
	return flag;
}

bool ServerWithDC::ServerSendtoDC_DeleteComponent(NoteComponent& receivedObject, int userIdFromCC){
	int noteID = receivedObject.getnoteId();
	int componentID = receivedObject.getcomponentId();
	bool flag = false;
	if(userIdFromCC != -1 && noteID != -1 && componentID != -1){
		//call appropriate function in Data Controller to handle signup request
		flag = dataController->Dc_DeleteNoteComponent(componentID, userIdFromCC, noteID);     
	}
	return flag;
}

bool ServerWithDC::ServerSendtoDC_ListComponents(Note& receivedObject, vector<NoteComponent>& components, string& responseFromDC){
	int idOfUser = receivedObject.getuserId();
	int idOfNote = receivedObject.getnoteId();
	if(idOfUser != -1 && idOfNote != -1){
		//call appropriate function in Data Controller to handle create note request
		vector<NoteComponent> componentsFromDC = dataController->Dc_ListNoteComponents(receivedObject, responseFromDC);
		if(responseFromDC == "Success"){
			for (NoteComponent& item : componentsFromDC) {
				components.push_back(item);
			}
			return true;
		}
	}
	return false;
}

bool ServerWithDC::ServerSendtoDC_AddTag(Tag& receivedObject, Tag& responseObject, int userIdFromCC){
	int idOfNote = receivedObject.getnoteId();
	string tagNameFromCC = receivedObject.gettagName();
	bool flag = false;
	if(tagNameFromCC != "null" && idOfNote != -1 && userIdFromCC != -1){
		//call appropriate function in Data Controller to handle signup request
		flag = dataController->Dc_AddTag(receivedObject, userIdFromCC);
		responseObject.settagId(receivedObject.gettagId());
	}
	return flag;
}

bool ServerWithDC::ServerSendtoDC_UpdateTag(Tag& receivedObject, int userIdFromCC){
	int idOfNote = receivedObject.getnoteId();
	int idOfTag = receivedObject.gettagId();
	string tagNameFromCC = receivedObject.gettagName();
	bool flag = false;
	if(tagNameFromCC != "null" && idOfNote != -1 && idOfTag != -1 && userIdFromCC != -1){
		//call appropriate function in Data Controller to handle signup request
		flag = dataController->Dc_UpdateTag(receivedObject, userIdFromCC);
	}
	return flag;
}

bool ServerWithDC::ServerSendtoDC_DeleteTag(Tag& receivedObject, int userIdFromCC){
	int idOfNote = receivedObject.getnoteId();
	int idOfTag = receivedObject.gettagId();
	bool flag = false;
	if(idOfNote != -1 && idOfTag != -1 && userIdFromCC != -1){
		//call appropriate function in Data Controller to handle signup request
		flag = dataController->Dc_DeleteTag(receivedObject, userIdFromCC);
	}
	return flag;
}

bool ServerWithDC::ServerSendtoDC_FilterByTagName(int& userIdFromCC, string& tagNameFromCC, vector<Note>& notes, string& responseFromDC){
	if(userIdFromCC != -1 && tagNameFromCC != "null"){
		//call appropriate function in Data Controller to handle create note request
		vector<Note> notesFromDC = dataController->Dc_FilterByTagName(tagNameFromCC, userIdFromCC, responseFromDC);
		if(responseFromDC == "Success"){
			for (Note& item : notesFromDC) {
				notes.push_back(item);
			}
			return true;
		}
	}
	return false;
}

bool ServerWithDC::ServerSendtoDC_ListNoteTags(Note& receivedObject, vector<Tag>& tags, string& responseFromDC){
	int userIdFromCC = receivedObject.getuserId();
	int noteIdFromCC = receivedObject.getnoteId();

	if(userIdFromCC != -1 && noteIdFromCC != -1){
		//call appropriate function in Data Controller to handle signup request
		vector<Tag> tagsFromDC = dataController->Dc_ListNoteTags(noteIdFromCC, userIdFromCC, responseFromDC);  
		if(responseFromDC == "Success"){   
			for (Tag& item : tagsFromDC) {
					tags.push_back(item);
			}
			return true;
		}
	}
	return false;
}

bool ServerWithDC::ServerSendtoDC_UpdateUserData(User& receivedObject){
	string name = receivedObject.getuserName();
	string email = receivedObject.getemail();
	string password = receivedObject.gethashedPassword();

	bool flag = false;
	if(name != "null" && email != "null", password != "null"){
		//call appropriate function in Data Controller to handle signup request
		flag = dataController->Dc_UpdateUserData(receivedObject);     
	}
	return flag;
}

ServerWithDC::~ServerWithDC(){
	delete dataController;
}