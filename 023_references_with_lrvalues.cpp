#include <iostream>

void printName(const int& lref) {
    std::cout << "Lvalue reference: " << lref << std::endl;
}

void printName(int&& rref) {
    std::cout << "Rvalue reference: " << rref << std::endl;
}

int main() {
    int x = 50;

    // Lvalue Reference (&) -> Binds to lvalues
    int& lref = x; 
    // int& bad_lref = 50; // Error: standard lvalue reference can't bind to an rvalue

    // Const Lvalue Reference -> Exceptional rule: can bind to rvalues read-only
    const int& const_lref = 50; 

    // Rvalue Reference (&&) -> Binds strictly to temporary rvalues
    int&& rref = 50; 
    // int&& bad_rref = x; // Error: rvalue reference cannot bind to an lvalue

    // Function Overloading Resolution
    printName(x);    // Triggers Lvalue version (x is a variable)
    printName(50);   // Triggers Rvalue version (50 is a temporary literal)
    printName(lref); // Triggers Lvalue version 
    // Reason: 'lref' is a named variable pointing to 'x'. It is a classic lvalue.
    printName(const_lref); // Triggers Lvalue version 'const_lref' is also a named variable. 
    printName(rref); // Triggers Lvalue version!!
    // Reason: Even though 'rref' binds to a temporary (50), the variable 'rref' 
    // itself has a name and an address. Therefore, the expression 'rref' evaluates 
    // as an lvalue.
    printName(std::move(rref));  // Triggers: Rvalue version!
    // std::move doesn't actually move anything at runtime
    // it performs a static cast that turns an lvalue expression into an rvalue expression 
    // (specifically an xvalue, or "eXpiring value").

}
