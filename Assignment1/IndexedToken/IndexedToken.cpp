//
// Created by Alex Sutherland on 2025-05-19.
//
#include "IndexedToken.h"

// Parameterized constructor: Initialize with text and first line number
IndexedToken::IndexedToken(const char* text, int lineNumber)
    : token(text), lines() {
    lines.append(lineNumber);
}

// Parameterized constructor: Initialize with token and first line number
IndexedToken::IndexedToken(const Token& token, int lineNumber)
    : token(token), lines() {
    lines.append(lineNumber);
}

// Append a line number to the lines list
void IndexedToken::appendLineNumber(int lineNumber) {
    lines.append(lineNumber);
}

// Return the token by const reference
const Token& IndexedToken::getToken() const {
    return token;
}

// Return the line numbers by const reference
const IntList& IndexedToken::getLineNumbers() const {
    return lines;
}

// Print token followed by lines to output stream
void IndexedToken::print(std::ostream& os) const {
    os << token << " ";
    lines.print(os);
}

// Compare token's text with a C-string (delegates to Token::compare)
int IndexedToken::compare(const char* other) const {
    return token.compare(Token(other));
}

// Compare token with another IndexedToken's token (delegates to Token::compare)
int IndexedToken::compare(const IndexedToken& other) const {
    return token.compare(other.token);
}

// Get the length of the token text
size_t IndexedToken::length() const {
    return token.length();
}

// Get the token text as const char*
const char* IndexedToken::c_str() const {
    return token.c_str();
}

// Comparison operators
bool IndexedToken::operator<(const IndexedToken& other) const {
    return compare(other) < 0;
}

bool IndexedToken::operator>(const IndexedToken& other) const {
    return compare(other) > 0;
}

bool IndexedToken::operator==(const IndexedToken& other) const {
    return compare(other) == 0;
}

bool IndexedToken::operator!=(const IndexedToken& other) const {
    return compare(other) != 0;
}

// Stream output operator
std::ostream& operator<<(std::ostream& os, const IndexedToken& indexedToken) {
    indexedToken.print(os);
    return os;
}