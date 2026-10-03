#include <iostream>

int main()
{
    int x = 5;
    const int* ptr_to_const = &x; // Pointer to constant integer
    int* const const_ptr = &x; // Constant pointer to integer
    const int* const const_ptr_to_const = &x; // Constant pointer to constant integer

    // The easiest way to understand any complex pointer declaration is to read it from right to left:
    // const_ptr_to_const = variable name
    // const = variable name is a const
    // * = pointer
    // const int = to a const int

    *const_ptr = 6;
    std::cout << "const_ptr's value can be changed, x = " << x << std::endl;
    std::cout << "ptr_to_const's value cannot be changed";
    std::cout << "const_ptr_to_const's value cannot be changed";

    // For references,  there are just 2 styles
    int& ref = x; // Reference or alias to integer
    const int& ref = x; // Const Reference, a read-only alias to an integer.
}

// Why do we need these consts?
// When designing functions, They allow you to enforce data security (read-only enforcement), 
// optimize performance (avoiding copying big data), and communicate your intent clearly to other developers.

// const int* ptr_to_const (Pointer to Constant Integer)
// What it tells the function: "You can look at this data, but you are not allowed to change it."
// Why it's important: It provides safety. When you pass large structures, classes, or arrays to a function,
// you pass them by pointer (or reference) to avoid the performance cost of copying them.
// However, passing a raw pointer allows the function to accidentally modify your original data.
// Adding const prevents this.

// int* const const_ptr (Constant Pointer to Integer)
// This variant is rarely used as a function parameter because it is mostly redundant.
// What it tells the function: 
// "You can change the value of the data, 
// but you cannot change this pointer to point to a different memory address."
// Why it's rarely useful in parameters: 
// In C and C++, function arguments are passed by value (copied). 
// If you pass a pointer into a function, the function gets a copy of that pointer. 
// If the function changes where its local copy points to, it doesn't affect the caller anyway.
// Where it does matter: 
// It is useful inside the function body for local variables if you want to ensure a pointer is safely locked
// to one specific variable for the duration of the function.

// const int* const const_ptr_to_const (Constant Pointer to Constant Integer)
// This is a combination of the first two. It locks down absolutely everything.
// What it tells the function: 
// "You cannot change the data, and you cannot change where this pointer points."
// Why it's used: 
// It provides the ultimate level of strictness. 
// It is used when you want to pass data safely (read-only) and you also want to strictly prevent the
// internal function logic from accidentally redirecting the local pointer variable.

// Without consts, a function can pass data via:
// 1. By value. 
// Signature: void f(Matrix m)
// It cannot modify the original since it copies the value. 
// How much data is copied depends on the copy constructor.
// 
// 2. By Pointer
// Signature: void f(Matrix* p)
// Can modify original. Fast.
// 
// 3. By Reference
// Signature: void f(Matrix& r)
// Can modify original. Also fast. 
// Usually preferred over pointer unless an optional parameter is needed with nullptr.
//
// With these consts, a function can pass data via 
// 1. By Pointer to Const
// Signature: void f(const Matrix* p)
// Cannot modify original. Fast. 
// Read-only, but requires checking for nullptr.
//
// 2. By Const Reference
// Signature: void f(const Matrix& r)
// Cannot modify original. Fast & Safe. 
// The absolute default choice for passing large objects/classes in C++.