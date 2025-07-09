#include <bits/stdc++.h>
using namespace std;

/* ===================================================================
 * LEETCODE 1423: MAXIMUM POINTS YOU CAN OBTAIN FROM CARDS
 * =================================================================== */

/**
 * @brief Given an array of card points and an integer k, pick exactly k cards
 *        from either the beginning or the end of the array to maximize the total score.
 *
 * ALGORITHM (Sliding Window from Edges):
 * - Think of picking `k` cards as leaving out a subarray of size `n - k` in the middle.
 * - Instead of trying all combinations, reverse approach:
 *     → Start with picking first k cards from the left
 *     → Slide the window: remove from left, add from right
 *     → Track max sum of the left + right side combined
 *
 * TIME COMPLEXITY: O(k)
 * SPACE COMPLEXITY: O(1)
 */

class Solution
{
public:
    /**
     * @brief Calculates the max score by picking k cards from either end
     *
     * @param cardPoints  Points of each card in the row
     * @param k           Number of cards to pick
     * @return            Maximum total score obtainable
     */
    int maxScore(vector<int> &cardPoints, int k)
    {
        int n = cardPoints.size();
        int left_sum = 0, right_sum = 0, max_sum = 0;

        // Step 1: Take first k cards from the front (left prefix)
        for (int i = 0; i < k; i++)
        {
            left_sum += cardPoints[i];
        }

        // Initial assumption: take all k cards from front
        max_sum = left_sum;

        // Step 2: Gradually shift cards from left end to right end
        int end = n - 1;
        for (int i = k - 1; i >= 0; i--)
        {
            left_sum -= cardPoints[i];      // Remove one from left
            right_sum += cardPoints[end--]; // Add one from right
            max_sum = max(max_sum, left_sum + right_sum);
        }

        return max_sum;
    }
};

/* ===================================================================
 * LEETCODE 3: LONGEST SUBSTRING WITHOUT REPEATING CHARACTERS
 * =================================================================== */

/**
 * @brief Given a string s, find the length of the longest substring without repeating characters.
 *
 * ALGORITHM (Sliding Window + Hashing):
 * - Use two pointers (left and right) to maintain a window [l, r].
 * - Use a hash map (or array) to store the last seen index of each character.
 * - If a character is already seen **within the current window**, move the left pointer.
 * - Keep updating the max length of the window.
 *
 * TIME COMPLEXITY: O(N)
 * SPACE COMPLEXITY: O(1) — 256 characters max (ASCII)
 */

class Solution
{
public:
    /**
     * @brief Finds length of longest substring with no repeating characters
     *
     * @param s  Input string
     * @return   Length of longest valid substring
     */
    int lengthOfLongestSubstring(string s)
    {
        int n = s.size();

        // ASCII hashmap: store last seen index of each character
        vector<int> hash(256, -1);

        int l = 0, r = 0;
        int maxLen = 0;

        while (r < n)
        {
            // Character has been seen and lies within the current window
            if (hash[s[r]] != -1 && hash[s[r]] >= l)
            {
                l = hash[s[r]] + 1; // shrink window from the left
            }

            // Update current character's last seen index
            hash[s[r]] = r;

            // Update max window length
            maxLen = max(maxLen, r - l + 1);

            r++; // move right pointer
        }

        return maxLen;
    }
};

/* ===================================================================
 * LEETCODE 1004: MAX CONSECUTIVE ONES III
 * =================================================================== */

/**
 * @brief Given a binary array `nums` and an integer `k`, return the maximum number
 *        of consecutive 1's in the array if you can flip at most `k` 0's.
 *
 * ALGORITHM (Sliding Window):
 * - Use two pointers to define a window [l, r].
 * - Count the number of 0's in the window.
 * - If the count exceeds `k`, shrink the window from the left.
 * - Keep updating the max window length where number of 0's ≤ k.
 *
 * TIME COMPLEXITY: O(N)
 * SPACE COMPLEXITY: O(1)
 */

class Solution
{
public:
    /**
     * @brief Finds max number of 1's with at most k zero flips
     *
     * @param nums  Input binary array
     * @param k     Max number of 0's that can be flipped
     * @return      Maximum length of valid subarray
     */
    int longestOnes(vector<int> &nums, int k)
    {
        int n = nums.size();
        int l = 0, r = 0;
        int maxLen = 0;
        int zeroes = 0; // number of 0's in current window

        while (r < n)
        {
            // Expand the window and update zero count
            if (nums[r] == 0)
                zeroes++;

            // Shrink the window until 0's in window ≤ k
            while (zeroes > k)
            {
                if (nums[l] == 0)
                    zeroes--;
                l++; // move left pointer
            }

            // Update max window length
            maxLen = max(maxLen, r - l + 1);
            r++; // move right pointer
        }

        return maxLen;
    }
};

/* ===================================================================
 * LEETCODE 438: FIND ALL ANAGRAMS IN A STRING
 * =================================================================== */

/**
 * @brief Given strings `s` and `p`, return all starting indices in `s`
 *        where the substring is an anagram of `p`.
 *
 * ALGORITHM (Sliding Window + Hash Map):
 * - Use a hashmap to store frequency of characters in string `p`.
 * - Use a fixed-size sliding window of length `k = p.size()` over `s`.
 * - Maintain a count of how many unique characters still need to match.
 * - When count == 0 and window size matches, it's an anagram.
 * - As the window slides, update the frequency map and count accordingly.
 *
 * TIME COMPLEXITY: O(N), where N = s.length()
 * SPACE COMPLEXITY: O(1) — max 26 characters in lowercase alphabet
 */

class Solution
{
public:
    /**
     * @brief Finds all start indices where anagram of p appears in s
     *
     * @param s  Main string
     * @param p  Pattern string (anagram target)
     * @return   List of starting indices of valid anagrams
     */
    vector<int> findAnagrams(string s, string p)
    {
        unordered_map<char, int> mpp;

        // Step 1: Build frequency map for string p
        for (char ch : p)
        {
            mpp[ch]++;
        }

        int cnt = mpp.size(); // Number of unique characters to match
        int k = p.length();   // Fixed window size
        int i = 0, j = 0;
        vector<int> ans;

        // Step 2: Start sliding window
        while (j < s.length())
        {
            // If current character is in pattern, decrement its frequency
            if (mpp.count(s[j]))
            {
                mpp[s[j]]--;
                if (mpp[s[j]] == 0)
                {
                    cnt--; // Character matched completely
                }
            }

            // If window size is less than k, just expand
            if (j - i + 1 < k)
            {
                j++;
            }

            // When window size hits k
            else if (j - i + 1 == k)
            {
                if (cnt == 0)
                {
                    ans.push_back(i); // Anagram found
                }

                // Before sliding the window, restore left character
                if (mpp.count(s[i]))
                {
                    if (mpp[s[i]] == 0)
                    {
                        cnt++; // Character mismatch reintroduced
                    }
                    mpp[s[i]]++;
                }

                // Slide the window
                i++;
                j++;
            }
        }

        return ans;
    }
};
