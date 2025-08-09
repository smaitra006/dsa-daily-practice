/* ==============================================================================
 * Problem: Sort an Array
 *
 * Task:
 * - Given an integer array `nums`, return the array sorted in ascending order.
 *
 * Approach: Min-Heap (Priority Queue)
 * 1. Push all elements into a min-heap (priority queue with smallest element at the top).
 * 2. Pop elements one by one and place them back into `nums` in sorted order.
 *
 * Time Complexity  : O(n log n) — Each insertion and extraction takes O(log n).
 * Space Complexity : O(n)       — Extra space for the priority queue.
 * ============================================================================== */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> sortArray(vector<int>& nums)
    {
        // Min-heap to store elements in ascending order
        priority_queue<int, vector<int>, greater<int>> pq;

        // Push all elements into the min-heap
        for (int num : nums) {
            pq.push(num);
        }

        // Extract elements in sorted order
        for (int i = 0; i < nums.size(); i++) {
            nums[i] = pq.top();
            pq.pop();
        }

        return nums;
    }
};

/* ==============================================================================
 * Example Usage:
 *
 * int main() {
 *     vector<int> nums = {5, 2, 3, 1};
 *     Solution sol;
 *     vector<int> sorted = sol.sortArray(nums);
 *
 *     // Output: 1 2 3 5
 *     for (int x : sorted) cout << x << " ";
 *     cout << endl;
 *
 *     return 0;
 * }
 * ============================================================================== */
