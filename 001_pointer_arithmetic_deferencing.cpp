// Pointer Arithmetic
#include <iostream>

int sumArray(int* arr, int size) 
{
    int total = 0;
    for (int i = 0; i < size; ++i) 
    {
        total += *arr; // Access value at current pointer address
        arr++;         // Advance pointer to the next element
        // Note that the compiler knows how many bytes to advance because it knows the data type.

        // Step    CodePointer              Address (Hex)   Visual Memory Gap
        // Start   int* ptr = &numbers[0];  0x1000          Points to 1st item
        // Step 1  ptr++;                   0x1004          Jumps 4 bytes to 2nd item
        // Step 2  ptr++;                   0x1008          Jumps 4 bytes to 3rd item
        // Step 3  ptr++;                   0x100C          Jumps 4 bytes to 4th item
    }
    return total;
}

// Changing Value via Pointer and Double Pointer
void incrementArray(int* arr)
{
    *arr += 1;
    arr++;
    int** ptr = &arr;
    **ptr += 2;
}

int main() 
{
    int numbers[] = {5, 10, 15, 20, 25}; // Created on the stack
    // Same energy but created on the heap
    // int* numbers = new int[5] {5, 10, 15, 20, 25};

    std::cout << "Sum: " << sumArray(numbers, 5) << std::endl; // Should print 75

    incrementArray(numbers);
    std::cout << "Incremented arr: " << numbers[0] << ", " << numbers[1];
    return 0;
}
