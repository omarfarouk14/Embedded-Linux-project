# Embedded Linux IoT Communication System

## Author: Omar Farouk

---

## 🌐 Project Overview

This project represents the culmination of an Embedded Linux specialization and delivers a complete IoT communication system integrating:

- A **Qt6 GUI server** for interactive monitoring and configuration
- **Console-based server/client** tools for debugging and validation
- A **Yocto-based embedded client** running on QEMU

It allows a client to send temperature readings to the server over a TCP socket. The server, in turn, manages threshold values and controls LED status based on those readings. The entire system demonstrates modular design principles and cross-platform compatibility, and it runs seamlessly on both host and emulated embedded platforms.

---

## 🎯 Project Goals

- Enable two-way **socket communication** using TCP (and extensible to UDP)
- Provide a **user-friendly GUI** with real-time QML visualizations
- Deploy a **minimal embedded client** using the Yocto build system and QEMU
- Showcase **modern C++**, **Qt development**, and **embedded Linux skills**
- Apply design patterns and modular architecture to real-world IoT systems

---

## 📁 Project Structure


---

## 🪰 Requirements

- **Qt6**: For GUI server development (use Qt Creator)
- **g++**: C++17 or higher
- **CMake ≥ 3.16**: For compiling native tools
- **Yocto Project**: Poky (e.g., Kirkstone branch)
- **QEMU**: To emulate ARM64 device for Yocto
- **Linux Environment**: Recommended for Yocto builds

---

## ⚙️ Building the Project

### 1. Build Console Server & Client

```bash
cd "Socket Programming Drivers"
mkdir build && cd build
cmake ..
make
cd GUI/Server_Gui
mkdir build && cd build
cmake -DCMAKE_PREFIX_PATH=/path/to/Qt6 ..
make
git clone -b kirkstone git://git.yoctoproject.org/poky
cd poky
source oe-init-build-env build
bitbake-layers add-layer ../Yocto\ Image/meta-client-layer
IMAGE_INSTALL:append = " client"
MACHINE ??= "qemuarm64"
bitbake core-image-base
./Socket\ Programming\ Drivers/build/server 127.0.0.1 8080
./Socket\ Programming\ Drivers/build/client 127.0.0.1 8080
./GUI/Server_Gui/build/Server_Gui 192.168.7.2 8080
runqemu qemuarm64
# Login as root
client 192.168.7.2 8080
./GUI/Server_Gui/build/Server_Gui 192.168.7.2 8080
runqemu qemuarm64
client 192.168.7.2 8080
Connected to the server.
Received new threshold: 30°C – LED Status: OFF
