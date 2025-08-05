#include <bits/stdc++.h>
using namespace std;

/* ==============================================================================
 * Problem: Majority Element (Leetcode 169)
 *
 * Given an array `nums` of size n, return the majority element.
 * The majority element is the element that appears more than ⌊n / 2⌋ times.
 * You may assume that the majority element always exists in the array.
 *
 * Approach: Boyer-Moore Majority Voting Algorithm
 * - Maintain a candidate and a vote count.
 * - If vote count becomes 0, pick current element as candidate.
 * - Increment vote if current == candidate, else decrement.
 *
 * Time Complexity  : O(n)
 * Space Complexity : O(1)
 * ============================================================================== */

class Solution {
public:
    int majorityElement(vector<int>& nums)
    {
        int vote = 0;   // Vote count
        int curr = 0;   // Current candidate

        for (int i = 0; i < nums.size(); i++) {
            if (vote == 0) {
                curr = nums[i];
                vote = 1;
            }
            else {
                if (nums[i] == curr) {
                    vote++;
                }
                else {
                    vote--;
                }
            }
        }

        return curr;
    }
};
