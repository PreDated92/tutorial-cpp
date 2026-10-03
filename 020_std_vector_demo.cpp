#include <iostream>
#include <vector>

    // vec.size() vs vec.capacity()
    // vec.size():      Returns the actual number of elements currently stored in the vector.
    // vec.capacity():  Returns the total memory allocated (expressed in number of elements) 
    //                  before the vector must reallocate space

void printStats(const std::string& label, const std::vector<int>& vec) {
    std::cout << label 
    << " -> Size: " << vec.size() 
    << " | Capacity: " << vec.capacity() << "\n";
}

void push_back_reallocation_demo(std::vector<int>& vec) {
    vec.push_back(10);
    printStats("After 1 push_backs ", vec); // After 1 push_backs  -> Size: 1 | Capacity: 1
    vec.push_back(20);
    printStats("After 2 push_backs ", vec); // After 2 push_backs  -> Size: 2 | Capacity: 2
    vec.push_back(30);
    printStats("After 3 push_backs ", vec); // After 3 push_backs  -> Size: 3 | Capacity: 4
    vec.push_back(40);
    printStats("After 4 push_backs ", vec); // After 4 push_backs  -> Size: 4 | Capacity: 4
    vec.push_back(50);
    printStats("After 5 push_backs ", vec); // After 5 push_backs  -> Size: 5 | Capacity: 8

    // Notice that the allocation grows in a doubling manner.

    // Compiler / Library	Growth Factor	Example Chain (Starting at 1)
    // GCC / Clang          2.0             1 > 2 > 4 > 8 >	16 > 32 > 64
    // MSVC                 1.5             1 > 2 > 3 > 4 > 6 > 9 > 13
     
    // MSVC's growth factor with integer truncation is used because of Memory Reusability.
    // When a vector grows, it allocates a new chunk of memory elsewhere and releases the old chunk.
    // If you use a growth factor of 2, the new memory block required is always larger than all 
    // previously allocated blocks combined. The computer can almost never reuse the memory slots 
    // the vector just abandoned.
    // If you use a growth factor of 1.5, after a few reallocations, the sum of the previously freed blocks 
    // becomes large enough to hold the next new block. This makes your program much more memory-efficient 
    // and friendly to the system's memory manager.

}

int main() {
    // 1. Initial State
    std::vector<int> numbers;
    printStats("Initial empty vector", numbers);

    // 2. Demonstrating push_back
    push_back_reallocation_demo(numbers);

    // 3. Demonstrating reserve
    numbers.reserve(100); 
    printStats("After reserve(100)  ", numbers); 
    // Notice: Capacity jumped to 100, but Size stayed at 5!

    // 4. Demonstrating pop_back
    numbers.pop_back();
    numbers.pop_back();
    numbers.pop_back();
    printStats("After 3 pop_back    ", numbers);
    // Notice: Size goes down to 2, Capacity remains 100.

    // 5. Demonstrating resize
    numbers.resize(5);
    printStats("After resize(5)     ", numbers);
    // Notice: Size is now 5. The 3 new spots are filled with 0.
    std::cout << "Elements: ";
    for (int n : numbers) std::cout << n << " "; // Outputs: 10 20 0 0 0
    std::cout << "\n";

    return 0;
}

