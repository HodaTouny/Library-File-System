cmake_minimum_required(VERSION 3.24)
project(Library_File_System)

set(CMAKE_CXX_STANDARD 17)

add_executable(Library_File_System main.cpp
        LinkedList.cpp
        cmake-build-debug/.cmake/Interface.cpp
        QueryProcessor.cpp
        PrimaryIndex.cpp
        SecondaryIndex.cpp
        IndexHelper.cpp
        EntityFiles.cpp
        FilesHelper.cpp
        AVAILSystem.cpp
        LibraryInterface.cpp
        LibraryInterface.h
)