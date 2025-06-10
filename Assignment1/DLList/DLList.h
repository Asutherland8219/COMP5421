//
// Created by Alex Sutherland on 2025-05-19.
//

#ifndef DLLIST_H
#define DLLIST_H

#include <iostream>
#include "../IndexedToken/IndexedToken.h"

/**
 * @class DLList
 */
class DLList {
private:
    /**
     * @class Node
     */
    class Node {
    public:
        IndexedToken data;  ///< The IndexedToken stored in this node
        Node* next;         ///< Pointer to the next node
        Node* prev;         ///< Pointer to the previous node

        /**
         * Default Constructor for token
         * @param token IndexedToken to store in this node
         */
        explicit Node(const IndexedToken& token) : data(token), next(nullptr), prev(nullptr) {}
    };

    Node* head;     ///< Pointer to the first node
    Node* tail;     ///< Pointer to the last node
    size_t size;    ///< Number of elements in the list

public:
    /**
     * @brief Default constructor - creates empty list
     */
    DLList();

    /**
     * @brief Copy constructor - performs deep copy
     * @param other DLList to copy from
     */
    DLList(const DLList& other);

    /**
     * @brief Copy assignment operator - performs deep copy
     * @param other DLList to assign from
     */
    DLList& operator=(const DLList& other);

    /**
     * @brief Move constructor - transfers ownership
     * @param other DLList to move from (left in valid empty state)
     */
    DLList(DLList&& other) noexcept;

    /**
     * @brief Move assignment operator - transfers ownership
     * @param other DLList to move from
     */
    DLList& operator=(DLList&& other) noexcept;

    /**
     * @brief Destructor - deallocates all nodes
     */
    ~DLList();

    /**
     * @brief Inserts an IndexedToken in sorted order
     * @param token IndexedToken to insert
     */
    void insertSorted(const IndexedToken& token);

    /**
     * @brief Searches for a token with matching text
     * @param text C-string to search for
     */
    IndexedToken* findToken(const char* text);

    /**
     * @brief Removes all elements and clears memory
     */
    void clear();

    /**
     * @brief Checks if the list is empty
     */
    bool isEmpty() const;

    /**
     * @brief Gets the number of elements in the list
     */
    size_t getSize() const;

    /**
     * @brief Prints all tokens in the list to output stream
     * @param os Output stream to write to
     */
    void print(std::ostream& os) const;

    /**
     * @brief Prints tokens of a specific length; used in display menu
     * @param os Output stream to write to
     * @param length Length of tokens to display
     */
    void printByLength(std::ostream& os, size_t length) const;

private:
    /**
     * @brief Helper method to deallocate all nodes
     */
    void deleteAllNodes();

    /**
     * @brief Helper method to copy all nodes from another list
     * @param other DLList to copy from
     */
    void copyFrom(const DLList& other);
};

#endif // DLLIST_H