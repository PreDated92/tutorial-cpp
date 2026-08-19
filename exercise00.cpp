// Pointers and References
#include <iostream>

int main() {
    int a = 10;
    int b = 20;

    int* ptr = &a; // int* is a pointer type, &a means address of a
    int& ref = a; // int& is a reference type, ref is an alias for a

    ptr = &b; // shifts the pointer ptr so it now stores the memory address of b.
    ref = b; // since ref is a, so this line is a = b;
    // references cannot be rebound
    // asking for the value of ref returns the value of a

    // *ptr is dereferencing ptr
    std::cout << "a: " << a << ", b: " << b << ", *ptr: " << *ptr << ", ref: " << ref << std::endl;
    return 0;
}

// a: 20, b: 20, *ptr: 20, ref: 20