//
// Created by Alex Sutherland on 2025-06-12.
// Assignment 2 - Replace DLList with std::list
//


#include "Indexer.h"
#include <fstream>
#include <sstream>
#include <cctype>
#include <iostream>

// Helper function to determine which section (0-26) a character belongs to
int getSectionIndex(char c) {
    if (isalpha(c)) {
        return tolower(c) - 'a';  // 'a' or 'A' -> 0, 'b' or 'B' -> 1, etc.
    }
    return Indexer::NUM_SECTIONS - 1;  // Non-alphabetic characters go to section 26
}

// Default constructor - std::array and std::list are automatically initialized
Indexer::Indexer() : currentFilename("") {
    // STL containers handle initialization automatically via RAII
}

void Indexer::processToken(const char* text, int lineNumber) {
    if (!text || !*text) return; // Skip empty or null tokens

    // Determine which section this token belongs to based on first character
    int sectionIndex = getSectionIndex(text[0]);
    std::list<IndexedToken>& targetSection = index[sectionIndex];

    // Use iterators to search for existing token in the sorted list
    auto it = targetSection.begin();
    while (it != targetSection.end() && it->compare(text) < 0) {
        ++it;
    }

    // Check if token already exists at this position
    if (it != targetSection.end() && it->compare(text) == 0) {
        // Token exists; add this line number to existing token
        // Note: We need to modify the existing token, but iterators point to const objects
        // We'll need to use a non-const approach
        const_cast<IndexedToken&>(*it).appendLineNumber(lineNumber);
    } else {
        // Token doesn't exist; create new IndexedToken and insert at sorted position
        IndexedToken newToken(text, lineNumber);
        targetSection.insert(it, newToken);
    }
}

// Overloaded version that accepts std::string
void Indexer::processToken(const std::string& token, int lineNumber) {
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
    int totalTokens = 0;

    while (std::getline(file, line)) {
        // Tokenize the line
        std::istringstream iss(line);
        std::string word;

        // Extract words separated by whitespace
        while (iss >> word) {
            // Clean the word (remove punctuation, etc.)
            std::string cleanWord = cleanToken(word);
            if (!cleanWord.empty()) {
                processToken(cleanWord, lineNumber);
                totalTokens++;
            }
        }

        lineNumber++;
    }

    file.close();

    // Print success message with line and token counts
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
    // Use iterators to clear each section
    for (auto it = index.begin(); it != index.end(); ++it) {
        it->clear();  // std::list::clear() automatically handles memory management
    }
    currentFilename = "";
}

// Check if the index is empty
bool Indexer::isEmpty() const {
    // Use const_iterators to check each section
    for (auto it = index.cbegin(); it != index.cend(); ++it) {
        if (!it->empty()) {
            return false;
        }
    }
    return true;
}

// Displays the entire index
void Indexer::print(std::ostream& os) const {
    if (!currentFilename.empty()) {
        os << "Index for file: " << currentFilename << std::endl;
        os << "================================" << std::endl;
    }

    // Use iterators to traverse the array of sections
    for (size_t i = 0; i < index.size(); ++i) {
        if (!index[i].empty()) {
            if (i < 26) {
                os << "--- Section " << static_cast<char>('A' + i) << " ---" << std::endl;
            } else {
                os << "--- Section [Non-alphabetic] ---" << std::endl;
            }

            // Use const_iterators to traverse each section's list
            for (auto tokenIt = index[i].cbegin(); tokenIt != index[i].cend(); ++tokenIt) {
                tokenIt->print(os);
                os << std::endl;
            }
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
    if (sectionIndex < 0 || sectionIndex >= NUM_SECTIONS) {
        std::cout << "Invalid section index: " << sectionIndex << std::endl;
        return;
    }

    if (index[sectionIndex].empty()) {
        if (sectionIndex < NUM_SECTIONS - 1) {
            std::cout << "Section " << static_cast<char>('A' + sectionIndex) << " is empty." << std::endl;
        } else {
            std::cout << "Section [Non-alphabetic] is empty." << std::endl;
        }
    } else {
        if (sectionIndex < NUM_SECTIONS - 1) {
            std::cout << "--- Section " << static_cast<char>('A' + sectionIndex) << " ---" << std::endl;
        } else {
            std::cout << "--- Section [Non-alphabetic] ---" << std::endl;
        }

        // Use const_iterators to display section contents
        for (auto it = index[sectionIndex].cbegin(); it != index[sectionIndex].cend(); ++it) {
            it->print(std::cout);
            std::cout << std::endl;
        }
    }
}

// Displays the tokens of a specified length
void Indexer::listByLength(size_t length) const {
    bool found = false;

    std::cout << "Tokens of length " << length << ":" << std::endl;

    // Use iterators to traverse each section
    for (size_t i = 0; i < index.size(); ++i) {
        if (!index[i].empty()) {
            // Check if this section has any tokens of the specified length
            bool sectionHasMatches = false;
            std::ostringstream tempStream;

            // Use const_iterators to search for tokens of specified length
            for (auto tokenIt = index[i].cbegin(); tokenIt != index[i].cend(); ++tokenIt) {
                if (tokenIt->length() == length) {
                    if (!sectionHasMatches) {
                        // First match in this section - print section header
                        if (found) {
                            tempStream << std::endl; // Add spacing between sections
                        }

                        if (i < NUM_SECTIONS - 1) {
                            tempStream << "--- Section " << static_cast<char>('A' + i) << " ---" << std::endl;
                        } else {
                            tempStream << "--- Section [Non-alphabetic] ---" << std::endl;
                        }
                        sectionHasMatches = true;
                        found = true;
                    }

                    tokenIt->print(tempStream);
                    tempStream << std::endl;
                }
            }

            // Output the section if it had matches
            if (sectionHasMatches) {
                std::cout << tempStream.str();
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
        sectionIndex = NUM_SECTIONS - 1;  // Non-alphabetic section
    }

    if (sectionIndex >= 0 && sectionIndex < NUM_SECTIONS) {
        if (sectionIndex < NUM_SECTIONS - 1) {
            std::cout << "--- Section " << static_cast<char>(toupper(section)) << " ---" << std::endl;
        } else {
            std::cout << "--- Section [Non-alphabetic] ---" << std::endl;
        }

        if (index[sectionIndex].empty()) {
            std::cout << "No tokens in this section." << std::endl;
        } else {
            // Use const_iterators to display section contents
            for (auto it = index[sectionIndex].cbegin(); it != index[sectionIndex].cend(); ++it) {
                it->print(std::cout);
                std::cout << std::endl;
            }
        }
    } else {
        std::cout << "Invalid section: " << section << std::endl;
    }
}