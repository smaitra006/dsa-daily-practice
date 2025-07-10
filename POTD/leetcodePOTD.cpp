// LeetCode POTD Questions

#include <bits/stdc++.h>
using namespace std;

/* ===================================================================
 * PROBLEM 3330: FIND THE ORIGINAL TYPED STRING I (LeetCode)
 * =================================================================== */

/**
 * @brief Return the total number of possible original strings
 *
 * PROBLEM STATEMENT:
 * Alice typed a string `word` on her keyboard. She may have pressed at most
 * one key for **too long**, causing a character to repeat one or more times.
 *
 * You are given the final string `word`. Determine how many **possible original
 * strings** Alice could have intended to type.
 *
 * A character group of repeated characters could be reduced to just one character
 * (only one group can be reduced in total).
 *
 * EXAMPLE:
 * Input:  word = "aaab"
 * Output: 3
 * Explanation: Alice may have intended to type "aab", "ab", or "aaab".
 *
 * APPROACH:
 * - Traverse the string and identify groups of consecutive identical characters.
 * - Each such group (of length > 1) is a candidate for being the *long press* group.
 * - Only one group can be reduced — total possible original strings = number of such groups + 1
 *   (1 for the case where Alice didn't long press at all).
 *
 * STRATEGY:
 * - Initialize `possible = 1` for the no-long-press case.
 * - For each index `i`, if word[i] == word[i-1], it is part of a long-press group.
 *   Increment `possible` for each group (counted only once per group).
 *
 * @param word The final typed string shown on screen
 * @return int Total number of possible original strings
 *
 * @complexity
 * Time: O(N) — single traversal of the string
 * Space: O(1) — constant extra space
 */

 class Solution {
    public:
        int numberOfPossibleOriginalStrings(string word) {
            int possible = 1;  // No long-press case is always valid

            for (int i = 1; i < word.size(); i++) {
                // If a new long-press group starts
                if (word[i] == word[i - 1]) {
                    possible++;
                }
            }

            return possible;
        }
    };

/* ===================================================================
 * PROBLEM 3333: FIND THE ORIGINAL TYPED STRING II (LeetCode)
 * =================================================================== */

/**
 * @brief Count total possible original strings given final string and length constraint
 *
 * PROBLEM STATEMENT:
 * Alice was trying to type a string, but she may have pressed a key for too long,
 * causing some characters to repeat. She did this clumsily at most once per character group.
 *
 * You're given:
 * - `word`: the final typed string (may contain long presses)
 * - `k`: the minimum length of the original string
 *
 * Return the number of possible original strings Alice could have intended to type
 * that are of length at least `k`. Since the result may be large, return it modulo 1e9+7.
 *
 * EXAMPLE:
 * Input:  word = "aaabb", k = 2
 * Output: 5
 * Explanation: All possible compressed combinations of length ≥ 2 are counted.
 *
 * APPROACH:
 * - First, break `word` into consecutive character groups (e.g., "aaabb" → [3,2]).
 * - For each group of length `g`, we can choose to reduce it to size `1` through `g`.
 * - So, total possible combinations = product of sizes of all groups.
 *
 * - However, we must subtract those combinations where the final compressed string
 *   has length less than `k`.
 *
 * STRATEGY:
 * - Use DP to count the number of ways to compress groups such that resulting length < k.
 * - Use prefix sum technique within DP for efficiency.
 * - Subtract invalid counts from total.
 *
 * @param word The final typed string (after clumsy typing)
 * @param k Minimum required length of original string
 * @return int Total number of valid original strings modulo 1e9+7
 *
 * @complexity
 * Time:  O(N * k) — where N = number of character groups in `word`
 * Space: O(k) — dynamic programming with space optimization
 */

 class Solution {
    public:
        const int MOD = 1e9 + 7;

        int possibleStringCount(string word, int k) {
            if (word.empty()) return 0;

            // Step 1: Break the string into consecutive character groups
            vector<int> groups;
            int count = 1;

            for (int i = 1; i < word.size(); i++) {
                if (word[i] == word[i - 1])
                    count++;
                else {
                    groups.push_back(count);
                    count = 1;
                }
            }
            groups.push_back(count);  // Add last group

            // Step 2: Calculate total possible combinations
            long total = 1;
            for (int g : groups) {
                total = (total * g) % MOD;
            }

            // Step 3: If k is more than max possible original string length, it's invalid
            if (k > groups.size()) {
                // DP[s]: Number of ways to get a compressed string of length s
                vector<int> dp(k, 0);
                dp[0] = 1;

                for (int g : groups) {
                    vector<int> new_dp(k, 0);
                    long sum = 0;

                    for (int s = 0; s < k; s++) {
                        if (s > 0)
                            sum = (sum + dp[s - 1]) % MOD;
                        if (s > g)
                            sum = (sum - dp[s - g - 1] + MOD) % MOD;

                        new_dp[s] = sum;
                    }

                    dp = new_dp;
                }

                // Step 4: Sum all invalid cases with length < k
                long invalid = 0;
                for (int s = groups.size(); s < k; s++) {
                    invalid = (invalid + dp[s]) % MOD;
                }

                // Final result = total - invalid
                return (total - invalid + MOD) % MOD;
            }

            return total;
        }
    };

/* ================================================================
 * PROBLEM 3304: FIND THE K-TH CHARACTER IN STRING GAME I (LeetCode)
 * ================================================================ */

/**
 * @brief Return the k-th character in a growing string generated by simulation
 *
 * GAME RULE:
 * - Start with word = "a"
 * - Each operation:
 *     → For every character c in word, compute its next character
 *       (i.e., 'a' → 'b', ..., 'z' → 'a')
 *     → Append the new characters to the original word
 *
 * For example:
 * "a" → "ab"
 * "ab" → "abbc"
 * "abbc" → "abbcbccd"
 *
 * We are to return the k-th character (1-indexed) after enough operations such
 * that the word length is ≥ k.
 *
 * SOLUTION:
 * - Simulate the process until the word has at least k characters
 * - At each step:
 *     → Generate "next characters" and append to the original word
 * - Return word[k - 1]
 *
 * @param k The 1-based position of the desired character
 * @return char The k-th character after simulation
 *
 * @complexity
 * Time: O(k) — in the worst case, we may simulate until string length reaches k
 * Space: O(k) — storing the expanded string
 */

class Solution {
public:
    // Helper function to generate "next characters" of a given string
    string solve(string word) {
        string next = "";
        for (char c : word) {
            // 'z' should wrap around to 'a'
            next += (c == 'z') ? 'a' : (c + 1);
        }
        return next;
    }

    // Main function to find the k-th character
    char kthCharacter(int k) {
        string word = "a";

        // Keep growing the word until it has at least k characters
        while (word.size() < k) {
            word += solve(word);
        }

        return word[k - 1];  // Convert to 0-based index
    }
};

/* =====================================================================================
 * PROBLEM 3307: FIND THE K-TH CHARACTER IN STRING GAME II (LeetCode Hard)
 * ===================================================================================== */

/**
 * @brief Simulate string operations without building the full string, and return the k-th character.
 *
 * PROBLEM STATEMENT:
 * Initially, Alice has a string `word = "a"`.
 * You're given an array `operations` and a number `k`.
 *
 * For each operation in `operations[i]`:
 * - If `operations[i] == 0`: word = word + word
 * - If `operations[i] == 1`: word = word + shift(word) → where each character moves to the next (z→a)
 *
 * Return the character at the `k-th` position (1-indexed) after all operations.
 * Note: String grows exponentially, so building it directly is not feasible.
 *
 * EXAMPLE:
 * Input: k = 4, operations = [0, 1]
 * Output: 'c'
 *
 * STRATEGY:
 * - Instead of constructing the full string, calculate the number of characters added by each operation.
 * - Work backwards from the last operation using recursion.
 * - At each step:
 *   → If `pows[i] < k`, then the character at `k` lies in the appended portion → reduce k and update answer.
 *   → If not, continue to earlier operations.
 * - Use modulo 26 to determine character value from index.
 *
 * @complexity
 * Time: O(n) where n = operations.size() (up to 55 due to 2^55 > 10^16)
 * Space: O(n) recursion stack + O(n) for power array
 */

 class Solution {
    public:
        #define ll long long
        vector<ll> pows;

        // Helper function to recursively find how many +1 shifts were applied to get to the kth character
        int f(int index, ll k, vector<int>& operations) {
            if (index < 0) return 0; // base case: we're at the original 'a'

            if (index >= 55) return f(index - 1, k, operations); // beyond limit (2^55 > 10^16)

            // If kth character is in the added portion of this operation
            if (pows[index] < k) {
                return operations[index] + f(index - 1, k - pows[index], operations);
            }

            // Otherwise, it's from the original segment
            return f(index - 1, k, operations);
        }

        char kthCharacter(long long k, vector<int>& operations) {
            pows.resize(55, 1);
            pows[0] = 1;

            // Precompute powers: pows[i] = total size of string after i operations
            for (int i = 1; i < 55; i++) {
                pows[i] = 2 * pows[i - 1];
            }

            int n = operations.size();
            int shifts = f(n - 1, k, operations); // how many +1 shifts happened along the path
            return 'a' + (shifts % 26);           // final character after that many shifts from 'a'
        }
    };

/* ===================================================================
 * LEETCODE 1394: FIND LUCKY INTEGER IN AN ARRAY
 * =================================================================== */

/**
 * @brief Return the largest lucky integer in the array
 *
 * PROBLEM STATEMENT:
 * Given an array of integers `arr`, a **lucky integer** is an integer
 * whose value is equal to its frequency in the array.
 *
 * You are to return the **largest lucky integer**. If no lucky integer exists, return -1.
 *
 * Input:
 * - vector<int> arr: Array of integers (1 <= arr.length <= 500)
 *
 * Output:
 * - Integer representing the largest lucky number, or -1 if none exists
 *
 * EXAMPLE:
 * Input: arr = [2,2,3,4]
 * Output: 2
 * (Explanation: The number 2 appears exactly 2 times)
 *
 * ALGORITHM:
 * - Use a hash map to count frequency of each element
 * - Traverse the map and check if any key has key == frequency
 * - Track the maximum such key (lucky number)
 *
 * COMPLEXITY:
 * - Time: O(N) where N is the size of the array
 * - Space: O(N) for the hash map
 */

 class Solution {
    public:
        int findLucky(vector<int>& arr) {
            int n = arr.size();
            unordered_map<int, int> freq;

            // Count frequency of each number
            for (int i = 0; i < n; i++) {
                freq[arr[i]]++;
            }

            int luckyInt = -1;

            // Check for lucky numbers
            for (auto it : freq) {
                if (it.first == it.second) {
                    luckyInt = max(luckyInt, it.first);
                }
            }

            return luckyInt;
        }
    };

    /* ===================================================================
     * LEETCODE 1865: FINDING PAIRS WITH A CERTAIN SUM
     * =================================================================== */

    /**
     * @brief Implement a data structure to support dynamic sum pair queries
     *
     * PROBLEM STATEMENT:
     * You are given two integer arrays `nums1` and `nums2`.
     * Implement a class `FindSumPairs` with the following operations:
     *
     * 1. `add(index, val)` → Adds `val` to `nums2[index]`
     * 2. `count(tot)` → Returns the number of pairs `(i, j)` such that:
     *                   nums1[i] + nums2[j] == tot
     *
     * INPUT:
     * - vector<int> nums1, nums2
     * - Queries: add(index, val), count(tot)
     *
     * OUTPUT:
     * - Integer: Count of valid (i, j) pairs for given `tot`
     *
     * EXAMPLE:
     * Input:
     * FindSumPairs([[1,1,2,2,2,3], [1,4,5,2,5,4]])
     * add(3, 2)
     * count(7) → Count pairs (i, j) such that nums1[i] + nums2[j] == 7
     *
     * ALGORITHM:
     * - Use a frequency map for nums2 to quickly count complements in `count(tot)`
     * - Update the map dynamically when `add()` is called
     *
     * COMPLEXITY:
     * - Constructor: O(n) for nums2 frequency map
     * - add(): O(1)
     * - count(): O(n1), where n1 = size of nums1
     */

    class FindSumPairs
    {
    public:
        vector<int> n1, n2;
        unordered_map<int, int> m;

        /**
         * @brief Initialize the object with two arrays
         */
        FindSumPairs(vector<int> &nums1, vector<int> &nums2)
        {
            n1 = nums1;
            n2 = nums2;

            // Create frequency map for nums2
            for (int x : n2)
            {
                m[x]++;
            }
        }

        /**
         * @brief Adds val to nums2[index] and updates the frequency map
         */
        void add(int index, int val)
        {
            m[n2[index]]--;   // Remove old value from frequency map
            n2[index] += val; // Update nums2[index]
            m[n2[index]]++;   // Add new value to frequency map
        }

        /**
         * @brief Count number of valid pairs (i, j) where n1[i] + n2[j] == tot
         */
        int count(int tot)
        {
            int c = 0;

            for (int x : n1)
            {
                int complement = tot - x;
                c += m[complement]; // Look up how many times complement exists in nums2
            }

            return c;
        }
    };

    /**
     * Example Usage:
     * FindSumPairs* obj = new FindSumPairs(nums1, nums2);
     * obj->add(index, val);
     * int result = obj->count(tot);
     */

    /* ===================================================================
     * LEETCODE 1353: MAXIMUM NUMBER OF EVENTS THAT CAN BE ATTENDED
     * =================================================================== */

    /**
     * @brief Attend the maximum number of non-overlapping events
     *
     * PROBLEM STATEMENT:
     * You are given an array of `events` where events[i] = [startDay_i, endDay_i].
     * You can attend only one event per day, and can choose any day `d` such that:
     *     startDay_i <= d <= endDay_i
     *
     * Return the maximum number of events that can be attended.
     *
     * INPUT:
     * - vector<vector<int>> events: list of events as [startDay, endDay]
     *
     * OUTPUT:
     * - int: maximum number of events that can be attended
     *
     * EXAMPLE:
     * Input: events = [[1,2],[2,3],[3,4]]
     * Output: 3
     *
     * ALGORITHM (Greedy + DSU with Path Compression):
     * - Sort events by their end day (to attend earlier-finishing events first)
     * - Use a Disjoint Set (nextDay[i]) to find the earliest free day for an event
     * - Once a day is taken, update it to point to the next available day
     *
     * COMPLEXITY:
     * - Time: O(N log N + M α(N)), where N = number of events, M = max end day
     * - Space: O(M), where M = maximum end day
     */

    class Solution
    {
        /**
         * @brief DSU find function with path compression to get the next free day
         */
        int findNext(vector<int> &nextDay, int day)
        {
            if (nextDay[day] != day)
            {
                nextDay[day] = findNext(nextDay, nextDay[day]); // Path compression
            }
            return nextDay[day];
        }

    public:
        /**
         * @brief Main function to return the max number of events that can be attended
         */
        int maxEvents(vector<vector<int>> &events)
        {
            // Step 1: Sort events based on their ending day (greedy strategy)
            sort(events.begin(), events.end(), [](const vector<int> &a, const vector<int> &b)
                 { return a[1] < b[1]; });

            // Step 2: Find the latest day among all events to size DSU array
            int maxDay = 0;
            for (const auto &evt : events)
            {
                maxDay = max(maxDay, evt[1]);
            }

            // Step 3: Initialize DSU (each day points to itself)
            vector<int> nextDay(maxDay + 2); // +2 to handle boundary case
            for (int d = 0; d <= maxDay + 1; ++d)
            {
                nextDay[d] = d;
            }

            int count = 0;

            // Step 4: Process each event
            for (const auto &evt : events)
            {
                int start = evt[0];
                int end = evt[1];

                // Find the earliest available day to attend this event
                int day = findNext(nextDay, start);

                if (day <= end)
                {
                    ++count;                                   // Attend this event
                    nextDay[day] = findNext(nextDay, day + 1); // Mark the day as used
                }
            }

            return count;
        }
    };

    /* ===================================================================
     * LEETCODE 3439: RESCHEDULE MEETINGS FOR MAXIMUM FREE TIME I
     * =================================================================== */

    /**
     * @brief Given non-overlapping meetings and event duration,
     *        you can shift at most k meetings earlier (preserving order and duration)
     *        to **maximize the longest free time** during the event.
     *
     * CONSTRAINTS:
     * - Meetings must remain non-overlapping
     * - At most k meetings can be rescheduled
     * - Rescheduling means moving the start earlier, duration stays the same
     * - All meetings must fit in [0, eventTime]
     *
     * GOAL: Maximize the longest continuous **free period**
     *       within [0, eventTime] after at most `k` reschedules.
     *
     * ALGORITHM (Binary Search + Greedy Simulation):
     * - Binary search on answer: longest possible free time F
     * - For each candidate F:
     *     → Simulate scheduling the meetings greedily
     *     → Shift up to k meetings to ensure each free gap ≥ F
     * - If possible → try larger F, else try smaller
     *
     * TIME COMPLEXITY: O(n log eventTime)
     */

    class Solution
    {
    public:
        /**
         * @brief Simulates rescheduling to test if a minimum free time gap is possible
         *
         * @param start      Original start times of meetings
         * @param end        Original end times of meetings
         * @param k          Max number of allowed reschedules
         * @param eventTime  Duration of the overall event
         * @param gap        Target free time gap to validate
         * @return           true if gap is achievable, false otherwise
         */
        bool isPossible(vector<int> &start, vector<int> &end, int k, int eventTime, int gap)
        {
            int n = start.size();
            int rescheduled = 0;
            int currentTime = 0;

            for (int i = 0; i < n; i++)
            {
                int duration = end[i] - start[i];
                // Required earliest start to maintain `gap` before this meeting
                int minStart = currentTime + gap;

                if (start[i] < minStart)
                {
                    // Must reschedule this meeting to start at minStart
                    if (++rescheduled > k)
                        return false;
                    currentTime = minStart + duration;
                }
                else
                {
                    // No reschedule needed, take original position
                    currentTime = start[i] + duration;
                }

                if (currentTime > eventTime)
                    return false;
            }

            // Check if there's a gap at the end
            return (eventTime - currentTime) >= gap;
        }

        /**
         * @brief Returns the maximum free time possible after at most k reschedules
         *
         * @param eventTime  Duration of the entire event
         * @param startTime  Start times of meetings
         * @param endTime    End times of meetings
         * @param k          Max reschedules allowed
         * @return           Longest continuous free time after adjustments
         */
        int maxFreeTime(int eventTime, vector<int> &startTime, vector<int> &endTime, int k)
        {
            int low = 0, high = eventTime, ans = 0;

            while (low <= high)
            {
                int mid = low + (high - low) / 2;

                if (isPossible(startTime, endTime, k, eventTime, mid))
                {
                    ans = mid; // valid gap found, try larger
                    low = mid + 1;
                }
                else
                {
                    high = mid - 1; // too large gap, reduce
                }
            }

            return ans;
        }
    };

    /* ===================================================================
     * LEETCODE 3439: MAXIMUM FREE TIME AFTER ONE RESCHEDULE II
     * =================================================================== */

    /**
     * @brief Given meetings scheduled in an event timeline, compute the maximum
     *        continuous free time possible if you are allowed to reschedule exactly
     *        one meeting (shift earlier without overlapping, maintaining order).
     *
     * STRATEGY:
     * - Compute all free gaps:
     *     → gap[0] = before first meeting
     *     → gap[i] = between end of meeting i-1 and start of meeting i
     *     → gap[n] = after last meeting till end of event
     *
     * - Precompute:
     *     → largest gap to the **right** of each index (suffix max)
     *
     * - Then, iterate through each potential reschedule point:
     *     → Try combining adjacent gaps with the shifted meeting duration
     *     → Maintain maximum merged gap found
     *
     * TIME COMPLEXITY: O(n)
     * SPACE COMPLEXITY: O(n)
     */

    class Solution
    {
    public:
        /**
         * @brief Computes max free time after one allowed reschedule
         *
         * @param eventTime   Total duration of the event
         * @param startTime   Start times of the meetings
         * @param endTime     End times of the meetings
         * @return            Maximum continuous free time possible
         */
        int maxFreeTime(int eventTime, vector<int> &startTime, vector<int> &endTime)
        {
            int n = startTime.size();

            // Step 1: Calculate free gaps before, between, and after meetings
            vector<int> gap;
            gap.push_back(startTime[0]); // before first meeting
            for (int i = 1; i < n; ++i)
            {
                gap.push_back(startTime[i] - endTime[i - 1]); // between meetings
            }
            gap.push_back(eventTime - endTime.back()); // after last meeting

            int m = gap.size();

            // Step 2: Precompute largest gap to the right (suffix max)
            vector<int> largestRight(m, 0);
            for (int i = m - 2; i >= 0; --i)
            {
                largestRight[i] = max(largestRight[i + 1], gap[i + 1]);
            }

            // Step 3: Iterate and evaluate max possible merged free time
            int ans = 0, largestLeft = 0;

            for (int i = 1; i < m; ++i)
            {
                int meetingDuration = endTime[i - 1] - startTime[i - 1];

                // Try merging current meeting with adjacent gaps if its duration
                // is not larger than the max free time on either side
                if (meetingDuration <= max(largestLeft, largestRight[i]))
                {
                    ans = max(ans, gap[i - 1] + gap[i] + meetingDuration);
                }

                // Or just merge the two gaps without shifting any meeting
                ans = max(ans, gap[i - 1] + gap[i]);

                // Update largest gap seen to the left
                largestLeft = max(largestLeft, gap[i - 1]);
            }

            return ans;
        }
    };
