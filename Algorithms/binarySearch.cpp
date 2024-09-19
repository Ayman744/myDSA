#include <bits/stdc++.h>
using namespace std;
int binarySearch(vector<int> &nums, int val)//O(log n)
{
    if (nums.empty())
        return -1;
    int start = 0, end = (int)nums.size() - 1;
    while (start <= end)  // Continue searching while the search space is valid (start <= end)
    {
        int mid = start + (end - start) / 2;  // Calculate the middle index, avoiding overflow
        if (nums[mid] == val)  // Check if the middle element is the target value
            return mid;  // If found, return the index of the target value
        if (nums[mid] < val)  // If the middle element is less than the target value
            start = mid + 1;  // Narrow the search to the right half (ignore left half)
        else if (nums[mid] > val)  // If the middle element is greater than the target value
            end = mid - 1;  // Narrow the search to the left half (ignore right half)
    }
    return -1;  // If the value is not found, return -1
}
int findFirstIdx (vector<int> nums, int target)// O(log n)
{
    if (nums.empty()) return -1;

    int start = 0, end = (int)nums.size() - 1, pos = -1; // pos is initialized to -1 (indicating "not found")
    // Standard binary search loop; runs until start crosses end
    while (start <= end)
    {
        // Calculate the middle index to avoid overflow using (start + (end - start) / 2)
        int mid = start + (end - start) / 2;
        // If target is greater than mid element, discard the left half
        if (target > nums[mid])
            start = mid + 1;
            // If target is smaller than mid element, discard the right half
        else if (target < nums[mid])
            end = mid - 1;
            // If target is found at mid, update pos and continue searching the left half for the first occurrence
        else
            pos = mid, end = mid - 1;
    }
    // Return the index of the first occurrence of target (or -1 if not found)
    return pos;
}
int findLastIdx(vector<int> nums, int target)//O(log n)
{
    if (nums.empty()) return -1;

    int start = 0, end = (int)nums.size() - 1, pos = -1; // pos is initialized to -1 (indicating "not found")
    while (start <= end)
    {
        // 'mid' is the middle index of the current subarray, calculated to avoid overflow
        int mid = start + (end - start) / 2;
        // Case 1: If target is greater than the middle element,
        // the target must be in the right half of the array
        if (target > nums[mid])
            start = mid + 1;  // Move the start to the right of mid

            // Case 2: If target is smaller than the middle element,
            // the target must be in the left half of the array
        else if (target < nums[mid])
            end = mid - 1;  // Move the end to the left of mid

            // Case 3: If target is equal to the middle element,
            // record the position and search in the right half for possible later occurrences
        else
            pos = mid , start = mid + 1;  // Store the current position of the target , Move to the right to find the last occurrence
    }

    // Return the last found position, or -1 if not found
    return pos;
}
/// On real
double f(double x)
{
    return 4 * pow(x, 7) + 3 * pow(x, 5) - 1000;
}
double binarySearchOnRealValues (double EPS = 1e-9)
{
    int start=0 , end=3;
    while (end-start > EPS)
    {
        int mid = start + (end - start) /2;
        if (f(mid) < 0.0)
            start=mid;
        else
            end=mid;
    }
    return start;
}