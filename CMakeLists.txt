cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 20)

project(COMP5421)

# Define the executable with all source files
add_executable(COMP5421_Assignment2
        Assignment2/main.cpp
        Assignment2/IndexerUI/IndexerUI.cpp
        Assignment2/Indexer/Indexer.cpp
        Assignment2/IndexedToken/IndexedToken.cpp
)
