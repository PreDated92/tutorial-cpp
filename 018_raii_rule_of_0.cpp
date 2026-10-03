#include <iostream>
#include <memory>  // Required for std::unique_ptr

class DynamicArray
{
    private:
    std::unique_ptr<int[]> m_buffer; // Smart pointer handles the RAII memory management
    int m_size;
    
    public:
    // Constructor
    DynamicArray(int size) 
        : m_buffer(std::make_unique<int[]>(size)), m_size(size) {}

    // RULE OF ZERO: 
    // We completely omit the Destructor, Copy Constructor, Copy Assignment, 
    // Move Constructor, and Move Assignment! 
    // The compiler will automatically generate perfectly safe ones because 
    // std::unique_ptr already handles the RAII mechanics safely.

    // Subscript operators remain exactly the same
    int operator[](int index) const { return m_buffer[index]; }
    int& operator[](int index)       { return m_buffer[index]; }
    
    void Resize(int new_size)
    {
        // Allocates new memory using RAII
        auto new_buffer = std::make_unique<int[]>(new_size);
        int min_size = new_size < m_size ? new_size : m_size;
        
        for (int i = 0; i < min_size; i++)
        {
            new_buffer[i] = m_buffer[i];
        }
        
        // Ownership transfer: old memory is automatically deleted here
        m_buffer = std::move(new_buffer); 
        m_size = new_size;
    }
};
