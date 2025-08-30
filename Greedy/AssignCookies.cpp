#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Assign Cookies (LeetCode 455)
//
// Task:
// Assume you are an awesome parent and want to give your children cookies.
// Each child i has a greed factor g[i], which is the minimum size of a cookie
// that the child will be content with. Each cookie j has a size s[j].
// If s[j] >= g[i], the child i can be contented with the cookie j.
//
// Goal: Maximize the number of content children by distributing cookies.
//
// Example:
//   Input:  g = [1,2,3], s = [1,1]
//   Output: 1
//
//   Input:  g = [1,2], s = [1,2,3]
//   Output: 2
//
// Approach (Greedy):
// 1. Sort greed factors `g` and cookie sizes `s`.
// 2. Use two pointers: i for children, j for cookies.
// 3. If the current cookie satisfies the current child, assign and move to next child.
// 4. Always move to the next cookie regardless (since each cookie can only be used once).
// 5. Count maximum matches.
//==============================================================================

class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s)
    {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int i = 0, j = 0;
        int m = g.size(), n = s.size();
        int cnt = 0;

        // Two-pointer matching
        while (i < m && j < n) {
            if (g[i] <= s[j]) {  // Current cookie can satisfy child i
                cnt++;
                i++;             // Move to next child
            }
            j++;                 // Move to next cookie
        }
        return cnt;
    }
};

//==============================================================================
// Complexity Analysis:
// - Sorting: O(M log M + N log N), where M = number of children, N = cookies.
// - Two-pointer scan: O(M + N).
// - Total: O(M log M + N log N).
// - Space: O(1) (ignoring sorting space).
//
// Example Walkthrough:
// Input:  g = [1,2], s = [1,2,3]
// Sorted: g = [1,2], s = [1,2,3]
// Match g[0]=1 with s[0]=1 → cnt=1
// Match g[1]=2 with s[1]=2 → cnt=2
// Output: 2
//==============================================================================
