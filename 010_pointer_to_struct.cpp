#include <iostream>

struct Rectangle {
    int length;
    int width;
};

int main() {
    // Allocates on the stack
    Rectangle rect = {10, 5};
    
    // Declare and initialize a pointer to the structure
    Rectangle* rect_ptr = &rect; 

    // (*ptr).member;  // 1. Manually dereference the pointer, then access the member
    // ptr->member;    // 2. The exact same behavior, but cleaner and preferred
    std::cout << "Original dimensions: " << rect_ptr->length 
              << " x " << rect_ptr->width << std::endl;

    // Modify members using the arrow operator
    rect_ptr->length = 15;
    rect_ptr->width = 7;

    std::cout << "New dimensions: " << rect.length 
              << " x " << rect.width << std::endl;

    return 0;
}