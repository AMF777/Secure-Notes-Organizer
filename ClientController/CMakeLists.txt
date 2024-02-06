cmake_minimum_required(VERSION 3.5)

project(ClientController LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add pthread library
find_package(Threads REQUIRED)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()


find_package(Qt6 COMPONENTS Widgets REQUIRED)

if(ANDROID)
  add_library(ClientController SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
  )
else()
  add_executable(ClientController
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    clientcontroller.cpp
    clientcontroller.h
    clientconnection.cpp
    clientconnection.h
    json.hpp
    Note.cpp
    Note.h
    NoteComponent.cpp
    NoteComponent.h
    User.h
    User.cpp
    Tag.cpp
    Tag.h
  )
endif()

# Link against the pthread library
target_link_libraries(ClientController PRIVATE Qt6::Widgets Threads::Threads)
