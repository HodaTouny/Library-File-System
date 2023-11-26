cmake_minimum_required(VERSION 3.26)
project(Library_File_System)

set(CMAKE_CXX_STANDARD 17)

add_executable(Library_File_System main.cpp
        IFilesSystem.cpp
        IFilesSystem.h
        IFilesSystem.h
        LinkedList.cpp
        LinkedList.h
)
