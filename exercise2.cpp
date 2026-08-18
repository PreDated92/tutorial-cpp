#include <iostream>
#include <string>
#include <utility>
#include <stdexcept>

// Templates exercise with Rule of Five
// UniversalOptional is a wrapper class meant to accept any data type (T) and manage its lifecycle.
template <typename T>
class UniversalOptional {
private:
    T* value_ptr = nullptr; // Dynamically stores the value if present

public:
    // Default constructor: creates an empty optional
    UniversalOptional() = default;

    // Destructor: clean up memory if a value exists
    ~UniversalOptional() 
    {
        reset();
    }

    // Constructor: Allocate memory on the heap and copy/move the value into it.
    UniversalOptional(T val)
    {
        value_ptr = new T(val);
    }

    // Copy Constructor
    UniversalOptional(const UniversalOptional& other)
    {
        if (other.has_value())
            value_ptr = new T(*other.value_ptr);
    }

    // Copy assignment operator
    UniversalOptional& operator=(const UniversalOptional& other)
    {
        if (this == &other)
            return *this;
        
        reset();

        if (other.has_value())
            value_ptr = new T(*other.value_ptr);

        return *this;
    }

    // Move Constructor
    UniversalOptional(UniversalOptional&& other) noexcept
    {
        if (other.has_value())
            value_ptr = other.value_ptr;

        other.value_ptr = nullptr;
    }

    // Move assignment operator
    UniversalOptional& operator=(UniversalOptional&& other) noexcept
    {
        if (this == &other)
            return *this;

        reset();

        if (other.has_value())
            value_ptr = other.value_ptr;

        other.value_ptr = nullptr;

        return *this;
    }

    bool has_value() const {
        return value_ptr != nullptr;
    }

    T& value() {
        if (has_value())
            return *value_ptr;
        else
            throw std::runtime_error("Empty optional");
    }

    void reset() {
        delete value_ptr;
        value_ptr = nullptr;
    }
};


int main() {
    // Testing with an integer
    UniversalOptional<int> opt_int(42);
    if (opt_int.has_value()) {
        std::cout << "Integer value: " << opt_int.value() << "\n"; // Expected: 42
    }

    // Testing with a string (Demonstrates template adaptability)
    UniversalOptional<std::string> opt_str("Hello Templates!");
    std::cout << "String value: " << opt_str.value() << "\n";

    // Testing reset behavior
    opt_str.reset();
    try {
        std::cout << opt_str.value() << "\n"; // This should crash safely
    }
    catch (const std::runtime_error& e) {
        std::cout << "Caught expected error: " << e.what() << "\n";
    }

    return 0;
}

/// Create a simplified version of std::optional. 
/// It is a class template that either holds a single value of type T, or holds nothing at all.
/// 