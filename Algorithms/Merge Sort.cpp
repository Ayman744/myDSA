#include <bits/stdc++.h>
using namespace std;
vector<int> tmp; // Temporary vector used for merging sorted subarrays
void mergeSortedSubarrays(vector<int>& lst, int start, int mid, int end)
{
    for (int i = start, j = mid + 1, k = start; k <= end; ++k)
    {
        if (i > mid)
            tmp[k] = lst[j++]; // If left subarray is exhausted, take from the right subarray
        else if (j > end)
            tmp[k] = lst[i++]; // If right subarray is exhausted, take from the left subarray
        else if (lst[i] < lst[j])
            tmp[k] = lst[i++]; // If the element in the left subarray is smaller, take it
        else
            tmp[k] = lst[j++]; // Otherwise, take from the right subarray
    }
    for (int i = start; i <= end; ++i)
        lst[i] = tmp[i]; // Copy the merged elements back to the original array
}
void MergeSort(vector<int>& lst, int start, int end)
{
    if (start == end)
        return; // Base case: If the subarray has one element, it's already sorted.
    int mid = start + (end - start) / 2; // Find the middle index
    MergeSort(lst, start, mid); // Recursively sort the left half
    MergeSort(lst, mid + 1, end); // Recursively sort the right half
    mergeSortedSubarrays(lst, start, mid, end); // Merge the sorted halves
}
void MergeSort(vector<int>& lst)
{
    tmp = lst; // Initialize tmp with the same size as lst to avoid resizing during merge
    MergeSort(lst, 0, (int)lst.size() - 1); // Start recursive sort with the full array
}
int main()
{
    vector<int> lst = {38, 27, 43, 3, 9, 82, 10};
    MergeSort(lst);
    for (int i = 0; i < (int) lst.size(); ++i)
        cout << lst[i] << " ";
    return 0;
}