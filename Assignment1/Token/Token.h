//
// Created by Alex Sutherland on 2025-05-19.
//

#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>

/**
 * @class Token
 * @brief A string wrapper class that manages dynamic C-style strings
 */
class Token {
private:
    char* text;  ///< Pointer to dynamically allocated C-string

public:
    /**
     * @brief Default Constructor
     */
    Token();

    /**
     * @brief Parameterized constructor
     */
    explicit Token(const char* str = "");

    /**
     * @brief Deep Copy constructor
     */
    Token(const Token& other);

    /**
     * @brief Destructor - releases allocated memory by deleting text
     */
    ~Token();

    /**
     * @brief Copy assignment operator - performs deep copy
     */
    Token& operator=(const Token& other);

    /**
     * @brief Move assignment operator
     */
    Token& operator=(Token&& other) noexcept;

    /**
     * @brief Gets the first character of the token

     */
    char getFirstChar() const;

    /**
     * @brief Gets the token text as a C-string
     */
    const char* c_str() const;

    /**
     * @brief Gets the length of the token text
     */
    size_t length() const;

    /**
     * @brief Writes token text to output stream
     */
    void print(std::ostream& os) const;

    /**
     * @brief Performs case-sensitive string comparison
     */
    int compare(const Token& other) const;
};

    std::ostream& operator<<(std::ostream& os, const Token& token);

#endif // TOKEN_H