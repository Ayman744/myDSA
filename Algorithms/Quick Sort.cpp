#include <bits/stdc++.h>
using namespace std;
// Function to create a pivot element and partition the array
int makePivot(vector<int> &vec, int start, int end)
{
    // Calculate the middle index and set the pivot value to the middle element
    int mid = start + (end - start) / 2;
    int pivot = vec[mid];
    // `cnt` will store the number of elements smaller than the pivot
    int cnt = 0;
    // Count how many elements are smaller than the pivot within the range [start, end]
    for (int i = start; i <= end; ++i)
        if (vec[i] < pivot)
            cnt += 1;
    // `pivotIdx` is the index where the pivot will be finally placed after partitioning
    int pivotIdx = cnt + start;
    // Swap the pivot value (vec[mid]) to its correct position in the sorted array
    swap(vec[pivotIdx], vec[mid]);
    // Rearrange the elements such that elements smaller than the pivot are on its left,
    // and elements greater than the pivot are on its right
    for (int s = start, e = end; s < pivotIdx && e > pivotIdx; s += 1, e -= 1)
    {
        // Move `s` forward until an element greater than or equal to the pivot is found
        while (vec[s] < pivot)
            s += 1;
        // Move `e` backward until an element smaller than or equal to the pivot is found
        while (vec[e] > pivot)
            e -= 1;
        // Swap the elements found by `s` and `e` to place them on correct sides of the pivot
        swap(vec[s], vec[e]);
    }
    // Return the final position of the pivot
    return pivotIdx;
}
// Recursive QuickSort function to sort elements in the range [start, end]
void QuickSort(vector<int> &vec, int start, int end)//O(n log n)
{
    // Base case: if the range is invalid or there is only one element, stop recursion
    if (start >= end)
        return;
    // Call `makePivot` to partition the array and get the pivot's correct index
    int pivotIdx = makePivot(vec, start, end);
    // Recursively sort the left half of the array (elements smaller than the pivot)
    QuickSort(vec, start, pivotIdx - 1);
    // Recursively sort the right half of the array (elements greater than the pivot)
    QuickSort(vec, pivotIdx + 1, end);
}
// Overloaded QuickSort function that starts sorting the entire array
void QuickSort(vector<int> &vec)
{
    // Call the actual recursive QuickSort function with the full range of the array
    QuickSort(vec, 0, (int)vec.size() - 1);
}