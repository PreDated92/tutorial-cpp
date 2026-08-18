#include <iostream>
#include <memory>
#include <utility>

template <typename T>
class Vector {
private:
    T* _data = nullptr;
    size_t _size = 0;
    size_t _capacity = 0;

    // Helper method to handle memory growth and element transfers
    void reallocate(size_t new_cap) {
        T* newData = new T[new_cap];
        size_t newSize = sizeof(T);
        
        int min_size = new_cap < _size ? new_cap : _size;
        for (int i = 0; i < min_size; i++)
        {
            newData[i] = _data[i];
        }

        delete[] _data;
        _data = newData;
        _size = newSize;
    }

public:
    Vector() = default;

    // Rule of 5 declarations
    ~Vector() { clear(); ::operator delete(_data); }

    // STEP 3: IMPLEMENT COPY AND MOVE LIFECYCLES
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);
    Vector(Vector&& other) noexcept;
    Vector& operator=(Vector&& other) noexcept;

    void push_back(const T& value) {
        if (_size == _capacity) reallocate(_capacity == 0 ? 1 : _capacity * 2);
        new(&_data[_size++]) T(value); // Construct in-place
    }

    void push_back(T&& value) {
        if (_size == _capacity) reallocate(_capacity == 0 ? 1 : _capacity * 2);
        new(&_data[_size++]) T(std::move(value)); // Move construct in-place
    }

    void clear() {
        for (size_t i = 0; i < _size; ++i) _data[i].~T();
        _size = 0;
    }

    size_t size() const { return _size; }
    size_t capacity() const { return _capacity; }
    T& operator[](size_t index) { return _data[index]; }
};

struct Traceable {
    static inline int copies = 0;
    static inline int moves = 0;

    Traceable() = default;
    Traceable(const Traceable&) { copies++; }
    Traceable(Traceable&&) noexcept { moves++; } // Toggle 'noexcept' here to test!
};

int main() {
    Vector<Traceable> vec;
    vec.push_back(Traceable{}); // Element 1

    Traceable::copies = 0;
    Traceable::moves = 0;

    std::cout << "Triggering custom vector reallocation...\n";
    vec.push_back(Traceable{}); // Element 2 (Triggers reallocation of Element 1)

    std::cout << "Copies during resize: " << Traceable::copies << "\n";
    std::cout << "Moves during resize: " << Traceable::moves << "\n";
}


/// Task A: Implement reallocate with Exception SafetyWrite the reallocate(size_t new_cap) function. 
/// It should:Allocate clean raw memory blocks using ::operator delete and ::operator new.
/// Transfer existing elements from old memory to new memory.
/// The noexcept test: Use std::move_if_noexcept to decide whether to move or copy each element.
/// Call destructors on the old elements and free the old buffer.
/// 
/// Task B: Add Rule of 5 Assignments
/// Implement the move constructor and move assignment operator with noexcept qualifiers to steal pointer resources without data copying.