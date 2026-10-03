#include <iostream>
#include <memory>

struct Widget {
    Widget() { std::cout << "Widget Created\n"; }
    ~Widget() { std::cout << "Widget Destroyed\n"; }
    void do_something() { std::cout << "Doing something...\n"; }
};

void main_demo() {
    // While you can initialize it with a raw pointer using new, 
    // the preferred and safer method since C++14 is std::make_unique
    // Preferred creation (C++14)
    std::unique_ptr<Widget> ptr1 = std::make_unique<Widget>();

    // Compile error: 'make_unique' is not a member of 'std'
    // If C++ 14 is not available (C++11 compatible):
    std::unique_ptr<Widget> ptr(new Widget());
    
    // Note: One reason why you might want to use the old way is because of Custom Deleters.
    // It is required if managing files/C-APIs.

    // Accessing members (works just like a raw pointer)
    ptr1->do_something();
    (*ptr1).do_something();

    // Non-Copyable: The copy constructor and copy assignment operator
    // are explicitly deleted to prevent duplicate ownership.
    // std::unique_ptr<Widget> ptr2 = ptr1; // ERROR: Copying is banned!

    // Ownership of the underlying resource can be transferred to another std::unique_ptr using std::move().
    std::unique_ptr<Widget> ptr2 = std::move(ptr1); // OK: Ownership transferred

    // ptr1 is now empty (nullptr)
    if (!ptr1) {
        std::cout << "ptr1 no longer owns the Widget\n";
    }

     // ptr and ptr2 goes out of scope after return, automatically deleting the Widget
}

void two_owners_problem() {
    // Dynamically allocate a resource manually
    int* rawPtr = new int(42);

    // CRASH WARNING: Two separate unique_ptrs are given the same raw address
    std::unique_ptr<int> ptr1(rawPtr);
    std::unique_ptr<int> ptr2(rawPtr); 

    std::cout << "ptr1 points to: " << *ptr1 << "\n";
    std::cout << "ptr2 points to: " << *ptr2 << "\n";

    // UNDEFINED BEHAVIOR / CRASH HAPPENS HERE:
    // 1. ptr2 goes out of scope and calls 'delete rawPtr'. Memory is freed.
    // 2. ptr1 goes out of scope and tries to call 'delete rawPtr' AGAIN. 
    // This is a "Double Free" error, causing the program to crash.
    // Console prints "free(): double free detected in tcache 2"
}

int main() {
    main_demo();
    two_owners_problem();

    return 0;
}