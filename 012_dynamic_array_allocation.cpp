#include <iostream>

int main()
{
    const int size = 5;
    int* array_ptr = new int[size];

    if (array_ptr == nullptr)
    {
        std::cerr << "Memory allocation failed!" << std::endl;
        return 1;
    }

    // Init array
    for (int i = 0; i < size; ++i)
    {
        *(array_ptr + i) = i;
    }

    std::cout << "Array contents: ";
    for (int i = 0; i < size; ++i)
    {
        std::cout << array_ptr[i];
        if (i == size - 1) break;
        std::cout << ", ";
    }
    std::cout << std::endl;

    // Cleanup
    delete[] array_ptr;
    array_ptr = nullptr;
}