#include <iostream>

void printValue(int* pointer)
{
    if (pointer == nullptr)
    {
        std::cout << "Pointer is null" << std::endl; 
    }
    else
    {
        std::cout << "Pointer value is: " << *pointer << std::endl;
    }
}

int main()
{
    int* dangerous_ptr;
    printValue(dangerous_ptr); // Attempt to read random memory address
    int* safe_ptr = nullptr;
    printValue(safe_ptr); // Pointer is null
    int a;
    int* ptr = &a;
    printValue(ptr); // Pointer value is: garbage value!
    *ptr = 77; // Equivalent to a = 77;
    printValue(ptr); // Pointer value is: 77
}