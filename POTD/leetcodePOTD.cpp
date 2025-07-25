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

class Solution
{
public:
    int numberOfPossibleOriginalStrings(string word)
    {
        int possible = 1; // No long-press case is always valid

        for (int i = 1; i < word.size(); i++)
        {
            // If a new long-press group starts
            if (word[i] == word[i - 1])
            {
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

class Solution
{
public:
    const int MOD = 1e9 + 7;

    int possibleStringCount(string word, int k)
    {
        if (word.empty())
            return 0;

        // Step 1: Break the string into consecutive character groups
        vector<int> groups;
        int count = 1;

        for (int i = 1; i < word.size(); i++)
        {
            if (word[i] == word[i - 1])
                count++;
            else
            {
                groups.push_back(count);
                count = 1;
            }
        }
        groups.push_back(count); // Add last group

        // Step 2: Calculate total possible combinations
        long total = 1;
        for (int g : groups)
        {
            total = (total * g) % MOD;
        }

        // Step 3: If k is more than max possible original string length, it's invalid
        if (k > groups.size())
        {
            // DP[s]: Number of ways to get a compressed string of length s
            vector<int> dp(k, 0);
            dp[0] = 1;

            for (int g : groups)
            {
                vector<int> new_dp(k, 0);
                long sum = 0;

                for (int s = 0; s < k; s++)
                {
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
            for (int s = groups.size(); s < k; s++)
            {
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

class Solution
{
public:
    // Helper function to generate "next characters" of a given string
    string solve(string word)
    {
        string next = "";
        for (char c : word)
        {
            // 'z' should wrap around to 'a'
            next += (c == 'z') ? 'a' : (c + 1);
        }
        return next;
    }

    // Main function to find the k-th character
    char kthCharacter(int k)
    {
        string word = "a";

        // Keep growing the word until it has at least k characters
        while (word.size() < k)
        {
            word += solve(word);
        }

        return word[k - 1]; // Convert to 0-based index
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

class Solution
{
public:
#define ll long long
    vector<ll> pows;

    // Helper function to recursively find how many +1 shifts were applied to get to the kth character
    int f(int index, ll k, vector<int> &operations)
    {
        if (index < 0)
            return 0; // base case: we're at the original 'a'

        if (index >= 55)
            return f(index - 1, k, operations); // beyond limit (2^55 > 10^16)

        // If kth character is in the added portion of this operation
        if (pows[index] < k)
        {
            return operations[index] + f(index - 1, k - pows[index], operations);
        }

        // Otherwise, it's from the original segment
        return f(index - 1, k, operations);
    }

    char kthCharacter(long long k, vector<int> &operations)
    {
        pows.resize(55, 1);
        pows[0] = 1;

        // Precompute powers: pows[i] = total size of string after i operations
        for (int i = 1; i < 55; i++)
        {
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

class Solution
{
public:
    int findLucky(vector<int> &arr)
    {
        int n = arr.size();
        unordered_map<int, int> freq;

        // Count frequency of each number
        for (int i = 0; i < n; i++)
        {
            freq[arr[i]]++;
        }

        int luckyInt = -1;

        // Check for lucky numbers
        for (auto it : freq)
        {
            if (it.first == it.second)
            {
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

/* ===================================================================
 * LEETCODE 2402: MEETING ROOMS III
 * =================================================================== */

/**
 * @brief You are given `n` meeting rooms and a list of meetings.
 *        Schedule all meetings in a way that respects:
 *        - A meeting can only be held in a room that is available
 *        - If all rooms are busy, delay the meeting until the earliest available room
 *        - Always choose the room with the **lowest index**
 *
 * Return the index of the room with the most meetings.
 *
 * TIME COMPLEXITY: O(M * N) in worst case
 * SPACE COMPLEXITY: O(N)
 */

class Solution
{
public:
    int mostBooked(int n, vector<vector<int>> &meetings)
    {
        // Step 1: Sort meetings by start time
        sort(meetings.begin(), meetings.end());
        int m = meetings.size();

        // last_available[i]: the earliest time room i becomes free
        vector<long long> last_available(n, 0);

        // used_count[i]: number of meetings room i has hosted
        vector<int> used_count(n, 0);

        // Step 2: Process each meeting
        for (auto &meet : meetings)
        {
            int start = meet[0];
            int end = meet[1];
            int duration = end - start;

            int chosenRoom = -1;

            // Try to find an available room (lowest index)
            for (int room = 0; room < n; ++room)
            {
                if (last_available[room] <= start)
                {
                    chosenRoom = room;
                    break;
                }
            }

            if (chosenRoom != -1)
            {
                // Room is available, assign meeting directly
                last_available[chosenRoom] = end;
                used_count[chosenRoom]++;
            }
            else
            {
                // No room is free, delay the meeting to earliest available room
                long long earliest = LLONG_MAX;

                for (int room = 0; room < n; ++room)
                {
                    if (last_available[room] < earliest)
                    {
                        earliest = last_available[room];
                        chosenRoom = room;
                    }
                }

                // Assign meeting starting at earliest time
                last_available[chosenRoom] += duration;
                used_count[chosenRoom]++;
            }
        }

        // Step 3: Find the room with max usage
        int ans = 0;
        for (int room = 1; room < n; ++room)
        {
            if (used_count[room] > used_count[ans])
            {
                ans = room;
            }
        }

        return ans;
    }
};

/* ===================================================================
 * LEETCODE 1900: EARLIEST AND LATEST ROUNDS WHERE PLAYERS MEET
 * =================================================================== */

/**
 * @brief In a knockout tournament of `n` players labeled 1 to n,
 *        players compete in rounds. Each round, players are paired
 *        from the outside inward (1 vs n, 2 vs n-1, etc.).
 *
 *        Two players `firstPlayer` and `secondPlayer` want to know
 *        the earliest and latest round they can possibly meet.
 *
 * STRATEGY:
 * ---------
 * Simulate all possible tournament paths using DFS and memoization.
 * For each round:
 *   - Pair players from the outside inward.
 *   - If players meet, record round.
 *   - Else, recursively simulate next round with all valid match outcomes.
 *
 * TIME COMPLEXITY: Exponential (but pruned due to symmetric conditions)
 * SPACE COMPLEXITY: O(N^2) stack space + cache (if memoized)
 */

class Solution
{
public:
    /**
     * @brief Depth-first search to compute earliest and latest round
     *        two players can meet in a knockout bracket.
     *
     * @param n   Total players in current round
     * @param p1  Position of first player
     * @param p2  Position of second player
     * @return    {earliest_round, latest_round}
     */
    pair<int, int> dfs(int n, int p1, int p2)
    {
        // Step 1: If they are currently facing each other
        if (p1 + p2 == n + 1)
        {
            return {1, 1};
        }

        // Step 2: Normalize positions (p1 < p2)
        if (p1 > p2)
        {
            swap(p1, p2);
        }

        // Step 3: Base case for small tournaments
        if (n <= 4)
        {
            return {2, 2};
        }

        int m = (n + 1) / 2; // Next round size
        int minR = INT_MAX;
        int maxR = INT_MIN;

        // Step 4: Reflect positions for symmetry optimization
        if (p1 - 1 > n - p2)
        {
            int t = n + 1 - p1;
            p1 = n + 1 - p2;
            p2 = t;
        }

        // Step 5: Simulate both players in left half
        if (p2 * 2 <= n + 1)
        {
            int a = p1 - 1;
            int b = p2 - p1 - 1;

            for (int i = 0; i <= a; ++i)
            {
                for (int j = 0; j <= b; ++j)
                {
                    auto [r1, r2] = dfs(m, i + 1, i + j + 2);
                    minR = min(minR, r1 + 1);
                    maxR = max(maxR, r2 + 1);
                }
            }
        }
        // Step 6: Players are in opposite halves
        else
        {
            int p4 = n + 1 - p2;
            int a = p1 - 1;
            int b = p4 - p1 - 1;
            int c = p2 - p4 - 1;

            for (int i = 0; i <= a; ++i)
            {
                for (int j = 0; j <= b; ++j)
                {
                    int offset = i + j + 1 + (c + 1) / 2 + 1;
                    auto [r1, r2] = dfs(m, i + 1, offset);
                    minR = min(minR, r1 + 1);
                    maxR = max(maxR, r2 + 1);
                }
            }
        }

        return {minR, maxR};
    }

    /**
     * @brief Main function to compute earliest and latest round
     *        two players can meet.
     */
    vector<int> earliestAndLatest(int n, int firstPlayer, int secondPlayer)
    {
        auto [earliest, latest] = dfs(n, firstPlayer, secondPlayer);
        return {earliest, latest};
    }
};

/* ============================================================================
 * LEETCODE 2410: MATCH PLAYERS WITH TRAINERS
 * ============================================================================ */

/**
 * @brief Each player has a strength requirement, and each trainer
 *        has a maximum strength they can train.
 *        We want to match as many players as possible with trainers such that:
 *        trainer[i] >= player[j] (each used only once)
 *
 * ALGORITHM:
 * - Sort both arrays
 * - Use two pointers to greedily match smallest eligible trainer to each player
 *
 * TIME COMPLEXITY: O(N log N + M log M)
 * SPACE COMPLEXITY: O(1)
 */

class Solution
{
public:
    int matchPlayersAndTrainers(vector<int> &players, vector<int> &trainers)
    {
        // Step 1: Sort both players and trainers
        sort(begin(players), end(players));
        sort(begin(trainers), end(trainers));

        int player = 0, trainer = 0;
        int count = 0;

        // Step 2: Greedily match trainers to players
        while (player < players.size() && trainer < trainers.size())
        {
            if (trainers[trainer] >= players[player])
            {
                // Found a match
                count++;
                player++;
                trainer++;
            }
            else
            {
                // Trainer too weak, try next trainer
                trainer++;
            }
        }

        return count;
    }
};

/* ============================================================================
 * LEETCODE 1290: CONVERT BINARY NUMBER IN A LINKED LIST TO INTEGER
 * ============================================================================ */

/**
 * @brief A singly linked list represents a binary number.
 *        Convert it into its corresponding integer value.
 *
 * ALGORITHM:
 * - Traverse the linked list from head to end.
 * - Use bit manipulation: left shift the result and add current node value.
 *
 * TIME COMPLEXITY: O(N) — one pass through the list
 * SPACE COMPLEXITY: O(1) — constant extra space
 */

/**
 * Definition for singly-linked list.
 */
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    static int getDecimalValue(ListNode *head)
    {
        int ans = 0;

        // Traverse the list and compute decimal value
        for (ListNode *curr = head; curr != nullptr; curr = curr->next)
        {
            ans = (ans << 1) + curr->val; // Left shift and add current bit
        }

        return ans;
    }
};

/* ============================================================================
 * CUSTOM VALIDATION: CHECK STRING FOR AT LEAST ONE VOWEL AND ONE CONSONANT
 * ============================================================================ */

/**
 * @brief Check if a string is valid:
 *        - At least length 3
 *        - Contains at least one vowel and one consonant
 *        - Only contains alphabets and digits (non-alphanumerics are invalid)
 *
 * TIME COMPLEXITY: O(N) — where N is length of string
 * SPACE COMPLEXITY: O(1)
 */

class Solution
{
public:
    bool isValid(string s)
    {
        int n = s.length();
        if (n < 3)
            return false;

        int vowels = 0, consonants = 0;
        string vowelList = "aeiouAEIOU";

        for (char c : s)
        {
            if (isalpha(c))
            {
                // Check for vowel or consonant
                if (vowelList.find(c) != string::npos)
                {
                    vowels++;
                }
                else
                {
                    consonants++;
                }
            }
            else if (!isdigit(c))
            {
                // Invalid character (not alphanumeric)
                return false;
            }
        }

        // At least one vowel and one consonant required
        return vowels >= 1 && consonants >= 1;
    }
};

/* ============================================================================
 * CUSTOM LOGIC: MAXIMUM LENGTH OF ALTERNATING EVEN-ODD SEQUENCE
 * ============================================================================ */

/**
 * @brief Given an array of integers, find the maximum length of a sequence
 *        that alternates between even and odd numbers.
 *
 * ALGORITHM:
 * - Count total number of evens and odds.
 * - Use dynamic programming logic:
 *   - even_dp: longest subsequence ending with even
 *   - odd_dp : longest subsequence ending with odd
 * - For each number:
 *     - If even → it can extend an odd-ending sequence
 *     - If odd  → it can extend an even-ending sequence
 *
 * TIME COMPLEXITY: O(N)
 * SPACE COMPLEXITY: O(1)
 */

class Solution
{
public:
    int maximumLength(vector<int> &nums)
    {
        int count_even = 0, count_odd = 0;

        // Step 1: Count total evens and odds
        for (int num : nums)
        {
            if (num % 2 == 0)
                count_even++;
            else
                count_odd++;
        }

        // Step 2: DP-style pass for longest alternating sequence
        int even_dp = 0, odd_dp = 0;

        for (int num : nums)
        {
            if (num % 2 == 0)
            {
                // Can extend a subsequence ending in odd
                even_dp = max(even_dp, odd_dp + 1);
            }
            else
            {
                // Can extend a subsequence ending in even
                odd_dp = max(odd_dp, even_dp + 1);
            }
        }

        // Step 3: Return max of simple counts or alternating chain
        return max({count_even, count_odd, even_dp, odd_dp});
    }
};

/* =============================================================================
 * 3202. Find the Maximum Length of Valid Subsequence II
 * =============================================================================
 * You are given an integer array nums and a positive integer k.
 *
 * A subsequence `sub` is valid if:
 *    (sub[0] + sub[1]) % k == (sub[1] + sub[2]) % k == ...
 *    == (sub[x - 2] + sub[x - 1]) % k.
 *
 * GOAL: Return the length of the longest valid subsequence.
 *
 * IDEA:
 * - Use DP to track the longest valid subsequence for each mod value.
 * - dp[mod][i]: longest valid subsequence ending at index i
 *               where (nums[j] + nums[i]) % k == mod
 *
 * TIME COMPLEXITY: O(n^2)
 * SPACE COMPLEXITY: O(k * n)
 */

class Solution
{
public:
    int maximumLength(vector<int> &nums, int k)
    {
        int n = nums.size();
        int maxSub = 1;

        // dp[mod][i] = max length of subsequence ending at i with pairwise % k == mod
        vector<vector<int>> dp(k, vector<int>(n, 1));

        // Compare each pair (j, i) to extend subsequence ending at j
        for (int i = 1; i < n; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                int mod = (nums[j] + nums[i]) % k;

                // If valid, update dp[mod][i] based on dp[mod][j]
                dp[mod][i] = max(dp[mod][i], 1 + dp[mod][j]);

                // Track global maximum
                maxSub = max(maxSub, dp[mod][i]);
            }
        }

        return maxSub;
    }
};

/* ============================================================================
 * LeetCode 2163. Minimum Difference in Sums After Removal of Elements
 * ============================================================================
 * Given an array of 3n integers, remove n elements such that:
 *   - n elements are removed from prefix (first 2n elements)
 *   - n elements are removed from suffix (last 2n elements)
 * Goal: Minimize the difference between sum of the smallest n from the first
 * 2n and the largest n from the last 2n elements.
 *
 * STRATEGY:
 * - Use a max-heap to track smallest `n` sum from left (first 2n)
 * - Use a min-heap to track largest `n` sum from right (last 2n)
 *
 * TIME COMPLEXITY: O(N log N)
 * SPACE COMPLEXITY: O(N)
 * ========================================================================= */

class Solution
{
public:
    long long minimumDifference(vector<int> &nums)
    {
        int N = nums.size();
        int n = N / 3;

        vector<long long> leftMinSum(N, 0);  // Sum of smallest n elements from left
        vector<long long> rightMaxSum(N, 0); // Sum of largest n elements from right

        // ----------- LEFT TO RIGHT: maintain smallest n from 0 to 2n-1 ----------
        priority_queue<int> maxHeap;
        long long leftSum = 0;

        for (int i = 0; i < 2 * n; i++)
        {
            maxHeap.push(nums[i]);
            leftSum += nums[i];

            if (maxHeap.size() > n)
            {
                leftSum -= maxHeap.top(); // remove largest (to keep n smallest)
                maxHeap.pop();
            }

            leftMinSum[i] = leftSum;
        }

        // ----------- RIGHT TO LEFT: maintain largest n from N-1 to n ------------
        priority_queue<int, vector<int>, greater<>> minHeap;
        long long rightSum = 0;

        for (int i = N - 1; i >= n; i--)
        {
            minHeap.push(nums[i]);
            rightSum += nums[i];

            if (minHeap.size() > n)
            {
                rightSum -= minHeap.top(); // remove smallest (to keep n largest)
                minHeap.pop();
            }

            rightMaxSum[i] = rightSum;
        }

        // ------------- Find minimum difference between prefix & suffix -----------
        long long ans = LLONG_MAX;
        for (int i = n - 1; i < 2 * n; i++)
        {
            ans = min(ans, leftMinSum[i] - rightMaxSum[i + 1]);
        }

        return ans;
    }
};

/* ============================================================================
 * LeetCode 1233. Remove Sub-Folders from the Filesystem
 * ============================================================================
 * Given a list of folder paths, remove all sub-folders such that only the
 * top-level (non-sub) folders remain.
 *
 * A folder is a sub-folder if it starts with a top-level folder path followed
 * immediately by a '/' (to avoid false matches like "/a" and "/ab").
 *
 * STRATEGY:
 * - Sort the folder list lexicographically.
 * - For each folder, check if it's a subfolder of the last added result.
 * - Use string matching with boundary check (next char is '/') to confirm.
 *
 * TIME COMPLEXITY: O(N * L log N) — N = number of folders, L = avg. folder length
 * SPACE COMPLEXITY: O(N)
 * ========================================================================= */

class Solution
{
public:
    vector<string> removeSubfolders(vector<string> &folder)
    {
        // Sort folders so subfolders follow their parent folders
        sort(folder.begin(), folder.end());

        vector<string> res;

        for (const auto &f : folder)
        {
            if (res.empty())
            {
                res.push_back(f); // First folder always added
            }
            else
            {
                const string &prev = res.back();

                // Check if current folder is a sub-folder of prev
                // Must start with prev and have '/' right after it
                if (f.find(prev) == 0 && f.size() > prev.size() && f[prev.size()] == '/')
                {
                    continue; // Skip sub-folder
                }
                else
                {
                    res.push_back(f); // Not a sub-folder, add to result
                }
            }
        }

        return res;
    }
};

/* ============================================================================
 * LeetCode 1948: Delete Duplicate Folders in a System
 * ============================================================================
 * You are given a list of folder paths. If two folder subtrees are identical
 * (i.e., same structure and names), remove all such duplicate folders.
 *
 * STRATEGY:
 * 1. Build a tree (Trie-like) from all paths.
 * 2. Assign a unique "signature" to each subtree (based on children structure).
 * 3. Use the signature to count duplicates.
 * 4. In second DFS, skip any subtree whose signature appears ≥2 times.
 *
 * TIME COMPLEXITY: O(N * L log L) — N = paths, L = avg path depth
 * SPACE COMPLEXITY: O(N * L)
 * ========================================================================= */

struct Node
{
    string name;
    unordered_map<string, Node *> children;
    string signature;

    Node(string name) : name(name) {}
};

class Solution
{
public:
    // Step 1: First DFS to compute unique subtree signatures
    void dfs(Node *node, unordered_map<string, int> &signatureCount)
    {
        if (node->children.empty())
        {
            node->signature = "";
            return;
        }

        vector<string> childSignatures;
        for (const auto &[name, child] : node->children)
        {
            dfs(child, signatureCount);
            // Build signature using folder name and child signature
            childSignatures.push_back(name + "(" + child->signature + ")");
        }

        // Sort to ensure deterministic order for matching
        sort(childSignatures.begin(), childSignatures.end());

        node->signature = "";
        for (const string &sig : childSignatures)
        {
            node->signature += sig;
        }

        // Count how many times this signature has appeared
        signatureCount[node->signature]++;
    }

    // Step 2: Second DFS to rebuild filtered tree
    void dfs2(Node *node, vector<string> &currentPath,
              vector<vector<string>> &result,
              unordered_map<string, int> &signatureCount)
    {

        // If subtree is duplicate, don't add to result
        if (!node->children.empty() && signatureCount[node->signature] >= 2)
        {
            return;
        }

        currentPath.push_back(node->name);
        result.push_back(currentPath);

        for (const auto &[name, child] : node->children)
        {
            dfs2(child, currentPath, result, signatureCount);
        }

        currentPath.pop_back(); // Backtrack
    }

    // Main function
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>> &paths)
    {
        // Step 0: Build folder tree
        Node *root = new Node("");
        for (const auto &path : paths)
        {
            Node *curr = root;
            for (const string &folder : path)
            {
                if (!curr->children.count(folder))
                {
                    curr->children[folder] = new Node(folder);
                }
                curr = curr->children[folder];
            }
        }

        // Step 1: Compute subtree signatures
        unordered_map<string, int> signatureCount;
        dfs(root, signatureCount);

        // Step 2: Reconstruct tree without duplicate subtrees
        vector<vector<string>> result;
        vector<string> currentPath;
        for (const auto &[name, child] : root->children)
        {
            dfs2(child, currentPath, result, signatureCount);
        }

        delete root; // Optional: cleanup root (no smart pointers used)
        return result;
    }
};

/* ============================================================================
 * LeetCode 1957: Delete Characters to Make Fancy String
 * ============================================================================
 * Problem:
 * Given a string `s`, delete the minimum number of characters so that no
 * three consecutive characters are the same.
 *
 * Strategy:
 * - Traverse the string while checking if the current character and its
 *   neighbors form a triplet.
 * - Skip characters that would cause three consecutive identical letters.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n) (for output string)
 * ========================================================================== */

class Solution
{
public:
    string makeFancyString(string s)
    {
        // Handle edge case: single character
        if (s.size() == 1)
            return s;

        string ans;
        ans += s[0]; // Always take the first character

        // Loop from 1 to n-2, checking for triplets
        for (int i = 1; i < s.size() - 1; i++)
        {
            // If current and both neighbors are the same, skip current
            if (s[i - 1] == s[i] && s[i] == s[i + 1])
            {
                continue;
            }
            ans += s[i]; // Otherwise, keep it
        }

        ans += s[s.size() - 1]; // Always take the last character
        return ans;
    }
};

/* ==============================================================================
 * LeetCode 1695: Maximum Erasure Value
 * ==============================================================================
 * Problem:
 * You are given an array of positive integers `nums`.
 * Return the maximum sum of a subarray with all unique elements.
 *
 * Approach: Sliding Window + HashMap (Two Pointers)
 * - Maintain a window `[l, r]` where all elements are unique.
 * - If a duplicate appears, shrink the window from the left until it's unique.
 * - Keep updating the sum and track the maximum.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * ============================================================================== */

class Solution
{
public:
    int maximumUniqueSubarray(vector<int> &nums)
    {
        int n = nums.size();
        int l = 0, r = 0;           // Left and right pointers
        int sum = 0;                // Current window sum
        int mx = -1;                // Maximum unique subarray sum
        unordered_map<int, int> mp; // Frequency map of elements in window

        while (r < n)
        {
            mp[nums[r]] += 1;

            // If nums[r] is a duplicate, shrink the window from the left
            if (mp[nums[r]] > 1)
            {
                while (mp[nums[r]] > 1 && l <= r)
                {
                    sum -= nums[l];
                    mp[nums[l]] -= 1;
                    l += 1;
                }
            }

            // Add current element to sum and update max
            sum += nums[r];
            mx = max(mx, sum);
            r += 1;
        }

        return mx;
    }
};

/* ==============================================================================
 * Problem: Maximum Gain from Substrings
 * ==============================================================================
 * You are given a string `s` and two integers `x` and `y`.
 * You can remove substrings "ab" for x points and "ba" for y points.
 * The removal can be done in any order.
 *
 * Goal: Maximize total score from such removals.
 *
 * Strategy:
 * - Always remove the higher value pair first (greedy).
 * - Traverse and simulate removing either "ab" or "ba" first,
 *   depending on which of x or y is larger.
 * - Use counters to simulate a stack-like behavior efficiently.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * ============================================================================== */

class Solution
{
public:
    int maximumGain(string s, int x, int y)
    {
        int cnt1 = 0, cnt2 = 0; // Stack simulation counters
        int score = 0;
        int i = 0;

        // Decide which pair to remove first based on value
        while (i < s.size())
        {
            if (y >= x)
            {
                // Prefer removing "ba" first (y is higher)
                if (s[i] == 'b')
                {
                    cnt2++;
                }
                else if (s[i] == 'a')
                {
                    if (cnt2 > 0)
                    {
                        cnt2--;     // Match with previous 'b'
                        score += y; // Add score for "ba"
                    }
                    else
                    {
                        cnt1++; // 'a' with no matching 'b'
                    }
                }
                else
                {
                    // Any non a/b character, reset and remove "ab" pairs
                    score += (x * min(cnt1, cnt2));
                    cnt1 = cnt2 = 0;
                }
            }
            else
            {
                // Prefer removing "ab" first (x is higher)
                if (s[i] == 'a')
                {
                    cnt2++;
                }
                else if (s[i] == 'b')
                {
                    if (cnt2 > 0)
                    {
                        cnt2--;     // Match with previous 'a'
                        score += x; // Add score for "ab"
                    }
                    else
                    {
                        cnt1++; // 'b' with no matching 'a'
                    }
                }
                else
                {
                    // Reset and remove "ba" pairs
                    score += (y * min(cnt1, cnt2));
                    cnt1 = cnt2 = 0;
                }
            }
            i++;
        }

        // Final leftover pair cleanup (secondary lower-valued pair)
        score += min(x, y) * min(cnt1, cnt2);
        return score;
    }
};

/* ==============================================================================
 * LeetCode 2322: Minimum Score After Removals on a Tree
 * ==============================================================================
 * Problem:
 * You are given a tree with `n` nodes and a value on each node. Remove two edges
 * such that the tree is split into three components. Return the minimum possible
 * difference between the maximum and minimum XOR value of these components.
 *
 * Approach: Post-order Traversal + Bit Manipulation + Preprocessing
 * - Use a queue to simulate DFS leaf removal.
 * - Track subtree XOR values and structure using a children set.
 * - Try all pairs of edges, classify their relation and calculate partition XORs.
 * - Take minimum of (max - min) over all valid 2-edge removals.
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(n^2)
 * ============================================================================== */

class Solution
{
public:
    int minimumScore(vector<int> &nums, vector<vector<int>> &edges)
    {
        int n = nums.size();
        vector<vector<int>> graph(n);
        vector<unordered_set<int>> children(n);
        vector<int> xor_val(nums);
        vector<int> degree(n, 0);

        // Build the tree graph
        for (const auto &e : edges)
        {
            int u = e[0], v = e[1];
            graph[u].push_back(v);
            graph[v].push_back(u);
            degree[u]++;
            degree[v]++;
        }

        int total = 0;
        queue<int> q;
        vector<bool> seen(n, false);

        // Initialize: XOR of all values, find all leaves
        for (int i = 0; i < n; ++i)
        {
            total ^= nums[i];
            if (degree[i] == 1)
            {
                q.push(i);
                seen[i] = true;
            }
        }

        // Bottom-up traversal to build children sets and xor_val
        while (!q.empty())
        {
            int cur = q.front();
            q.pop();
            for (int next : graph[cur])
            {
                if (!seen[next])
                {
                    children[next].insert(cur);
                    children[next].insert(children[cur].begin(), children[cur].end());
                    xor_val[next] ^= xor_val[cur];
                }
                degree[next]--;
                if (degree[next] == 1 && !seen[next])
                {
                    seen[next] = true;
                    q.push(next);
                }
            }
        }

        int res = INT_MAX;
        int m = edges.size();

        // Try all edge pairs
        for (int i = 0; i < m - 1; ++i)
        {
            for (int j = i + 1; j < m; ++j)
            {
                int a = edges[i][0], b = edges[i][1];
                if (children[a].count(b))
                    swap(a, b);

                int c = edges[j][0], d = edges[j][1];
                if (children[c].count(d))
                    swap(c, d);

                vector<int> vals;

                // Classify relationship of subtrees and compute XOR partitions
                if (children[a].count(c))
                {
                    vals = {xor_val[c], xor_val[a] ^ xor_val[c], total ^ xor_val[a]};
                }
                else if (children[c].count(a))
                {
                    vals = {xor_val[a], xor_val[c] ^ xor_val[a], total ^ xor_val[c]};
                }
                else
                {
                    vals = {xor_val[a], xor_val[c], total ^ xor_val[a] ^ xor_val[c]};
                }

                int max_v = *max_element(vals.begin(), vals.end());
                int min_v = *min_element(vals.begin(), vals.end());
                res = min(res, max_v - min_v);
            }
        }

        return res;
    }
};

/* ==============================================================================
 * LeetCode 3487: Max Sum of Unique Positive Integers
 * ==============================================================================
 * Problem:
 * Given an array of integers `nums`, return the sum of all unique positive elements.
 * If no such elements exist, return the maximum number in the array.
 *
 * Approach: Set + Conditional Sum
 * - Use a hash set to track unique elements.
 * - For each new unique element, add it to the sum if it's non-negative.
 * - Track the maximum element in case all values are negative.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * ============================================================================== */

class Solution
{
public:
    int maxSum(vector<int> &nums)
    {
        unordered_set<int> s;
        int sum = 0, mx = INT_MIN;
        bool allNegative = true;

        for (int num : nums)
        {
            mx = max(mx, num);
            int prevSize = s.size();
            s.insert(num);

            // If inserted (i.e., was unique)
            if (s.size() != prevSize)
            {
                if (num >= 0)
                {
                    sum += num;
                    allNegative = false;
                }
            }
        }

        return allNegative ? mx : sum;
    }
};
