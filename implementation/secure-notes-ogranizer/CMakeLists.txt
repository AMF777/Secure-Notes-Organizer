cmake_minimum_required(VERSION 3.5)

project(secure-notes-ogranizer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(secure-notes-ogranizer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        signin.h signin.cpp
        constants.h constants.cpp

        label_input_vlayout.h label_input_vlayout.cpp
        img_msg_vlayout.h img_msg_vlayout.cpp
        clickable_label.h clickable_label.cpp
        signup.h signup.cpp
        switcher_widget.h switcher_widget.cpp
        main_window.h main_window.cpp
        sidebar_vlayout.h sidebar_vlayout.cpp
        button_icon_vlayout.h button_icon_vlayout.cpp
        custom_widget.h custom_widget.cpp
        text_edit_component.h text_edit_component.cpp
        res.qrc
        add_note_dialog.h add_note_dialog.cpp



    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET secure-notes-ogranizer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(secure-notes-ogranizer SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(secure-notes-ogranizer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(secure-notes-ogranizer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.secure-notes-ogranizer)
endif()
set_target_properties(secure-notes-ogranizer PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS secure-notes-ogranizer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(secure-notes-ogranizer)
endif()
