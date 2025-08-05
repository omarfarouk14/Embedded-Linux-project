SUMMARY = "Client"
DESCRIPTION = "Custom C++ client application"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://Source/client.cpp;md5=91e9b2d235d3127061b83ca3f2277919"

SRC_URI = "\
    file://CMakeLists.txt \
    file://Source/client.cpp \
    file://Source/clientChannel.cpp \
    file://Source/TCPsocket.cpp \
    file://Include/channel.hpp \
    file://Include/clientChannel.hpp \
    file://Include/socket.hpp \
    file://Include/TCPsocket.hpp \
"

S = "${WORKDIR}"

inherit cmake

