//
// Created by Alex Sutherland on 2025-05-19.
//

#ifndef INDEXED_TOKEN_H
#define INDEXED_TOKEN_H

#include <string>
#include <vector>
#include <iostream>

/**
 * IndexedToken Class
 * Purpose: Aggregates a token (as std::string) and its list of line numbers (as std::vector<int>),
 * representing a complete index entry for the token.
 *
 * Uses modern C++ with STL containers for automatic memory management (RAII).
 */
class IndexedToken {
private:
    std::string token;           // The token as std::string (replaces Token class)
    std::vector<int> intlist;    // The list of line numbers as std::vector<int> (replaces IntList class)

public:
    // Parameterized constructors
    IndexedToken(const char* text, int lineNumber);
    IndexedToken(const std::string& tokenText, int lineNumber);

    // Copy constructor (default - STL containers handle deep copying automatically)
    IndexedToken(const IndexedToken& other) = default;

    // Move constructor (default - STL containers provide efficient move semantics)
    IndexedToken(IndexedToken&& other) noexcept = default;

    // Copy assignment operator (default - STL containers handle deep copying automatically)
    IndexedToken& operator=(const IndexedToken& other) = default;

    // Move assignment operator (default - STL containers provide efficient move semantics)
    IndexedToken& operator=(IndexedToken&& other) noexcept = default;

    // Destructor (default - STL containers automatically manage memory via RAII)
    ~IndexedToken() = default;

    // Append a line number to the intlist vector
    void appendLineNumber(int lineNumber);

    // Getters
    const std::string& getToken() const;
    const std::vector<int>& getLineNumbers() const;

    /**
     * @brief Get the length of the token text
     */
    size_t length() const;

    /**
     * @brief Get the token text as const char*
     */
    const char* c_str() const;

    // Print function - writes token followed by lines to output stream
    void print(std::ostream& os = std::cout) const;

    // Compare functions
    int compare(const char* other) const;
    int compare(const std::string& other) const;
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