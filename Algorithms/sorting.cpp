#include <bits/stdc++.h>
using namespace std;s
void insertionSort(vector<int> &nums)
{
    // Outer loop: iterate through each element starting from index 1
    for (int i = 1; i < (int)nums.size(); ++i)
    {
        // Set 'ele' as the current element to be inserted into the sorted portion
        int ele = nums[i], j = i - 1;
        // Inner loop: Compare the current element 'ele' with elements in the sorted portion
        // and shift elements greater than 'ele' to the right
        while (j >= 0 && nums[j] > ele)
        {
            // Shift the element nums[j] to the right
            nums[j + 1] = nums[j];
            // Move the index 'j' to the left
            j--;
        }
        // Place 'ele' in its correct position in the sorted portion
        nums[j + 1] = ele;
    }
}
void selectionSort(vector<int> &nums)
{
    int sz = (int)nums.size();
    // Outer loop runs over each element except the last one
    for (int i = 0; i < sz - 1; ++i)
    {
        // Assume the current element (at index i) is the smallest
        int minIdx = i;
        // Inner loop starts at i+1 and finds the smallest element in the remaining array
        for (int j = i + 1; j < sz; ++j)
        {
            // If a smaller element is found, update minIdx
            if (nums[j] < nums[minIdx])
                minIdx = j;
        }
        // Swap the smallest found element with the current element
        swap(nums[minIdx], nums[i]);
    }
}
void countSort(vector<int> &array)
{
    int size = (int)array.size(); // size stores the number of elements in the input array
    // Find the maximum value in the array
    int maxVal = array[0]; // Initialize maxVal with the first element
    for (int i = 0; i < size; ++i)// Loop through all elements
        if (array[i] > maxVal) // Update maxVal if a larger element is found
            maxVal = array[i];
    // Create a count array to store the frequency of each element
    vector<int> count(maxVal + 1); // Count array has size maxVal + 1, initialized to 0
    // Count the occurrences of each element in the original array
    for (int i = 0; i < size; ++i)
        count[array[i]] += 1; // Increment the count for the element array[i]
    // Overwrite the original array with sorted elements
    int idx = 0; // idx is used to track the position in the original array
    for (int i = 0; i <= maxVal; ++i)
    { // Loop through the count array
        for (int j = 0; j < count[i]; ++j, ++idx)
        { // Place 'i' in the array count[i] times
            array[idx] = i;
        }
    }
}