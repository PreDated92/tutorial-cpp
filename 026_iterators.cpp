#include <iostream>
#include <list>
#include <vector>

void iterator_demo() {
    std::list<int> myList = {10, 20, 30, 40};

    // ==========================================
    // METHOD 1: Traditional Index-Based Loop
    // ==========================================
    /* 
    for (int i = 0; i < myList.size(); ++i) {
        std::cout << myList[i] << " "; 
    }
    
    COMPILER ERROR: std::list does not support the [] operator 
    because its elements are scattered across memory, not sequential.
    */

    // In C++, an iterator is a pointer-like object that allows you to traverse and manipulate elements inside a 
    // Standard Template Library (STL) container (like vectors, lists, sets, and maps).
    // ==========================================
    //  METHOD 2: Explicit Iterator Loop
    // ==========================================
    std::cout << "Using explicit iterator: ";
    // A standard container range is half-open, typically represented as [begin, end).
    // begin() returns an iterator pointing to the first element.
    // end() returns an iterator pointing to the element just past the last element (a sentinel/boundary marker).
    for (std::list<int>::iterator it = myList.begin(); it != myList.end(); ++it) {
        // Dereferencing (*it) gets the value
        std::cout << *it << " "; // Works perfectly by jumping node-to-node
    }
    std::cout << "\n";


    // ==========================================
    //  METHOD 3: Range-Based For Loop (Modern C++)
    // ==========================================
    // The modern range-based for loop looks like a standard loop, but the compiler secretly 
    // translates it into the exact iterator code shown in Method 2.
    std::cout << "Using range-based loop:  ";
    for (const auto& val : myList) {
        std::cout << val << " "; 
    }
    std::cout << "\n";
}

void iterator_invalidation() {
    std::vector<int> vec = {1, 2, 3};
    
    // 1. Get an iterator pointing to the first element
    auto it = vec.begin(); 
    
    // 2. Modify the container (triggering reallocation)
    vec.push_back(4); 
    
    // 3. CRASH / UNDEFINED BEHAVIOR: 'it' still points to the old, deleted memory!
    std::cout << *it << std::endl; 

    // Most STL container modification functions (like erase or insert) return a new, 
    // valid iterator pointing to the element immediately following the removed or inserted item.
    // You should always assign the result back to your loop iterator.
}

int main() {
    iterator_demo();
    iterator_invalidation();
    return 0;
}

// Iterators act as a bridge between containers and STL algorithms. 
// By using iterators, a single algorithm like std::sort() or std::find() can work seamlessly across 
// completely different data structures without needing to know their underlying implementation.




