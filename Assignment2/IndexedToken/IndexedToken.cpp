//
// Created by Alex Sutherland on 2025-06-12.
//


#include "IndexedToken.h"

// Parameterized constructor from const char*
IndexedToken::IndexedToken(const char* text, int lineNumber)
    : token(text) {  // std::string constructor handles memory management
    intlist.push_back(lineNumber);  // std::vector handles dynamic memory
}

// Parameterized constructor from std::string
IndexedToken::IndexedToken(const std::string& tokenText, int lineNumber)
    : token(tokenText) {
    intlist.push_back(lineNumber);
}

// Append a line number to the intlist vector
void IndexedToken::appendLineNumber(int lineNumber) {
    intlist.push_back(lineNumber);  // std::vector automatically manages resizing
}

// Getters
const std::string& IndexedToken::getToken() const {
    return token;
}

const std::vector<int>& IndexedToken::getLineNumbers() const {
    return intlist;
}

// Get the length of the token text
size_t IndexedToken::length() const {
    return token.length();
}

// Get the token text as const char*
const char* IndexedToken::c_str() const {
    return token.c_str();
}

// Print function - writes token followed by intlist to output stream
void IndexedToken::print(std::ostream& os) const {
    os << token << " ";

    // Use iterators to traverse the vector (as required by assignment)
    for (auto it = intlist.cbegin(); it != intlist.cend(); ++it) {
        if (it != intlist.cbegin()) {
            os << " ";
        }
        os << *it;
    }
}

// Compare functions
int IndexedToken::compare(const char* other) const {
    return token.compare(other);  // std::string provides built-in comparison
}

int IndexedToken::compare(const std::string& other) const {
    return token.compare(other);
}

int IndexedToken::compare(const IndexedToken& other) const {
    return token.compare(other.token);
}

// Convenience operators for comparison
bool IndexedToken::operator<(const IndexedToken& other) const {
    return token < other.token;  // std::string provides lexicographical comparison
}

bool IndexedToken::operator>(const IndexedToken& other) const {
    return token > other.token;
}

bool IndexedToken::operator==(const IndexedToken& other) const {
    return token == other.token;
}

bool IndexedToken::operator!=(const IndexedToken& other) const {
    return token != other.token;
}

// Stream output operator
std::ostream& operator<<(std::ostream& os, const IndexedToken& indexedToken) {
    indexedToken.print(os);
    return os;
}