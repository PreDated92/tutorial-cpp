#include <iostream>

int main()
{
    // A multi-dimensional array needs the row defined as the 
    // compiler needs this number to determine the element location in memory
    int matrix[][3] = {
        {1,2,3}, 
        {4,5,6}, 
        {7,8,9}
    };

    // Intuitively, you'd think this would work
    // int* matrixPtr = matrix;
    // Unfortunately, a 2D array decays into a pointer to its first row (int (*)[3]), not a pointer to a single integer.

    // We can use a C-Style Cast to get contiguous access. 
    // This is discouraged for various reasons but will be elaborated in the future.
    int* matrixPtrUsingCast = (int*)matrix;
    // Print first and last element
    std::cout << "--matrixPtrUsingCast--" << std::endl;
    std::cout << "First element value: " << *matrixPtrUsingCast << std::endl;
    std::cout << "Last element value: " << *(matrixPtrUsingCast + 8) << std::endl;

    // We can use the first row of matrix using []
    int* matrixPtrUsingIndexing = matrix[0];
    // Print first and last element
    std::cout << "--matrixPtrUsingIndexing--" << std::endl;
    std::cout << "First element value: " << *matrixPtrUsingIndexing << std::endl;
    std::cout << "Last element value: " << *(matrixPtrUsingIndexing + 8) << std::endl;

    // De-referencing
    int* matrixPtrUsingDeReferencing = *matrix;
    // *matrix gives the first array, which immediately decays into an int* pointer.
    // Print first and last element
    std::cout << "--matrixPtrUsingDeReferencing--" << std::endl;
    std::cout << "First element value: " << *matrixPtrUsingDeReferencing << std::endl; // Equivalent to **matrix
    std::cout << "Last element value: " << *(matrixPtrUsingDeReferencing + 8) << std::endl; // Equivalent to *(*matrix + 8)

    // 2D array decay
    int (*matrixRawPtr)[3] = matrix;

    // Then we can use the matrixRawPtr
    // Method 1: Using array subscript syntax
    int* matrixRawPtrUsingIndexing = matrixRawPtr[0];
    // Print first and last element
    std::cout << "--matrixRawPtrUsingIndexing--" << std::endl;
    std::cout << "First element value: " << *matrixRawPtrUsingIndexing << std::endl;
    std::cout << "Last element value: " << *(matrixRawPtrUsingIndexing + 8) << std::endl;

    // Method 2: Using the dereference operator
    int* matrixRawPtrUsingDereference = *matrixRawPtr;
    // Print first and last element
    std::cout << "--matrixRawPtrUsingDereference--" << std::endl;
    std::cout << "First element value: " << *matrixRawPtrUsingDereference << std::endl;
    std::cout << "Last element value: " << *(matrixRawPtrUsingDereference + 8) << std::endl;

    // Bonus: Pointer to pointer array
    int* rowPtrs[] = { matrix[0], matrix[1], matrix[2] };
    int** newMatrixPtr = rowPtrs;
    // Double Dereferencing
    std::cout << "--Bonus: newMatrixPtr--" << std::endl;
    std::cout << "First element value: " << **newMatrixPtr << std::endl;
    std::cout << "Last element value: " << *(*newMatrixPtr + 8) << std::endl;
    
    int* newMatrixPtrUsingIndexing = newMatrixPtr[0];
    std::cout << "--Bonus: newMatrixPtrUsingIndexing--" << std::endl;
    std::cout << "First element value: " << *newMatrixPtrUsingIndexing << std::endl;
    std::cout << "Last element value: " << *(newMatrixPtrUsingIndexing + 8) << std::endl;
}