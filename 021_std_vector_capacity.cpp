#include <iostream>
#include <vector>

void printStats(const std::string& label, const std::vector<int>& vec) {
    std::cout << label 
    << " -> Size: " << vec.size() 
    << " | Capacity: " << vec.capacity() << "\n";
}

int main() {
    std::vector<int> numbers(10, 42); // Size: 10, filled with 42
    numbers.reserve(20);              // Explicitly push capacity to 20
    
    printStats("Before:", numbers);   // Size: 10, Capacity: 20
              
    // Call reserve with a value smaller than current capacity
    numbers.reserve(5);
    printStats("After:", numbers);   // Size: 10, Capacity: 20

    // No change is seen. When you call numbers.reserve(5) on a vector that already has a capacity of 20, 
    // the call is completely ignored, and the vector remains untouched.
    

    numbers.shrink_to_fit(); // Recommended
    // 1. This is a non-binding request to the compiler to reduce the capacity to match the current size. In your case, it would attempt to drop the capacity from 20 down to 10.
    printStats("Shrink to fit:", numbers);   // Size: 10, Capacity: 10

    numbers.reserve(20);
    printStats("Reserve 20:", numbers);   // Size: 10, Capacity: 20

    // The swap trick
    std::vector<int>(numbers).swap(numbers);
    printStats("Swap Trick:", numbers);   // Size: 10, Capacity: 10
    // std::vector<int>(numbers) creates a temporary copy of your original vector.
    // The copy only allocates enough memory to hold the actual elements currently inside it.
    // numbers then swaps internal memory pointers, sizes, and capacities with the temporary copy.
    // At the very end of the semicolon, the temporary vector goes out of scope and is automatically destroyed.

    // Resize interaction
    // Resize will increase capacity together with size for n > capacity
    numbers.resize(20);
    printStats("Resize 20:", numbers);   // Size: 20, Capacity: 20

    // Resize will not decrease capacity when n < capacity
    numbers.resize(10);
    printStats("Resize 10:", numbers);   // Size: 10, Capacity: 20

    // Clear will not impact capacity
    numbers.clear();
    printStats("Clear:", numbers);   // Size: 0, Capacity: 20

    // Empty initializer assignment
    numbers = {};
    // Assigning an empty initializer list behaves differently depending on the compiler.
    // It usually forces the vector to completely release its memory, dropping both size() and capacity() to 0.
    printStats("Empty initializer assignment:", numbers);   // Size: 0, Capacity: 0 (Maybe)

    return 0;
}

// Note: A non-binding request means it is a request, not a command.
// The compiler's implementation is technically allowed to completely ignore your request if it chooses to.
// This usually happens if:
// The amount of memory saved is too small to care about.
// The system's memory allocator naturally rounds up block allocations anyway 
// (e.g., if you ask to shrink to 10 elements, but the system allocator only gives out memory 
// in chunks that fit 16 elements, your capacity might only drop to 16).
