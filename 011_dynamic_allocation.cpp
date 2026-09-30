#include <iostream>

int main() {
    // Dynamically allocate a single float on the heap
    float* float_ptr = new float; 
    
    // Check if allocation was successful (optional but good practice)
    if (float_ptr == nullptr) 
    {
        std::cerr << "Memory allocation failed!" << std::endl;
        return 1;
    }

    // Initialize the allocated memory
    *float_ptr = 3.14f;

    std::cout << "Dynamically allocated float value: " << *float_ptr << std::endl;
    std::cout << "Address on heap: " << float_ptr << std::endl;

    // Deallocate the memory to prevent memory leak
    delete float_ptr;
    
    // Set the pointer to nullptr after deletion to avoid dangling pointer issues
    float_ptr = nullptr;

    return 0;
}

// For Dynamic pointers, the new keyword bypasses normal scoped memory and allocates space on the heap (dynamic memory). 
// The pointer p lives on the stack, but it points to a completely separate address on the heap. 
// This memory lives forever until you explicitly tell it to die. It owns the resource. 
// If the function ends and p goes out of scope, the heap memory remains allocated, causing a memory leak. 
// You must manually call delete p; to free it. 
// The object stays valid until you delete it. The danger is forgetting to delete it, or deleting it twice.
