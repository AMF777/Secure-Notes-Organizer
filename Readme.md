
# Secure Notes Generator

![Siemens_logo](https://logo-logos.com/2016/10/Siemens_logo.png)

## Description

The "Secure Notes Organizer" is a desktop application designed to provide users
with a secure and organized way to manage sensitive information. The primary focus
of the application is to allow users to create, store, and organize notes in a secure
environment, ensuring the confidentiality of the stored information.
A single server will be running that will save all the users’ encrypted authentication
data and all the notes. Multiple clients should be able to connect to the server
allowing the users to login and see their notes, edit them or add new notes

## Main functionality

1. Create and edit notes (locally)

2. Organize notes using tags

3. Secure syncing (encryption/hashing)

4. User authentication (login)

5. Customizing note (color)

## Advanced Functionality

1. Rich text (markdown)

2. Search notes

3. Sharing notes (Future work)

## Tools and languages used in Project

| Icon                                                                                                                                 | Tech   |
| ------------------------------------------------------------------------------------------------------------------------------------ | ------ |
| <img height="50" src="https://user-images.githubusercontent.com/25181517/192108372-f71d70ac-7ae6-4c0d-8395-51d8870c2ef0.png">        | Git    |
| <img height="50" src="https://user-images.githubusercontent.com/25181517/192108374-8da61ba1-99ec-41d7-80b8-fb2f7c0a4948.png">        | GitHub |
| <img height="50" src="https://user-images.githubusercontent.com/25181517/183912952-83784e94-629d-4c34-a961-ae2ae795b662.png">        | Jira   |
| <img height="50" src="https://user-images.githubusercontent.com/25181517/189715289-df3ee512-6eca-463f-a0f4-c10d94a06b2f.png">        | Figma  |
| <img height="50" src="https://user-images.githubusercontent.com/25181517/192106073-90fffafe-3562-4ff9-a37e-c77a2da0ff58.png">        | C++    |
| <img height="50" src="https://github.com/marwin1991/profile-technology-icons/assets/136815194/11e7dfe7-c1f6-483c-9d92-276f1fa9363b"> | Qt Version 6    |
| <img height="50" src="https://www.michaelstults.com/wp-content/uploads/2014/10/MySQLWorkbench.png">        | My SQL Workbench  |
| <img height="50" src="https://www.incredibuild.com/wp-content/uploads/2020/10/gtest.jpg">                                            | GTest  |
| <img height="50" src="https://user-images.githubusercontent.com/25181517/192108891-d86b6220-e232-423a-bf5f-90903e6887c3.png">                                            | Visual Studio Code  |
| <img height="50" src="https://cdn-icons-png.flaticon.com/512/136/136525.png">                                            | JSON  |
| <img height="50" src="https://static-00.iconduck.com/assets.00/cmake-icon-2048x2046-qsjo7g7r.png">                                            | cmake  |
| <img height="50" src="https://user-images.githubusercontent.com/25181517/186884153-99edc188-e4aa-4c84-91b0-e2df260ebc33.png">                                            | Ubuntu  |

## Run Locally

Clone the project

```bash
  git clone https://github.com/AMF777/Secure-Notes-Organizer
```

Install dependencies

Set up My Sql Workbench 

```bash
  https://linuxhint.com/installing_mysql_workbench_ubuntu/
```
Download and Install C++ Connector for My Sql Workbench

```bash
  sudo apt-get install libmysqlcppconn-dev
```
Open my Sql Workbench

Open the DB.sql file inside the Database directory
```bash
  cd Server/Database/
```
Create Database Schema inside My Sql Workbench
```bash
  CREATE SCHEMA SecureNoteOrganizer;
```
Then execute DB.Sql in My Sql Workbench

Reconfigure the connection to Database with your username and password and Database Schema name in line 6 in the file ServerWithDC.cpp
```bash
  cd Server_with_cmake/Server/src/ServerWithDC/
```
Run the integration testing of Clinet Controller with Server
```bash
  cd Gtest/ClientControllerForGtest/

  g++ *.cpp -o client -I. -pthread -L/path/to/gtest/lib -lgtest -lgtest_main

  ./client  
```

Start the server

```bash
  cd Server_with_cmake/Server/

  mkdir build

  cd build 

  cmake ..

  make
  
  ./Server
```


## Authors

- [Ahmed Magdy](https://github.com/AMF777)
- [Ahmed Ashraf](https://github.com/12ahmed52)
- [Ahmed Hany](https://github.com/HNOONa-0)
- [Ayman Ashraf](https://github.com/Mo3gz)
- [Mary Magdy](https://github.com/MaryMagdyShinoda)
- [Youssef Abdelmaksoud](https://github.com/Youssefhassan1717)

