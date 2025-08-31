#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Minimum Number of Chairs in a Waiting Room (LeetCode 3168)
//
// Task:
// A string s is given, representing the sequence of people entering ('E')
// and leaving ('L') a waiting room. Each 'E' means one new person enters,
// each 'L' means one person leaves. The waiting room needs enough chairs
// so that nobody stands at any time.
//
// Return the minimum number of chairs needed.
//
// Example:
//   Input:  s = "ELELEEL"
//   Output: 2
//
//   Input:  s = "EEEELL"
//   Output: 4
//
// Approach:
// - Maintain a counter (cnt) for current people in the room.
// - Increment cnt for 'E', decrement cnt for 'L'.
// - Track max_cnt (maximum value of cnt during the process).
// - The answer = max_cnt (minimum chairs needed).
//==============================================================================

class Solution {
public:
    int minimumChairs(string s)
    {
        int cnt = 0;       // current people in room
        int max_cnt = 0;   // maximum occupancy

        for (char ch : s) {
            if (ch == 'E') {
                cnt++;     // person enters
            }
            else if (ch == 'L') {
                cnt--;     // person leaves
            }
            max_cnt = max(max_cnt, cnt); // update max occupancy
        }

        return max_cnt;
    }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(N), where N = length of string s.
// - Space: O(1).
//
// Example Walkthrough:
// Input: "ELELEEL"
// Steps:
//   E → cnt=1, max=1
//   L → cnt=0, max=1
//   E → cnt=1, max=1
//   L → cnt=0, max=1
//   E → cnt=1, max=1
//   E → cnt=2, max=2
//   L → cnt=1, max=2
// Output: 2
//==============================================================================
