#include <bits/stdc++.h>
using namespace std;

/* ===================================================================
 * SLIDING WINDOW + TWO POINTER TECHNIQUE
 * =================================================================== */

/**
 * @brief A powerful pattern used for solving problems on subarrays, substrings,
 *        or sequences that require continuous windows or optimal range queries.
 *
 * USE CASES:
 * - Longest/shortest subarray with condition
 * - Maximum/minimum sum or count in a subarray
 * - Find number of subarrays satisfying a property
 * - Strings: anagrams, unique characters, frequency tracking
 *
 * KEY IDEAS:
 * - Maintain a "window" using two pointers: [left, right]
 * - Expand right → to include more elements
 * - Shrink left ← to maintain constraints
 * - Window can grow and shrink dynamically
 *
 * TIME COMPLEXITY:
 * - O(N) in most cases, because each pointer moves at most N steps
 *
 * ===================================================================
 * TEMPLATE PATTERN (for arrays or strings)
 * =================================================================== */

int slidingWindow(vector<int> &nums)
{
    int n = nums.size();
    int left = 0, right = 0;
    int windowResult = 0;

    // optional state to maintain inside window
    unordered_map<int, int> freq;

    while (right < n)
    {
        // include nums[right] into the window
        freq[nums[right]]++;

        // shrink the window from left if constraint breaks
        while (/* some condition on freq / sum / size */)
        {
            freq[nums[left]]--;
            if (freq[nums[left]] == 0)
                freq.erase(nums[left]);
            left++;
        }

        // update answer based on current window [left, right]
        windowResult = max(windowResult, right - left + 1);

        right++; // expand window
    }

    return windowResult;
}

//  1. Fixed Size Window — Max/Min Sum of K Elements
int maxSumOfWindowK(vector<int> &nums, int k)
{
    int sum = 0, maxSum = INT_MIN;
    int left = 0;

    for (int right = 0; right < nums.size(); right++)
    {
        sum += nums[right];

        if (right - left + 1 == k)
        {
            maxSum = max(maxSum, sum);
            sum -= nums[left];
            left++;
        }
    }

    return maxSum;
}

// 2. Variable Size Window — Longest Substring with ≤ K Distinct Characters
int lengthOfLongestSubstringKDistinct(string s, int k)
{
    unordered_map<char, int> freq;
    int left = 0, maxLen = 0;

    for (int right = 0; right < s.size(); right++)
    {
        freq[s[right]]++;

        while (freq.size() > k)
        {
            freq[s[left]]--;
            if (freq[s[left]] == 0)
                freq.erase(s[left]);
            left++;
        }

        maxLen = max(maxLen, right - left + 1);
    }

    return maxLen;
}

// 3. Count Number of Subarrays With Given Sum / Property
int countSubarraysWithSum(vector<int> &nums, int target)
{
    int left = 0, sum = 0, count = 0;

    for (int right = 0; right < nums.size(); right++)
    {
        sum += nums[right];

        while (sum > target)
        {
            sum -= nums[left++];
        }

        if (sum == target)
            count++;
    }

    return count;
}
