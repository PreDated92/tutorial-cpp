// C++ differentiates between two types of expressions:
// Lvalues: Named objects that occupy a identifiable location in memory (e.g., int x = 5;, where x is an lvalue).
// Rvalues: Temporary values or objects that are about to be destroyed (e.g., the result of x + 5 or a temporary string returned from a function).

void main_demo(){
    // Example 1: Standard initialization
    int x = 10; 
    // 'x' is an lvalue (it has a location in memory).
    // '10' is an rvalue (it is a literal value with no persistent address).

    // Example 2: Assignment
    int y = x;
    // 'y' is an lvalue.
    // 'x' here is evaluated as an rvalue to read its content and assign it to y.

    // Example 3: Arithmetic Expression
    int sum = x + y;
    // 'sum' is an lvalue.
    // The expression 'x + y' produces a temporary result (e.g., 20), making it an rvalue.

    // Example 4: Pointers
    int* ptr = &x; 
    // 'ptr' is an lvalue.
    // '&x' returns a temporary address, which is an rvalue.
    // '*ptr' is an lvalue (it dereferences the pointer to a valid memory slot).

    // Because rvalues lack a persistent memory location, you cannot assign values to them or take their addresses directly:
    // INVALID: The left side must be an lvalue
    // 10 = x;       // Error: literal '10' is an rvalue.
    // x + y = 20;   // Error: temporary result of 'x + y' is an rvalue.

    // INVALID: You cannot take the address of an rvalue
    // int* p1 = &(x + y);  // Error: Cannot take the address of a temporary rvalue.
    // int* p2 = &5;        // Error: Cannot take the address of a literal.
}

int global_var = 42;

// Returns by VALUE
int getRValue() {
    return global_var; // Returns a temporary copy
}

// Returns by REFERENCE
int& getLValue() {
    return global_var; // Returns the actual memory slot
}

int main() {
    main_demo();
    // Example 5: Return by value is an rvalue
    int a = getRValue(); // Valid: assigning rvalue to lvalue
    // getRValue() = 100; // Error: cannot assign to an rvalue

    // Example 6: Return by reference is an lvalue
    int b = getLValue(); // Valid
    getLValue() = 100;   //  Valid: Updates 'global_var' directly to 100!

    return 0;
}

// Note there are more subcategories of lvalues and rvalues. They are shown below:
//                 Expression
//                /          \ 
//         glvalue            rvalue
//        /       \          /      \ 
//     lvalue        xvalue        prvalue
//
// glvalue (generalized lvalue): An expression that has an identity (a location in memory).
// rvalue: An expression that can be moved from (its data can be stolen).
// prvalue (pure rvalue): Has no identity, but can be moved. (e.g., 42, x + y, Widget{}).
// xvalue (eXpiring value): Has an identity, and can be moved. This usually happens when you turn an lvalue into an rvalue using std::move().
