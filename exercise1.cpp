#include <iostream>

class DynamicArray
{
    private:
    int* m_buffer;
    int m_size;
    
    public:
    DynamicArray(const DynamicArray&) = delete;
    DynamicArray& operator=(const DynamicArray&) = delete;

    DynamicArray(int size)
    {
        int* buffer = new int[size];
        m_buffer = buffer;
        m_size = size;
    }
    
    ~DynamicArray()
    {
        delete[] m_buffer;
    }
    
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