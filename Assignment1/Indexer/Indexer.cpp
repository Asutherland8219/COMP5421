//
// Created by Alex Sutherland on 2025-05-19.
//

#include "Indexer.h"
#include "../Token/Token.h"
#include "../IndexedToken/IndexedToken.h"
#include <fstream>
#include <sstream>
#include <cctype>
#include <iostream>

// Default constructor - initializes 27 empty sections
Indexer::Indexer() {
    // DLList array is automatically initialized
    currentFilename = "";
}

// Helper function to determine which section (0-26) a character belongs to
int getSectionIndex(char c) {
    if (isalpha(c)) {
        return tolower(c) - 'a';  // 'a' or 'A' -> 0, 'b' or 'B' -> 1, etc.
    }
    return 26;  // Non-alphabetic characters go to section 26
}


void Indexer::processToken(const char* text, int lineNumber) {
    if (!text || !*text) return; // Skip empty or null tokens

    // Determine which section this token belongs to based on first character
    int sectionIndex = getSectionIndex(text[0]);
    DLList& targetSection = index[sectionIndex];

    // Use DLList's findToken method to search for existing token
    IndexedToken* existingToken = targetSection.findToken(text);

    if (existingToken) {
        // Token exists; add this line number to existing token
        existingToken->appendLineNumber(lineNumber);
    } else {
        // Token doesn't exist; create new IndexedToken
        IndexedToken newToken(text, lineNumber);
        targetSection.insertSorted(newToken);
    }
}

// Overloaded version that accepts Token object
void Indexer::processToken(const Token& token, int lineNumber) {
    processToken(token.c_str(), lineNumber);
}

void Indexer::processTextFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "'" << std::endl;
        return;
    }

    // Clear existing index and update current filename
    clear();
    currentFilename = filename;

    std::string line;
    int lineNumber = 1;
    int totalTokens = 0;  // Add token counter

    while (std::getline(file, line)) {
        // Tokenize the line
        std::istringstream iss(line);
        std::string word;

        // Extract words separated by whitespace
        while (iss >> word) {
            // Clean the word (remove punctuation, etc.)
            std::string cleanWord = cleanToken(word);
            if (!cleanWord.empty()) {
                processToken(cleanWord.c_str(), lineNumber);
                totalTokens++;  // Increment token counter
            }
        }

        lineNumber++;
    }

    file.close();

    // Print success message with line and token counts to match sample output
    std::cout << "File indexed successfully (" << (lineNumber - 1)
              << " lines, " << totalTokens << " tokens processed)." << std::endl;
}

// Helper method to clean tokens
std::string Indexer::cleanToken(const std::string& word) {
    std::string result;

    for (char c : word) {
        if (isalnum(c) || c == '\'') { // Keep alphanumeric and apostrophes
            result += c;
        }
    }

    return result;
}

// Empties the entire index
void Indexer::clear() {
    for (int i = 0; i < 27; i++) {
        index[i].clear();
    }
    currentFilename = "";
}

// Check if the index is empty
bool Indexer::isEmpty() const {
    for (int i = 0; i < 27; i++) {
        if (!index[i].isEmpty()) {
            return false;
        }
    }
    return true;
}

// Displays the entire index, calling each section's print to write on os
void Indexer::print(std::ostream& os) const {
    if (!currentFilename.empty()) {
        os << "Index for file: " << currentFilename << std::endl;
        os << "================================" << std::endl;
    }

    for (int i = 0; i < 27; i++) {
        if (!index[i].isEmpty()) {
            if (i < 26) {
                os << "--- Section " << static_cast<char>('A' + i) << " ---" << std::endl;
            } else {
                os << "--- Section [Non-alphabetic] ---" << std::endl;
            }
            index[i].print(os);
            os << std::endl;
        }
    }
}

// Displays all tokens using print
void Indexer::displayAllTokens() const {
    print(std::cout);
}

// alias for displayAllTokens
void Indexer::displayAll() const {
    displayAllTokens();
}

// search by token length
void Indexer::searchByLength(size_t length) const {
    listByLength(length);
}

// display specific section by index
void Indexer::displaySection(int sectionIndex) const {
    if (sectionIndex < 0 || sectionIndex >= 27) {
        std::cout << "Invalid section index: " << sectionIndex << std::endl;
        return;
    }

    if (index[sectionIndex].isEmpty()) {
        if (sectionIndex < 26) {
            std::cout << "Section " << static_cast<char>('A' + sectionIndex) << " is empty." << std::endl;
        } else {
            std::cout << "Section [Non-alphabetic] is empty." << std::endl;
        }
    } else {
        if (sectionIndex < 26) {
            std::cout << "--- Section " << static_cast<char>('A' + sectionIndex) << " ---" << std::endl;
        } else {
            std::cout << "--- Section [Non-alphabetic] ---" << std::endl;
        }
        index[sectionIndex].print(std::cout);
    }
}

// Displays the tokens of a specified length
void Indexer::listByLength(size_t length) const {
    bool found = false;

    std::cout << "Tokens of length " << length << ":" << std::endl;

    for (int i = 0; i < 27; i++) {
        if (!index[i].isEmpty()) {
            // Check if this section has any tokens of the specified length
            // We'll print a section header if there are matches
            std::ostringstream tempStream;
            index[i].printByLength(tempStream, length);

            if (!tempStream.str().empty()) {
                if (found) {
                    std::cout << std::endl; // Add spacing between sections
                }

                // Print section header
                if (i < 26) {
                    std::cout << "--- Section " << static_cast<char>('A' + i) << " ---" << std::endl;
                } else {
                    std::cout << "--- Section [Non-alphabetic] ---" << std::endl;
                }

                // Print the tokens
                std::cout << tempStream.str();
                found = true;
            }
        }
    }

    if (!found) {
        std::cout << "No tokens of length " << length << " found." << std::endl;
    }
}

// Displays the tokens in a specified section
void Indexer::viewBySection(char section) const {
    int sectionIndex;

    if (isalpha(section)) {
        sectionIndex = tolower(section) - 'a';
    } else {
        sectionIndex = 26;  // Non-alphabetic section
    }

    if (sectionIndex >= 0 && sectionIndex < 27) {
        if (sectionIndex < 26) {
            std::cout << "--- Section " << static_cast<char>(toupper(section)) << " ---" << std::endl;
        } else {
            std::cout << "--- Section [Non-alphabetic] ---" << std::endl;
        }

        if (index[sectionIndex].isEmpty()) {
            std::cout << "No tokens in this section." << std::endl;
        } else {
            index[sectionIndex].print(std::cout);
        }
    } else {
        std::cout << "Invalid section: " << section << std::endl;
    }
}