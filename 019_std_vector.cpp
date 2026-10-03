#include <iostream>
#include <vector> // Required header

int main() {
    // 1. Initialize a vector of integers with 3 elements
    std::vector<int> numbers = {10, 20, 30};

    // 2. Add elements to the end (it resizes automatically)
    numbers.push_back(40);
    numbers.push_back(50);

    // 3. Access elements just like a raw array
    std::cout << "First element: " << numbers[0] << "\n"; // Outputs 10
    std::cout << "Size of vector: " << numbers.size() << "\n"; // Outputs 5

    // 4. Modify an element
    numbers[1] = 99;

    return 0; 
    // 5. RAII TRIGGERED: 'numbers' goes out of scope here.
    // All heap memory allocated by the vector is safely deleted automatically.
}

// This is the C++ standard version of DynamicArray that we have tried to build in exercise 017 and 018.
