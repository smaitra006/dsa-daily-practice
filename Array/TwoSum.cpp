#include <bits/stdc++.h>
using namespace std;

/* ==============================================================================
 * Problem: Two Sum (Leetcode 1)
 *
 * Given an array of integers `nums` and an integer `target`, return the indices
 * of the two numbers such that they add up to `target`.
 *
 * Approach:
 * - Use a hash map to store numbers we've seen and their indices.
 * - For each number, check if (target - current number) exists in the map.
 * - If it exists, return the pair of indices.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * ============================================================================== */

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target)
    {
        unordered_map<int, int> mp;  // value → index

        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];

            if (mp.find(complement) != mp.end()) {
                // Found the pair
                return { i, mp[complement] };
            }

            // Store the current number and its index
            mp[nums[i]] = i;
        }

        // If no pair found
        return {};
    }
};

