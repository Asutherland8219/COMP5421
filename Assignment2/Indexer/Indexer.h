//
// Created by Alex Sutherland on 2025-06-12.
// Assignment 2 - Replace DLList with std::list
//

#ifndef INDEXER_H
#define INDEXER_H

#include <array>
#include <list>
#include <string>
#include <iostream>
#include "../IndexedToken/IndexedToken.h"


/**
 * @class Indexer
 * @brief Manages a collection of 27 sections (A-Z plus non-alphabetic)
 * where each section contains a sorted list of IndexedToken objects.

 */
class Indexer {
public:
    static const int NUM_SECTIONS = 27;  // 26 letters + 1 for non-alphabetic

private:
    std::array<std::list<IndexedToken>, NUM_SECTIONS> index;
    std::string currentFilename;

    // Helper method to clean tokens (remove unwanted punctuation) and handle Hashtag values (non alphabetic)
    std::string cleanToken(const std::string& word);

public:
    // Default constructor
    Indexer();

    // Copy constructor
    Indexer(const Indexer& other) = default;

    // Move constructor
    Indexer(Indexer&& other) noexcept = default;

    // Copy assignment operator
    Indexer& operator=(const Indexer& other) = default;

    // Move assignment operator
    Indexer& operator=(Indexer&& other) noexcept = default;

    // Destructor
    ~Indexer() = default;

    // Process a single token and add it to the appropriate section
    void processToken(const char* text, int lineNumber);
    void processToken(const std::string& token, int lineNumber);

    // Process an entire text file
    void processTextFile(const std::string& filename);

    // Clear all sections
    void clear();

    // Check if the index is empty
    bool isEmpty() const;

    // Display functions
    void print(std::ostream& os = std::cout) const;
    void displayAllTokens() const;
    void displayAll() const;  // alias for displayAllTokens

    // Search and filter functions
    void searchByLength(size_t length) const;
    void listByLength(size_t length) const;
    void viewBySection(char section) const;
    void displaySection(int sectionIndex) const;
};

// Helper function to determine section index (0-26) for a character
int getSectionIndex(char c);

#endif // INDEXER_H