cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 20)

project(COMP5421)

# Define the executable with all source files
add_executable(COMP5421_Assignment1
        Assignment1/main.cpp
        Assignment1/IndexerUI/IndexerUI.cpp
        Assignment1/Indexer/Indexer.cpp
        Assignment1/DLList/DLList.cpp
        Assignment1/IndexedToken/IndexedToken.cpp
        Assignment1/IntList/IntList.cpp
        Assignment1/Token/Token.cpp
)
