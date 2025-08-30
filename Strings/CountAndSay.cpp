#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Count and Say (LeetCode 38)
//
// Task:
// The "count-and-say" sequence is a sequence of digit strings defined as:
//   - countAndSay(1) = "1"
//   - countAndSay(n) is the "count and say" of countAndSay(n-1).
//
// Example progression:
//   countAndSay(1) = "1"
//   countAndSay(2) = "11"     ("one 1")
//   countAndSay(3) = "21"     ("two 1s")
//   countAndSay(4) = "1211"   ("one 2, one 1")
//   countAndSay(5) = "111221" ("one 1, one 2, two 1s")
//
// Approach:
// 1. Base case: if n == 1, return "1".
// 2. Recursively compute the previous term (n-1).
// 3. Parse the string and count consecutive identical digits.
// 4. Append "count + digit" to form the new string.
// 5. Return the built string as the result.
//==============================================================================

class Solution {
public:
    string countAndSay(int n)
    {
        if (n == 1) return "1";   // Base case

        string say = countAndSay(n - 1);   // Recursive call to build previous term
        string result = "";

        for (int i = 0; i < say.length(); i++) {
            int cnt = 1;
            // Count consecutive same characters
            while (i < say.length() - 1 && say[i] == say[i + 1]) {
                cnt++;
                i++;
            }
            // Append "count + character" to result
            result += to_string(cnt) + string(1, say[i]);
        }

        return result;
    }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(N * M), where N = input n, and M = average length of terms.
//          (Each term is processed fully when generating the next one.)
// - Space: O(M) for storing the generated string at each step.
//
// Example:
// Input:  n = 4
// Output: "1211"
// Explanation:
//   countAndSay(1) = "1"
//   countAndSay(2) = "11"
//   countAndSay(3) = "21"
//   countAndSay(4) = "1211"
//==============================================================================
