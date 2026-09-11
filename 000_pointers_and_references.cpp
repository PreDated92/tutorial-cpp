// Pointers and References
#include <iostream>

//A. Passing Arguments by Reference to Functions
void increment(int& number) {
    number++; // Modifies the original variable passed into it
}

int main() {
    int a = 10;
    int b = 20;

    int* ptr = &a; // int* is a pointer type, &a means address of a
    int& ref = a; // int& is a reference type, ref is an alias for a
    // Note: Spacing does not change functionality. int& x, int &x, and int & x are completely identical to the compiler
    // int& denotes an lvalue reference to an integer

    ptr = &b; // shifts the pointer ptr so it now stores the memory address of b.
    ref = b; // since ref is a, so this line is a = b;
    // references cannot be rebound
    // asking for the value of ref returns the value of a

    increment(ref); //ref is passed by reference so ref (which is a) is incremented by 1

    // *ptr is dereferencing ptr
    std::cout << "a: " << a << ", b: " << b << ", *ptr: " << *ptr << ", ref: " << ref << std::endl;
    // a: 21, b: 20, *ptr: 20, ref: 21
    return 0;
}
