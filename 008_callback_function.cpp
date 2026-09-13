#include <iostream>

// Practice Problem: Define two simple functions: multiply(int, int) and subtract(int, int). 
// Write a function called compute_result that takes three arguments: 
// two integers and a function pointer (which must match the signature of multiply or subtract). 
// Inside compute_result, use the function pointer to perform the operation on the two integers and return the result.
// Use compute_result to call both multiply and subtract.

int multiply(int a, int b)
{
    return a * b;
}

int subtract(int a, int b)
{
    return a - b;
}

// Function that takes a function pointer (callback) as an argument
int compute_result(int a, int b, int (*ptr_func)(int,int))
{
    return (*ptr_func)(a, b);
}

// Modern C++ type alias (Recommended)
using CallbackType = int(*)(int, int);

// Legacy C-style typedef
typedef int (*CallbackTypeLegacy)(int, int);

// Typedef simplification
int sum_both_results(int a, int b, CallbackType ptr_func, CallbackTypeLegacy ptr_func2)
{
    return ptr_func(a, b) + ptr_func2(a, b);
}

int main()
{
    int x = 50;
    int y = 10;

    // Pass the multiply function's address (decayed name)
    int product = compute_result(x, y, multiply);
    std::cout << "Multiplication result: " << product << std::endl; 

    // Pass the subtract function's address (decayed name)
    int difference = compute_result(x, y, subtract);
    std::cout << "Subtraction result: " << difference << std::endl; 

    int sum_both = sum_both_results(x, y, multiply, subtract);
    std::cout << "Sum both result: " << sum_both << std::endl; 

    // Bonus: Lambda
    int sum = compute_result(x, y, [](int x, int y){ 
        return x+y;
    });
    std::cout << "Addition result: " << sum << std::endl; 

    return 0;
}

// With a callback, the relationship is inverted: 
// Your Code passes a pointer to your function into a Library Function.
// The Library Function runs its generic routines.
// At a specific moment, the Library Function reaches back up and executes your code