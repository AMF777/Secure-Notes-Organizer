#include <iostream>
#include "ParseJsonMesssge.h"

json processJsonMessage(const json& message){
	json responseMessage;
	try{
		if (message.find("ID") != message.end()) {
			int ID = message["ID"];
			std::cout << std::endl << std::endl;
			std::cout << "Server received: message " << ID;
			responseMessage = checkAction(message);
		}
		else{
			std::cout << "Key 'ID' not found in the message.\n";
			std::string error = "Key 'ID' not found in the message.";
            throw error;
		}
	}
	catch(const std::string error){
		responseMessage["Response"] = error;
	}
	catch(const json::exception& e){
		std::cout << e.what() << '\n';
        std::string jsonError = e.what();
        responseMessage["Response"] = jsonError;
	}
	return responseMessage;
}

static json checkAction(const json& message){
	json responseMessage;
	string action = message["Action"];
	responseMessage["ID"] = message["ID"];
	std::cout << ", with action " << action << std::endl;
	if(action == "signup"){
		processSignupMessage(message,responseMessage);
	}
	else if(action == "login"){ 
		processLoginMessage(message,responseMessage);
	}
	else if(action == "create note"){
		processCreateNoteMessage(message,responseMessage);
	}
	else if(action == "update note title"){
		processUpdateNoteTitleMessage(message,responseMessage);
	}
	else if(action == "delete note"){
		processDeleteNoteMessage(message,responseMessage);
	}
	else if(action == "list notes"){
		processListNotesMessage(message,responseMessage);
	}
	else if(action == "search by note title"){
		processSearchByTitleMessage(message,responseMessage);
	}
	else if(action == "create component"){
		processCreateComponentMessage(message,responseMessage);
	}
	else if(action == "update component"){
		processUpdateComponentMessage(message,responseMessage);
	}
	else if(action == "delete component"){
		processDeleteComponentMessage(message,responseMessage);
	}
	else if(action == "list components"){
		processListComponentsMessage(message,responseMessage);
	}
	else if(action == "add tag"){
		processAddTagMessage(message,responseMessage);
	}
	else if(action == "update tag"){
		processUpdateTagMessage(message,responseMessage);
	}
	else if(action == "delete tag"){
		processDeleteTagMessage(message,responseMessage);
	}
	else if(action == "filter by tag name"){
		processFilterByTagNameMessage(message,responseMessage);
	}
	else if(action == "list note tags"){
		processListNoteTagsMessage(message,responseMessage);
	}
	else if(action == "update user data"){
		processUpdateUserDatasMessage(message,responseMessage);
	}
	else{
		responseMessage["Response"] = "wrong action was sent";
		std::cout << "wrong action was sent" << std::endl;
	}
	return responseMessage;
}

static void processSignupMessage(const json& message, json& responseMessage){
	User receivedObject;
	User userTempObject;
	ServerWithDC ServerTempObject;
	int userIdFromDC;
	try{
		if (message.find("Data") != message.end()) {
			if(message["Data"].find("user email") != message["Data"].end()){
				receivedObject = userTempObject.fromJson(message["Data"]);
				bool response = ServerTempObject.ServerSendtoDC_Signup(receivedObject, userIdFromDC);
				if(response){
					responseMessage["Response"] = "signup successfully";
					responseMessage["user id"] = userIdFromDC;
				}else{
					responseMessage["Response"] = "signup failed, Email is already in use ";
				}
			}
			else{
				std::cout << "key 'Data' not have an object of type user.\n";
				std::string error = "key 'Data' not have an object of type user.";
           	 	throw error;
			}
		}
		else{
			std::cout << "Key 'Data' not found in the message.\n";
			std::string error = "Key 'Data' not found in the message.";
            throw error;
		}
	}
	catch(const std::string error){
		responseMessage["Response"] = error;
	}
	catch(const json::exception& e){
		std::cout << e.what() << '\n';
        std::string jsonError = e.what();
        responseMessage["Response"] = jsonError;
	}
}

static void processLoginMessage(const json& message, json& responseMessage){
	User receivedObject;
	User userTempObject;
	ServerWithDC ServerTempObject;
	User responseObject;
	try{
		if (message.find("Data") != message.end()) {
			if(message["Data"].find("user email") != message["Data"].end()){
				receivedObject = userTempObject.fromJson(message["Data"]);
				bool response = ServerTempObject.ServerSendtoDC_Login(receivedObject, responseObject);
				
				if(response){
					responseMessage["Response"] = "login successfully";
					responseMessage["Data"] = responseObject.toJson();
				}else{
					responseMessage["Response"] = "login failed, User not found";
				}
			}
			else{
				std::cout << "key 'Data' not have an object of type user.\n";
				std::string error = "key 'Data' not have an object of type user.";
           	 	throw error;
			}
		}
		else{
			std::cout << "Key 'Data' not found in the message.\n";
			std::string error = "Key 'Data' not found in the message.";
            throw error;
		}
	}
	catch(const std::string error){
		responseMessage["Response"] = error;
	}
	catch(const json::exception& e){
		std::cout << e.what() << '\n';
        std::string jsonError = e.what();
        responseMessage["Response"] = jsonError;
	}
}

static void processCreateNoteMessage(const json& message, json& responseMessage){
	Note receivedObject;
	Note noteTempObject;
	ServerWithDC ServerTempObject;
	Note responseObject;
	try{
		if (message.find("Data") != message.end()) {
			if(message["Data"].find("note title") != message["Data"].end()){
				receivedObject = noteTempObject.fromJson(message["Data"]);
				bool response = ServerTempObject.ServerSendtoDC_CreateNote(receivedObject, responseObject);

				if(response){
					responseMessage["Response"] = "note created successfully";
					responseMessage["Data"] = responseObject.toJson();
				}else{
					responseMessage["Response"] = "create note failed, User not found";
				}
			}
			else{
				std::cout << "key 'Data' not have an object of type note.\n";
				std::string error = "key 'Data' not have an object of type note.";
           	 	throw error;
			}
		}
		else{
			std::cout << "Key 'Data' not found in the message.\n";
			std::string error = "Key 'Data' not found in the message.";
            throw error;
		}
	}
	catch(const std::string error){
		responseMessage["Response"] = error;
	}
	catch(const json::exception& e){
		std::cout << e.what() << '\n';
        std::string jsonError = e.what();
        responseMessage["Response"] = jsonError;
	}
}

static void processUpdateNoteTitleMessage(const json& message, json& responseMessage){
	Note receivedObject;
	Note noteTempObject;
	ServerWithDC ServerTempObject;
	Note responseObject;
	try{
		if (message.find("Data") != message.end()) {
			if(message["Data"].find("note title") != message["Data"].end()){
				receivedObject = noteTempObject.fromJson(message["Data"]);
				bool response = ServerTempObject.ServerSendtoDC_UpdateNoteTitle(receivedObject, responseObject);

				if(response){
					responseMessage["Response"] = "note updated successfully";
					responseMessage["Data"] = responseObject.toJson();
				}else{
					responseMessage["Response"] = "update note failed, User or Note not found";
				}
			}
			else{
				std::cout << "key 'Data' not have an object of type note.\n";
				std::string error = "key 'Data' not have an object of type note.";
           	 	throw error;
			}
		}
		else{
			std::cout << "Key 'Data' not found in the message.\n";
			std::string error = "Key 'Data' not found in the message.";
            throw error;
		}
	}
	catch(const std::string error){
		responseMessage["Response"] = error;
	}
	catch(const json::exception& e){
		std::cout << e.what() << '\n';
        std::string jsonError = e.what();
        responseMessage["Response"] = jsonError;
	}
}


static void processDeleteNoteMessage(const json& message, json& responseMessage){
	Note receivedObject;
	Note noteTempObject;
	ServerWithDC ServerTempObject;
	try{
		if (message.find("Data") != message.end()) {
			if(message["Data"].find("note title") != message["Data"].end()){
				receivedObject = noteTempObject.fromJson(message["Data"]);
				bool response = ServerTempObject.ServerSendtoDC_DeleteNote(receivedObject);

				if(response){
					responseMessage["Response"] = "note deleted successfully";
				}else{
					responseMessage["Response"] = "delete note failed, User or Note not found";
				}
			}
			else{
				std::cout << "key 'Data' not have an object of type note.\n";
				std::string error = "key 'Data' not have an object of type note.";
           	 	throw error;
			}
		}
		else{
			std::cout << "Key 'Data' not found in the message.\n";
			std::string error = "Key 'Data' not found in the message.";
            throw error;
		}
	}
	catch(const std::string error){
		responseMessage["Response"] = error;
	}
	catch(const json::exception& e){
		std::cout << e.what() << '\n';
        std::string jsonError = e.what();
        responseMessage["Response"] = jsonError;
	}
}

static void processListNotesMessage(const json& message, json& responseMessage){
	ServerWithDC ServerTempObject;
	std::vector<Note> notes;
	try{
		if (message.find("user id") != message.end()) {
			int userIDFromCC = message["user id"];
			string responseFromDC;
			bool response = ServerTempObject.ServerSendtoDC_ListNotes(userIDFromCC, notes, responseFromDC);
			json notesArray = notes;
			if(response){
				responseMessage["Response"] = "list notes successfully";
				responseMessage["Data"] = notesArray; 
			}else{
				responseMessage["Response"] = responseFromDC;
			}
		}
		else{
			std::cout << "Key 'user id' not found in the message.\n";
			std::string error = "Key 'user id' not found in the message.";
            throw error;
		}
	}
	catch(const std::string error){
		responseMessage["Response"] = error;
	}
	catch(const json::exception& e){
		std::cout << e.what() << '\n';
        std::string jsonError = e.what();
        responseMessage["Response"] = jsonError;
	}
}

static void processSearchByTitleMessage(const json& message, json& responseMessage){
	Note receivedObject;
	Note noteTempObject;
	ServerWithDC ServerTempObject;
	std::vector<Note> notes;
	try{
		if (message.find("Data") != message.end()) {
			if(message["Data"].find("note title") != message["Data"].end()){
				receivedObject = noteTempObject.fromJson(message["Data"]);
				string responseFromDC;
				bool response = ServerTempObject.ServerSendtoDC_SearchByTitle(receivedObject, notes, responseFromDC);
				json notesArray = notes;
				if(response){
					responseMessage["Response"] = "search by title successfully";
					responseMessage["Data"] = notesArray; 
				}else{
					responseMessage["Response"] = responseFromDC;
				}
			}
			else{
				std::cout << "key 'Data' not have an object of type note.\n";
				std::string error = "key 'Data' not have an object of type note.";
           	 	throw error;
			}
		}
		else{
			std::cout << "Key 'Data' not found in the message.\n";
			std::string error = "Key 'Data' not found in the message.";
            throw error;
		}
	}
	catch(const std::string error){
		responseMessage["Response"] = error;
	}
	catch(const json::exception& e){
		std::cout << e.what() << '\n';
        std::string jsonError = e.what();
        responseMessage["Response"] = jsonError;
	}
}

static void processCreateComponentMessage(const json& message, json& responseMessage){
	NoteComponent receivedObject;
	NoteComponent noteComponentTempObject;
	ServerWithDC ServerTempObject;
	int componentIdFromDC;
	try{
		if (message.find("Data") != message.end() && message.find("user id") != message.end()) {
			if(message["Data"].find("component content") != message["Data"].end()){
				receivedObject = noteComponentTempObject.fromJson(message["Data"]);
				int userIdFromCC = message["user id"];
				bool response = ServerTempObject.ServerSendtoDC_CreateComponent(receivedObject, userIdFromCC ,componentIdFromDC);
				if(response){
					responseMessage["Response"] = "component created successfully";
					responseMessage["component id"] = componentIdFromDC; 
				}else{
					responseMessage["Response"] = "create component failed, User or Note not found";
				}
			}
			else{
				std::cout << "key 'Data' not have an object of type NoteComponent.\n";
				std::string error = "key 'Data' not have an object of type NoteComponent.";
           	 	throw error;
			}
		}
		else{
			std::cout << "Key 'Data' or 'user id' not found in the message.\n";
			std::string error = "Key 'Data' or 'user id' not found in the message.";
            throw error;
		}
	}
	catch(const std::string error){
		responseMessage["Response"] = error;
	}
	catch(const json::exception& e){
		std::cout << e.what() << '\n';
        std::string jsonError = e.what();
        responseMessage["Response"] = jsonError;
	}
}

static void processUpdateComponentMessage(const json& message, json& responseMessage){
	NoteComponent receivedObject;
	NoteComponent noteComponentTempObject;
	ServerWithDC ServerTempObject;
	try{
		if (message.find("Data") != message.end() && message.find("user id") != message.end()) {
			if(message["Data"].find("component content") != message["Data"].end()){
				receivedObject = noteComponentTempObject.fromJson(message["Data"]);
				int userIdFromCC = message["user id"];
				bool response = ServerTempObject.ServerSendtoDC_UpdateComponent(receivedObject, userIdFromCC);
				if(response){
					responseMessage["Response"] = "component updated successfully";
				}else{
					responseMessage["Response"] = "update component failed, User or Note or Component not found";
				}
			}
			else{
				std::cout << "key 'Data' not have an object of type NoteComponent.\n";
				std::string error = "key 'Data' not have an object of type NoteComponent.";
           	 	throw error;
			}
		}
		else{
			std::cout << "Key 'Data' or 'user id' not found in the message.\n";
			std::string error = "Key 'Data' or 'user id' not found in the message.";
            throw error;
		}
	}
	catch(const std::string error){
		responseMessage["Response"] = error;
	}
	catch(const json::exception& e){
		std::cout << e.what() << '\n';
        std::string jsonError = e.what();
        responseMessage["Response"] = jsonError;
	}
}

static void processDeleteComponentMessage(const json& message, json& responseMessage){
	NoteComponent receivedObject;
	NoteComponent noteComponentTempObject;
	ServerWithDC ServerTempObject;
	try{
		if (message.find("Data") != message.end() && message.find("user id") != message.end()) {
			if(message["Data"].find("component content") != message["Data"].end()){
				receivedObject = noteComponentTempObject.fromJson(message["Data"]);
				int userIdFromCC = message["user id"];
				bool response = ServerTempObject.ServerSendtoDC_DeleteComponent(receivedObject, userIdFromCC);
				if(response){
					responseMessage["Response"] = "component deleted successfully";
				}else{
					responseMessage["Response"] = "delete component failed, User or Note or Component not found";
				}
			}
			else{
				std::cout << "key 'Data' not have an object of type NoteComponent.\n";
				std::string error = "key 'Data' not have an object of type NoteComponent.";
           	 	throw error;
			}
		}
		else{
			std::cout << "Key 'Data' or 'user id' not found in the message.\n";
			std::string error = "Key 'Data' or 'user id' not found in the message.";
            throw error;
		}
	}
	catch(const std::string error){
		responseMessage["Response"] = error;
	}
	catch(const json::exception& e){
		std::cout << e.what() << '\n';
        std::string jsonError = e.what();
        responseMessage["Response"] = jsonError;
	}
}

static void processListComponentsMessage(const json& message, json& responseMessage){
	Note receivedObject;
	Note noteTempObject;
	ServerWithDC ServerTempObject;
	std::vector<NoteComponent> components;
	try{
		if (message.find("Data") != message.end()) {
			if(message["Data"].find("note title") != message["Data"].end()){
				receivedObject = noteTempObject.fromJson(message["Data"]);
				string responseFromDC;
				bool response = ServerTempObject.ServerSendtoDC_ListComponents(receivedObject, components, responseFromDC);
				json componentsArray = components;
				if(response){
					responseMessage["Response"] = "list components successfully";
					responseMessage["Data"] = componentsArray; 
				}else{
					responseMessage["Response"] = responseFromDC;
				}
			}
			else{
				std::cout << "key 'Data' not have an object of type note.\n";
				std::string error = "key 'Data' not have an object of type note.";
           	 	throw error;
			}
		}
		else{
			std::cout << "Key 'Data' not found in the message.\n";
			std::string error = "Key 'Data' not found in the message.";
            throw error;
		}
	}
	catch(const std::string error){
		responseMessage["Response"] = error;
	}
	catch(const json::exception& e){
		std::cout << e.what() << '\n';
        std::string jsonError = e.what();
        responseMessage["Response"] = jsonError;
	}
}

static void processAddTagMessage(const json& message, json& responseMessage){
	Tag receivedObject;
	Tag tagTempObject;
	Tag responseObject;
	ServerWithDC ServerTempObject;
	try{
		if (message.find("Data") != message.end() && message.find("user id") != message.end()) {
			if(message["Data"].find("tag name") != message["Data"].end()){
				receivedObject = tagTempObject.fromJson(message["Data"]);
				int userIdFromCC = message["user id"];
				bool response = ServerTempObject.ServerSendtoDC_AddTag(receivedObject, responseObject, userIdFromCC);
				if(response){
					responseMessage["Data"] = responseObject.toJson();
					responseMessage["Response"] = "tag added successfully";
				}else{
					responseMessage["Response"] = "add tag failed, User or Note not found";
				}
			}
			else{
				std::cout << "key 'Data' not have an object of type Tag.\n";
				std::string error = "key 'Data' not have an object of type Tag.";
           	 	throw error;
			}
		}
		else{
			std::cout << "Key 'Data' or 'user id' not found in the message.\n";
			std::string error = "Key 'Data' or 'user id' not found in the message.";
            throw error;
		}
	}
	catch(const std::string error){
		responseMessage["Response"] = error;
	}
	catch(const json::exception& e){
		std::cout << e.what() << '\n';
        std::string jsonError = e.what();
        responseMessage["Response"] = jsonError;
	}
}

static void processUpdateTagMessage(const json& message, json& responseMessage){
	Tag receivedObject;
	Tag tagTempObject;
	ServerWithDC ServerTempObject;
	try{
		if (message.find("Data") != message.end() && message.find("user id") != message.end()) {
			if(message["Data"].find("tag name") != message["Data"].end()){
				receivedObject = tagTempObject.fromJson(message["Data"]);
				int userIdFromCC = message["user id"];
				bool response = ServerTempObject.ServerSendtoDC_UpdateTag(receivedObject, userIdFromCC);
				if(response){
					responseMessage["Response"] = "tag updated successfully";
				}else{
					responseMessage["Response"] = "update tag failed, User or Note or Tag not found";
				}
			}
			else{
				std::cout << "key 'Data' not have an object of type Tag.\n";
				std::string error = "key 'Data' not have an object of type Tag.";
           	 	throw error;
			}
		}
		else{
			std::cout << "Key 'Data' or 'user id' not found in the message.\n";
			std::string error = "Key 'Data' or 'user id' not found in the message.";
            throw error;
		}
	}
	catch(const std::string error){
		responseMessage["Response"] = error;
	}
	catch(const json::exception& e){
		std::cout << e.what() << '\n';
        std::string jsonError = e.what();
        responseMessage["Response"] = jsonError;
	}
}

static void processDeleteTagMessage(const json& message, json& responseMessage){
	Tag receivedObject;
	Tag tagTempObject;
	ServerWithDC ServerTempObject;
	try{
		if (message.find("Data") != message.end() && message.find("user id") != message.end()) {
			if(message["Data"].find("tag name") != message["Data"].end()){
				receivedObject = tagTempObject.fromJson(message["Data"]);
				int userIdFromCC = message["user id"];
				bool response = ServerTempObject.ServerSendtoDC_DeleteTag(receivedObject, userIdFromCC);
				if(response){
					responseMessage["Response"] = "tag deleted successfully";
				}else{
					responseMessage["Response"] = "delete tag failed, User or Note or Tag not found";
				}
			}
			else{
				std::cout << "key 'Data' not have an object of type Tag.\n";
				std::string error = "key 'Data' not have an object of type Tag.";
           	 	throw error;
			}
		}
		else{
			std::cout << "Key 'Data' or 'user id' not found in the message.\n";
			std::string error = "Key 'Data' or 'user id' not found in the message.";
            throw error;
		}
	}
	catch(const std::string error){
		responseMessage["Response"] = error;
	}
	catch(const json::exception& e){
		std::cout << e.what() << '\n';
        std::string jsonError = e.what();
        responseMessage["Response"] = jsonError;
	}

}

static void processFilterByTagNameMessage(const json& message, json& responseMessage){
	ServerWithDC ServerTempObject;
	std::vector<Note> notes;
	try{
		if (message.find("tag name") != message.end() && message.find("user id") != message.end()) {
			int userIdFromCC = message["user id"];
			string tagNameFromCC = message["tag name"];
			string responseFromDC;
			bool response = ServerTempObject.ServerSendtoDC_FilterByTagName(userIdFromCC, tagNameFromCC, notes, responseFromDC);
			json notesArray = notes;
			if(response){
				responseMessage["Response"] = "filter by tag name successfully";
				responseMessage["Data"] = notesArray; 
			}else{
				responseMessage["Response"] = responseFromDC;
			}
		}
		else{
			std::cout << "Key 'tag name' or 'user id' not found in the message.\n";
			std::string error = "Key 'tag name' or 'user id' not found in the message.";
            throw error;
		}
	}
	catch(const std::string error){
		responseMessage["Response"] = error;
	}
	catch(const json::exception& e){
		std::cout << e.what() << '\n';
        std::string jsonError = e.what();
        responseMessage["Response"] = jsonError;
	}
}

static void processListNoteTagsMessage(const json& message, json& responseMessage){
	Note receivedObject;
	Note userTempObject;
	ServerWithDC ServerTempObject;
	std::vector<Tag> tags;
	try{
		if (message.find("Data") != message.end()) {
			if(message["Data"].find("note title") != message["Data"].end()){
				receivedObject = userTempObject.fromJson(message["Data"]);
				string responseFromDC;
				bool response = ServerTempObject.ServerSendtoDC_ListNoteTags(receivedObject, tags, responseFromDC);
				json tagsArray = tags;
				if(response){
					responseMessage["Response"] = "list tags of note successfully";
					responseMessage["Data"] = tagsArray;
				}else{
					responseMessage["Response"] = responseFromDC;
				}
			}
			else{
				std::cout << "key 'Data' not have an object of type user.\n";
				std::string error = "key 'Data' not have an object of type note.";
           	 	throw error;
			}
		}
		else{
			std::cout << "Key 'Data' not found in the message.\n";
			std::string error = "Key 'Data' not found in the message.";
            throw error;
		}
	}
	catch(const std::string error){
		responseMessage["Response"] = error;
	}
	catch(const json::exception& e){
		std::cout << e.what() << '\n';
        std::string jsonError = e.what();
        responseMessage["Response"] = jsonError;
	}
}

static void processUpdateUserDatasMessage(const json& message, json& responseMessage){
	User receivedObject;
	User userTempObject;
	ServerWithDC ServerTempObject;
	try{
		if (message.find("Data") != message.end()) {
			if(message["Data"].find("user email") != message["Data"].end()){
				receivedObject = userTempObject.fromJson(message["Data"]);
				bool response = ServerTempObject.ServerSendtoDC_UpdateUserData(receivedObject);
				if(response){
					responseMessage["Response"] = "update user data successfully";
				}else{
					responseMessage["Response"] = "update user data failed, Email not found";
				}
			}
			else{
				std::cout << "key 'Data' not have an object of type user.\n";
				std::string error = "key 'Data' not have an object of type user.";
           	 	throw error;
			}
		}
		else{
			std::cout << "Key 'Data' not found in the message.\n";
			std::string error = "Key 'Data' not found in the message.";
            throw error;
		}
	}
	catch(const std::string error){
		responseMessage["Response"] = error;
	}
	catch(const json::exception& e){
		std::cout << e.what() << '\n';
        std::string jsonError = e.what();
        responseMessage["Response"] = jsonError;
	}
}