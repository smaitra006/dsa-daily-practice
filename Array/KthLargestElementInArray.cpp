/*
==============================================================================
Problem: Find Kth Largest Element in an Array
==============================================================================
Task:
    Given an integer array `nums` and an integer `k`, return the k-th largest
    element in the array.

Approaches Implemented:
    1. Min-Heap Method (Priority Queue)
    2. QuickSelect Method (Average O(n) time)

Complexity:
    1. Min-Heap:
        - Time: O(n log k)
        - Space: O(k)
    2. QuickSelect:
        - Average Time: O(n)
        - Worst Time: O(n^2) (rare, if pivot choice is poor)
        - Space: O(1) (in-place)

==============================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    //--------------------------------------------------------------------------
    // Method 1: Min-Heap Approach
    //--------------------------------------------------------------------------
    int findKthLargest_Heap(vector<int>& nums, int k)
    {
        // Min-heap to store the k largest elements
        priority_queue<int, vector<int>, greater<>> pq;

        for (int num : nums) {
            pq.push(num);

            // Keep only k elements in the heap
            if (pq.size() > k) {
                pq.pop();
            }
        }
        return pq.top(); // The k-th largest element
    }

    //--------------------------------------------------------------------------
    // Method 2: QuickSelect Approach
    //--------------------------------------------------------------------------
    int findKthLargest_QuickSelect(vector<int>& nums, int k)
    {
        int n = nums.size();
        return quickSelect(nums, 0, n - 1, n - k);
    }

private:

    // Partition function (Lomuto partition scheme)
    int partition(vector<int>& nums, int left, int right)
    {
        int pivot = nums[right];
        int i = left;

        for (int j = left; j < right; ++j) {
            if (nums[j] <= pivot) {
                swap(nums[i], nums[j]);
                i++;
            }
        }
        swap(nums[i], nums[right]);
        return i;
    }

    // QuickSelect helper
    int quickSelect(vector<int>& nums, int left, int right, int k_smallest)
    {
        if (left == right) return nums[left];

        int pivot_index = partition(nums, left, right);

        if (k_smallest == pivot_index) {
            return nums[k_smallest];
        }
        else if (k_smallest < pivot_index) {
            return quickSelect(nums, left, pivot_index - 1, k_smallest);
        }
        else {
            return quickSelect(nums, pivot_index + 1, right, k_smallest);
        }
    }
};

/*
==============================================================================
Example Usage:
==============================================================================
int main() {
    Solution sol;
    vector<int> nums = {3,2,1,5,6,4};
    int k = 2;

    // Using Heap
    cout << sol.findKthLargest_Heap(nums, k) << endl; // Output: 5

    // Using QuickSelect
    cout << sol.findKthLargest_QuickSelect(nums, k) << endl; // Output: 5
}
==============================================================================
*/
