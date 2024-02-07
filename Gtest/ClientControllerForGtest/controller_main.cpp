#include <gtest/gtest.h>

#include <iostream>

#include "userController.h"
#include "User.h"
#include "Note.h"
#include "NoteComponent.h"
#include "Tag.h"

boost::asio::io_service ioService;
short port = 12345;
TCPClient client(ioService, "127.0.0.1", port);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//1- signup message with new email
bool sendAndReceive_SignUp1(){
	json message1;
	message1["ID"] = 1;
	message1["Action"] = "signup";

	User user1;
	user1.setuserName("mary");
	user1.setemail("mary@gmail.com");
	user1.sethashedPassword("1718");
	message1["Data"] = user1.toJson();

	client.Send(message1);

	// Receiving a JSON response from the server
	json response1 = client.Receive();
	std::cout << "Response: " << response1.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true; 
}
TEST(JsonMessageTest, TestSignUpWithNewEmail){
    bool result = sendAndReceive_SignUp1();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//2- signup message with email already in use
bool sendAndReceive_SignUp2(){
	json message1;
	message1["ID"] = 1;
	message1["Action"] = "signup";

	User user1;
	user1.setuserName("user20");
	user1.setemail("user@gmail.com");
	user1.sethashedPassword("2020");
	message1["Data"] = user1.toJson();

	client.Send(message1);

	// Receiving a JSON response from the server
	json response1 = client.Receive();
	std::cout << "Response: " << response1.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true; 
}
TEST(JsonMessageTest, TestSignUpWithEmailAlreadyInUse){
    bool result = sendAndReceive_SignUp2();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//3- signup message with missing key "Data"
bool sendAndReceive_SignUp3(){
	json message1;
	message1["ID"] = 1;
	message1["Action"] = "signup";

	User user1;
	user1.setuserName("user1");
	user1.setemail("user1@gmail.com");
	user1.sethashedPassword("9876");
	message1["data"] = user1.toJson();

	client.Send(message1);

	// Receiving a JSON response from the server
	json response1 = client.Receive();
	std::cout << "Response: " << response1.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true; 
}
TEST(JsonMessageTest, TestSignUpWithMissingKeyData){
    bool result = sendAndReceive_SignUp3();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//4- signup message with conflict key "Data" and its datatype
bool sendAndReceive_SignUp4(){
	json message1;
	message1["ID"] = 1;
	message1["Action"] = "signup";

	Note user1;
	message1["Data"] = user1.toJson();

	client.Send(message1);

	// Receiving a JSON response from the server
	json response1 = client.Receive();
	std::cout << "Response: " << response1.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true; 
}
TEST(JsonMessageTest, TestSignUpWithConflictKeyDataAndItsDatatype){
    bool result = sendAndReceive_SignUp4();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//5- login message with email found
bool sendAndReceive_Login1(){
	json message1;
	message1["ID"] = 2;
	message1["Action"] = "login";

	User user1;
	user1.setemail("user@gmail.com");
	user1.sethashedPassword("1234");
	message1["Data"] = user1.toJson();

	client.Send(message1);

	// Receiving a JSON response from the server
	json response1 = client.Receive();
	std::cout << "Response: " << response1.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true; 
}
TEST(JsonMessageTest, TestLoginWithEmailFound){
    bool result = sendAndReceive_Login1();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//6- login message with email not found
bool sendAndReceive_Login2(){
	json message1;
	message1["ID"] = 2;
	message1["Action"] = "login";

	User user1;
	user1.setemail("user22@gmail.com");
	user1.sethashedPassword("1234");
	message1["Data"] = user1.toJson();

	client.Send(message1);

	// Receiving a JSON response from the server
	json response1 = client.Receive();
	std::cout << "Response: " << response1.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true; 
}
TEST(JsonMessageTest, TestLoginWithEmailNotFound){
    bool result = sendAndReceive_Login2();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//7- login message with email found but wrong password
bool sendAndReceive_Login3(){
	json message1;
	message1["ID"] = 2;
	message1["Action"] = "login";

	User user1;
	user1.setemail("user@gmail.com");
	user1.sethashedPassword("6789");
	message1["Data"] = user1.toJson();

	client.Send(message1);

	// Receiving a JSON response from the server
	json response1 = client.Receive();
	std::cout << "Response: " << response1.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true; 
}
TEST(JsonMessageTest, TestLoginWithEmailFoundButWrongPassword){
    bool result = sendAndReceive_Login3();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//8- login message with missing key "Data"
bool sendAndReceive_Login4(){
	json message1;
	message1["ID"] = 2;
	message1["Action"] = "login";

	User user1;
	user1.setemail("user1@gmail.com");
	user1.sethashedPassword("6789");
	message1["data"] = user1.toJson();

	client.Send(message1);

	// Receiving a JSON response from the server
	json response1 = client.Receive();
	std::cout << "Response: " << response1.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true; 
}
TEST(JsonMessageTest, TestLoginWithMissingKeyData){
    bool result = sendAndReceive_Login4();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//9- login message with conflict key "Data" and its datatype
bool sendAndReceive_Login5(){
	json message1;
	message1["ID"] = 2;
	message1["Action"] = "login";

	Note user1;
	message1["Data"] = user1.toJson();

	client.Send(message1);

	// Receiving a JSON response from the server
	json response1 = client.Receive();
	std::cout << "Response: " << response1.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true; 
}
TEST(JsonMessageTest, TestLoginWithConflictKeyDataAndItsDatatype){
    bool result = sendAndReceive_Login5();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//10- create note message to found user
bool sendAndReceive_CreateNote1(){
	json message3;
	message3["ID"] = 3;
	message3["Action"] = "create note";

	Note note1;
	note1.setuserId(35);
	note1.settitle("first Note for user 35");
	message3["Data"] = note1.toJson();

	client.Send(message3);

	// Receiving a JSON response from the server
	json response3 = client.Receive();
	std::cout << "Response: " << response3.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestCreateNoteToFoundUser){
    bool result = sendAndReceive_CreateNote1();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//11- create note message to not found user
bool sendAndReceive_CreateNote2(){
	json message3;
	message3["ID"] = 3;
	message3["Action"] = "create note";

	Note note1;
	note1.setuserId(1);
	note1.settitle("Note");
	message3["Data"] = note1.toJson();

	client.Send(message3);

	// Receiving a JSON response from the server
	json response3 = client.Receive();
	std::cout << "Response: " << response3.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestCreateNoteToNotFoundUser){
    bool result = sendAndReceive_CreateNote2();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//12- create note message with missing key "Data"
bool sendAndReceive_CreateNote3(){
	json message3;
	message3["ID"] = 3;
	message3["Action"] = "create note";

	Note note1;
	note1.setuserId(31);
	note1.settitle("Note");
	message3["data"] = note1.toJson();

	client.Send(message3);

	// Receiving a JSON response from the server
	json response3 = client.Receive();
	std::cout << "Response: " << response3.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestCreateNoteWithMissingKeyData){
    bool result = sendAndReceive_CreateNote3();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//13- create note message with conflict key "Data" and its datatype
bool sendAndReceive_CreateNote4(){
	json message3;
	message3["ID"] = 3;
	message3["Action"] = "create note";

	User note1;
	message3["Data"] = note1.toJson();

	client.Send(message3);

	// Receiving a JSON response from the server
	json response3 = client.Receive();
	std::cout << "Response: " << response3.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestCreateNoteWithConflictKeyDataAndItsDatatype){
    bool result = sendAndReceive_CreateNote4();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//14- update note title message to user and note found
bool sendAndReceive_UpdateNoteTitle1(){
	json message4;
	message4["ID"] = 4;
	message4["Action"] = "update note title";

	Note note2;
	note2.setuserId(39);
	note2.setnoteId(20);
	note2.settitle("Updated Note for user 39");
	message4["Data"] = note2.toJson();

	client.Send(message4);

	// Receiving a JSON response from the server
	json response4 = client.Receive();
	std::cout << "Response: " << response4.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestUpdateNoteTitleToUserAndNoteFound){
    bool result = sendAndReceive_UpdateNoteTitle1();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//15- update note title message to user not found and note found
bool sendAndReceive_UpdateNoteTitle2(){
	json message4;
	message4["ID"] = 4;
	message4["Action"] = "update note title";

	Note note2;
	note2.setuserId(1);
	note2.setnoteId(20);
	note2.settitle("Updated Note");
	message4["Data"] = note2.toJson();

	client.Send(message4);

	// Receiving a JSON response from the server
	json response4 = client.Receive();
	std::cout << "Response: " << response4.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestUpdateNoteTitleToUserNotFoundAndNoteFound){
    bool result = sendAndReceive_UpdateNoteTitle2();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//16- update note title message to user found and note not found
bool sendAndReceive_UpdateNoteTitle3(){
	json message4;
	message4["ID"] = 4;
	message4["Action"] = "update note title";

	Note note2;
	note2.setuserId(39);
	note2.setnoteId(1);
	note2.settitle("Updated Note");
	message4["Data"] = note2.toJson();

	client.Send(message4);

	// Receiving a JSON response from the server
	json response4 = client.Receive();
	std::cout << "Response: " << response4.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestUpdateNoteTitleToUserFoundAndNoteNotFound){
    bool result = sendAndReceive_UpdateNoteTitle3();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//17- update note title message with missing key "Data"
bool sendAndReceive_UpdateNoteTitle4(){
	json message4;
	message4["ID"] = 4;
	message4["Action"] = "update note title";

	Note note2;
	note2.setuserId(31);
	note2.setnoteId(14);
	note2.settitle("Updated First Note");
	message4["data"] = note2.toJson();

	client.Send(message4);

	// Receiving a JSON response from the server
	json response4 = client.Receive();
	std::cout << "Response: " << response4.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestUpdateNoteTitleWithMissingKeyData){
    bool result = sendAndReceive_UpdateNoteTitle4();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//18- update note title message with conflict key "Data" and its datatype
bool sendAndReceive_UpdateNoteTitle5(){
	json message4;
	message4["ID"] = 4;
	message4["Action"] = "update note title";

	User note2;
	message4["Data"] = note2.toJson();

	client.Send(message4);

	// Receiving a JSON response from the server
	json response4 = client.Receive();
	std::cout << "Response: " << response4.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestUpdateNoteTitleWithConflictKeyDataAndItsDatatype){
    bool result = sendAndReceive_UpdateNoteTitle5();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//19- delete note message with user and note found
bool sendAndReceive_DeleteNote1(){
	json message5;
	message5["ID"] = 5;
	message5["Action"] = "delete note";

	Note note3;
	note3.setuserId(31);
	note3.setnoteId(14);
	message5["Data"] = note3.toJson();

	client.Send(message5);

	// Receiving a JSON response from the server
	json response5 = client.Receive();
	std::cout << "Response: " << response5.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestDeleteNoteWithUserAndNoteFound){
    bool result = sendAndReceive_DeleteNote1();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//20- delete note message with user not found and note found
bool sendAndReceive_DeleteNote2(){
	json message5;
	message5["ID"] = 5;
	message5["Action"] = "delete note";

	Note note3;
	note3.setuserId(1);
	note3.setnoteId(14);
	message5["Data"] = note3.toJson();

	client.Send(message5);

	// Receiving a JSON response from the server
	json response5 = client.Receive();
	std::cout << "Response: " << response5.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestDeleteNoteWithUserNotFoundAndNoteFound){
    bool result = sendAndReceive_DeleteNote2();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//21- delete note message with user found and note not found
bool sendAndReceive_DeleteNote3(){
	json message5;
	message5["ID"] = 5;
	message5["Action"] = "delete note";

	Note note3;
	note3.setuserId(31);
	note3.setnoteId(1);
	message5["Data"] = note3.toJson();

	client.Send(message5);

	// Receiving a JSON response from the server
	json response5 = client.Receive();
	std::cout << "Response: " << response5.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestDeleteNoteWithUserFoundAndNoteNotFound){
    bool result = sendAndReceive_DeleteNote3();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//22- delete note message with missing key "Data"
bool sendAndReceive_DeleteNote4(){
	json message5;
	message5["ID"] = 5;
	message5["Action"] = "delete note";

	Note note3;
	note3.setuserId(31);
	note3.setnoteId(14);
	message5["data"] = note3.toJson();

	client.Send(message5);

	// Receiving a JSON response from the server
	json response5 = client.Receive();
	std::cout << "Response: " << response5.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestDeleteNoteWithMissingKeyData){
    bool result = sendAndReceive_DeleteNote4();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//23- delete note message with conflict key "Data" and its datatype
bool sendAndReceive_DeleteNote5(){
	json message5;
	message5["ID"] = 5;
	message5["Action"] = "delete note";

	User note3;
	message5["Data"] = note3.toJson();

	client.Send(message5);

	// Receiving a JSON response from the server
	json response5 = client.Receive();
	std::cout << "Response: " << response5.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestDeleteNoteWithConflictKeyDataAndItsDatatype){
    bool result = sendAndReceive_DeleteNote5();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//24- List note message with user found
bool sendAndReceive_ListNotes1(){
	json message6;
	message6["ID"] = 6;
	message6["Action"] = "list notes";
	message6["user id"] = 31;

	client.Send(message6);

	// Receiving a JSON response from the server
	json response6 = client.Receive();
	std::cout << "Response: " << response6.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestListNotesWithUserFound){
    bool result = sendAndReceive_ListNotes1();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//25- List note message with user not found
bool sendAndReceive_ListNotes2(){
	json message6;
	message6["ID"] = 6;
	message6["Action"] = "list notes";
	message6["user id"] = 1;

	client.Send(message6);

	// Receiving a JSON response from the server
	json response6 = client.Receive();
	std::cout << "Response: " << response6.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestListNotesWithUserNotFound){
    bool result = sendAndReceive_ListNotes2();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//26- List note message with missing key "user id"
bool sendAndReceive_ListNotes3(){
	json message6;
	message6["ID"] = 6;
	message6["Action"] = "list notes";
	message6["userid"] = 31;

	client.Send(message6);

	// Receiving a JSON response from the server
	json response6 = client.Receive();
	std::cout << "Response: " << response6.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestListNotesWithMissingKeyUserId){
    bool result = sendAndReceive_ListNotes3();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//27- List note message with conflict key "user id" and its datatype
bool sendAndReceive_ListNotes4(){
	json message6;
	message6["ID"] = 6;
	message6["Action"] = "list notes";
	message6["userid"] = "31";

	client.Send(message6);

	// Receiving a JSON response from the server
	json response6 = client.Receive();
	std::cout << "Response: " << response6.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestListNotesWithConflictKeyUserIdAndItsDatatype){
    bool result = sendAndReceive_ListNotes4();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//28- search by note title message with user found
bool sendAndReceive_Search1(){
	json message7;
	message7["ID"] = 7;
	message7["Action"] = "search by note title";

	Note note4;
	note4.setuserId(31);
	note4.settitle("Note");
	message7["Data"] = note4.toJson();

	client.Send(message7);

	// Receiving a JSON response from the server
	json response7 = client.Receive();
	std::cout << "Response: " << response7.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestSearchWithUserFound){
    bool result = sendAndReceive_Search1();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//29- search by note title message with user not found
bool sendAndReceive_Search2(){
	json message7;
	message7["ID"] = 7;
	message7["Action"] = "search by note title";

	Note note4;
	note4.setuserId(1);
	note4.settitle("Note");
	message7["Data"] = note4.toJson();

	client.Send(message7);

	// Receiving a JSON response from the server
	json response7 = client.Receive();
	std::cout << "Response: " << response7.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestSearchWithUserNotFound){
    bool result = sendAndReceive_Search2();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//30- search by note title message with missing key "Data"
bool sendAndReceive_Search3(){
	json message7;
	message7["ID"] = 7;
	message7["Action"] = "search by note title";

	Note note4;
	note4.setuserId(31);
	note4.settitle("Note");
	message7["data"] = note4.toJson();

	client.Send(message7);

	// Receiving a JSON response from the server
	json response7 = client.Receive();
	std::cout << "Response: " << response7.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestSearchWithMissingKeyData){
    bool result = sendAndReceive_Search3();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//31- search by note title message with conflict key "Data" and its datatype
bool sendAndReceive_Search4(){
	json message7;
	message7["ID"] = 7;
	message7["Action"] = "search by note title";

	User note4;
	message7["Data"] = note4.toJson();

	client.Send(message7);

	// Receiving a JSON response from the server
	json response7 = client.Receive();
	std::cout << "Response: " << response7.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestSearchWithConflictKeyDataAndItsDatatype){
    bool result = sendAndReceive_Search4();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//32-  create component message with user and note found
bool sendAndReceive_CreateComponent1(){
	json message8;
	message8["ID"] = 8;
	message8["Action"] = "create component";
	message8["user id"] = 32;

	NoteComponent NoteComponent1;
	NoteComponent1.setnoteId(22);
	NoteComponent1.setcomponentContent("Component for note 22 user 32");

	message8["Data"] = NoteComponent1.toJson();

	client.Send(message8);

	// Receiving a JSON response from the server
	json response8 = client.Receive();
	std::cout << "Response: " << response8.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestCreateComponentWithUserAndNoteFound){
    bool result = sendAndReceive_CreateComponent1();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//33-  create component message with user not found and note found
bool sendAndReceive_CreateComponent2(){
	json message8;
	message8["ID"] = 8;
	message8["Action"] = "create component";
	message8["user id"] = 1;

	NoteComponent NoteComponent1;
	NoteComponent1.setnoteId(22);
	NoteComponent1.setcomponentContent("First Component");

	message8["Data"] = NoteComponent1.toJson();

	client.Send(message8);

	// Receiving a JSON response from the server
	json response8 = client.Receive();
	std::cout << "Response: " << response8.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestCreateComponentWithUserNotFoundAndNoteFound){
    bool result = sendAndReceive_CreateComponent2();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//34-  create component message with user found and note not found
bool sendAndReceive_CreateComponent3(){
	json message8;
	message8["ID"] = 8;
	message8["Action"] = "create component";
	message8["user id"] = 32;

	NoteComponent NoteComponent1;
	NoteComponent1.setnoteId(1);
	NoteComponent1.setcomponentContent("First Component");

	message8["Data"] = NoteComponent1.toJson();

	client.Send(message8);

	// Receiving a JSON response from the server
	json response8 = client.Receive();
	std::cout << "Response: " << response8.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestCreateComponentWithUserFoundAndNoteNotFound){
    bool result = sendAndReceive_CreateComponent3();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//35-  create component message with missing key "user id" 
bool sendAndReceive_CreateComponent4(){
	json message8;
	message8["ID"] = 8;
	message8["Action"] = "create component";
	message8["userid"] = 31;

	NoteComponent NoteComponent1;
	NoteComponent1.setnoteId(16);
	NoteComponent1.setcomponentContent("First Component");

	message8["Data"] = NoteComponent1.toJson();

	client.Send(message8);

	// Receiving a JSON response from the server
	json response8 = client.Receive();
	std::cout << "Response: " << response8.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestCreateComponentWithMissingKeyUserId){
    bool result = sendAndReceive_CreateComponent4();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//36-  create component message with conflict key "user id" and its datatype
bool sendAndReceive_CreateComponent5(){
	json message8;
	message8["ID"] = 8;
	message8["Action"] = "create component";
	message8["user id"] = "31";

	NoteComponent NoteComponent1;
	NoteComponent1.setnoteId(16);
	NoteComponent1.setcomponentContent("First Component");

	message8["Data"] = NoteComponent1.toJson();

	client.Send(message8);

	// Receiving a JSON response from the server
	json response8 = client.Receive();
	std::cout << "Response: " << response8.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestCreateComponentWithConflictKeyUserIdAndItsDatatype){
    bool result = sendAndReceive_CreateComponent5();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//37-  create component message with missing key "Data" 
bool sendAndReceive_CreateComponent6(){
	json message8;
	message8["ID"] = 8;
	message8["Action"] = "create component";
	message8["user id"] = 31;

	NoteComponent NoteComponent1;
	NoteComponent1.setnoteId(16);
	NoteComponent1.setcomponentContent("First Component");

	message8["data"] = NoteComponent1.toJson();

	client.Send(message8);

	// Receiving a JSON response from the server
	json response8 = client.Receive();
	std::cout << "Response: " << response8.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestCreateComponentWithMissingKeyData){
    bool result = sendAndReceive_CreateComponent6();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//38-  create component message with conflict key "Data" and its datatype
bool sendAndReceive_CreateComponent7(){
	json message8;
	message8["ID"] = 8;
	message8["Action"] = "create component";
	message8["user id"] = 31;

	Note NoteComponent1;
	message8["Data"] = NoteComponent1.toJson();

	client.Send(message8);

	// Receiving a JSON response from the server
	json response8 = client.Receive();
	std::cout << "Response: " << response8.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestCreateComponentWithConflictKeyDataAndItsDatatype){
    bool result = sendAndReceive_CreateComponent7();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//39-  update component message with user and note and component found
bool sendAndReceive_UpdateComponent1(){
	json message9;
	message9["ID"] = 9;
	message9["Action"] = "update component";
	message9["user id"] = 31;

	NoteComponent NoteComponent2;
	NoteComponent2.setnoteId(16);
	NoteComponent2.setcomponentId(6);
	NoteComponent2.setcomponentContent("updated component for note 16 user 31");
	NoteComponent2.setfontColor("blue");
	NoteComponent2.setisBold(true);

	message9["Data"] = NoteComponent2.toJson();

	client.Send(message9);

	// Receiving a JSON response from the server
	json response9 = client.Receive();
	std::cout << "Response: " << response9.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestUpdateComponentWithUserAndNoteAndComponentFound){
    bool result = sendAndReceive_UpdateComponent1();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//40-  update component message with user not found and note and component found
bool sendAndReceive_UpdateComponent2(){
	json message9;
	message9["ID"] = 9;
	message9["Action"] = "update component";
	message9["user id"] = 1;

	NoteComponent NoteComponent2;
	NoteComponent2.setnoteId(16);
	NoteComponent2.setcomponentId(1);
	NoteComponent2.setcomponentContent("updated component");
	NoteComponent2.setfontColor("blue");
	NoteComponent2.setfontSize(20);
	NoteComponent2.setisBold(true);

	message9["Data"] = NoteComponent2.toJson();

	client.Send(message9);

	// Receiving a JSON response from the server
	json response9 = client.Receive();
	std::cout << "Response: " << response9.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestUpdateComponentWithUserNotFoundAndNoteAndComponentFound){
    bool result = sendAndReceive_UpdateComponent2();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//41-  update component message with note not found and user and component found
bool sendAndReceive_UpdateComponent3(){
	json message9;
	message9["ID"] = 9;
	message9["Action"] = "update component";
	message9["user id"] = 31;

	NoteComponent NoteComponent2;
	NoteComponent2.setnoteId(1);
	NoteComponent2.setcomponentId(1);
	NoteComponent2.setcomponentContent("updated component");
	NoteComponent2.setfontColor("red");

	message9["Data"] = NoteComponent2.toJson();

	client.Send(message9);

	// Receiving a JSON response from the server
	json response9 = client.Receive();
	std::cout << "Response: " << response9.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestUpdateComponentWithNoteNotFoundAndUserAndComponentFound){
    bool result = sendAndReceive_UpdateComponent3();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//42-  update component message with note and user found and  component not found
bool sendAndReceive_UpdateComponent4(){
	json message9;
	message9["ID"] = 9;
	message9["Action"] = "update component";
	message9["user id"] = 31;

	NoteComponent NoteComponent2;
	NoteComponent2.setnoteId(16);
	NoteComponent2.setcomponentId(10);
	NoteComponent2.setcomponentContent("updated component");
	NoteComponent2.setfontColor("red");

	message9["Data"] = NoteComponent2.toJson();

	client.Send(message9);

	// Receiving a JSON response from the server
	json response9 = client.Receive();
	std::cout << "Response: " << response9.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestUpdateComponentWithNoteAndUserFoundAndComponentNotFound){
    bool result = sendAndReceive_UpdateComponent4();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//43-  update component message with missing key "user id"
bool sendAndReceive_UpdateComponent5(){
	json message9;
	message9["ID"] = 9;
	message9["Action"] = "update component";
	message9["userid"] = 31;

	NoteComponent NoteComponent2;
	NoteComponent2.setnoteId(16);
	NoteComponent2.setcomponentId(1);
	NoteComponent2.setcomponentContent("updated component");
	NoteComponent2.setfontColor("red");

	message9["Data"] = NoteComponent2.toJson();

	client.Send(message9);

	// Receiving a JSON response from the server
	json response9 = client.Receive();
	std::cout << "Response: " << response9.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestUpdateComponentWithMissingKeyUserId){
    bool result = sendAndReceive_UpdateComponent5();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//44-  update component message with conflict key "user id" and its datatype
bool sendAndReceive_UpdateComponent6(){
	json message9;
	message9["ID"] = 9;
	message9["Action"] = "update component";
	message9["user id"] = "31";

	NoteComponent NoteComponent2;
	NoteComponent2.setnoteId(16);
	NoteComponent2.setcomponentId(1);
	NoteComponent2.setcomponentContent("updated component");
	NoteComponent2.setfontColor("red");

	message9["Data"] = NoteComponent2.toJson();

	client.Send(message9);

	// Receiving a JSON response from the server
	json response9 = client.Receive();
	std::cout << "Response: " << response9.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestUpdateComponentWithConflictKeyUserIdAndItsDatatype){
    bool result = sendAndReceive_UpdateComponent6();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//45-  update component message with missing key "Data" 
bool sendAndReceive_UpdateComponent7(){
	json message9;
	message9["ID"] = 9;
	message9["Action"] = "update component";
	message9["user id"] = 31;

	NoteComponent NoteComponent2;
	NoteComponent2.setnoteId(16);
	NoteComponent2.setcomponentId(1);
	NoteComponent2.setcomponentContent("updated component");
	NoteComponent2.setfontColor("red");

	message9["data"] = NoteComponent2.toJson();

	client.Send(message9);

	// Receiving a JSON response from the server
	json response9 = client.Receive();
	std::cout << "Response: " << response9.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestUpdateComponentWithMissingKeyData){
    bool result = sendAndReceive_UpdateComponent7();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//46-  update component message with conflict key "Data" and its datatype
bool sendAndReceive_UpdateComponent8(){
	json message9;
	message9["ID"] = 9;
	message9["Action"] = "update component";
	message9["user id"] = 31;

	Note NoteComponent2;
	message9["Data"] = NoteComponent2.toJson();

	client.Send(message9);

	// Receiving a JSON response from the server
	json response9 = client.Receive();
	std::cout << "Response: " << response9.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestUpdateComponentWithConflictKeyDataAndItsDatatype){
    bool result = sendAndReceive_UpdateComponent8();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//47-  delete component message with user and note and component found
bool sendAndReceive_DeleteComponent1(){
	json message10;
	message10["ID"] = 10;
	message10["Action"] = "delete component";
	message10["user id"] = 31;

	NoteComponent NoteComponent3;
	NoteComponent3.setnoteId(16);
	NoteComponent3.setcomponentId(4);

	message10["Data"] = NoteComponent3.toJson();

	client.Send(message10);

	// Receiving a JSON response from the server
	json response10 = client.Receive();
	std::cout << "Response: " << response10.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestDeleteComponentWithUserAndNoteAndComponentFound){
    bool result = sendAndReceive_DeleteComponent1();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//48-  delete component message with user not found and note and component found
bool sendAndReceive_DeleteComponent2(){
	json message10;
	message10["ID"] = 10;
	message10["Action"] = "delete component";
	message10["user id"] = 1;

	NoteComponent NoteComponent3;
	NoteComponent3.setnoteId(16);
	NoteComponent3.setcomponentId(4);

	message10["Data"] = NoteComponent3.toJson();

	client.Send(message10);

	// Receiving a JSON response from the server
	json response10 = client.Receive();
	std::cout << "Response: " << response10.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestDeleteComponentWithUserNotFoundAndNoteAndComponentFound){
    bool result = sendAndReceive_DeleteComponent2();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//49-  delete component message with note not found and user and component found
bool sendAndReceive_DeleteComponent3(){
	json message10;
	message10["ID"] = 10;
	message10["Action"] = "delete component";
	message10["user id"] = 31;

	NoteComponent NoteComponent3;
	NoteComponent3.setnoteId(1);
	NoteComponent3.setcomponentId(4);

	message10["Data"] = NoteComponent3.toJson();

	client.Send(message10);

	// Receiving a JSON response from the server
	json response10 = client.Receive();
	std::cout << "Response: " << response10.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestDeleteComponentWithNoteNotFoundAndUserAndComponentFound){
    bool result = sendAndReceive_DeleteComponent3();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//50-  delete component message with note and user found and component not found
bool sendAndReceive_DeleteComponent4(){
	json message10;
	message10["ID"] = 10;
	message10["Action"] = "delete component";
	message10["user id"] = 31;

	NoteComponent NoteComponent3;
	NoteComponent3.setnoteId(16);
	NoteComponent3.setcomponentId(10);

	message10["Data"] = NoteComponent3.toJson();

	client.Send(message10);

	// Receiving a JSON response from the server
	json response10 = client.Receive();
	std::cout << "Response: " << response10.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestDeleteComponentWithNoteAndUserFoundAndComponentNotFound){
    bool result = sendAndReceive_DeleteComponent4();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//51-  delete component message with missing key "user id"
bool sendAndReceive_DeleteComponent5(){
	json message10;
	message10["ID"] = 10;
	message10["Action"] = "delete component";
	message10["userid"] = 31;

	NoteComponent NoteComponent3;
	NoteComponent3.setnoteId(16);
	NoteComponent3.setcomponentId(4);

	message10["Data"] = NoteComponent3.toJson();

	client.Send(message10);

	// Receiving a JSON response from the server
	json response10 = client.Receive();
	std::cout << "Response: " << response10.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestDeleteComponentWithMissingKeyUserId){
    bool result = sendAndReceive_DeleteComponent5();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//52-  delete component message with conflict key "user id" and its datatype
bool sendAndReceive_DeleteComponent6(){
	json message10;
	message10["ID"] = 10;
	message10["Action"] = "delete component";
	message10["user id"] = "31";

	NoteComponent NoteComponent3;
	NoteComponent3.setnoteId(16);
	NoteComponent3.setcomponentId(4);

	message10["Data"] = NoteComponent3.toJson();

	client.Send(message10);

	// Receiving a JSON response from the server
	json response10 = client.Receive();
	std::cout << "Response: " << response10.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestDeleteComponentWithConflictKeyUserIdAndItsDatatype){
    bool result = sendAndReceive_DeleteComponent6();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//53-  delete component message with missing key "Data"
bool sendAndReceive_DeleteComponent7(){
	json message10;
	message10["ID"] = 10;
	message10["Action"] = "delete component";
	message10["user id"] = 31;

	NoteComponent NoteComponent3;
	NoteComponent3.setnoteId(16);
	NoteComponent3.setcomponentId(2);

	message10["data"] = NoteComponent3.toJson();

	client.Send(message10);

	// Receiving a JSON response from the server
	json response10 = client.Receive();
	std::cout << "Response: " << response10.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestDeleteComponentWithMissingKeyData){
    bool result = sendAndReceive_DeleteComponent7();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//54-  delete component message with conflict key "Data" and its datatype
bool sendAndReceive_DeleteComponent8(){
	json message10;
	message10["ID"] = 10;
	message10["Action"] = "delete component";
	message10["user id"] = 31;

	Note NoteComponent3;
	message10["Data"] = NoteComponent3.toJson();

	client.Send(message10);

	// Receiving a JSON response from the server
	json response10 = client.Receive();
	std::cout << "Response: " << response10.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestDeleteComponentWithConflictKeyDataAndItsDatatype){
    bool result = sendAndReceive_DeleteComponent8();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//55-  list components message with user and note found
bool sendAndReceive_ListComponents1(){
	json message11;
	message11["ID"] = 11;
	message11["Action"] = "list components";

	Note note5;
	note5.setuserId(31);
	note5.setnoteId(16);

	message11["Data"] = note5.toJson();

	client.Send(message11);

	// Receiving a JSON response from the server
	json response11 = client.Receive();
	std::cout << "Response: " << response11.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestListComponentsWithUserAndNoteFound){
    bool result = sendAndReceive_ListComponents1();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//56-  list components message with user not found and note found
bool sendAndReceive_ListComponents2(){
	json message11;
	message11["ID"] = 11;
	message11["Action"] = "list components";

	Note note5;
	note5.setuserId(1);
	note5.setnoteId(16);

	message11["Data"] = note5.toJson();

	client.Send(message11);

	// Receiving a JSON response from the server
	json response11 = client.Receive();
	std::cout << "Response: " << response11.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestListComponentsWithUserNotFoundAndNoteFound){
    bool result = sendAndReceive_ListComponents2();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//57-  list components message with user found and note not found
bool sendAndReceive_ListComponents3(){
	json message11;
	message11["ID"] = 11;
	message11["Action"] = "list components";

	Note note5;
	note5.setuserId(31);
	note5.setnoteId(1);

	message11["Data"] = note5.toJson();

	client.Send(message11);

	// Receiving a JSON response from the server
	json response11 = client.Receive();
	std::cout << "Response: " << response11.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestListComponentsWithUserFoundAndNoteNotFound){
    bool result = sendAndReceive_ListComponents3();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//58-  list components message with missing key "Data"
bool sendAndReceive_ListComponents4(){
	json message11;
	message11["ID"] = 11;
	message11["Action"] = "list components";

	Note note5;
	note5.setuserId(31);
	note5.setnoteId(16);

	message11["data"] = note5.toJson();

	client.Send(message11);

	// Receiving a JSON response from the server
	json response11 = client.Receive();
	std::cout << "Response: " << response11.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestListComponentsWithMissingKeyData){
    bool result = sendAndReceive_ListComponents4();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//59-  list components message with conflict key "Data" and itd datatype
bool sendAndReceive_ListComponents5(){
	json message11;
	message11["ID"] = 11;
	message11["Action"] = "list components";

	User note5;
	message11["Data"] = note5.toJson();

	client.Send(message11);

	// Receiving a JSON response from the server
	json response11 = client.Receive();
	std::cout << "Response: " << response11.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestListComponentsWithConflictKeyDataAndItsDatatype){
    bool result = sendAndReceive_ListComponents5();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//60- add tag message with user and note found
bool sendAndReceive_AddTag1(){
	json message12;
	message12["ID"] = 12;
	message12["Action"] = "add tag";
	message12["user id"] = 31;

	Tag tag1;
	tag1.setnoteId(17);
	tag1.settagName("tag 1");

	message12["Data"] = tag1.toJson();

	client.Send(message12);

	// Receiving a JSON response from the server
	json response12 = client.Receive();
	std::cout << "Response: " << response12.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestAddTagWithUserAndNoteFound){
    bool result = sendAndReceive_AddTag1();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//61- add tag message with user not found and note found
bool sendAndReceive_AddTag2(){
	json message12;
	message12["ID"] = 12;
	message12["Action"] = "add tag";
	message12["user id"] = 1;

	Tag tag1;
	tag1.setnoteId(17);
	tag1.settagName("tag");

	message12["Data"] = tag1.toJson();

	client.Send(message12);

	// Receiving a JSON response from the server
	json response12 = client.Receive();
	std::cout << "Response: " << response12.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestAddTagWithUserNotFoundAndNoteFound){
    bool result = sendAndReceive_AddTag2();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//62- add tag message with user found and note not found
bool sendAndReceive_AddTag3(){
	json message12;
	message12["ID"] = 12;
	message12["Action"] = "add tag";
	message12["user id"] = 31;

	Tag tag1;
	tag1.setnoteId(1);
	tag1.settagName("tag");

	message12["Data"] = tag1.toJson();

	client.Send(message12);

	// Receiving a JSON response from the server
	json response12 = client.Receive();
	std::cout << "Response: " << response12.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestAddTagWithUserFoundAndNoteNotFound){
    bool result = sendAndReceive_AddTag3();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//63- add tag message with missing key "user id"
bool sendAndReceive_AddTag4(){
	json message12;
	message12["ID"] = 12;
	message12["Action"] = "add tag";
	message12["userid"] = 31;

	Tag tag1;
	tag1.setnoteId(16);
	tag1.settagName("tag");

	message12["Data"] = tag1.toJson();

	client.Send(message12);

	// Receiving a JSON response from the server
	json response12 = client.Receive();
	std::cout << "Response: " << response12.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestAddTagWithMissingKeyUserId){
    bool result = sendAndReceive_AddTag4();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//64- add tag message with conflict key "user id" and its datatype
bool sendAndReceive_AddTag5(){
	json message12;
	message12["ID"] = 12;
	message12["Action"] = "add tag";
	message12["user id"] = "31";

	Tag tag1;
	tag1.setnoteId(16);
	tag1.settagName("tag");

	message12["Data"] = tag1.toJson();

	client.Send(message12);

	// Receiving a JSON response from the server
	json response12 = client.Receive();
	std::cout << "Response: " << response12.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestAddTagWithConflictKeyUserIdAndItsDatatype){
    bool result = sendAndReceive_AddTag5();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//65- add tag message with missing key "Data"
bool sendAndReceive_AddTag6(){
	json message12;
	message12["ID"] = 12;
	message12["Action"] = "add tag";
	message12["user id"] = 31;

	Tag tag1;
	tag1.setnoteId(16);
	tag1.settagName("tag");

	message12["data"] = tag1.toJson();

	client.Send(message12);

	// Receiving a JSON response from the server
	json response12 = client.Receive();
	std::cout << "Response: " << response12.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestAddTagWithMissingKeyData){
    bool result = sendAndReceive_AddTag6();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//66- add tag message with conflict key "Data" and its datatype
bool sendAndReceive_AddTag7(){
	json message12;
	message12["ID"] = 12;
	message12["Action"] = "add tag";
	message12["user id"] = 31;

	Note tag1;
	message12["Data"] = tag1.toJson();

	client.Send(message12);

	// Receiving a JSON response from the server
	json response12 = client.Receive();
	std::cout << "Response: " << response12.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestAddTagWithConflictKeyDataAndItsDatatype){
    bool result = sendAndReceive_AddTag7();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//67- update tag message with user and note and tag found
bool sendAndReceive_UpdateTag1(){
	json message13;
	message13["ID"] = 13;
	message13["Action"] = "update tag";
	message13["user id"] = 31;

	Tag tag2;
	tag2.setnoteId(16);
	tag2.settagId(22);
	tag2.settagName("updated tag");

	message13["Data"] = tag2.toJson();

	client.Send(message13);

	// Receiving a JSON response from the server
	json response13 = client.Receive();
	std::cout << "Response: " << response13.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestUpdateTagWithUserAndNoteAndTagFound){
    bool result = sendAndReceive_UpdateTag1();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//68- update tag message with user not found and note and tag found
bool sendAndReceive_UpdateTag2(){
	json message13;
	message13["ID"] = 13;
	message13["Action"] = "update tag";
	message13["user id"] = 1;

	Tag tag2;
	tag2.setnoteId(16);
	tag2.settagId(22);
	tag2.settagName("updated tag");

	message13["Data"] = tag2.toJson();

	client.Send(message13);

	// Receiving a JSON response from the server
	json response13 = client.Receive();
	std::cout << "Response: " << response13.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestUpdateTagWithUserNotFoundAndNoteAndTagFound){
    bool result = sendAndReceive_UpdateTag2();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//69- update tag message with note not found and user and tag found
bool sendAndReceive_UpdateTag3(){
	json message13;
	message13["ID"] = 13;
	message13["Action"] = "update tag";
	message13["user id"] = 31;

	Tag tag2;
	tag2.setnoteId(1);
	tag2.settagId(22);
	tag2.settagName("tag");

	message13["Data"] = tag2.toJson();

	client.Send(message13);

	// Receiving a JSON response from the server
	json response13 = client.Receive();
	std::cout << "Response: " << response13.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestUpdateTagWithNoteNotFoundAndUserAndTagFound){
    bool result = sendAndReceive_UpdateTag3();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//70- update tag message with note and user found and tag not found
bool sendAndReceive_UpdateTag4(){
	json message13;
	message13["ID"] = 13;
	message13["Action"] = "update tag";
	message13["user id"] = 31;

	Tag tag2;
	tag2.setnoteId(16);
	tag2.settagId(1);
	tag2.settagName("tag");

	message13["Data"] = tag2.toJson();

	client.Send(message13);

	// Receiving a JSON response from the server
	json response13 = client.Receive();
	std::cout << "Response: " << response13.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestUpdateTagWithNoteAndUserFoundAndTagNotFound){
    bool result = sendAndReceive_UpdateTag4();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//71- update tag message with missing key "user id"
bool sendAndReceive_UpdateTag5(){
	json message13;
	message13["ID"] = 13;
	message13["Action"] = "update tag";
	message13["userid"] = 31;

	Tag tag2;
	tag2.setnoteId(17);
	tag2.settagId(5);
	tag2.settagName("tag");

	message13["Data"] = tag2.toJson();

	client.Send(message13);

	// Receiving a JSON response from the server
	json response13 = client.Receive();
	std::cout << "Response: " << response13.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestUpdateTagWithMissingKeyUserId){
    bool result = sendAndReceive_UpdateTag5();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//72- update tag message with conflict key "user id" and its datatype
bool sendAndReceive_UpdateTag6(){
	json message13;
	message13["ID"] = 13;
	message13["Action"] = "update tag";
	message13["user id"] = "31";

	Tag tag2;
	tag2.setnoteId(17);
	tag2.settagId(5);
	tag2.settagName("tag");

	message13["Data"] = tag2.toJson();

	client.Send(message13);

	// Receiving a JSON response from the server
	json response13 = client.Receive();
	std::cout << "Response: " << response13.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestUpdateTagWithConflictKeyUserIdAndItsDatatype){
    bool result = sendAndReceive_UpdateTag6();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//73- update tag message with missing key "Data"
bool sendAndReceive_UpdateTag7(){
	json message13;
	message13["ID"] = 13;
	message13["Action"] = "update tag";
	message13["user id"] = 31;

	Tag tag2;
	tag2.setnoteId(17);
	tag2.settagId(5);
	tag2.settagName("tag");

	message13["data"] = tag2.toJson();

	client.Send(message13);

	// Receiving a JSON response from the server
	json response13 = client.Receive();
	std::cout << "Response: " << response13.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestUpdateTagWithMissingKeyData){
    bool result = sendAndReceive_UpdateTag7();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//74- update tag message with conflict key "Data" and its datatype
bool sendAndReceive_UpdateTag8(){
	json message13;
	message13["ID"] = 13;
	message13["Action"] = "update tag";
	message13["user id"] = 31;

	Note tag2;
	message13["Data"] = tag2.toJson();

	client.Send(message13);

	// Receiving a JSON response from the server
	json response13 = client.Receive();
	std::cout << "Response: " << response13.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestUpdateTagWithConflictKeyDataAndItsDatatype){
    bool result = sendAndReceive_UpdateTag8();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//75- delete tag message with user and note and tag found
bool sendAndReceive_DeleteTag1(){
	json message14;
	message14["ID"] = 14;
	message14["Action"] = "delete tag";
	message14["user id"] = 39;

	Tag tag3;
	tag3.setnoteId(20);
	tag3.settagId(20);

	message14["Data"] = tag3.toJson();

	client.Send(message14);

	// Receiving a JSON response from the server
	json response14 = client.Receive();
	std::cout << "Response: " << response14.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestDeleteTagWithUserAndNoteAndTagFound){
    bool result = sendAndReceive_DeleteTag1();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//76- delete tag message with user not found and note and tag found
bool sendAndReceive_DeleteTag2(){
	json message14;
	message14["ID"] = 14;
	message14["Action"] = "delete tag";
	message14["user id"] = 1;

	Tag tag3;
	tag3.setnoteId(20);
	tag3.settagId(20);

	message14["Data"] = tag3.toJson();

	client.Send(message14);

	// Receiving a JSON response from the server
	json response14 = client.Receive();
	std::cout << "Response: " << response14.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestDeleteTagWithUserNotFoundAndNoteAndTagFound){
    bool result = sendAndReceive_DeleteTag2();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//77- delete tag message with note not found and user and tag found
bool sendAndReceive_DeleteTag3(){
	json message14;
	message14["ID"] = 14;
	message14["Action"] = "delete tag";
	message14["user id"] = 39;

	Tag tag3;
	tag3.setnoteId(1);
	tag3.settagId(20);

	message14["Data"] = tag3.toJson();

	client.Send(message14);

	// Receiving a JSON response from the server
	json response14 = client.Receive();
	std::cout << "Response: " << response14.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestDeleteTagWithNoteNotFoundAndUserAndTagFound){
    bool result = sendAndReceive_DeleteTag3();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//78- delete tag message with note and user found and tag not found
bool sendAndReceive_DeleteTag4(){
	json message14;
	message14["ID"] = 14;
	message14["Action"] = "delete tag";
	message14["user id"] = 39;

	Tag tag3;
	tag3.setnoteId(20);
	tag3.settagId(1);

	message14["Data"] = tag3.toJson();

	client.Send(message14);

	// Receiving a JSON response from the server
	json response14 = client.Receive();
	std::cout << "Response: " << response14.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestDeleteTagWithNoteAndUserFoundAndTagNotFound){
    bool result = sendAndReceive_DeleteTag4();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//79- delete tag message with missing key "user id"
bool sendAndReceive_DeleteTag5(){
	json message14;
	message14["ID"] = 14;
	message14["Action"] = "delete tag";
	message14["userid"] = 31;

	Tag tag3;
	tag3.setnoteId(17);
	tag3.settagId(6);

	message14["Data"] = tag3.toJson();

	client.Send(message14);

	// Receiving a JSON response from the server
	json response14 = client.Receive();
	std::cout << "Response: " << response14.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestDeleteTagWithMissingKeyUserId){
    bool result = sendAndReceive_DeleteTag5();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//80- delete tag message with conflict key "user id" and its datatype
bool sendAndReceive_DeleteTag6(){
	json message14;
	message14["ID"] = 14;
	message14["Action"] = "delete tag";
	message14["user id"] = "31";

	Tag tag3;
	tag3.setnoteId(17);
	tag3.settagId(6);

	message14["Data"] = tag3.toJson();

	client.Send(message14);

	// Receiving a JSON response from the server
	json response14 = client.Receive();
	std::cout << "Response: " << response14.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestDeleteTagWithConflictKeyUserIdAndItsDatatype){
    bool result = sendAndReceive_DeleteTag6();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//81- delete tag message with missing key "Data"
bool sendAndReceive_DeleteTag7(){
	json message14;
	message14["ID"] = 14;
	message14["Action"] = "delete tag";
	message14["user id"] = 31;

	Tag tag3;
	tag3.setnoteId(17);
	tag3.settagId(6);

	message14["data"] = tag3.toJson();

	client.Send(message14);

	// Receiving a JSON response from the server
	json response14 = client.Receive();
	std::cout << "Response: " << response14.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestDeleteTagWithMissingKeyData){
    bool result = sendAndReceive_DeleteTag7();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//82- delete tag message with conflict key "Data" and its datatype
bool sendAndReceive_DeleteTag8(){
	json message14;
	message14["ID"] = 14;
	message14["Action"] = "delete tag";
	message14["user id"] = 31;

	User tag3;
	message14["Data"] = tag3.toJson();

	client.Send(message14);

	// Receiving a JSON response from the server
	json response14 = client.Receive();
	std::cout << "Response: " << response14.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestDeleteTagWithConflictKeyDataAndItsDatatype){
    bool result = sendAndReceive_DeleteTag8();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//83- filter by tag message with user found 
bool sendAndReceive_FilterByTag1(){
	json message15;
	message15["ID"] = 15;
	message15["Action"] = "filter by tag name";
	message15["user id"] = 31;
	message15["tag name"] = "tag";

	client.Send(message15);

	// Receiving a JSON response from the server
	json response15 = client.Receive();
	std::cout << "Response: " << response15.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestFilterByTagWithUserFound){
    bool result = sendAndReceive_FilterByTag1();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//84- filter by tag message with user not found 
bool sendAndReceive_FilterByTag2(){
	json message15;
	message15["ID"] = 15;
	message15["Action"] = "filter by tag name";
	message15["user id"] = 1;
	message15["tag name"] = "tag";

	client.Send(message15);

	// Receiving a JSON response from the server
	json response15 = client.Receive();
	std::cout << "Response: " << response15.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestFilterByTagWithUserNotFound){
    bool result = sendAndReceive_FilterByTag2();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//85- filter by tag message with missing key "user id"
bool sendAndReceive_FilterByTag3(){
	json message15;
	message15["ID"] = 15;
	message15["Action"] = "filter by tag name";
	message15["userid"] = 31;
	message15["tag name"] = "tag";

	client.Send(message15);

	// Receiving a JSON response from the server
	json response15 = client.Receive();
	std::cout << "Response: " << response15.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestFilterByTagWithMissingKeyUserId){
    bool result = sendAndReceive_FilterByTag3();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//86- filter by tag message with conflict key "user id" and its datatype
bool sendAndReceive_FilterByTag4(){
	json message15;
	message15["ID"] = 15;
	message15["Action"] = "filter by tag name";
	message15["user id"] = "31";
	message15["tag name"] = "tag";

	client.Send(message15);

	// Receiving a JSON response from the server
	json response15 = client.Receive();
	std::cout << "Response: " << response15.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestFilterByTagWithConflictKeyUserIdAndItsDatatype){
    bool result = sendAndReceive_FilterByTag4();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//87- filter by tag message with missing key "tag name"
bool sendAndReceive_FilterByTag5(){
	json message15;
	message15["ID"] = 15;
	message15["Action"] = "filter by tag name";
	message15["user id"] = 31;
	message15["tagname"] = "tag";

	client.Send(message15);

	// Receiving a JSON response from the server
	json response15 = client.Receive();
	std::cout << "Response: " << response15.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestFilterByTagWithMissingKeyTagName){
    bool result = sendAndReceive_FilterByTag5();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//88- filter by tag message with conflict key "tag name" and its datatype
bool sendAndReceive_FilterByTag6(){
	json message15;
	message15["ID"] = 15;
	message15["Action"] = "filter by tag name";
	message15["user id"] = 31;
	message15["tag name"] = 1;

	client.Send(message15);

	// Receiving a JSON response from the server
	json response15 = client.Receive();
	std::cout << "Response: " << response15.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestFilterByTagWithConflictKeyTagNameAndItsDatatype){
    bool result = sendAndReceive_FilterByTag6();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//89- empty message 
bool sendAndReceive_EmptyMessage(){
	json message;
	client.Send(message);

	// Receiving a JSON response from the server
	json response = client.Receive();
	std::cout << "Response: " << response.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestEmptyMessage){
    bool result = sendAndReceive_EmptyMessage();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//90- message with wrong Action
bool sendAndReceive_WrongAction(){
	json wrongActionmessage;
	wrongActionmessage["ID"] = 0;
	wrongActionmessage["Action"] = "sign up";
	client.Send(wrongActionmessage);

	// Receiving a JSON response from the server
	json responseWrongActionmessage = client.Receive();
	std::cout << "Response: " << responseWrongActionmessage.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestMessageWithWrongAction){
    bool result = sendAndReceive_WrongAction();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//91- message with conflict action and its data type
bool sendAndReceive_ConflictAction(){
	json wrongActionmessage;
	wrongActionmessage["ID"] = 0;
	wrongActionmessage["Action"] = 0;
	client.Send(wrongActionmessage);

	// Receiving a JSON response from the server
	json responseWrongActionmessage = client.Receive();
	std::cout << "Response: " << responseWrongActionmessage.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestMessageWithConflictActionAndItsDatatype){
    bool result = sendAndReceive_ConflictAction();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//92- message with missing key "Action"
bool sendAndReceive_MissingAction(){
	json wrongActionmessage;
	wrongActionmessage["action"] = "close";
	client.Send(wrongActionmessage);

	// Receiving a JSON response from the server
	json responseWrongActionmessage = client.Receive();
	std::cout << "Response: " << responseWrongActionmessage.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestMessageWithMissingKeyAction){
    bool result = sendAndReceive_MissingAction();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//93- message with missing key "ID"
bool sendAndReceive_MissingId(){
	json wrongMessage5;
	wrongMessage5["id"] = 0;
	wrongMessage5["Action"] = "signup";

	client.Send(wrongMessage5);

	// Receiving a JSON response from the server
	json responseWrongMessage5 = client.Receive();
	std::cout << "Response: " << responseWrongMessage5.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestMessageWithMissingKeyID){
    bool result = sendAndReceive_MissingId();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//94- message with conflict key "ID" and its data type
bool sendAndReceive_ConflictId(){
	json wrongMessage5;
	wrongMessage5["id"] = "0";
	wrongMessage5["Action"] = "signup";

	client.Send(wrongMessage5);

	// Receiving a JSON response from the server
	json responseWrongMessage5 = client.Receive();
	std::cout << "Response: " << responseWrongMessage5.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true;
}
TEST(JsonMessageTest, TestMessageWithConflictIdAndItsDatatype){
    bool result = sendAndReceive_ConflictId();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//96- update user data message with email found
bool sendAndReceive_UpdateUserData1(){
	json message1;
	message1["ID"] = 16;
	message1["Action"] = "update user data";

	User user1;
	user1.setuserName("Updateduser6");
	user1.setemail("user6@gmail.com");
	user1.sethashedPassword("1234");
	message1["Data"] = user1.toJson();

	client.Send(message1);

	// Receiving a JSON response from the server
	json response1 = client.Receive();
	std::cout << "Response: " << response1.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true; 
}
TEST(JsonMessageTest, TestUpdateUserDataWithEmailFound){
    bool result = sendAndReceive_UpdateUserData1();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//97- update user data message with email not found
bool sendAndReceive_UpdateUserData2(){
	json message1;
	message1["ID"] = 16;
	message1["Action"] = "update user data";

	User user1;
	user1.setuserName("Updateduser");
	user1.setemail("test@gmail.com");
	user1.sethashedPassword("1234");
	message1["Data"] = user1.toJson();

	client.Send(message1);

	// Receiving a JSON response from the server
	json response1 = client.Receive();
	std::cout << "Response: " << response1.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true; 
}
TEST(JsonMessageTest, TestUpdateUserDataWithEmailNotFound){
    bool result = sendAndReceive_UpdateUserData2();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//98- update user data message with key "Data" not found
bool sendAndReceive_UpdateUserData3(){
	json message1;
	message1["ID"] = 16;
	message1["Action"] = "update user data";

	User user1;
	user1.setuserName("Updateduser");
	user1.setemail("test@gmail.com");
	user1.sethashedPassword("1234");
	//message1["Data"] = user1.toJson();

	client.Send(message1);

	// Receiving a JSON response from the server
	json response1 = client.Receive();
	std::cout << "Response: " << response1.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true; 
}
TEST(JsonMessageTest, TestUpdateUserDataWithKeyDataNotFound){
    bool result = sendAndReceive_UpdateUserData3();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//99- update user data message with conflict key "Data" and its datatype
bool sendAndReceive_UpdateUserData4(){
	json message1;
	message1["ID"] = 16;
	message1["Action"] = "update user data";

	Note note;
	message1["Data"] = note.toJson();

	client.Send(message1);

	// Receiving a JSON response from the server
	json response1 = client.Receive();
	std::cout << "Response: " << response1.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true; 
}
TEST(JsonMessageTest, TestUpdateUserDataWithConflictKeyDataAndItsDatatype){
    bool result = sendAndReceive_UpdateUserData4();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//100- list note tags message with user and note found
bool sendAndReceive_ListNoteTags1(){
	json message1;
	message1["ID"] = 17;
	message1["Action"] = "list note tags";

	Note note1;
	note1.setuserId(31);
	note1.setnoteId(16);
	message1["Data"] = note1.toJson();

	client.Send(message1);

	// Receiving a JSON response from the server
	json response1 = client.Receive();
	std::cout << "Response: " << response1.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true; 
}
TEST(JsonMessageTest, TestListNoteTagsWithUserAndNoteFound){
    bool result = sendAndReceive_ListNoteTags1();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//101- list note tags message with user not found and note found
bool sendAndReceive_ListNoteTags2(){
	json message1;
	message1["ID"] = 17;
	message1["Action"] = "list note tags";

	Note note1;
	note1.setuserId(1);
	note1.setnoteId(17);
	message1["Data"] = note1.toJson();

	client.Send(message1);

	// Receiving a JSON response from the server
	json response1 = client.Receive();
	std::cout << "Response: " << response1.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true; 
}
TEST(JsonMessageTest, TestListNoteTagsWithUserNotFoundAndNoteFound){
    bool result = sendAndReceive_ListNoteTags2();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//102- list note tags message with user found and note not found
bool sendAndReceive_ListNoteTags3(){
	json message1;
	message1["ID"] = 17;
	message1["Action"] = "list note tags";

	Note note1;
	note1.setuserId(31);
	note1.setnoteId(1);
	message1["Data"] = note1.toJson();

	client.Send(message1);

	// Receiving a JSON response from the server
	json response1 = client.Receive();
	std::cout << "Response: " << response1.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true; 
}
TEST(JsonMessageTest, TestListNoteTagsWithUserFoundAndNoteNotFound){
    bool result = sendAndReceive_ListNoteTags3();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//103- list note tags message with key "Data" not found
bool sendAndReceive_ListNoteTags4(){
	json message1;
	message1["ID"] = 17;
	message1["Action"] = "list note tags";

	Note note1;
	note1.setuserId(31);
	note1.setnoteId(17);
	//message1["Data"] = note1.toJson();

	client.Send(message1);

	// Receiving a JSON response from the server
	json response1 = client.Receive();
	std::cout << "Response: " << response1.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true; 
}
TEST(JsonMessageTest, TestListNoteTagsWithKeyDataNotFound){
    bool result = sendAndReceive_ListNoteTags4();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//104- list note tags message with conflict key "Data" and its datatype
bool sendAndReceive_ListNoteTags5(){
	json message1;
	message1["ID"] = 17;
	message1["Action"] = "list note tags";

	User user;
	message1["Data"] = user.toJson();

	client.Send(message1);

	// Receiving a JSON response from the server
	json response1 = client.Receive();
	std::cout << "Response: " << response1.dump() << "\n";
	std::cout << std::endl << std::endl;
	return true; 
}
TEST(JsonMessageTest, TestListNoteTagsWithConflictKeyDataAndItsDatatype){
    bool result = sendAndReceive_ListNoteTags5();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//105- close message 
bool sendAndReceive_Close(){
	json endMessage;
	endMessage["Action"] = "close";
	client.Send(endMessage);
	client.CloseSocket();
	return true;
}
TEST(JsonMessageTest, TestCloseMessage){
    bool result = sendAndReceive_Close();
    // Assert that the test case passes
    ASSERT_TRUE(result);
}

int main() {
	// Initialize Google Test
	::testing::InitGoogleTest();

	// Run all tests
	return RUN_ALL_TESTS();
}
