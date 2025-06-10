//
// Created by Alex Sutherland on 2025-05-19.
//

#include "IntList.h"
#include <stdexcept>

//  base constructor
IntList::IntList() {
    capacity = 2;
    size = 0;
    p_array = new int[capacity];
}

// deep copy constructor
IntList::IntList(const IntList& other) {
    capacity = other.capacity;
    size = other.size;
    p_array = new int[capacity];

    // Copy all elements
    for (size_t i = 0; i < size; i++) {
        p_array[i] = other.p_array[i];
    }
}

// Copy assignment operator - performs deep copy with self-assignment safety`
IntList& IntList::operator=(const IntList& other) {
    if (this != &other) {  // Handle self-assignment
        delete[] p_array;     // Clean up existing memory

        capacity = other.capacity;
        size = other.size;
        p_array = new int[capacity];

        // Copy all elements
        for (size_t i = 0; i < size; i++) {
            p_array[i] = other.p_array[i];
        }
    }
    return *this;
}

// move constructor
IntList::IntList(IntList&& other) noexcept {
    // Transfer ownership
    p_array = other.p_array;
    size = other.size;
    capacity = other.capacity;

    // leave the remaining in a valid empty state
    other.p_array = new int[2];
    other.size = 0;
    other.capacity = 2;
}

// move assignment operator - transfers ownership and handles self-assignment
IntList& IntList::operator=(IntList&& other) noexcept {
    if (this != &other) {
        delete[] p_array;  // Clean up

        // Transfer ownership
        p_array = other.p_array;
        size = other.size;
        capacity = other.capacity;

        // leave the remaining in a valid empty state
        other.p_array = new int[2];
        other.size = 0;
        other.capacity = 2;
    }
    return *this;
}

// destructor
IntList::~IntList() {
    delete[] p_array;
}

// adds the line number to the end of the list
void IntList::append(int lineNumber) {
    if (isFull()) {
        resize();
    }
    p_array[size] = lineNumber;
    size++;
}

//  List deconstructor; removes all elements from the array
void IntList::clear() {
    delete[] p_array;
    capacity = 2;
    size = 0;
    p_array = new int[capacity];
}

// returns the size of the array
size_t IntList::getSize() const {
    return size;
}

// Resizes array, starting at 2 and doubles when full
void IntList::resize() {
    if (capacity == 0) {
        capacity = 2;
    } else {
        capacity *= 2;
    }

    // inits the new arrawy when full
    int* newData = new int[capacity];

    // copy to new array
    for (size_t i = 0; i < size; i++) {
        newData[i] = p_array[i];
    }

    // clean up old array and set new as current
    delete[] p_array;
    p_array = newData;
}

// empty check
bool IntList::isEmpty() const {
    return size == 0;
}

// capacity check
bool IntList::isFull() const {
    return size == capacity;
}

//  print statement to output the line
void IntList::print(std::ostream& os) const {
    for (size_t i = 0; i < size; i++) {
        os << p_array[i];
        if (i < size - 1) {
            os << " ";
        }
    }
}

// returns element x at index y
int IntList::getElementAt(size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return p_array[index];
}