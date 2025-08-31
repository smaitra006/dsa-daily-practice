#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Combination Sum III (LeetCode 216)
//
// Task:
// Find all possible combinations of `k` numbers that add up to a number `n`,
// given that only numbers 1 through 9 can be used and each combination must
// be a unique set of numbers (no repeated numbers in a combination).
//
// Example:
//   Input:  k = 3, n = 7
//   Output: [[1,2,4]]
//
//   Input:  k = 3, n = 9
//   Output: [[1,2,6],[1,3,5],[2,3,4]]
//
// Approach (Backtracking):
// 1. Use backtracking to explore all possible combinations of numbers 1-9.
// 2. Keep track of current path, remaining sum (`target`), and remaining numbers (`k`).
// 3. Stop recursion if `target < 0` or `k < 0`.
// 4. If `target == 0` and `k == 0` → valid combination, add to result.
// 5. Use `start` to avoid reusing numbers and ensure ascending order.
//==============================================================================

class Solution {
public:
    vector<vector<int>> res;

    void backtrack(int k, int target, int start, vector<int>& path)
    {
        // Base case: valid combination found
        if (target == 0 && k == 0) {
            res.push_back(path);
            return;
        }

        for (int i = start; i <= 9; ++i) {
            if (i > target || k <= 0) break;  // pruning
            path.push_back(i);
            backtrack(k - 1, target - i, i + 1, path); // recurse
            path.pop_back(); // backtrack
        }
    }

    vector<vector<int>> combinationSum3(int k, int n)
    {
        vector<int> path;
        backtrack(k, n, 1, path);
        return res;
    }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(C(9, k)), number of combinations of 9 elements taken k at a time.
// - Space: O(k) for recursion stack and path storage.
//
// Example Walkthrough:
// Input: k=3, n=7
// - Explore numbers [1..9], recursively selecting 3 numbers adding to 7
// - Valid combination found: [1,2,4]
// Output: [[1,2,4]]
//==============================================================================
