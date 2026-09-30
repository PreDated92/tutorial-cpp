#include<iostream>

// The primary rule of C++ memory safety is that the pointed-to object must outlive the pointer variable.
// If the object is destroyed while a pointer still references its memory address, 
// the pointer becomes a dangling pointer, and dereferencing it causes undefined behavior (UB)
void dangling_pointer_example() {
    int* ptr = nullptr; // Pointer variable 'ptr' begins its lifetime here
    {
        int local_var = 42; 
        ptr = &local_var; // 'ptr' points to 'local_var'
    } // 'local_var' lifetime ENDS here (stack memory freed)

    // 'ptr' still exists! Its lifetime is active until the end of the function.
    // *ptr = 10; <-- UNDEFINED BEHAVIOR! 'ptr' is now a dangling pointer.
} // Pointer variable 'ptr' lifetime ends here.

// Common Lifetime Disasters (Dangling Pointers)
// A. Returning a Pointer to Local Stack Memory
int* getDanglingPointer() {
    int secret = 100;
    return &secret; // Bad: 'secret' dies as soon as the function returns
}

// B. Manual Deallocation (delete) Without Nullifying
void manual_deallocation_example(){
    int* ptr = new int(5);
    delete ptr; // Pointed-to object is dead. 

    // ptr is now a dangling pointer!
    // *ptr = 20; <-- Undefined Behavior!

    ptr = nullptr; // Clear it to prevent accidental use
}

// To eliminate manual tracking and prevent dangling pointers, modern C++ uses Smart Pointers (from <memory>).
// They bind the lifetime of the pointer and the data together automatically using the 
// Resource Acquisition Is Initialization (RAII) idiom
// std::unique_ptr: Represents exclusive ownership. The managed object is destroyed automatically 
//                  as soon as the unique_ptr variable goes out of scope.
// std::shared_ptr: Represents shared ownership. Multiple pointers can point to the same object. 
//                  The object is destroyed only when the last shared_ptr pointing to it goes out of scope 
//                  (via reference counting).
// std::weak_ptr:   A non-owning observer to an object managed by a shared_ptr. 
//                  It does not prevent the object from dying, but it can safely check if the object is still alive 
//                  before accessing it.