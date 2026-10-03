// The Core Components
// Move semantics relies on three main technical building blocks:
// 1. Rvalue References (&&)
// 2. The Move Constructor and Move Assignment Operator
// 3. std::move

#include <iostream>
#include <utility> // For std::move

class Buffer {
private:
    int* data;
    size_t size;

public:
    // Regular Constructor
    Buffer(size_t sz) : size(sz) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) data[i] = i + 1; // Fill with 1, 2, 3...
    }

    // Destructor
    ~Buffer() { delete[] data; }

    // Move Constructor
    Buffer(Buffer&& other) noexcept : data(other.data), size(other.size) {
        // An rvalue reference (written as T&&) binds specifically to these temporary objects, 
        // alerting the compiler that it is safe to strip resources from them
        other.data = nullptr; // Reset the source so it won't delete our memory
        other.size = 0;
    }
    // Note : data(other.data), size(other.size) is member initializer list syntax.

    void print() const {
        if (!data) { std::cout << "Empty\n"; return; }
        for (size_t i = 0; i < size; ++i) std::cout << data[i] << " ";
        std::cout << "\n";
    }
};

int main() {
    // Introduced in C++11, move semantics is a language feature that allows the compiler to 
    // transfer resource ownership (like dynamic memory, file handles, or sockets) from a 
    // temporary or expiring object directly to a new object, instead of creating an expensive deep copy

    // 1. Create the initial buffer (allocates dynamic memory)
    Buffer b1(5); 
    std::cout << "b1 elements: "; b1.print(); // Prints: 1 2 3 4 5

    // 2. Cast b1 to an rvalue, triggering b2's move constructor
    Buffer b2 = std::move(b1); 

    // 3. Check the results
    std::cout << "b2 elements: "; b2.print(); // Prints: 1 2 3 4 5
    std::cout << "b1 status:   "; b1.print(); // Prints: Empty

    return 0;
}


// Note: Marking move operations as noexcept is highly recommended so that standard library containers 
// (like std::vector) can safely use them during memory reallocations