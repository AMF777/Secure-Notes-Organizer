cmake_minimum_required(VERSION 3.0)
project(Server)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Find all directories within the include folder
file(GLOB INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include/*")

# Add additional system include directories
list(APPEND INCLUDE_DIRS
    /usr/include/cppconn  # Include directory for MySQL Connector/C++
)

# Include directories
include_directories(${INCLUDE_DIRS})

# Add source files
set(SOURCES
    src/Connection/Connection.cpp
    src/DataController/DataController.cpp
    src/Note/Note.cpp
    src/NoteComponent/NoteComponent.cpp
    src/ParseJsonMesssge/ParseJsonMesssge.cpp
    src/ServerWithDC/ServerWithDC.cpp
    src/Tag/Tag.cpp
    src/User/User.cpp
    src/ServerWithDC/server_main.cpp
)

# Add executable
add_executable(Server ${SOURCES})

# Link libraries
target_link_libraries(Server
    boost_system  # Link to Boost system library
    pthread       # Link to pthread library
    mysqlcppconn  # Link to MySQL Connector/C++ library
)

