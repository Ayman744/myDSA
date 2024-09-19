#include <bits/stdc++.h>
using namespace std;
class Vector
{
private:
    int *arr{nullptr};   // Pointer to dynamic array.
    int size{0};         // Current number of elements.
    int capacity{};      // Total allocated capacity of the array.
public:
    // Constructor: Initializes the vector with a given size.
    Vector(int size):size(size)
    {
        if (size < 0)    // Ensure size is not negative.
            size = 1;    // If negative, default to size = 1.
        capacity = size + 10;   // Initial capacity is slightly larger than size.
        arr = new int[capacity]{ };  // Dynamically allocate memory for the array.
    }
    // Destructor: Cleans up dynamically allocated memory.
    ~Vector()
    {
        delete[] arr;   // Release the memory for the array.
        arr = nullptr;  // Nullify the pointer for safety.
    }
    int get(int idx)
    {
        assert(idx >= 0 && idx < size);
        return arr[idx];
    }
    int getFront()
    {
        return arr[0];
    }
    int getBack()
    {
        return arr[size - 1];
    }
    void set(int idx, int val)
    {
        assert(idx >= 0 && idx < size);
        arr[idx] = val;
    }
    void print()
    {
        for (int i = 0; i < size; ++i)
            cout << arr[i] << " ";
        cout << "\n";
    }
    // Find the index of the first occurrence of a value.
    int find(int val)
    {
        for (int i = 0; i < size; ++i)
        {
            if (val == arr[i])
                return i;  // Return the index if value is found.
        }
        return -1;  // Return -1 if value is not found.
    }
    void expandCapacity()
    {
        capacity *= 2;  // Double the capacity.
        int *arr2 = new int[capacity]{ };  // Allocate new array with double capacity.
        for (int i = 0; i < size; ++i)
            arr2[i] = arr[i];  // Copy elements from old array to new array.
        swap(arr, arr2);  // Swap the old array with the new array.
        delete[] arr2;  // Delete the old array.
    }
    // Function to shrink the capacity if the size is significantly smaller
    void shrinkCapacity()
    {
        if (size <= capacity / 2)  // Shrink if size is less than or equal to half of capacity
        {
            capacity = size + 10;  // Set capacity to size + 10
            int *arr2 = new int[capacity]{ };  // Allocate a smaller array
            for (int i = 0; i < size; ++i)
                arr2[i] = arr[i];  // Copy current elements to the new array
            swap(arr, arr2);  // Swap the old array with the new one
            delete[] arr2;  // Delete the old array
        }
    }
    // Add an element at the end of the array.
    void pushBack(int val)
    {
        if (size == capacity)
            expandCapacity();  // Expand capacity if necessary.
        arr[size++] = val;  // Insert the value and increase the size.
    }
    // Insert a value at a specific index and shift elements to the right.
    void insert(int idx, int val)
    {
        assert(idx >= 0 && idx < size);  // Ensure index is within bounds.
        if (size == capacity)
            expandCapacity();  // Expand capacity if necessary.
        for (int i = size - 1; i >= idx; --i)
            arr[i + 1] = arr[i];  // Shift elements to the right to make space.
        arr[idx] = val;  // Insert the value at the given index.
        ++size;  // Increase the size after insertion.
    }
    // Right rotate the array by one position.
    void rightRotate()
    {
        int val = arr[size - 1];  // Store the last element.
        for (int i = size - 2; i >= 0; --i)
            arr[i + 1] = arr[i];  // Shift all elements one position to the right.
        arr[0] = val;  // Place the last element at the front.
    }
    // Right rotate the array multiple times.
    void rightRotate(int times)
    {
        times %= size;  // Normalize the number of rotations if times > size.
        while (times--)  // Perform right rotation 'times' times.
            rightRotate();  // Call the single right rotation function.
    }
    // Left rotate the array by one position.
    void leftRotate()
    {
        int val = arr[0];  // Store the first element.
        for (int i = 1; i < size; ++i)
            arr[i - 1] = arr[i];  // Shift all elements one position to the left.
        arr[size - 1] = val;  // Place the first element at the back.
    }
    // Remove an element at a specific index and shift elements to the left.
    int pop(int idx)
    {
        assert(idx >= 0 && idx < size);  // Ensure index is valid
        int rVal = arr[idx];  // Store the value to be removed
        for (int i = idx + 1; i < size; ++i)
            arr[i - 1] = arr[i];  // Shift elements to the left to fill the gap
        --size;  // Decrease the size after removal
        shrinkCapacity();  // Call the shrink function if capacity needs to be reduced
        return rVal;  // Return the removed value
    }
    // Find and perform transposition search (swap element with its previous one if found).
    int finTransposition(int val)
    {
        for (int i = 0; i < size; ++i)
        {
            if (arr[i] == val)
            {
                if (i == 0)  // If the element is at the start, no need to swap.
                    return 0;
                swap(arr[i], arr[i - 1]);  // Swap the found element with the one before it.
                return i - 1;  // Return the new index of the element.
            }
        }
        return -1;  // Return -1 if the element is not found.
    }
};
