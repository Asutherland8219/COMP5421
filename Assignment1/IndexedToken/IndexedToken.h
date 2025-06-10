//
// Created by Alex Sutherland on 2025-05-19.
//

#ifndef INDEXED_TOKEN_H
#define INDEXED_TOKEN_H

#include "../Token/Token.h"
#include "../IntList/IntList.h"
#include <iostream>
#include <cstring>

/**
 * IndexedToken Class
 * Purpose: Aggregates a token and its list of line numbers,
 * representing a complete index entry for the token.
 */
class IndexedToken {
private:
    Token token;      // The token
    IntList lines;    // The list of line numbers

public:

    /**
     * @brief Get the length of the token text
     */
    size_t length() const;

    /**
     * @brief Get the token text as const char*
     */
    const char* c_str() const;
    // Parameterized constructors
    IndexedToken(const char* text, int lineNumber);
    IndexedToken(const Token& token, int lineNumber);

    // Copy constructor (default)
    IndexedToken(const IndexedToken& other) = default;

    // Move constructor (default)
    IndexedToken(IndexedToken&& other) noexcept = default;

    // Copy assignment operator (default)
    IndexedToken& operator=(const IndexedToken& other) = default;

    // Move assignment operator (default)
    IndexedToken& operator=(IndexedToken&& other) noexcept = default;

    // Destructor (default)
    ~IndexedToken() = default;

    // Append a line number to the lines list
    void appendLineNumber(int lineNumber);

    // Getters
    const Token& getToken() const;
    const IntList& getLineNumbers() const;

    // Print function - writes token followed by lines to output stream
    void print(std::ostream& os = std::cout) const;

    // Compare functions
    int compare(const char* other) const;
    int compare(const IndexedToken& other) const;

    // Convenience operators for comparison
    bool operator<(const IndexedToken& other) const;
    bool operator>(const IndexedToken& other) const;
    bool operator==(const IndexedToken& other) const;
    bool operator!=(const IndexedToken& other) const;

    // Stream output operator
    friend std::ostream& operator<<(std::ostream& os, const IndexedToken& indexedToken);
};

#endif // INDEXED_TOKEN_H