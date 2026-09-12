#include <iostream>

int* findMinPtrInArray(int* arrayPtr, int size)
{
    // Start off with nullptr for safety and also signifies we couldn't find a minimum
    int* minValuePtr = nullptr;

    // Safety for 0 size
    if (size == 0) return minValuePtr; // Just return the nullptr

    // Use the first element as current minimum
    // int minValue = *arrayPtr; // If you have a pointer, you don't need to track the value
    minValuePtr = arrayPtr;

    // It is generally better to avoid manual pointer arithmetic when working with arrays in modern programming
    for (int i = 1; i < size; ++i)
    {
        // if (arrayPtr[i] < minValue) // Use pointer directly instead
        if (arrayPtr[i] < *minValuePtr) 
        {
            // minValue = *arrayPtr; // Use pointer directly instead
            // Get the pointer to an array element. It requires the address of operator.
            minValuePtr = &arrayPtr[i]; 
        }
    }

    return minValuePtr;
}

int main()
{
    int numbers[] = {56, 30, 88, 17, 3};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int* minPtr = findMinPtrInArray(numbers, size);
    std::cout << "The minimum value in the array is: " << *minPtr << std::endl;
}

// Note: In low-level systems, custom memory allocators, or embedded drivers, pointer arithmetic is favourable since 
// we can do the following:
// Managing Unstructured, Arbitrary Memory Blocks 
// Direct Interaction with Memory-Mapped I/O (MMIO) 
// Stripping Away Runtime Overhead