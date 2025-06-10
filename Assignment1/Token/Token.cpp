//
// Created by Alex Sutherland on 2025-05-19.
//

#include "Token.h"
#include <iostream>
#include <cstring>


    // Default constructor - creates empty token with valid null-terminated string
    Token::Token() {
        text = new char[1];
        text[0] = '\0';
    }

    // Parameterized constructor - handles null or empty string by allocating one-character array containing only nullptr
    Token::Token(const char* str) {
        if (str == nullptr || strlen(str) == 0) {
            text = new char[1];
            text[0] = '\0';
        } else {
            text = new char[strlen(str) + 1];
            strcpy(text, str);
        }
    }

    // copy constructor
    Token::Token(const Token& other) {
        if (other.text == nullptr) {
            text = nullptr;
        } else {
            text = new char[strlen(other.text) + 1];
            strcpy(text, other.text);
        }
    }

    // Destructor , wipes the text
    Token::~Token() {
        delete[] text;
    }

    // Copy assignment operator (deep copy, handles self-assignment and transfers ownership, leaving the moved-from object where as valid empty token)
    Token& Token::operator=(const Token& other) {
            if (this != &other) {  // Handle self-assignment
                delete[] text;  // Clean up existing memory
                text = new char[strlen(other.text) + 1];
                strcpy(text, other.text);
            }
            return *this;
        }

    // Move assignment operator - handles self-assignment and transfers ownership, leaving the moved-from object where as valid empty token
    Token& Token::operator=(Token&& other) noexcept {
        if (this != &other) {
            delete[] text;
            text = other.text;
            other.text = new char[1];
            other.text[0] = '\0';
        }
        return *this;
    }

    // Returns first character of token text[0]
    char Token::getFirstChar() const {
        return text[0];
    }

    // Returns this token's text as a const char*
    const char* Token::c_str() const {
        return text;
    }

    // Returns the length of token's text using strlen
    size_t Token::length() const {
        return strlen(text);
    }

    // Writes the token text to the output stream os
    void Token::print(std::ostream& os) const {
            os << text;
    }

    // Performs case-sensitive comparison using std::strcmp.
    int Token::compare(const Token& other) const {
        return strcmp(text, other.text);
    }

std::ostream& operator<<(std::ostream& os, const Token& token) {
        os << token.c_str();
        return os;
    }
