#include <iostream>

class Buffer {
private:
    int* data;
    size_t size;

public:
    // Regular Constructor (Allocates memory)
    Buffer(size_t sz) : size(sz) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) data[i] = i + 1; // Fill with 1, 2, 3...
    }

    // Destructor (Frees memory)
    ~Buffer() { delete[] data; }

    // --- COPY SEMANTICS ---
    // Copy Constructor (Performs a Deep Copy)
    Buffer(const Buffer& other) : size(other.size) {
        std::cout << "[Copy Constructor Called] Allocating new memory...\n";
        
        // 1. Allocate entirely new heap memory for the copy
        data = new int[size]; 
        
        // 2. Loop through and copy every single element individually
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    void print() const {
        if (!data) { std::cout << "Empty\n"; return; }
        for (size_t i = 0; i < size; ++i) std::cout << data[i] << " ";
        std::cout << "\n";
    }
};

Buffer createBuffer() {
    return Buffer(5); // Returns a temporary rvalue
}

int main() {
    // 1. Create the initial buffer (allocates original memory)
    Buffer b1(5); 
    std::cout << "b1 elements: "; b1.print(); // Prints: 1 2 3 4 5

    // 2. Triggers the Copy Constructor
    // b2 becomes a completely independent clone of b1
    Buffer b2 = b1; 

    // 3. Both objects exist simultaneously with identical but separate data
    std::cout << "b2 elements: "; b2.print(); // Prints: 1 2 3 4 5
    std::cout << "b1 elements: "; b1.print(); // Prints: 1 2 3 4 5

    // 4. Passing a temporary rvalue directly to initialize a new object
    // 4.1. No copy or move constructor is called because of a mandatory compiler optimization 
    // introduced in C++17 called Guaranteed Copy Elision (specifically, RVO or Return Value Optimization.)
    
    // This uses Copy Elision (No copy constructor is called)
    Buffer b3 = createBuffer();

    // 4.2. This forces the rvalue match and calls the copy constructor fallback
    Buffer b4 = std::move(createBuffer());

    // 5. Using std::move on an lvalue turns it into an rvalue, 
    // but because there's no move constructor, it invokes the copy constructor anyway.
    Buffer b5 = std::move(b1);  

    return 0; // All buffers b1, b2, b3 and b4 safely deallocate their own separate heap arrays
}
