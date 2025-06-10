//
// Created by Alex Sutherland on 2025-05-19.
//

#include "DLList.h"
#include <cstring>

// Default constructor - creates empty list
DLList::DLList() : head(nullptr), tail(nullptr), size(0) {
}

// Copy constructor - performs deep copy
DLList::DLList(const DLList& other) : head(nullptr), tail(nullptr), size(0) {
    copyFrom(other);
}

// Copy assignment operator - performs deep copy
DLList& DLList::operator=(const DLList& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

// Move constructor - transfers ownership
DLList::DLList(DLList&& other) noexcept
    : head(other.head), tail(other.tail), size(other.size) {
    // Leave other in empty state
    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
}

// Move assignment operator - transfers ownership with self-assignment safety
DLList& DLList::operator=(DLList&& other) noexcept {
    if (this != &other) {
        clear();

        // Transfer ownership
        head = other.head;
        tail = other.tail;
        size = other.size;

        // Leave other in empty state
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }
    return *this;
}

// Destructor - deallocates all nodes
DLList::~DLList() {
    clear();
}

// Inserts an IndexedToken in sorted order (alphabetical by token text)
void DLList::insertSorted(const IndexedToken& token) {
    Node* newNode = new Node(token);

    // If list is empty
    if (head == nullptr) {
        head = tail = newNode;
        size++;
        return;
    }

    // Find correct position for insertion (sorted by token text)
    Node* current = head;
    while (current != nullptr && token.compare(current->data) > 0) {
        current = current->next;
    }

    // Insert at beginning
    if (current == head) {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    // Insert at end
    else if (current == nullptr) {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    // Insert in middle
    else {
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
    }

    size++;
}

// Searches for a token with matching text
IndexedToken* DLList::findToken(const char* text) {
    if (text == nullptr) {
        return nullptr;
    }

    Node* current = head;
    while (current != nullptr) {
        if (strcmp(current->data.c_str(), text) == 0) {
            return &(current->data);
        }
        current = current->next;
    }

    return nullptr;
}

// Removes all elements and deallocates memory
void DLList::clear() {
    deleteAllNodes();
    head = tail = nullptr;
    size = 0;
}

// Checks if the list is empty
bool DLList::isEmpty() const {
    return head == nullptr;
}

// Gets the number of elements in the list
size_t DLList::getSize() const {
    return size;
}

// Prints all tokens in the list to output stream
void DLList::print(std::ostream& os) const {
    Node* current = head;
    while (current != nullptr) {
        current->data.print(os);
        if (current->next != nullptr) {
            os << std::endl;
        }
        current = current->next;
    }
}

// Prints tokens of a specific length
void DLList::printByLength(std::ostream& os, size_t length) const {
    Node* current = head;
    bool found = false;

    while (current != nullptr) {
        if (current->data.length() == length) {
            if (found) {
                os << std::endl;
            }
            current->data.print(os);
            found = true;
        }
        current = current->next;
    }
}

// Helper method to deallocate all nodes
void DLList::deleteAllNodes() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

// Helper method to copy all nodes from another list
void DLList::copyFrom(const DLList& other) {
    Node* current = other.head;
    while (current != nullptr) {
        insertSorted(current->data);
        current = current->next;
    }
}