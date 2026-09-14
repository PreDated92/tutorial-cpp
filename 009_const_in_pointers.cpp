#include <iostream>

int main()
{
    int x = 5;
    const int* ptr_to_const = &x;
    int* const const_ptr = &x;

    *const_ptr = 6;
    std::cout << "const_ptr's value can be changed, x = " << x << std::endl;
    std::cout << "ptr_to_const's value cannot be changed";

}