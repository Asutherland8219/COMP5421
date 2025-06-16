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
 * Indexer Class
 * Purpose: Manages a collection of 27 sections (A-Z plus non-alphabetic)
 * where each section contains a sorted list of IndexedToken objects.
 *
 * Uses modern C++ with STL containers:
 * - std::array<std::list<IndexedToken>, 27> for the 27 sections
 * - std::list<IndexedToken> for each section (replaces DLList)
 * - Automatic memory management via RAII
 */
class Indexer {
public:
    static const int NUM_SECTIONS = 27;  // 26 letters + 1 for non-alphabetic

private:
    std::array<std::list<IndexedToken>, NUM_SECTIONS> index;  // 27 sections: A-Z + non-alphabetic
    std::string currentFilename;

    // Helper method to clean tokens (remove unwanted punctuation)
    std::string cleanToken(const std::string& word);

public:
    // Default constructor
    Indexer();

    // Copy constructor (default - STL containers handle deep copying)
    Indexer(const Indexer& other) = default;

    // Move constructor (default - STL containers provide efficient move semantics)
    Indexer(Indexer&& other) noexcept = default;

    // Copy assignment operator (default - STL containers handle deep copying)
    Indexer& operator=(const Indexer& other) = default;

    // Move assignment operator (default - STL containers provide efficient move semantics)
    Indexer& operator=(Indexer&& other) noexcept = default;

    // Destructor (default - STL containers automatically manage memory via RAII)
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