#include <bits/stdc++.h>
using namespace std;

/* ==============================================================================
 * LeetCode 136: Single Number
 * ==============================================================================
 * Problem:
 * Given a non-empty array `nums` where every element appears **twice** except for
 * one, return the single element that appears only once.
 *
 * Approach: Bit Manipulation (XOR)
 * - XOR of two identical numbers is 0.
 * - XOR of a number with 0 is the number itself.
 * - Therefore, XORing all elements cancels out the duplicates, leaving the single one.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * ============================================================================= */

class Solution {
public:
    int singleNumber(vector<int>& nums)
    {
        int Xor = 0;

        for (int i : nums) {
            Xor ^= i;
        }

        return Xor;
    }
};

