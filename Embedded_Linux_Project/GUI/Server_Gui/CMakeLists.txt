cmake_minimum_required(VERSION 3.19)
project(Server_Gui LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable automatic handling of Qt-specific files
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Widgets Quick Charts QuickWidgets)

qt_standard_project_setup()

# Define QML files (optional, for clarity)
set(QML_FILES
    Resources/qml/chart.qml
    Resources/qml/meter.qml
)

set(IoT_Device_Communication_System_Lib ${CMAKE_CURRENT_SOURCE_DIR}/Lib/libIoT_Device_Communication_System_Lib.a)

qt_add_executable(Server_Gui
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    Include/channel.hpp Include/clientChannel.hpp Include/serverChannel.hpp Include/socket.hpp Include/TCPsocket.hpp Include/UDPsocket.hpp
    resources.qrc
    server.hpp
    server.cpp
    ${QML_FILES}
    mainwindow.ui
)

target_link_libraries(Server_Gui
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Quick
        Qt6::QuickWidgets
        Qt6::Charts
        ${IoT_Device_Communication_System_Lib}
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

# Specify resource paths for images and QML files
#set_source_files_properties(${QML_FILES} PROPERTIES
#    QT_RESOURCE_PREFIX "/qml"
#)
set_source_files_properties(
    Resources/icons/facebook.png
    Resources/icons/instagram.png
    Resources/icons/linkedin.png
    Resources/icons/background.jpg
    PROPERTIES
    QT_RESOURCE_PREFIX "/icons"
)


include(GNUInstallDirs)

install(TARGETS Server_Gui
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Server_Gui
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
