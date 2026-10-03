#include <iostream>
#include <memory>

int main() {
    std::weak_ptr<int> weak_observe;

    {
        // Create a resource managed by a shared_ptr
        auto shared_owner = std::make_shared<int>(42);
        
        // Point the weak_ptr to it
        weak_observe = shared_owner; 

        // To read the value, you MUST lock it first
        if (auto temporary_shared = weak_observe.lock()) {
            std::cout << "Object is alive: " << *temporary_shared << "\n";
        }
    } // shared_owner goes out of scope here -> the int(42) is destroyed.

    // Expiry Detection
    if (weak_observe.expired())
    {
        std::cout << "weak_observe has expired.\n";
    }

    // Try to access it again after destruction
    if (auto temporary_shared = weak_observe.lock()) {
        std::cout << "This will not print.\n";
    } else {
        std::cout << "Object has expired and was safely cleaned up!\n";
    }

    return 0;
}

// .expired(): Returns true if the managed object has already been deleted, and false otherwise.
// .lock(): Attempts to elevate the weak reference into a temporary std::shared_ptr. 
// If the object is still alive, it returns a valid std::shared_ptr 
// (preventing it from being deleted while you use it). 
// If the object is dead, it returns an empty std::shared_ptr

// Primary Use Cases
// 1. Breaking Circular References (Memory Leaks)
// If two objects hold a std::shared_ptr to each other, they create a cyclical dependency. 
// Their reference counts will never drop to zero, causing a permanent memory leak. 
// Replacing one of those links with a std::weak_ptr breaks the loop.

// 2. Caching Systems
// If you want to maintain a collection of temporary references to objects without 
// forcing them to stay alive in memory, you can use a cache of std::weak_ptr elements. 
// If a different part of the program deletes the resource, 
// the cache simply detects that the pointer has .expired().
