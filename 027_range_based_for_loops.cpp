#include <iostream>
#include <vector>
#include <string>

int main() {
    // Introduced in C++11, the range-based for loop provides a clean, safe, and readable syntax to
    // iterate over all elements in a collection. It eliminates the need to manage array indices or
    // iterator increments manually, effectively preventing off-by-one errors.
    // It works seamlessly with standard arrays, std::string, and STL containers like
    // std::vector, std::map,and std::set.

    // for (range-declaration : range-expression)
    // range-declaration: Defines the variable that represents the current element in the loop.
    // range-expression: The collection or container you want to loop through.

    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Basic read-only loop (creates a copy of each element)
    for (int num : numbers) { 
        std::cout << num << " ";
    }

    // Best Practices: Choosing Your Loop Variable
    // How you declare the range-declaration variable drastically changes performance and behavior.
    // 1. auto
    // Creates copies. Avoid for heavy objects like std::string or vectors.
    // Best used for Primitive types (int, char, double).
    for (auto num : numbers) { 
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // 2. const auto&
    // No copies (Reference). Read-only window into the container.
    // Best used for Large objects/structures that you do not want to modify.
    std::vector<std::string> names = {"alice", "bob", "charlie"};
    for (const auto& name : names) {
        std::cout << name << "\n";
    }

    // 3. auto&
    // No copies (Reference). Modifies the collection directly.
    // Best used when you need to update or write data back into the container.
    for (auto& name : names) {
        name[0] = std::toupper(name[0]); // Capitalize first letter
        std::cout << name << "\n";
    }
}


