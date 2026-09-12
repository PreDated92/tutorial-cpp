#include <iostream>

// Note that int array[] is just syntactic sugar for int* array
int unableToFindSizeOf(int array[])
{
    // This doesn't work because of array to pointer decay
    // The method only receives array's first element pointer
    // Compiler will complain: 
    // warning: 'sizeof' on array function parameter 'array' will return size of 'int*' [-Wsizeof-array-argument]
    int size = sizeof(array) / sizeof(array[0]);
    // sizeof(array) will give 8, if using a 64 bit architecture. It is the pointer size.
    // sizeof(array[0]) will give 4, since int is 4 bytes.
    return size; // returns 2
}

// Pass raw array by reference, requires the size to be defined
// This function will ONLY accept an integer array of exactly size 5
void printReverseValueByRef(int (&arrRef)[5])
{    
    std::cout << "--- Printing by Ref ---" << std::endl;
    
    int size = sizeof(arrRef) / sizeof(arrRef[0]);
    for (int i = size - 1; i >= 0; --i)
    {
        std::cout << "Element " << i << " has value " << arrRef[i] << std::endl;
    }
    std::cout << std::endl;
}

// Pass raw array by pointer, array to pointer decay is implicit
// Size is needed as the method has no way of knowing how long the raw array is
// Using int[] arrPtr would work here as well
void printReverseValueByPtr(int* arrPtr, int size)
{
    std::cout << "--- Printing by Pointer ---" << std::endl;
    
    arrPtr = arrPtr + size - 1; // Modify in place to the last element
    for (int i = size - 1; i >= 0; --i)
    {
        std::cout << "Element " << i << " has value " << *arrPtr-- << std::endl;
        // Decrement after print
    }
    std::cout << std::endl;
}

bool compare(int* arrPtr, int* arr2Ptr) 
{
    return arrPtr == arr2Ptr;
}

int main()
{
    int numbers[] = {1, 2, 3, 4, 5};
    int incorrectSize = unableToFindSizeOf(numbers);
    std::cout << "The size of numbers is " << incorrectSize << std::endl << std::endl; // incorrectSize is 2;

    printReverseValueByRef(numbers);

    int size = sizeof(numbers) / sizeof(numbers[0]);
    printReverseValueByPtr(numbers, size);
    // Note that numbers is passed instead of &numbers due to array to pointer decay

    // Comparing
    int* numberPtrFromDecay = numbers; // No cast is needed if we want to get the pointer from an array
    int* numberPtrFromFirstElem = &numbers[0];
    bool same = compare(numberPtrFromDecay, numberPtrFromFirstElem);
    std::cout << "numberPtrFromDecay and numberPtrFromFirstElem are the same: " << (same ? "YES" : "NO");
}

// Fun fact:
// When looping through complex data structures using standard template library (STL) iterators 
// (e.g., std::vector<int>::iterator), ++ is an overloaded function.
// ++i modifies the iterator in place and returns a reference.
// i++ must create a full copy of the iterator object, increment the original, and then return the temporary copy
//
// In C++, it is widely considered a best practice to default to pre-increment (++i). 
// It ensures you never suffer a hidden performance penalty when transitioning from basic integer loops 
// to complex object iterators. This is also true for decrement (--).