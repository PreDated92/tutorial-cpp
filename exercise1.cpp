#include <iostream>

// Rule of 5 exercise, RAII
class DynamicArray
{
    private:
    int* m_buffer;
    int m_size;
    
    public:
    // Copy Constructor
    // DynamicArray f(g);
    // DynamicArray f = g;
    DynamicArray(const DynamicArray& other)
    {
        int size = other.m_size;
        int* buffer = new int[size];
        m_buffer = buffer;
        m_size = size;

        for (int i=0; i<size; i++)
        {
            m_buffer[i] = other.m_buffer[i];
        }
    }

    // Copy assignment operator
    // DynamicArray f, g;
    // f(g);
    // f = g;
    DynamicArray& operator=(const DynamicArray& other)
    {
        // prevent data deletion of self copy
        if (this == &other)
            return *this;

        // delete to avoid memory leak
        delete[] m_buffer;

        int size = other.m_size;
        int* buffer = new int[size];
        m_buffer = buffer;
        m_size = size;

        for (int i=0; i < size; i++)
        {
            m_buffer[i] = other.m_buffer[i];
        }

        return *this;
    }

    // Move Constructor
    // DynamicArray g;
    // DynamicArray f = std::move(g);
    // DynamicArray h = DynamicArray(1);
    DynamicArray(DynamicArray&& other) noexcept
    {
        m_size = other.m_size;
        m_buffer = other.m_buffer;

        other.m_size = 0;
        other.m_buffer = nullptr;
    }

    // Move assignment operator
    // DynamicArray f, g, h;
    // f = std::move(g);
    // h = DynamicArray(1);
    DynamicArray& operator=(DynamicArray&& other) noexcept
    {
        // prevent data deletion of self copy
        if (this == &other)
            return *this;
        
        // delete to avoid memory leak
        delete[] m_buffer;

        m_size = other.m_size;
        m_buffer = other.m_buffer;

        other.m_size = 0;
        other.m_buffer = nullptr;

        return *this;
    }

    // Constructor
    DynamicArray(int size)
    {
        int* buffer = new int[size];
        m_buffer = buffer;
        m_size = size;
    }
    
    // Destructor
    ~DynamicArray()
    {
        delete[] m_buffer;
    }
    
    // Const subscript operator overload
    int operator[](int index) const
    {
        return m_buffer[index];
    }

    // Subscript operator overload
    int& operator[](int index)
    {
        return m_buffer[index];
    }
    
    void Resize(int new_size)
    {
        int* buffer = new int[new_size];
        int min_size = new_size < m_size ? new_size : m_size;
        for (int i=0; i<min_size; i++)
        {
            buffer[i] = m_buffer[i];
        }
        
        delete[] m_buffer;
        m_buffer = buffer;
        m_size = new_size;
    }
};

int main()
{
    DynamicArray arr(1000);
    arr.Resize(1500);

    return 0;
}