#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Add to Array-Form of Integer
//------------------------------------------------------------------------------
// Task:
// The array-form of an integer num is an integer represented as an array of its digits.
// Given num (as vector<int>) and an integer k, return the array-form of the integer num + k.
//
// Approach:
// 1. Traverse num from right to left (least significant digit to most).
// 2. Add k to the current digit and update digit with modulo 10.
// 3. Carry forward k = num[i] / 10 for next iteration.
// 4. After processing all digits, if k > 0, insert its digits at the front.
// 5. Return the updated array.
//
// Complexity Analysis:
// - Time: O(n + log(k)) where n = num.size() (digits traversed once, extra digits added).
// - Space: O(1) additional (modifies num in place).
//==============================================================================

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> addToArrayForm(vector<int>& num, int k)
    {
        // Traverse from the least significant digit
        for (int i = num.size() - 1; i >= 0; i--) {
            num[i] += k;        // add k to current digit
            k = num[i] / 10;    // carry for next digit
            num[i] %= 10;       // keep only single digit
        }

        // If k still remains, insert its digits at the beginning
        while (k > 0) {
            num.insert(num.begin(), k % 10);
            k /= 10;
        }

        return num;
    }
};

//==============================================================================
// Example Usage:
// Input:  num = [1,2,0,0], k = 34
// Output: [1,2,3,4]
// Explanation: 1200 + 34 = 1234
//==============================================================================
