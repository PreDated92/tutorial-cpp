// Pass-by-Pointer vs. Pass-by-Reference
#include <iostream>

// Requires dereferencing variables inside the function to alter original memory values
void swapByPointerValue(int* ptr1, int* ptr2)
{
    if (ptr1 == nullptr || ptr2 == nullptr) return; // Defensive null check
    int temp = *ptr1; // temp holds the value from ptr1
    *ptr1 = *ptr2;    // ptr1 value is now the value of ptr2
    *ptr2 = temp;     // ptr2 value is now the value of temp
}

// Cleaner syntax; acts exactly like working with original scope variables
void swapByReference(int& ref1, int& ref2)
{
    int temp = ref1;
    ref1 = ref2;
    ref2 = temp;
}

void unableToSwapByValue(int ref1, int ref2)
{
    // This doesn't work because ref1 and ref2 are just copies of x and y.
    // Swapping them does not affect x and y
    int temp = ref1;
    ref1 = ref2;
    ref2 = temp;
}

// Bonus: Pass by Reference to Pointer
// This implies that Pass-by-Pointer is creating a copy of the pointer 
void swapByReferenceToPointer(int*& refPtr1, int*& refPtr2) 
{
    if (refPtr1 == nullptr || refPtr2 == nullptr) return;
    int* temp = refPtr1; // temp holds the address from refPtr1
    refPtr1 = refPtr2;   // refPtr1 now points to refPtr2's address
    refPtr2 = temp;      // refPtr2 now points to temp's (original refPtr1) address
}

int main() {
    int x = 100, y = 500;

    swapByPointerValue(&x, &y); // Pass by pointer requires the address
    std::cout << "After Swap by Pointer -> x: " << x << ", y: " << y << std::endl; // 500, 100

    swapByReference(x, y); // Pass by reference requires the variable
    std::cout << "After Swap by Reference -> x: " << x << ", y: " << y << std::endl; // 100, 500

    unableToSwapByValue(x, y); // Pass by value requires the variable
    std::cout << "After Swap by Value -> x: " << x << ", y: " << y << std::endl; // 100, 500

    // Bonus
    int* p1 = &x; int* p2 = &y;
    std::cout << "\n--- Before Pointer-to-Pointer Swap ---" << std::endl;
    std::cout << "p1 points to x with value of: " << *p1 << std::endl; // 100
    std::cout << "p2 points to y with value of: " << *p2 << std::endl; // 500

    swapByReferenceToPointer(p1, p2); // Pass by Reference to Pointer requires the pointer variables
    // Extra note: you cannot do swapByReferenceToPointer(&x, &y); because &x and &y are rvalues (temporary)
    // The idea is to swap p1 to &y and p2 to &x after the function, so they have to be declared as variables first

    std::cout << "\n--- After Pointer-to-Pointer Swap ---" << std::endl;
    std::cout << "p1 now points to y with value of: " << *p1 << std::endl; // 500 (Points to y now!)
    std::cout << "p2 now points to x with value of: " << *p2 << std::endl; // 100 (Points to x now!)
    
    // Notice that x and y themselves DID NOT swap!
    std::cout << "Original x: " << x << ", y: " << y << std::endl; // 100, 500
    
    return 0;
}
