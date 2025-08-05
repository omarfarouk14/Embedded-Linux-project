#Author: Mohamed Newir
#Date: 10/5/2025
#File Name: CMakelists.txt
#Description: This file is used to compile the source code for the project
#             and set the required version of cmake and the required standard version of C++.
#             It also sets the compile options and the include directories for the project. 

#set the minimum required version of cmake
cmake_minimum_required(VERSION 3.10)

#set the project name
project(IoT_Device_Communication_System_Using_C++_with_Yocto_V1.0
        VERSION 1.0.0
        DESCRIPTION "IoT Device Communication System Using C++ with Yocto V1.0"
        LANGUAGES CXX)

#CPP standard version required for the project  
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Header path
include_directories(./Include)

#set the sources to be compiled 
set(SOURCES
    ./Source/TCPsocket.cpp
#   ./Source/UDPsocket.cpp
    ./Source/clientChannel.cpp
)

#add the executable
add_executable(client ./Source/client.cpp ${SOURCES})
#add the include directories
target_include_directories(client PRIVATE ./Include)
#compile features required for the project
target_compile_features(client PRIVATE cxx_std_17)
#add the compile options
# target_compile_options(Output PRIVATE -Wall -Wextra -Werror -Wpedantic)

#install the executable
#this will install the binary to the bin directory
#in the sysroot of the target system
#the destination is relative to the sysroot
#which is defined in the Yocto build system
install(TARGETS client DESTINATION bin)





