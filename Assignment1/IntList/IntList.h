//
// Created by Alex Sutherland on 2025-05-19.
//

#ifndef INTLIST_H
#define INTLIST_H

#include <iostream>

/**
 * @class IntList
 * @brief A dynamic array that doubles when capacity is reached
 */
class IntList {
private:
    int* p_array;         ///< Pointer to the dynamic array
    size_t size;        ///< Number of elements currently stored
    size_t capacity;    ///< Size of the dynamic array currently allocated

public:
    /**
     * @brief Default constructor - initializes empty list with capacity 2
     */
    IntList();

    /**
     * @brief Deep copy constructor
     */
    IntList(const IntList& other);

    /**
     * @brief Copy assignment - performs deep copy with self-assignment
     * @return Reference to this IntList
     */
    IntList& operator=(const IntList& other);

    /**
     * @brief Move constructor - transfers ownership of dynamic array

     */
    IntList(IntList&& other) noexcept;

    /**
     * @brief Move assignment operator - transfers ownership and handles self-assignment
     * @return Reference to this IntList
     */
    IntList& operator=(IntList&& other) noexcept;

    /**
     * @brief Destructor
     */
    ~IntList();

    /**
     * @brief Appends lineNumber to the end of the list, resizing if necessary
     */
    void append(int lineNumber);

    /**
     * @brief Removes all elements and deallocates memory
     */
    void clear();

    /**
     * @brief Returns the number of integers stored
     */
    size_t getSize() const;

    /**
     * @brief Resizes array starting at 2 then doubles when full
     */
    void resize();

    /**
     * @brief Checks if size is 0
     */
    bool isEmpty() const;

    /**
     * @brief Checks if size is equal to capacity
     */
    bool isFull() const;

    /**
     * @brief prints the line output
     */
    void print(std::ostream& os) const;

    /**
     * @brief Returns element at the specified index
     */
    int getElementAt(size_t index) const;
};

#endif // INTLIST_H