#include <iostream>
#include <memory> // Required header for smart pointers

class MyClass {
public:
    MyClass() { std::cout << "Constructor called\n"; }
    ~MyClass() { std::cout << "Destructor called\n"; }
};

int main() {
    // 1. Create a shared pointer (Recommended way using std::make_shared)
    std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>();
    std::cout << "Count: " << ptr1.use_count() << "\n"; // Outputs 1

    // Unlike make_unique, make_shared is available in C++ 11
    // Instead of using std::shared_ptr<T>(new T()), always use std::make_shared<T>(). 
    // It is more efficient because it allocates the object memory and the control block in a single memory allocation
    // rather than two.

    {
        // 2. Share ownership by copying
        std::shared_ptr<MyClass> ptr2 = ptr1;
        std::cout << "Count inside block: " << ptr1.use_count() << "\n"; // Outputs 2
    } // ptr2 goes out of scope here, reference count decreases

    std::cout << "Count outside block: " << ptr1.use_count() << "\n"; // Outputs 1

    return 0;
} // ptr1 goes out of scope here. Count becomes 0, and Destructor is automatically called.

// The internal reference counter is thread-safe (uses atomic operations), 
// meaning you can safely copy or destroy pointers across different threads.
// You still need thread safety when modifying the contents of the pointer.

// If Object A holds a shared_ptr to Object B, and Object B holds a shared_ptr to Object A, 
// they will keep each other's reference count above zero forever, causing a memory leak. 
// To break these cycles, use std::weak_ptr

// Golden Rule of Smart Pointers
// Default to std::unique_ptr first. 
// It is lightweight, efficient, and handles the vast majority of memory management needs 
// (like class members or local factory methods).

// Only upgrade to std::shared_ptr if you explicitly require a single object 
// to have multiple, independent owners across your codebase where you cannot 
// predict which owner will outlive the others.