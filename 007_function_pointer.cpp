#include <iostream>

int add(int a, int b)
{
    return a + b;
}

int main()
{
    // Declare a function pointer
    int (*add_ptr)(int, int) = add;

    // It defines a variable named add_ptr that can store the memory address of any function 
    // that takes two int arguments and returns an int

    int result1 = add_ptr(10, 5); 
    int result2 = (*add_ptr)(25, 75); // Equivalent call using explicit dereference

    // When you use the explicit dereference syntax *func_ptr, it yields a function designator (the underlying function lvalue).
    // Except when used with sizeof or &, any function designator automatically decays right back into a function pointer

    std::cout << "Result 1 (10 + 5): " << result1 << std::endl;
    std::cout << "Result 2 (25 + 75): " << result2 << std::endl;

    return 0;
}