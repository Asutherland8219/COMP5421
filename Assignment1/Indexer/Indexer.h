//
// Created by Alex Sutherland on 2025-05-19.
//

#ifndef INDEXER_H
#define INDEXER_H

#include <iostream>
#include <string>
#include "../DLList/DLList.h"
#include "../Token/Token.h"

/**
 * @class Indexer
 * @brief Manages the entire text file indexing process
 *
 */
class Indexer {
private:
    DLList index[27];           ///< Stores the index, all 27 sections (DLLists)
    std::string currentFilename; ///< Name of the currently indexed file
    /**
     * @brief Helper method to clean tokens
     */
    std::string cleanToken(const std::string& word);

public:
    /**
     * @brief Default constructor - initializes 27 empty sections
     */
    Indexer();

    /**
     * @brief Destructor - uses default cleanup
     */
    ~Indexer() = default;

    /**
     * @brief Copy constructor
     */
    Indexer(const Indexer& source) = delete;

    /**
     * @brief Copy assignment operator
     */
    Indexer& operator=(const Indexer& source) = delete;

    /**
     * @brief Move constructor
     */
    Indexer(Indexer&& source) = default;

    /**
     * @brief Move assignment operator
     */
    Indexer& operator=(Indexer&& source) = default;

    /**
     * @brief Locates the correct section and checks if the supplied token already exists
     */
    void processToken(const char* text, int lineNumber);

    /**
     * @brief Overloaded version that accepts Token object
     */
    void processToken(const Token& token, int lineNumber);

    /**
     * @brief Processes an entire text file
     */
    void processTextFile(const std::string& filename);

    /**
     * @brief Empties the entire index
     */
    void clear();

    /**
     * @brief Check if the index is empty
     */
    bool isEmpty() const;

    /**
     * @brief Displays the entire index, calling each section's print to write on os
     */
    void print(std::ostream& os) const;

    /**
     * @brief Displays all tokens using print(std::cout)
     */
    void displayAllTokens() const;

    /**
     * @brief Displays the tokens of a specified length
     */
    void listByLength(size_t length) const;

    /**
     * @brief Displays the tokens in a specified section
     */
    void viewBySection(char section) const;

    void displayAll() const;

    /**
     * @brief Search and display tokens by length
     */
    void searchByLength(size_t length) const;

    /**
     * @brief Display specific section by index
     */
    void displaySection(int sectionIndex) const;

    /**
     * @brief Constant for number of sections (27)
     */
    static const int NUM_SECTIONS = 27;
};

#endif // INDEXER_H