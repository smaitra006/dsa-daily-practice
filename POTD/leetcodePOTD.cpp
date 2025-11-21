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

class Solution
{
public:
  struct Node
  {
    string name;
    unordered_map<string, Node *> children;
    string signature;

    Node(string name) : name(name) {}
  };

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

/* ==============================================================================
 * LeetCode XXXX: Max Subarrays After Resolving Conflicts
 * ==============================================================================
 * Problem:
 * Given an integer `n` and a list of `conflictingPairs` where each pair [a, b]
 * implies a conflict between index `a` and `b`, calculate the maximum number
 * of valid subarrays that can be formed while accounting for conflicts.
 *
 * Approach: Greedy + Sorting + Gain Tracking
 * - Normalize all conflicting pairs to ensure a < b.
 * - Sort the pairs by their second value.
 * - Use max1 and max2 to track furthest non-overlapping starts.
 * - Track gain and occupied space at each step.
 * - Final result is total - totalOccupied + maxGain.
 *
 * Time Complexity: O(m log m) where m is the number of conflicting pairs
 * Space Complexity: O(1) extra (in-place operations)
 * ============================================================================== */

class Solution
{
public:
  long long maxSubarrays(int n, std::vector<std::vector<int>> &conflictingPairs)
  {
    // Normalize each pair so the smaller index comes first
    for (auto &pair : conflictingPairs)
    {
      if (pair[1] < pair[0])
      {
        std::swap(pair[0], pair[1]);
      }
    }

    // Sort pairs by the second index
    std::sort(conflictingPairs.begin(), conflictingPairs.end(),
              [](const std::vector<int> &a, const std::vector<int> &b)
              {
                return a[1] < b[1];
              });

    int m = conflictingPairs.size();
    int max1 = 0, max2 = 0;
    long long gain = 0, maxGain = 0, totalOccupied = 0;

    for (int i = 0; i < m; ++i)
    {
      int start = conflictingPairs[i][0];
      int base = n + 1 - conflictingPairs[i][1];

      // Adjust base if there’s a next conflict
      if (i < m - 1)
      {
        base = conflictingPairs[i + 1][1] - conflictingPairs[i][1];
      }

      // Update top two maximums
      if (start > max1)
      {
        max2 = max1;
        max1 = start;
        gain = 0;
      }
      else if (start > max2)
      {
        max2 = start;
      }

      gain += static_cast<long long>(max1 - max2) * base;
      totalOccupied += static_cast<long long>(max1) * base;

      maxGain = std::max(maxGain, gain);
    }

    long long total = static_cast<long long>(n) * (n + 1) / 2;
    return total - totalOccupied + maxGain;
  }
};

/* ==============================================================================
 * LeetCode 2210: Count Hills and Valleys in an Array
 * ==============================================================================
 * Problem:
 * A hill is defined as an element that is strictly greater than its closest non-equal
 * neighbors. A valley is defined as an element that is strictly smaller than its
 * closest non-equal neighbors. Return the number of hills and valleys in `nums`.
 *
 * Approach: Skip Equal Neighbors + Compare with Previous
 * - Traverse the array while skipping equal consecutive elements.
 * - Compare current element with last valid distinct number (`j`) and the next.
 * - Count hills (peak) and valleys (dip) based on inequality patterns.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * ============================================================================== */

class Solution
{
public:
  int countHillValley(vector<int> &nums)
  {
    int cnt = 0;
    int j = 0;
    int n = nums.size();

    for (int i = 1; i < n - 1; ++i)
    {
      if ((nums[j] < nums[i] && nums[i] > nums[i + 1]) || // Hill
          (nums[j] > nums[i] && nums[i] < nums[i + 1]))
      { // Valley
        cnt++;
        j = i;
      }
    }

    return cnt;
  }
};

/* ================================================================
 * COUNT MAXIMUM OR SUBSETS (Leetcode 2044)
 * ================================================================
 *
 * Problem:
 * --------
 * Given an integer array nums, return the number of non-empty subsets whose bitwise OR is equal to the maximum possible bitwise OR of nums.
 *
 * Approach:
 * ---------
 * 1. First, compute the maximum OR possible of the full array.
 * 2. Explore all subsets using recursion or DP.
 * 3. Count those with OR value equal to the maximum.
 *
 * TIME COMPLEXITY: O(2^n)
 * SPACE COMPLEXITY: O(n) recursion depth (for backtracking)
 */

class Solution
{
public:
  /* ---------------------------------------------------------------
   * METHOD 1: Recursion (Brute-force all subsets)
   * TIME: O(2^n)
   * SPACE: O(n) recursion stack
   * --------------------------------------------------------------- */
  int recur(vector<int> &nums, int i, int currOR, int maxOR)
  {
    if (i == nums.size())
      return currOR == maxOR ? 1 : 0;

    int not_take = recur(nums, i + 1, currOR, maxOR);
    int take = recur(nums, i + 1, currOR | nums[i], maxOR);

    return not_take + take;
  }

  /* ---------------------------------------------------------------
   * METHOD 2: Memoization (Top-Down DP with OR compression)
   * TIME: O(n * 2^13)   [since max OR value for constraints is <= 2^13]
   * SPACE: O(n * 2^13)
   * --------------------------------------------------------------- */
  int memo(int i, int currOR, vector<int> &nums, int maxOR, vector<vector<int>> &dp)
  {
    if (i == nums.size())
      return currOR == maxOR ? 1 : 0;

    if (dp[i][currOR] != -1)
      return dp[i][currOR];

    int not_take = memo(i + 1, currOR, nums, maxOR, dp);
    int take = memo(i + 1, currOR | nums[i], nums, maxOR, dp);

    return dp[i][currOR] = not_take + take;
  }

  /* ---------------------------------------------------------------
   * METHOD 3: Tabulation (Bottom-Up DP)
   * TIME: O(n * 2^13)
   * SPACE: O(n * 2^13)
   * --------------------------------------------------------------- */
  int tabulation(vector<int> &nums)
  {
    int n = nums.size();
    int maxOR = 0;
    for (int num : nums)
      maxOR |= num;

    vector<vector<int>> dp(n + 1, vector<int>(1 << 13, 0));
    dp[0][0] = 1;

    for (int i = 0; i < n; i++)
    {
      for (int or_val = 0; or_val < (1 << 13); or_val++)
      {
        if (dp[i][or_val])
        {
          dp[i + 1][or_val] += dp[i][or_val];           // not take
          dp[i + 1][or_val | nums[i]] += dp[i][or_val]; // take
        }
      }
    }

    return dp[n][maxOR];
  }

  /* ---------------------------------------------------------------
   * METHOD 4: Optimized DFS (Final Submission)
   * TIME: O(2^n)
   * SPACE: O(n)
   * --------------------------------------------------------------- */
  int solve(vector<int> &nums, int i, int currOR, int maxOR)
  {
    if (i == nums.size())
      return currOR == maxOR ? 1 : 0;

    int not_take = solve(nums, i + 1, currOR, maxOR);
    int take = solve(nums, i + 1, currOR | nums[i], maxOR);

    return not_take + take;
  }

  int countMaxOrSubsets(vector<int> &nums)
  {
    int maxOR = 0;
    for (int val : nums)
      maxOR |= val;

    return solve(nums, 0, 0, maxOR);
  }
};

/* ==============================================================================
 * LeetCode 2411: Smallest Subarrays With Maximum Bitwise OR
 * ==============================================================================
 * Problem:
 * You are given an array `nums`. For every index `i`, find the length of the smallest
 * subarray starting at `i` such that the bitwise OR of the subarray equals the
 * maximum possible bitwise OR from that starting index.
 *
 * Approach: Bit Tracking + Backward Scan
 * - Traverse from right to left to maintain the last seen position of each bit.
 * - For each index, determine how far to extend the subarray to include all 1s
 *   required to match the max OR from that index.
 *
 * Time Complexity: O(n * 30)
 * Space Complexity: O(30) = O(1)
 * ============================================================================== */

class Solution
{
public:
  vector<int> smallestSubarrays(vector<int> &nums)
  {
    int n = nums.size();
    vector<int> lastSeen(30, 0); // Last seen index for each bit (0 to 29)
    vector<int> res(n, 1);       // Result: length of smallest subarray for each index

    // Traverse from end to start
    for (int i = n - 1; i >= 0; --i)
    {
      for (int bit = 0; bit < 30; ++bit)
      {
        if ((nums[i] & (1 << bit)) > 0)
        {
          lastSeen[bit] = i;
        }

        // Update subarray length to include this bit's last occurrence
        res[i] = max(res[i], lastSeen[bit] - i + 1);
      }
    }

    return res;
  }
};

/* ==============================================================================
 * LeetCode 2419: Longest Subarray With Maximum Bitwise AND
 * ==============================================================================
 * Problem:
 * You are given an array `nums`. Find the length of the longest subarray where
 * every element is equal to the maximum element of the array.
 *
 * Approach: Linear Scan
 * - First, find the maximum value in the array.
 * - Then scan the array and count the longest contiguous sequence of elements
 *   equal to that maximum.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * ============================================================================= */

class Solution
{
public:
  int longestSubarray(vector<int> &nums)
  {
    int maxx = *max_element(nums.begin(), nums.end()); // Find maximum element
    int y = 0, maxy = 0;                               // y: current streak, maxy: longest streak

    // Traverse the array
    for (int num : nums)
    {
      if (num == maxx)
      {
        y++;
        maxy = max(maxy, y); // Update longest streak if needed
      }
      else
      {
        y = 0; // Reset streak
      }
    }

    return maxy;
  }
};

/* ==============================================================================
 * LeetCode 898: Bitwise ORs of Subarrays
 * ==============================================================================
 * Problem:
 * Given an integer array `arr`, return the number of distinct values in the
 * bitwise OR of all subarrays.
 *
 * Approach: Sliding OR Window + Set Tracking
 * - Maintain a running set `curr` of all possible ORs ending at the current index.
 * - For each element:
 *     - Start a new set `next` with the current number.
 *     - For each value in `curr`, OR it with the current number and store it in `next`.
 *     - Replace `curr` with `next` and merge into the global answer set.
 *
 * Time Complexity: O(n * 30)  -- At most 30 distinct OR values per position
 * Space Complexity: O(n * 30)
 * ============================================================================= */

class Solution
{
public:
  int subarrayBitwiseORs(vector<int> &arr)
  {
    unordered_set<int> ans, curr;

    for (int num : arr)
    {
      unordered_set<int> next;
      next.insert(num);

      for (int i : curr)
      {
        next.insert(i | num); // OR with previous subarray values
      }

      curr = next;

      for (int i : curr)
      {
        ans.insert(i); // Add all OR results to answer set
      }
    }

    return ans.size();
  }
};

/* ==============================================================================
 * LeetCode 118: Pascal's Triangle
 * ==============================================================================
 * Problem:
 * Given an integer `numRows`, generate the first `numRows` of Pascal's Triangle.
 *
 * Approach: Dynamic Programming (Bottom-Up Construction)
 * - Initialize a 2D vector of size `numRows`.
 * - Each row starts and ends with 1.
 * - Every inner element is the sum of the two elements directly above it.
 *
 * Time Complexity: O(numRows^2)
 * Space Complexity: O(numRows^2)
 * ============================================================================= */

class Solution
{
public:
  vector<vector<int>> generate(int numRows)
  {
    vector<vector<int>> result(numRows);

    for (int i = 0; i < numRows; ++i)
    {
      result[i] = vector<int>(i + 1, 1); // Initialize row with 1s

      // Compute inner values using previous row
      for (int j = 1; j < i; ++j)
      {
        result[i][j] = result[i - 1][j - 1] + result[i - 1][j];
      }
    }

    return result;
  }
};

/* ==============================================================================
 * LeetCode 2563: Count the Minimum Cost of Rearranging Two Baskets
 * ==============================================================================
 * Problem:
 * You are given two integer arrays `basket1` and `basket2` of the same length.
 * In one move, you can swap elements between the arrays. Find the **minimum total cost**
 * to make both baskets equal, where the cost of a swap is the minimum of the two swapped values.
 * If it's not possible, return -1.
 *
 * Approach: Frequency Mapping + Greedy Swap Cost
 * - Count the net frequency of each element across both baskets.
 * - If any element has an odd frequency, it's impossible to make them equal → return -1.
 * - Store half of the excess elements in a temp array.
 * - Sort the temp array and greedily compute the cost of pairing smallest values,
 *   considering whether it's cheaper to double-swap the globally smallest element.
 *
 * Time Complexity: O(n log n)
 * Space Complexity: O(n)
 * ============================================================================= */

class Solution
{
public:
  long long minCost(vector<int> &basket1, vector<int> &basket2)
  {
    unordered_map<int, int> mpp;

    // Frequency difference between baskets
    for (int b : basket1)
      mpp[b]++;
    for (int b : basket2)
      mpp[b]--;

    int minEle = INT_MAX;
    vector<int> temp;

    // Collect excess elements (half of net imbalance)
    for (auto &[val, freq] : mpp)
    {
      if (freq % 2 != 0)
        return -1; // Impossible to balance

      for (int i = 0; i < abs(freq) / 2; ++i)
      {
        temp.push_back(val);
      }

      minEle = min(minEle, val); // Track minimum element overall
    }

    sort(temp.begin(), temp.end());
    long long ans = 0;

    // Greedily choose the minimum cost: direct swap vs double swap via minEle
    for (int i = 0; i < temp.size() / 2; ++i)
    {
      ans += min(temp[i], 2 * minEle);
    }

    return ans;
  }
};

/* ==============================================================================
 * LeetCode 904: Fruit Into Baskets
 * ==============================================================================
 * Problem:
 * You are given an array `fruits` where each element is a type of fruit.
 * Starting from any index, you can pick fruits moving only to the right, and you can
 * carry at most **two types** of fruits. Return the **length of the longest subarray**
 * containing at most two types of fruits.
 *
 * Approach: Sliding Window + Hash Map
 * - Use a sliding window to maintain a range with at most 2 distinct fruit types.
 * - Expand the window by moving the right pointer.
 * - Shrink the window from the left whenever we have more than two types.
 * - Update the maximum length found at each step.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1) — since map size is bounded (max 3 entries)
 * ============================================================================= */

class Solution
{
public:
  int totalFruit(vector<int> &fruits)
  {
    int n = fruits.size();
    int l = 0, r = 0;
    int maxLen = 0;
    unordered_map<int, int> mp;

    while (r < n)
    {
      mp[fruits[r]]++; // Add current fruit type to the basket

      // Shrink window if we exceed two types
      while (mp.size() > 2)
      {
        mp[fruits[l]]--;
        if (mp[fruits[l]] == 0)
        {
          mp.erase(fruits[l]);
        }
        l++;
      }

      maxLen = max(maxLen, r - l + 1); // Update max length
      r++;
    }

    return maxLen;
  }
};

/* ==============================================================================
 * Problem: Count Unplaced Fruits
 * ==============================================================================
 * Given two arrays `fruits` and `baskets`, each of size `n`, determine how many
 * fruits could not be placed in baskets. Each fruit can only go into a basket
 * that has a capacity >= size of the fruit. Each basket can hold only one fruit.
 *
 * Approach:
 * - For each fruit, try to find the first unvisited basket that can accommodate it.
 * - Mark that basket as used (`visited[j] = 1`).
 * - Count baskets that remain unvisited (i.e., no fruit could be placed).
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(n)
 * ============================================================================== */

class Solution
{
public:
  int numOfUnplacedFruits(vector<int> &fruits, vector<int> &baskets)
  {
    int n = baskets.size();
    vector<int> visited(n, -1); // -1: unused basket

    // Try to place each fruit
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (visited[j] == -1 && baskets[j] >= fruits[i])
        {
          visited[j] = 1; // Mark basket as used
          break;
        }
      }
    }

    // Count unvisited (unused) baskets
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
      if (visited[i] == -1)
      {
        cnt++;
      }
    }

    return cnt;
  }
};

/* ==============================================================================
 * Problem: Number of Unplaced Fruits
 *
 * Task:
 * - You are given two arrays: `fruits` and `baskets`.
 * - Each fruit has a size, and each basket has a capacity.
 * - Assign each fruit to a basket such that:
 *     → A fruit can only be placed in a basket if its size ≤ basket capacity.
 *     → A basket can hold at most one fruit.
 * - Count how many fruits cannot be placed in any basket.
 *
 * Optimized Approach:
 * - Use a Segment Tree to store the current max capacity of each basket.
 * - For each fruit:
 *     → Find the leftmost basket with capacity ≥ fruit size.
 *     → If found, assign it (set capacity to 0 in tree).
 *     → Else, increment unplaced fruit count.
 *
 * Time Complexity  : O(n log n)
 * Space Complexity : O(4n)
 * ============================================================================== */

class Solution
{
  int n;
  vector<int> seg; // Segment tree array

  // Utility: Update current node from its children
  void Update(int p)
  {
    seg[p] = max(seg[p << 1], seg[p << 1 | 1]);
  }

  // Build segment tree from baskets array
  void Build(int p, int l, int r, vector<int> &baskets)
  {
    if (l == r)
    {
      seg[p] = baskets[l];
      return;
    }
    int mid = (l + r) >> 1;
    Build(p << 1, l, mid, baskets);
    Build(p << 1 | 1, mid + 1, r, baskets);
    Update(p);
  }

  // Assign a value `v` to basket at position `x`
  void Assign(int x, int v, int p, int l, int r)
  {
    if (x < l || x > r)
      return;

    if (l == r)
    {
      seg[p] = v;
      return;
    }

    int mid = (l + r) >> 1;
    Assign(x, v, p << 1, l, mid);
    Assign(x, v, p << 1 | 1, mid + 1, r);
    Update(p);
  }

  // Query: Find leftmost basket index with capacity ≥ v
  int FirstLarger(int v, int p, int l, int r)
  {
    if (seg[p] < v)
      return r + 1; // No such basket

    if (l == r)
      return r;

    int mid = (l + r) >> 1;
    int lf = FirstLarger(v, p << 1, l, mid);
    if (lf <= mid)
      return lf;

    return FirstLarger(v, p << 1 | 1, mid + 1, r);
  }

public:
  int numOfUnplacedFruits(vector<int> &fruits, vector<int> &baskets)
  {
    n = fruits.size();
    seg.assign(4 * n + 1, 0); // Initialize segment tree

    Build(1, 0, n - 1, baskets); // Build tree from basket capacities

    int res = 0; // Counter for unplaced fruits

    for (const auto &x : fruits)
    {
      int pos = FirstLarger(x, 1, 0, n - 1);
      if (pos == n)
      {
        res++; // No valid basket
      }
      else
      {
        Assign(pos, 0, 1, 0, n - 1); // Use the basket
      }
    }

    return res;
  }
};

/* ==============================================================================
 * Problem: 808. Soup Servings (Leetcode)
 *
 * Description:
 * - There are two soups A and B, initially with n ml each.
 * - Four types of operations are chosen with equal probability:
 *      1. Serve 100 ml of A, 0 ml of B
 *      2. Serve 75 ml of A, 25 ml of B
 *      3. Serve 50 ml of A, 50 ml of B
 *      4. Serve 25 ml of A, 75 ml of B
 * - The process stops when either soup is empty.
 * - Return the probability that soup A will be empty first, plus half the probability
 *   that both become empty at the same time.
 *
 * Key Observations:
 * 1. Since servings are multiples of 25 ml, we can normalize n to "units" of 25 ml.
 * 2. If n is very large (> 4450 ml), the probability approaches 1 and we can directly return 1.
 * 3. Use DP where dp[i][j] = probability result with i units of A and j units of B left.
 *
 * Approach:
 * - Normalize: N = ceil(n / 25)
 * - Bottom-up DP:
 *      Base cases:
 *        - dp[0][0] = 0.5   (both empty simultaneously)
 *        - dp[0][j] = 1.0   (A empty first)
 *        - dp[i][0] = 0.0   (B empty first)
 *      Transition:
 *        dp[i][j] = average of 4 serving scenarios.
 *
 * Time Complexity  : O(N^2)
 * Space Complexity : O(N^2)
 * ============================================================================== */

class Solution
{
public:
  double soupServings(int n)
  {
    // Optimization: for large n, probability is ~1
    if (n > 4450)
      return 1;

    // Convert ml to units of 25 ml (ceiling division)
    int N = (n + 24) / 25;

    // DP table: dp[i][j] → probability with i units of A, j units of B
    vector<vector<double>> dp(N + 1, vector<double>(N + 1, 0.0));

    // Base cases
    dp[0][0] = 0.5; // Both empty at same time
    for (int j = 1; j <= N; ++j)
      dp[0][j] = 1.0; // A empty first
    for (int i = 1; i <= N; ++i)
      dp[i][0] = 0.0; // B empty first

    // Fill table bottom-up
    for (int i = 1; i <= N; ++i)
    {
      for (int j = 1; j <= N; ++j)
      {
        dp[i][j] = 0.25 * (dp[max(0, i - 4)][j] +
                           dp[max(0, i - 3)][max(0, j - 1)] +
                           dp[max(0, i - 2)][max(0, j - 2)] +
                           dp[max(0, i - 1)][max(0, j - 3)]);
      }
    }

    return dp[N][N];
  }
};

/* ==============================================================================
 * Problem: Reordered Power of 2
 *
 * Task:
 * - Given a positive integer `N`, check if its digits can be rearranged
 *   to form a power of 2.
 *
 * Approach:
 * 1. **Digit Frequency Counting**:
 *    - Count the occurrences of each digit in `N`.
 * 2. **Power of 2 Generation**:
 *    - For all powers of 2 up to 2^30 (since 2^30 < 10^9), count digit frequencies.
 * 3. **Comparison**:
 *    - If the frequency matches with any power of 2, return `true`.
 *
 * Time Complexity  : O(30 * log10(N)) — At most 31 frequency comparisons.
 * Space Complexity : O(1) — Constant extra storage for frequency arrays.
 * ============================================================================== */

class Solution
{
private:
  // Count digit frequency of an integer
  vector<int> digitFreq(int n)
  {
    vector<int> freq(10, 0);
    while (n > 0)
    {
      freq[n % 10]++;
      n /= 10;
    }
    return freq;
  }

  // Compare two digit frequency arrays
  bool equalFreq(const vector<int> &a, const vector<int> &b)
  {
    for (int i = 0; i < 10; ++i)
    {
      if (a[i] != b[i])
        return false;
    }
    return true;
  }

public:
  bool reorderedPowerOf2(int N)
  {
    vector<int> target = digitFreq(N);

    // Check all powers of 2 up to 2^30
    for (int i = 0; i <= 30; ++i)
    {
      int powerOf2 = (int)pow(2, i);
      if (equalFreq(target, digitFreq(powerOf2)))
      {
        return true;
      }
    }
    return false;
  }
};

/* ==============================================================================
 * Example Usage:
 *
 * int main() {
 *     Solution sol;
 *     cout << boolalpha << sol.reorderedPowerOf2(46) << endl; // Output: true (46 → 64)
 *     cout << boolalpha << sol.reorderedPowerOf2(10) << endl; // Output: false
 *
 *     return 0;
 * }
 * ============================================================================== */

// ============================================================================
// Problem: Product Queries of Powers
// Approach:
//   1. Extract all powers of 2 present in n's binary representation.
//   2. For each query [l, r], compute the product of powers in that range.
//   3. Use modulo 1e9+7 to avoid overflow.
// Complexity:
//   Time: O(log n + q * log n) — log n to extract powers, each query up to log n multiplications.
//   Space: O(log n) — storing extracted powers of 2.
// ============================================================================

class Solution
{
public:
  vector<int> productQueries(int n, vector<vector<int>> &queries)
  {
    const int MOD = 1e9 + 7;
    vector<long> powers; // Store the powers of 2 from n's binary form
    vector<int> result;

    // Extract all powers of 2 present in n
    int bitIndex = 0;
    while (n > 0)
    {
      if (n & 1)
      {
        powers.push_back(1L << bitIndex);
      }
      n >>= 1;
      bitIndex++;
    }

    // Process each query
    for (auto &q : queries)
    {
      long long product = 1;
      for (int j = q[0]; j <= q[1]; j++)
      {
        product = (product * powers[j]) % MOD;
      }
      result.push_back(static_cast<int>(product));
    }

    return result;
  }
};

/*
================================================================================
Problem:
    Given two integers n and x, return the number of ways n can be expressed
    as the sum of the x-th powers of unique natural numbers.

Approach:
    1. Precompute the maximum base whose x-th power is <= n.
    2. Use recursion with memoization to explore:
        - "Take" the current base (subtract its x-th power from n)
        - "Not take" the current base
    3. Use modulo to prevent overflow.

Key Points:
    - Memoization ensures optimal subproblem reuse.
    - Binary search to find max base to avoid unnecessary recursion.
    - Power computation is done with an integer exponentiation helper.

Complexity:
    Let m = maxBaseInt(n, x)
    Time Complexity: O(n * m)
    Space Complexity: O(n * m)  (due to memoization table)
================================================================================
*/

class Solution
{
public:
  const int MOD = 1e9 + 7;

  //--------------------------------------------------------------------------
  // Helper: Compute integer power (base^exp)
  //--------------------------------------------------------------------------
  long long intPow(int base, int exp)
  {
    long long result = 1;
    while (exp--)
    {
      result *= base;
    }
    return result;
  }

  //--------------------------------------------------------------------------
  // Recursive function with memoization
  // n     -> remaining sum
  // x     -> power to be used
  // i     -> current base to consider
  // memo  -> DP cache
  //--------------------------------------------------------------------------
  int recur(int n, int x, int i, vector<vector<int>> &memo)
  {
    if (n == 0)
      return 1; // Exact sum found
    if (n < 0 || i <= 0)
      return 0; // Invalid path

    if (memo[n][i] != -1)
      return memo[n][i];

    // Option 1: Do not take current base
    int not_take = recur(n, x, i - 1, memo) % MOD;

    // Option 2: Take current base (if possible)
    int take = 0;
    long long power = intPow(i, x);
    if (n - power >= 0)
    {
      take = recur(n - power, x, i - 1, memo) % MOD;
    }

    return memo[n][i] = (take + not_take) % MOD;
  }

  //--------------------------------------------------------------------------
  // Helper: Find max integer base whose x-th power <= n
  //--------------------------------------------------------------------------
  int maxBaseInt(int n, int x)
  {
    int lo = 1, hi = n;
    while (lo <= hi)
    {
      int mid = (lo + hi) / 2;
      long long p = 1;
      for (int i = 0; i < x; i++)
      {
        p *= mid;
        if (p > n)
          break;
      }
      if (p == n)
        return mid;
      if (p < n)
        lo = mid + 1;
      else
        hi = mid - 1;
    }
    return hi;
  }

  //--------------------------------------------------------------------------
  // Main Function
  //--------------------------------------------------------------------------
  int numberOfWays(int n, int x)
  {
    vector<vector<int>> memo(n + 1, vector<int>(n + 1, -1));
    int maxBase = maxBaseInt(n, x);
    return recur(n, x, maxBase, memo);
  }
};

/*
================================================================================
Problem: Power of Three (LeetCode 326)
================================================================================
Task:
    Given an integer n, return true if it is a power of three. Otherwise, return false.

    A power of three is a number of the form 3^x where x is an integer and x >= 0.

--------------------------------------------------------------------------------
Approach:
    1. If n <= 0, it cannot be a power of three → return false.
    2. Repeatedly divide n by 3 as long as it is divisible by 3.
    3. If the final result is 1, then n was a power of three; otherwise, it wasn’t.

--------------------------------------------------------------------------------
Complexity Analysis:
    Time Complexity:  O(log₃ n)
        - Each division by 3 reduces n by a factor of 3.

    Space Complexity: O(1)
        - No extra space used.
================================================================================
*/

class Solution
{
public:
  bool isPowerOfThree(int n)
  {
    if (n <= 0)
      return false; // Negative numbers & zero can't be powers of 3

    while (n % 3 == 0)
    {
      n /= 3; // Keep dividing by 3
    }

    return n == 1; // If reduced to 1 → it's a power of 3
  }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    n = 27
Output:
    true
Explanation:
    27 = 3³ → power of three
================================================================================
*/

/*
================================================================================
Problem: Largest 3-Same-Digit Number in String (LeetCode 2264)
================================================================================
Task:
    Given a string num representing a large integer, return the largest good
    integer as a string.

    A "good integer" is a substring of length 3 that consists of the same digit.
    If no such substring exists, return "".

--------------------------------------------------------------------------------
Approach:
    1. Iterate through the string from index 1 to length-2.
    2. Check if current digit and its previous & next digits are equal.
    3. Keep track of the largest digit seen that forms a good integer.
    4. Return the string of that digit repeated 3 times, or "" if none found.

--------------------------------------------------------------------------------
Complexity Analysis:
    Time Complexity:  O(n)
        - We scan the string once.
    Space Complexity: O(1)
        - Only a few variables are used.
================================================================================
*/

class Solution
{
public:
  string largestGoodInteger(string num)
  {
    int largest = INT_MIN; // Track largest digit found
    string result = "";

    for (int i = 1; i < (int)num.length() - 1; i++)
    {
      if (num[i - 1] == num[i] && num[i] == num[i + 1])
      {
        if (num[i] - '0' > largest)
        {
          largest = num[i] - '0';
          result = string(3, num[i]); // Create "xxx"
        }
      }
    }

    return (largest == INT_MIN) ? "" : result;
  }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    num = "6777133339"
Output:
    "777"
Explanation:
    Good integers: "777", "333"
    Largest is "777"
================================================================================
*/

/*
================================================================================
Problem: Power of Four (LeetCode 342)
================================================================================
Task:
    Given an integer n, return true if it is a power of four.
    Otherwise, return false.

    An integer n is a power of four if there exists an integer x such that:
        n == 4^x

--------------------------------------------------------------------------------
Approach:
    1. Handle base cases:
        - If n == 1 → true (4^0 = 1)
        - If n < 4 → false
    2. While n is divisible by 4, keep dividing by 4.
    3. If after all divisions, n becomes 1 → return true.
    4. Else → return false.

--------------------------------------------------------------------------------
Complexity Analysis:
    Time Complexity:  O(log₄(n))  // Each division reduces n by factor of 4
    Space Complexity: O(1)        // Constant space used
================================================================================
*/

class Solution
{
public:
  bool isPowerOfFour(int n)
  {
    if (n == 1)
      return true; // 4^0 = 1
    if (n < 4)
      return false; // Cannot be a power of 4

    while (n % 4 == 0)
    { // Keep dividing by 4
      n /= 4;
    }

    return n == 1;
  }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    n = 16
Output:
    true
Explanation:
    16 = 4^2 → power of four.

--------------------------------------------------------------------------------
Input:
    n = 8
Output:
    false
Explanation:
    8 is not a power of four.
================================================================================
*/

/*
================================================================================
Problem: Maximum 69 Number (LeetCode 1323)
================================================================================
Task:
    You are given a positive integer num consisting only of digits 6 and 9.
    Return the maximum number you can get by changing at most one digit (6 → 9).

--------------------------------------------------------------------------------
Approach:
    1. Extract all digits from num and store them in a vector.
    2. Reverse to restore correct digit order.
    3. Traverse digits from left to right:
        - Change the first occurrence of 6 → 9 (to maximize the number).
        - Break after the first change.
    4. Reconstruct the number from the updated digits.
    5. Return the new number.

--------------------------------------------------------------------------------
Complexity Analysis:
    Time Complexity:  O(d)  // d = number of digits in num
    Space Complexity: O(d)  // for storing digits in a vector
================================================================================
*/

class Solution
{
public:
  int maximum69Number(int num)
  {
    vector<int> digits;

    // Extract digits from num
    while (num != 0)
    {
      digits.push_back(num % 10);
      num /= 10;
    }

    // Restore correct digit order
    reverse(digits.begin(), digits.end());

    // Change the first 6 → 9
    for (int i = 0; i < digits.size(); i++)
    {
      if (digits[i] == 6)
      {
        digits[i] = 9;
        break;
      }
    }

    // Reconstruct the number
    for (int i = 0; i < digits.size(); i++)
    {
      num = num * 10 + digits[i];
    }

    return num;
  }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    num = 9669
Output:
    9969
Explanation:
    Change the first '6' to '9' → maximum number.

--------------------------------------------------------------------------------
Input:
    num = 9999
Output:
    9999
Explanation:
    No '6' found → number remains unchanged.
================================================================================
*/

/*
================================================================================
Problem: 24 Game (LeetCode 679)
================================================================================
Task:
    You are given an integer array cards of length 4.
    You have four numbers and you need to return true if you can get 24 by
    applying the operations (+, -, *, /) and using each number exactly once.

    Operations can be performed in any order and at any depth of parentheses.

--------------------------------------------------------------------------------
Approach (Backtracking + Floating Point Precision):
    1. Convert integers to doubles (to handle division results).
    2. Recursively reduce the problem:
        - Pick any two numbers (i, j).
        - Combine them with all possible operations.
        - Recurse with the reduced set of numbers.
    3. Base case:
        - If only one number remains, check if it's close enough to 24.
    4. Use small epsilon (1e-6) for floating point comparison.

--------------------------------------------------------------------------------
Complexity Analysis:
    Time Complexity:  O(N! * N) ≈ O(4! * 4) = O(96)
        - For each pair of numbers, we try all 6 operations.
        - Search space is small (at most 4! permutations).
    Space Complexity: O(N) recursion depth + O(N) auxiliary storage
================================================================================
*/

class Solution
{
public:
  bool judgePoint24(vector<int> &cards)
  {
    vector<double> nums(cards.begin(), cards.end());
    return backtrack(nums);
  }

private:
  // Recursive helper
  bool backtrack(vector<double> nums)
  {
    // Base case: check if the last number is close to 24
    if (nums.size() == 1)
    {
      return fabs(nums[0] - 24.0) < 1e-6;
    }

    int n = nums.size();
    // Try all pairs of numbers
    for (int i = 0; i < n; i++)
    {
      for (int j = i + 1; j < n; j++)
      {
        vector<double> newNums;

        // Keep all numbers except i and j
        for (int k = 0; k < n; k++)
        {
          if (k != i && k != j)
            newNums.push_back(nums[k]);
        }

        // Try all combinations of nums[i] and nums[j]
        for (double x : combine(nums[i], nums[j]))
        {
          newNums.push_back(x);
          if (backtrack(newNums))
            return true;
          newNums.pop_back(); // backtrack
        }
      }
    }
    return false;
  }

  // Generate all possible results of combining a and b
  unordered_set<double> combine(double a, double b)
  {
    unordered_set<double> res;
    res.insert(a + b);
    res.insert(a - b);
    res.insert(b - a);
    res.insert(a * b);

    if (fabs(a) > 1e-6)
      res.insert(b / a);
    if (fabs(b) > 1e-6)
      res.insert(a / b);

    return res;
  }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    cards = [4, 1, 8, 7]
Output:
    true
Explanation:
    (8 - 4) * (7 - 1) = 24

--------------------------------------------------------------------------------
Input:
    cards = [1, 2, 1, 2]
Output:
    false
Explanation:
    No sequence of operations yields 24.
================================================================================
*/

/*
================================================================================
Problem: Zero-Filled Subarrays (LeetCode 2348)
================================================================================
Task:
    Given an integer array nums, return the number of subarrays filled with 0.

    A subarray is a contiguous non-empty sequence of elements within an array.

--------------------------------------------------------------------------------
Approach (Streak Counting):
    1. Traverse the array and maintain a running count `streak` of consecutive 0s.
    2. Each time we encounter a 0:
        - Increase `streak`.
        - Add `streak` to the total count `cnt` (since every new 0 extends
          all previous zero subarrays by 1, plus itself).
    3. Reset `streak` when a non-zero element is encountered.
    4. The accumulated `cnt` is the result.

--------------------------------------------------------------------------------
Complexity Analysis:
    Time Complexity:  O(N)
        - Single pass through nums.
    Space Complexity: O(1)
        - Constant extra space used.
================================================================================
*/

class Solution
{
public:
  long long zeroFilledSubarray(vector<int> &nums)
  {
    long long cnt = 0;    // Total count of zero-filled subarrays
    long long streak = 0; // Length of current consecutive zero streak

    for (int num : nums)
    {
      if (num == 0)
      {
        streak++;      // Extend streak
        cnt += streak; // Add all new subarrays ending here
      }
      else
      {
        streak = 0; // Reset streak
      }
    }
    return cnt;
  }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    nums = [1, 3, 0, 0, 2, 0, 0, 4]
Output:
    6
Explanation:
    Subarrays with all zeros:
    [0], [0], [0,0], [0], [0], [0,0]

--------------------------------------------------------------------------------
Input:
    nums = [0, 0, 0, 2, 0, 0]
Output:
    9
Explanation:
    Subarrays with all zeros:
    [0], [0], [0], [0,0], [0,0], [0], [0], [0,0], [0,0,0]
================================================================================
*/

/*
================================================================================
Problem: Count Square Submatrices with All Ones (LeetCode 1277)
================================================================================
Task:
    Given a m x n binary matrix (0s and 1s), return the total number of square
    submatrices with all ones.

--------------------------------------------------------------------------------
Approach (Dynamic Programming with In-Place Update):
    1. Each cell (i, j) in the matrix represents the maximum size of a square
       submatrix with all ones that ends at (i, j).
    2. Transition:
       If matrix[i][j] == 1 and i > 0 and j > 0:
            matrix[i][j] = min(
                                matrix[i-1][j],     // Top
                                matrix[i][j-1],     // Left
                                matrix[i-1][j-1]    // Top-left
                              ) + 1;
       Otherwise, it remains 1 (if it's already 1).
    3. Accumulate these values in `res` since each size-k square contributes to
       exactly one valid square ending at (i, j).
    4. Return the total count.

--------------------------------------------------------------------------------
Complexity Analysis:
    Time Complexity:  O(m * n)
        - We process each cell once.
    Space Complexity: O(1)
        - DP is done in-place by modifying the input matrix.
================================================================================
*/

class Solution
{
public:
  int countSquares(vector<vector<int>> &matrix)
  {
    int m = matrix.size();
    if (m == 0)
      return 0;

    int n = matrix[0].size();
    int res = 0; // Total count of square submatrices

    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (matrix[i][j] == 1 && i > 0 && j > 0)
        {
          // Update current cell with max square size ending here
          matrix[i][j] = min({
                             matrix[i - 1][j],    // Top
                             matrix[i][j - 1],    // Left
                             matrix[i - 1][j - 1] // Top-left
                         }) +
                         1;
        }
        res += matrix[i][j]; // Add all squares ending at (i, j)
      }
    }
    return res;
  }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    matrix = [
        [0,1,1,1],
        [1,1,1,1],
        [0,1,1,1]
    ]
Output:
    15
Explanation:
    Squares are counted as:
    - 10 squares of size 1
    - 4 squares of size 2
    - 1 square of size 3
    Total = 15

--------------------------------------------------------------------------------
Input:
    matrix = [
        [1,0,1],
        [1,1,0],
        [1,1,0]
    ]
Output:
    7
Explanation:
    Squares are counted as:
    - 6 squares of size 1
    - 1 square of size 2
    Total = 7
================================================================================
*/

/*
================================================================================
Problem: Count Submatrices With All Ones (LeetCode 1504)
================================================================================
Task:
    Given a binary matrix `mat`, return the number of submatrices
    that contain all ones.

--------------------------------------------------------------------------------
Approach:
    1. Use histogram technique:
        - For each row, build heights array `h[j]` representing
          consecutive `1`s up to that row for each column.
    2. For each position `(i, j)`:
        - Consider `h[j]` as the minimum height of rectangle ending at column j.
        - Extend leftwards (columns k = j → 0),
          maintaining the minimum height so far.
        - Accumulate the number of rectangles possible at each step.
    3. Sum across all rows.

--------------------------------------------------------------------------------
Complexity Analysis:
    Let m = rows, n = columns.

    Time Complexity:  O(m * n^2)
        - For each row, we process n columns and for each column,
          we may look leftwards up to n.
    Space Complexity: O(n)
        - For maintaining histogram heights.
================================================================================
*/

class Solution
{
public:
  int numSubmat(vector<vector<int>> &mat)
  {
    int m = mat.size(), n = mat[0].size();
    vector<int> h(n, 0); // histogram heights
    int cnt = 0;         // total submatrices

    for (int i = 0; i < m; i++)
    {
      // Step 1: update histogram heights for row i
      for (int j = 0; j < n; j++)
      {
        h[j] = mat[i][j] ? h[j] + 1 : 0;
      }

      // Step 2: count rectangles ending at row i
      for (int j = 0; j < n; j++)
      {
        int mn = h[j];
        for (int k = j; k >= 0 && mn > 0; k--)
        {
          mn = min(mn, h[k]); // minimum height across window
          cnt += mn;          // add possible submatrices
        }
      }
    }
    return cnt;
  }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    mat = [
        [1,0,1],
        [1,1,0],
        [1,1,0]
    ]

Output:
    13

Explanation:
    Possible submatrices with all ones are counted row by row using histogram.
--------------------------------------------------------------------------------
Notes:
    - Histogram trick converts the problem into rectangle counting.
    - Optimized stack-based solution exists with O(m * n),
      but this O(m * n^2) approach is acceptable for constraints.
================================================================================
*/

/*
==============================================================================
Problem: Minimum Sum of Three Non-Overlapping Rectangles Covering All Ones
==============================================================================
You are given a binary grid (matrix) consisting of 0s and 1s.
The task is to cover all cells containing 1s using at most three
non-overlapping rectangles. Each rectangle must cover only cells of the grid
(submatrix) and their total area is minimized.

Return the minimum possible sum of the areas of such rectangles.

------------------------------------------------------------------------------
Approach:
1. Precompute a prefix sum `pre` to quickly count 1s in any submatrix.
2. Define helper functions:
   - `countOnes(r1, r2, c1, c2)`: counts number of 1s in the submatrix.
   - `boundingArea(r1, r2, c1, c2)`: computes bounding rectangle area
     that covers all 1s inside the given submatrix.
3. Use 4D DP:
   - dp1[r1][r2][c1][c2] → minimum area to cover 1s with 1 rectangle.
   - dp2[r1][r2][c1][c2] → minimum area with 2 rectangles.
   - dp3[r1][r2][c1][c2] → minimum area with 3 rectangles.
4. Iterate over all submatrices by height and width.
5. For each submatrix:
   - Base case: cover with 1 rectangle.
   - Try vertical & horizontal splits to divide into smaller submatrices
     for dp2 and dp3.
6. Answer is `dp3[0][n-1][0][m-1]`.

------------------------------------------------------------------------------
Complexity:
- Time:  O(n^2 * m^2 * (n + m)) due to iterating all submatrices and
         splitting in both directions.
- Space: O(n^2 * m^2) for the 4D DP arrays.

==============================================================================
*/

class Solution
{
public:
  int minimumSum(vector<vector<int>> &grid)
  {
    int n = grid.size(), m = grid[0].size();

    // ---------------------------------------------------------------------
    // Prefix sum for fast submatrix sum
    // ---------------------------------------------------------------------
    vector<vector<int>> pre(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        pre[i + 1][j + 1] = pre[i + 1][j] + pre[i][j + 1] - pre[i][j] + grid[i][j];

    // Count number of 1s in submatrix [r1..r2][c1..c2]
    auto countOnes = [&](int r1, int r2, int c1, int c2) -> int
    {
      if (r1 > r2 || c1 > c2)
        return 0;
      return pre[r2 + 1][c2 + 1] - pre[r1][c2 + 1] - pre[r2 + 1][c1] + pre[r1][c1];
    };

    // Bounding rectangle area covering all 1s in submatrix
    auto boundingArea = [&](int r1, int r2, int c1, int c2) -> int
    {
      int cnt = countOnes(r1, r2, c1, c2);
      if (cnt == 0)
        return 0;

      int top = r1, bottom = r2, left = c1, right = c2;
      while (top <= r2 && countOnes(top, top, c1, c2) == 0)
        ++top;
      while (bottom >= r1 && countOnes(bottom, bottom, c1, c2) == 0)
        --bottom;
      while (left <= c2 && countOnes(r1, r2, left, left) == 0)
        ++left;
      while (right >= c1 && countOnes(r1, r2, right, right) == 0)
        --right;

      return (bottom - top + 1) * (right - left + 1);
    };

    // ---------------------------------------------------------------------
    // Initialize 4D DP arrays: dp1, dp2, dp3
    // ---------------------------------------------------------------------
    auto make4D = [&](int init)
    {
      return vector(n, vector(n, vector(m, vector<int>(m, init))));
    };
    auto dp1 = make4D(0), dp2 = make4D(0), dp3 = make4D(0);

    // ---------------------------------------------------------------------
    // Iterate over all submatrices by height & width
    // ---------------------------------------------------------------------
    for (int h = 1; h <= n; ++h)
    {
      for (int r1 = 0; r1 + h - 1 < n; ++r1)
      {
        int r2 = r1 + h - 1;
        for (int w = 1; w <= m; ++w)
        {
          for (int c1 = 0; c1 + w - 1 < m; ++c1)
          {
            int c2 = c1 + w - 1;

            int cnt = countOnes(r1, r2, c1, c2);
            if (cnt == 0)
            {
              dp1[r1][r2][c1][c2] = dp2[r1][r2][c1][c2] = dp3[r1][r2][c1][c2] = 0;
              continue;
            }

            // Base: one rectangle
            int one = boundingArea(r1, r2, c1, c2);
            int best2 = one, best3 = one;

            // -----------------------------------------------------
            // Vertical splits
            // -----------------------------------------------------
            for (int mid = c1; mid < c2; ++mid)
            {
              int lcnt = countOnes(r1, r2, c1, mid);
              int rcnt = cnt - lcnt;

              best2 = min(best2, dp1[r1][r2][c1][mid] + dp1[r1][r2][mid + 1][c2]);
              if (rcnt == 0)
                best2 = min(best2, dp2[r1][r2][c1][mid]);
              if (lcnt == 0)
                best2 = min(best2, dp2[r1][r2][mid + 1][c2]);

              best3 = min(best3, dp2[r1][r2][c1][mid] + dp1[r1][r2][mid + 1][c2]);
              best3 = min(best3, dp1[r1][r2][c1][mid] + dp2[r1][r2][mid + 1][c2]);
              if (rcnt == 0)
                best3 = min(best3, dp3[r1][r2][c1][mid]);
              if (lcnt == 0)
                best3 = min(best3, dp3[r1][r2][mid + 1][c2]);
            }

            // -----------------------------------------------------
            // Horizontal splits
            // -----------------------------------------------------
            for (int mid = r1; mid < r2; ++mid)
            {
              int tcnt = countOnes(r1, mid, c1, c2);
              int bcnt = cnt - tcnt;

              best2 = min(best2, dp1[r1][mid][c1][c2] + dp1[mid + 1][r2][c1][c2]);
              if (bcnt == 0)
                best2 = min(best2, dp2[r1][mid][c1][c2]);
              if (tcnt == 0)
                best2 = min(best2, dp2[mid + 1][r2][c1][c2]);

              best3 = min(best3, dp2[r1][mid][c1][c2] + dp1[mid + 1][r2][c1][c2]);
              best3 = min(best3, dp1[r1][mid][c1][c2] + dp2[mid + 1][r2][c1][c2]);
              if (bcnt == 0)
                best3 = min(best3, dp3[r1][mid][c1][c2]);
              if (tcnt == 0)
                best3 = min(best3, dp3[mid + 1][r2][c1][c2]);
            }

            dp1[r1][r2][c1][c2] = one;
            dp2[r1][r2][c1][c2] = best2;
            dp3[r1][r2][c1][c2] = best3;
          }
        }
      }
    }

    // Final result: minimum sum using up to 3 rectangles
    return dp3[0][n - 1][0][m - 1];
  }
};

//==============================================================================
// Problem: Longest Subarray of 1's After Deleting One Element
//------------------------------------------------------------------------------
// Task:
// Given a binary array `nums`, return the length of the longest subarray
// consisting of only 1’s after deleting exactly one element.
//
// Approach (Sliding Window):
// 1. Maintain two pointers (l, r) and a counter `zeros` for the number of zeros
//    in the current window.
// 2. Expand the window by moving `r` and include nums[r].
// 3. If zeros > 1, shrink window from the left until we have at most one zero.
// 4. Track the maximum window size as (r - l) because one element must be deleted.
//
// Complexity Analysis:
// - Time: O(n), since each element is visited at most twice (expand + shrink).
// - Space: O(1), only a few variables used.
//==============================================================================

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  int longestSubarray(vector<int> &nums)
  {
    int n = nums.size();
    int zeros = 0, ans = 0;

    for (int l = 0, r = 0; r < n; r++)
    {
      // Include nums[r] into the window
      if (nums[r] == 0)
        zeros++;

      // Shrink window if more than 1 zero
      while (zeros > 1)
      {
        if (nums[l] == 0)
          zeros--;
        l++;
      }

      // Update max length (delete one element => r - l)
      ans = max(ans, r - l);
    }
    return ans;
  }
};

//==============================================================================
// Example Usage:
// Input: nums = [1,1,0,1]
// Output: 3
// Explanation: Delete the single 0, longest subarray of 1’s = 3.
//==============================================================================

//==============================================================================
// Problem: Diagonal Traverse
//------------------------------------------------------------------------------
// Task:
// Given an m x n matrix, return all elements of the matrix in diagonal order.
//
// Approach:
// 1. Use simulation with (row, col) indices.
// 2. At each step, move diagonally up-right if (row + col) is even,
//    otherwise diagonally down-left.
// 3. Handle boundary conditions carefully when hitting top, bottom, left, or right edges.
// 4. Continue until all m * n elements are collected.
//
// Complexity Analysis:
// - Time: O(m * n), since each element is visited exactly once.
// - Space: O(m * n) for the result vector.
//==============================================================================

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  vector<int> findDiagonalOrder(vector<vector<int>> &matrix)
  {
    // Edge case: empty matrix
    if (matrix.empty() || matrix[0].empty())
      return {};

    int m = matrix.size();
    int n = matrix[0].size();
    vector<int> result(m * n);

    int row = 0, col = 0;

    for (int i = 0; i < m * n; i++)
    {
      result[i] = matrix[row][col];

      // If sum of indices is even, move up-right
      if ((row + col) % 2 == 0)
      {
        if (col == n - 1)
        {
          row++; // Hit right boundary → move down
        }
        else if (row == 0)
        {
          col++; // Hit top boundary → move right
        }
        else
        {
          row--;
          col++; // Normal move: up-right
        }
      }
      // If sum of indices is odd, move down-left
      else
      {
        if (row == m - 1)
        {
          col++; // Hit bottom boundary → move right
        }
        else if (col == 0)
        {
          row++; // Hit left boundary → move down
        }
        else
        {
          row++;
          col--; // Normal move: down-left
        }
      }
    }

    return result;
  }
};

//==============================================================================
// Example Usage:
// Input:  matrix = [[1,2,3],[4,5,6],[7,8,9]]
// Output: [1,2,4,7,5,3,6,8,9]
// Explanation: Elements are traversed diagonally as required.
//==============================================================================

//==============================================================================
// Problem: Longest V-Shaped Diagonal Path in Grid
//------------------------------------------------------------------------------
// Task:
// Given a 2D grid, find the maximum length of a diagonal path that starts from
// a cell with value = 1 and alternates diagonally such that the difference
// between adjacent cell values is exactly 2.
// The path is allowed to take at most one turn in direction.
//
// Approach:
// 1. Each cell with value = 1 is a potential starting point.
// 2. From each starting point, explore all 4 diagonal directions.
// 3. DFS function `f(x, y, dirNo, turns)` explores the path while:
//      - Continuing in the same direction (turnOff case).
//      - Turning once (turnOn case) if turns == 0.
// 4. Track the maximum path length encountered.
//
// Complexity Analysis:
// - Time: O(n * m * 4 * path_length) in the worst case, since from each cell
//   DFS explores possible diagonals.
// - Space: O(recursion_depth) due to DFS stack.
//==============================================================================

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  int n, m;
  vector<int> dx = {-1, 1, 1, -1}; // diagonal row movements
  vector<int> dy = {1, 1, -1, -1}; // diagonal col movements

  //------------------------------------------------------------------------------
  // Recursive DFS to find longest diagonal path
  //------------------------------------------------------------------------------
  int f(int x, int y, int dirNo, int turns, vector<vector<int>> &grid)
  {
    int nx, ny;

    // Case 1: Continue in the same direction (turnOff)
    int turnOff = 1;
    nx = x + dx[dirNo];
    ny = y + dy[dirNo];
    if (nx >= 0 && ny >= 0 && nx < n && ny < m && abs(grid[x][y] - grid[nx][ny]) == 2)
    {
      turnOff = 1 + f(nx, ny, dirNo, turns, grid);
    }

    // Case 2: Turn to next diagonal direction (turnOn) if no turn used yet
    int turnOn = 1;
    nx = x + dx[(dirNo + 1) % 4];
    ny = y + dy[(dirNo + 1) % 4];
    if (turns == 0 && nx >= 0 && ny >= 0 && nx < n && ny < m && abs(grid[x][y] - grid[nx][ny]) == 2)
    {
      turnOn = 1 + f(nx, ny, (dirNo + 1) % 4, turns + 1, grid);
    }

    return max(turnOff, turnOn);
  }

  //------------------------------------------------------------------------------
  // Main function to compute maximum V-diagonal length
  //------------------------------------------------------------------------------
  int lenOfVDiagonal(vector<vector<int>> &grid)
  {
    n = grid.size();
    m = grid[0].size();
    int maxi = 0;

    // Iterate through all cells to find valid starting points
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        if (grid[i][j] == 1)
        {
          maxi = max(maxi, 1);

          // Try all 4 diagonal directions
          for (int dirNo = 0; dirNo < 4; dirNo++)
          {
            int nx = i + dx[dirNo];
            int ny = j + dy[dirNo];

            // Check if valid diagonal move
            if (nx < 0 || ny < 0 || nx >= n || ny >= m || grid[nx][ny] <= 1)
              continue;

            int val = 1 + f(nx, ny, dirNo, 0, grid);
            maxi = max(maxi, val);
          }
        }
      }
    }
    return maxi;
  }
};

//==============================================================================
// Example Usage:
// Input: grid = [[1,0,3],
//                [0,3,0],
//                [3,0,1]]
// Output: 3
// Explanation: Longest valid V-shaped diagonal has length 3.
//==============================================================================

//==============================================================================
// Problem: Flower Game (LeetCode 2928)
//
// Task:
// Alice and Bob play a game. Alice chooses an integer `x` between 1 and `n`,
// Bob chooses an integer `y` between 1 and `m`. Alice wins if the sum `x + y`
// is odd. Find the total number of ways Alice can win.
//
// Approach:
// - The sum `x + y` is odd if one is even and the other is odd.
// - Count evens and odds separately for both n and m.
//   - odd_n = (n + 1) / 2, even_n = n / 2
//   - odd_m = (m + 1) / 2, even_m = m / 2
// - Winning pairs = (odd_n * even_m) + (even_n * odd_m)
// - This simplifies to (n * m) / 2.
//==============================================================================

class Solution
{
public:
  long long flowerGame(int n, int m)
  {
    return (1LL * n * m) / 2;
  }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(1)   (Direct formula calculation)
// - Space: O(1)
//
// Example:
// Input:  n = 3, m = 2
// Output: 3
// Explanation: Possible winning pairs are (1,2), (2,1), (3,2).
//==============================================================================

//==============================================================================
// Problem: Maximum Average Pass Ratio (LeetCode 1792)
//
// Task:
// Each class is represented as [pass, total], where "pass" is the number of
// students passing the exam and "total" is the total students in the class.
// You are given an integer extraStudents, representing additional students who
// will definitely pass. Distribute them across classes to maximize the overall
// average pass ratio.
//
// Example:
//   Input:  classes = [[1,2],[3,5],[2,2]], extraStudents = 2
//   Output: 0.78333
//
// Approach (Greedy + Priority Queue):
// 1. For each class, compute the "gain" in pass ratio if one extra student is added.
//    gain(p, t) = (p+1)/(t+1) - p/t
// 2. Use a max-heap (priority_queue) to always allocate the next student to the
//    class with the maximum gain.
// 3. Repeat for all extraStudents.
// 4. Compute the final average pass ratio.
//
// Justification: Each additional student should go to the class with the maximum
// marginal gain, ensuring optimal distribution (greedy strategy).
//==============================================================================

class Solution
{
public:
  double maxAverageRatio(vector<vector<int>> &classes, int extraStudents)
  {
    // Helper lambda to compute gain from adding one student
    auto gain = [](int p, int t)
    {
      return (double)(p + 1) / (t + 1) - (double)p / t;
    };

    // Max heap storing (gain, pass, total)
    priority_queue<tuple<double, int, int>> pq;
    for (auto &c : classes)
    {
      pq.push({gain(c[0], c[1]), c[0], c[1]});
    }

    // Distribute extra students
    while (extraStudents--)
    {
      auto [g, p, t] = pq.top();
      pq.pop();
      p++, t++; // add student
      pq.push({gain(p, t), p, t});
    }

    // Compute total average
    double total = 0.0;
    while (!pq.empty())
    {
      auto [g, p, t] = pq.top();
      pq.pop();
      total += (double)p / t;
    }

    return total / classes.size();
  }
};

//==============================================================================
// Complexity Analysis:
// - Time: O((n + extraStudents) log n), where n = number of classes
//         (each heap operation costs log n).
// - Space: O(n), for storing heap elements.
//
// Example Walkthrough:
// Input: classes = [[1,2],[3,5],[2,2]], extraStudents = 2
// - Initial gains calculated, push into max heap
// - Allocate 1st student to maximize gain → update heap
// - Allocate 2nd student similarly
// - Final average computed
// Output: 0.78333
//==============================================================================

//==============================================================================
// Problem: Number of Pairs of Interchangeable Rectangles (Variant - Geometry)
//
// Task:
// Given a list of points in 2D space, count the number of valid pairs (i, j)
// that satisfy specific ordering and bounding conditions.
//
// Details of conditions implemented here:
// 1. Sort points primarily by x (ascending).
//    - If x is equal, sort by y (descending).
// 2. For each point i, check all subsequent points j (j > i):
//    - If y_j lies strictly between the "bot" (previously chosen min y)
//      and "top" (y_i), then it's valid.
//    - Increase count and update "bot".
//    - Stop early if bot == top.
//
// Example:
//   Input:  points = [[1,3],[2,2],[3,1]]
//   After sorting: [[1,3],[2,2],[3,1]]
//   Output: 2
//
// Approach:
// - Sort points by (x asc, y desc).
// - For each point i, maintain [bot, top] bounds.
// - Greedily count valid j’s where y_j is between (bot, top].
//==============================================================================

class Solution
{
public:
  int numberOfPairs(vector<vector<int>> &points)
  {
    // Sort by x ascending, if tie then y descending
    sort(points.begin(), points.end(), [](const auto &a, const auto &b)
         {
            if (a[0] == b[0]) return a[1] > b[1];
            return a[0] < b[0]; });

    int n = points.size();
    int result = 0;

    // Traverse each point as potential "top" bound
    for (int i = 0; i < n; i++)
    {
      int top = points[i][1];
      int bot = INT_MIN;

      // Check subsequent points
      for (int j = i + 1; j < n; j++)
      {
        int y = points[j][1];

        if (bot < y && y <= top)
        {
          result++;
          bot = y; // update lower bound
          if (bot == top)
            break; // optimization
        }
      }
    }

    return result;
  }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(n^2) in the worst case due to nested loops.
// - Space: O(1) extra space, ignoring input storage.
//
// Notes:
// - Sorting ensures proper left-to-right ordering of points.
// - The descending y-order ensures no invalid over-counting for same x.
//==============================================================================

//==============================================================================
// Problem: Find Closest Number to Target
//
// Task:
// Given three integers x, y, and z, determine whether x or y is closer to z.
// Return:
//   1 -> if x is closer
//   2 -> if y is closer
//   0 -> if both are equally close
//
// Example:
//   Input:  x = 3, y = 8, z = 5
//   Distances: |5 - 3| = 2, |5 - 8| = 3
//   Output: 1  (x is closer)
//
// Approach:
// - Compute absolute difference between x and z, and y and z.
// - Compare the distances.
// - Return result based on which distance is smaller.
//==============================================================================

class Solution
{
public:
  int findClosest(int x, int y, int z)
  {
    int x_dist = abs(z - x);
    int y_dist = abs(z - y);

    if (x_dist < y_dist)
      return 1; // x is closer
    else if (x_dist > y_dist)
      return 2; // y is closer
    else
      return 0; // equally close
  }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(1), constant-time arithmetic and comparisons.
// - Space: O(1), no extra space used.
//==============================================================================

/*
Example Usage:
--------------
Solution sol;
cout << sol.findClosest(3, 8, 5);   // Output: 1
cout << sol.findClosest(10, 2, 6);  // Output: 0 (both equally close)
*/

//==============================================================================
// Problem: Make The Integer Zero
//
// Task:
// Given two integers num1 and num2, find the smallest integer k (1 <= k <= 60)
// such that the value (num1 - num2 * k) can be expressed as the sum of exactly
// k powers of two (where repetitions are allowed). If no such k exists,
// return -1.
//
// Key Observations:
// - After subtracting k * num2, the remainder (x) must be >= k (since we need
//   at least k numbers to sum to x).
// - The number of set bits in x (popcount) gives the minimum number of powers
//   of two required to represent x.
// - If k >= popcount(x), then it's possible to split x into exactly k powers
//   of two.
//
// Approach:
// 1. Iterate k from 1 to 60.
// 2. Compute x = num1 - num2 * k.
// 3. If x < k, break (not enough to distribute).
// 4. If k >= popcount(x), return k.
// 5. If no valid k found, return -1.
//
//==============================================================================

class Solution
{
public:
  int makeTheIntegerZero(int num1, int num2)
  {
    for (int k = 1; k <= 60; k++)
    {
      long long x = num1 - 1LL * num2 * k;

      // Condition: x must be >= k
      if (x < k)
      {
        return -1;
      }

      // Check if x can be split into exactly k powers of 2
      if (k >= __builtin_popcountll(x))
      {
        return k;
      }
    }
    return -1;
  }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(60) = O(1), since k ranges only up to 60.
// - Space: O(1), constant extra space used.
//==============================================================================

/*
Example Usage:
--------------
Solution sol;
cout << sol.makeTheIntegerZero(12, 2); // Output: 2
cout << sol.makeTheIntegerZero(5, 3);  // Output: -1
*/

//==============================================================================
// Problem: Minimum Operations on Ranges (Custom Problem)
//
// Task:
// Given a set of queries where each query is a range [st, end], calculate the
// minimum operations required based on certain rules involving powers of 4
// and multipliers. For each query:
// - Compute contributions from segments defined by powers of 4.
// - Weight contributions by a multiplier (mul), which increases with each step.
// - Sum the contributions and add half of it (rounded up) to the total answer.
//
// Key Observations:
// - Multiplier (mul) starts from (log2(st - 1) / 2) + 1 if st > 1, else 1.
// - Ranges are divided into blocks of length 4^k.
// - For partial blocks at the end, only the portion up to `end` is considered.
// - Each block contributes its length * multiplier to the sum.
// - Final contribution for each query is ceil(sum / 2).
//
// Approach:
// 1. For each query [st, end]:
//    - Initialize multiplier based on st.
//    - Find the first complete block starting from st.
//    - Add contributions from partial block before beg.
//    - Iterate through full blocks until end.
//    - Add final partial block contribution if necessary.
// 2. Return accumulated total across all queries.
//
//==============================================================================

class Solution
{
public:
  long long minOperations(vector<vector<int>> &queries)
  {
    long long ans = 0;

    for (auto &x : queries)
    {
      long long sum = 0;
      int st = x[0];
      int end = x[1];

      // Base multiplier depends on st
      int base = 0;
      if (st > 1)
        base = log2(st - 1) / 2;

      long long mul = base + 1;
      long long beg = pow(4, base + 1);

      // If the first block already exceeds 'end'
      if (beg > end)
      {
        ans += ceil(((end - st + 1) * mul) / 2.0);
        continue;
      }

      // Partial block contribution before beg
      sum += (beg - st) * mul;

      // Traverse through full blocks
      while (true)
      {
        long long next = beg * 4;
        mul++;

        if (next - 1 >= end)
        {
          // Final partial block
          sum += (end - beg + 1) * mul;
          break;
        }
        else
        {
          // Full block contribution
          sum += (next - beg) * mul;
        }

        beg *= 4;
      }

      // Add ceil(sum / 2) to result
      ans += ceil(sum / 2.0);
    }

    return ans;
  }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(Q * logN), where Q is number of queries, N is the largest `end`.
//   Each query may traverse ~log4(N) blocks.
// - Space: O(1), constant extra space used.
//
//==============================================================================

/*
Example Usage:
--------------
Solution sol;
vector<vector<int>> queries = {{1, 10}, {5, 20}};
cout << sol.minOperations(queries); // Output depends on rules
*/

//==============================================================================
// Problem: Find N Unique Integers Sum up to Zero (LeetCode 1304)
//
// Task:
// Given an integer n, return any array of n unique integers such that
// they sum up to 0.
//
// Key Observations:
// - For every positive integer i, we can add its negative counterpart -i.
// - If n is odd, we must also include 0 to balance the sum.
// - If n is even, pairs (i, -i) are enough to ensure sum = 0.
//
// Approach:
// 1. Initialize an empty result vector.
// 2. If n is odd, add 0 first.
// 3. Loop from 1 to n/2:
//    - Push back i and -i as a pair.
// 4. Return the constructed vector.
//
//==============================================================================

class Solution
{
public:
  vector<int> sumZero(int n)
  {
    vector<int> result;

    // Handle odd n by adding 0
    if (n % 2 != 0)
    {
      result.push_back(0);
    }

    // Add pairs (i, -i)
    for (int i = 1; i <= n / 2; i++)
    {
      result.push_back(i);
      result.push_back(-i);
    }

    return result;
  }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(n), constructing n elements.
// - Space: O(n), storing the result array.
//
//==============================================================================

/*
Example Usage:
--------------
Solution sol;
int n = 5;
vector<int> ans = sol.sumZero(n);
// Example Output: {0, 1, -1, 2, -2}  (any valid order is acceptable)
*/

//==============================================================================
// Problem: Convert Integer to the Sum of Two No-Zero Integers (LeetCode 1317)
//
// Task:
// Given an integer n, return a list of two integers [a, b] such that:
// - a + b = n
// - Both a and b are no-zero integers (no digit contains '0').
//
// Key Observations:
// - We can iterate over possible values of a and check if both a and n - a
//   are valid no-zero integers.
// - Checking validity requires ensuring no digit equals 0.
//
// Approach:
// 1. Define a helper function isValid(num):
//    - Returns false if any digit of num is 0.
//    - Otherwise, returns true.
// 2. Iterate a from 1 to n - 1:
//    - Compute b = n - a.
//    - If both a and b are valid, return {a, b}.
// 3. If no such pair exists (though guaranteed by the problem), return {}.
//
//==============================================================================

class Solution
{
public:
  // Helper function: check if number contains no zero digits
  bool isValid(int num)
  {
    while (num > 0)
    {
      if (num % 10 == 0)
        return false; // digit '0' found
      num /= 10;
    }
    return true;
  }

  // Main function: find two no-zero integers that sum to n
  vector<int> getNoZeroIntegers(int n)
  {
    for (int a = 1; a < n; a++)
    {
      int b = n - a;
      if (isValid(a) && isValid(b))
      {
        return {a, b};
      }
    }
    return {}; // fallback, though problem guarantees a solution exists
  }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(n * log(n)), as we check up to n values and each check scans digits.
// - Space: O(1), only using constant extra memory.
//==============================================================================

/*
Example Usage:
--------------
Solution sol;
int n = 11;
vector<int> ans = sol.getNoZeroIntegers(n);
// Example Output: {2, 9} or {3, 8}, etc. (any valid pair is acceptable)
*/

//==============================================================================
// Problem: Number of People Aware of a Secret (LeetCode 2327)
//
// Task:
// A secret is shared by one person on day 1. Each person who knows the secret:
//   - Starts sharing it with one new person per day starting at `delay` days
//     after they learn it.
//   - Stops sharing (forgets it) after `forget` days.
// Given integers n, delay, and forget, return the number of people aware of the
// secret at day n. Answer modulo 1e9+7.
//
// Key Observations:
// - Dynamic Programming can be used to simulate the process.
// - dp[t] = number of people who *learn* the secret on day t.
// - share = running count of people who are currently eligible to share.
// - We add dp[t - delay] when they become eligible to share.
// - We subtract dp[t - forget] when they forget the secret.
// - Finally, sum the number of people who *still know* the secret by day n.
//
// Approach:
// 1. Initialize dp[1] = 1 (one person knows secret on day 1).
// 2. For each day t from 2 to n:
//    - Add people who become eligible at (t - delay).
//    - Remove people who forget at (t - forget).
//    - Set dp[t] = number of new people learning on day t.
// 3. At the end, sum dp[i] for last `forget` days to count those who still know.
//==============================================================================

class Solution
{
public:
  int peopleAwareOfSecret(int n, int delay, int forget)
  {
    vector<long long> dp(n + 1, 0);
    dp[1] = 1; // Day 1: one person knows the secret
    long long share = 0, MOD = 1000000007;

    for (int t = 2; t <= n; t++)
    {
      if (t - delay > 0)
        share = (share + dp[t - delay] + MOD) % MOD; // new sharers
      if (t - forget > 0)
        share = (share - dp[t - forget] + MOD) % MOD; // forgetters
      dp[t] = share;
    }

    long long know = 0;
    for (int i = n - forget + 1; i <= n; i++)
    {
      know = (know + dp[i]) % MOD; // sum up last active people
    }
    return (int)know;
  }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(n), iterating over each day up to n.
// - Space: O(n), storing dp values for each day.
//==============================================================================

/*
Example Usage:
--------------
Solution sol;
int n = 6, delay = 2, forget = 4;
int result = sol.peopleAwareOfSecret(n, delay, forget);
// Expected Output: 5
*/

//==============================================================================
// Problem: Minimum Number of People to Teach (LeetCode 1733)
//
// Task:
// There are `n` users and `totalLanguages` languages. Each user may know
// multiple languages. A friendship exists between some pairs of users.
// Two users can communicate if they share at least one common language.
// You may teach one language to some users. Return the minimum number of users
// that must be taught so that *all friends* can communicate.
//
// Key Observations:
// - For each friendship, check if the pair can already communicate.
// - If not, both users become candidates for teaching.
// - Then, try teaching each possible language and count how many of the
//   "users-to-teach" still don’t know it.
// - The minimum across all languages is the answer.
//
// Approach:
// 1. Iterate over friendships, mark pairs who cannot communicate.
// 2. Gather all such users into a `usersToTeach` set.
// 3. For each language `L`:
//    - Count how many users in `usersToTeach` don’t know `L`.
//    - Track the minimum count.
// 4. Return the minimum count as the answer.
//==============================================================================

class Solution
{
public:
  int minimumTeachings(int totalLanguages, vector<vector<int>> &userLanguages, vector<vector<int>> &friendships)
  {
    unordered_set<int> usersToTeach;

    // Step 1: Identify users in friendships who cannot communicate
    for (auto &friendship : friendships)
    {
      int user1 = friendship[0] - 1;
      int user2 = friendship[1] - 1;
      bool canCommunicate = false;

      for (int lang1 : userLanguages[user1])
      {
        for (int lang2 : userLanguages[user2])
        {
          if (lang1 == lang2)
          {
            canCommunicate = true;
            break;
          }
        }
        if (canCommunicate)
          break;
      }

      if (!canCommunicate)
      {
        usersToTeach.insert(user1);
        usersToTeach.insert(user2);
      }
    }

    // Step 2: Try teaching each language
    int minUsersToTeach = userLanguages.size() + 1;

    for (int language = 1; language <= totalLanguages; language++)
    {
      int count = 0;

      for (int user : usersToTeach)
      {
        bool knowsLanguage = false;
        for (int lang : userLanguages[user])
        {
          if (lang == language)
          {
            knowsLanguage = true;
            break;
          }
        }
        if (!knowsLanguage)
          count++;
      }

      minUsersToTeach = min(minUsersToTeach, count);
    }

    return minUsersToTeach;
  }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(F * L + N * L), where
//   F = number of friendships, L = average languages per user, N = number of users.
//   Checking communication = O(F * L^2).
//   Teaching simulation = O(N * L).
// - Space: O(N), storing candidate users to teach.
//==============================================================================

/*
Example Usage:
--------------
Solution sol;
int totalLanguages = 3;
vector<vector<int>> userLanguages = {{2}, {1,3}, {1,2}, {3}};
vector<vector<int>> friendships = {{1,4}, {1,2}, {3,4}, {2,3}};

int result = sol.minimumTeachings(totalLanguages, userLanguages, friendships);
// Expected Output: 2
*/

//==============================================================================
// Problem: Sort Vowels in a String (LeetCode 2785)
//
// Task:
// Given a string `s`, sort only the vowels in the string while keeping all
// other characters in their original positions. Return the modified string.
//
// Key Observations:
// - Only vowels ('a', 'e', 'i', 'o', 'u' in both cases) are affected.
// - Extract all vowels, sort them, and then reinsert them in order.
// - Non-vowel characters remain untouched.
//
// Approach:
// 1. Traverse the string and collect all vowels into a vector.
// 2. Sort the vowel vector alphabetically.
// 3. Traverse the string again, replacing each vowel with the next one
//    from the sorted list.
//==============================================================================

class Solution
{
public:
  // Helper function to check if a character is a vowel
  bool isVowel(char c)
  {
    switch (c)
    {
    case 'A':
    case 'E':
    case 'I':
    case 'O':
    case 'U':
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
      return true;
    default:
      return false;
    }
  }

  string sortVowels(string s)
  {
    vector<char> vowels;

    // Step 1: Extract all vowels
    for (char c : s)
    {
      if (isVowel(c))
      {
        vowels.push_back(c);
      }
    }

    // Step 2: Sort the vowels
    sort(vowels.begin(), vowels.end());

    // Step 3: Reinsert vowels in sorted order
    int idx = 0;
    for (char &c : s)
    {
      if (isVowel(c))
      {
        c = vowels[idx++];
      }
    }

    return s;
  }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(N + V log V), where N = length of the string, V = number of vowels.
//   Extracting vowels = O(N), sorting vowels = O(V log V), reinserting = O(N).
// - Space: O(V), storing extracted vowels.
//==============================================================================

/*
Example Usage:
--------------
Solution sol;
string s = "lEetcOde";
string result = sol.sortVowels(s);
// Expected Output: "lEOtcede"
*/

//==============================================================================
// Problem: Check if Alice Wins
//
// Task:
// Given a string `s`, determine if Alice wins. Alice wins if the string
// contains at least one vowel ('a', 'e', 'i', 'o', 'u').
//
// Approach:
// - Iterate through each character in the string.
// - If any character is a vowel, return true.
// - If no vowels are found, return false.
//==============================================================================

class Solution
{
public:
  bool doesAliceWin(string s)
  {
    for (char c : s)
    {
      if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
      {
        return true;
      }
    }
    return false;
  }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(N), where N = length of the string (single traversal).
// - Space: O(1), no extra storage apart from variables.
//==============================================================================

/*
Example Usage:
--------------
Solution sol;
string s = "leetcode";
bool result = sol.doesAliceWin(s);
// Expected Output: true (since vowels exist in the string)
*/

//==============================================================================
// Problem: Maximum Frequency Sum
//
// Task:
// Given a string `s`, find the maximum frequency of any vowel plus the maximum
// frequency of any consonant in the string.
//
// Approach:
// 1. Use an unordered_map to count the frequency of each character.
// 2. Track the highest frequency among vowels and the highest frequency among consonants.
// 3. Return their sum.
//
// Notes:
// - Vowels considered: 'a', 'e', 'i', 'o', 'u'.
//==============================================================================

class Solution
{
public:
  int maxFreqSum(string s)
  {
    unordered_map<char, int> mp;

    // Count frequencies of all characters
    for (char ch : s)
    {
      mp[ch]++;
    }

    int vowel_cnt = 0, conso_cnt = 0;

    // Find max frequency of vowels and consonants
    for (auto item : mp)
    {
      char ch = item.first;
      int cnt = item.second;

      if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
      {
        vowel_cnt = max(vowel_cnt, cnt);
      }
      else
      {
        conso_cnt = max(conso_cnt, cnt);
      }
    }

    return vowel_cnt + conso_cnt;
  }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(N), where N = length of string (counting + scanning map).
// - Space: O(K), where K = number of unique characters (bounded by 26 for lowercase).
//==============================================================================

/*
Example Usage:
--------------
Solution sol;
string s = "leetcode";
int result = sol.maxFreqSum(s);
// Frequencies: l=1, e=3, t=1, c=1, o=1, d=1
// Max vowel = 3 (e), Max consonant = 1 (any of l,t,c,d)
// Expected Output: 4
*/

//==============================================================================
// Problem: Vowel Spellchecker
//
// Task:
// Implement a spellchecker with the following rules applied in order of priority:
// 1. **Exact Match**: If the query matches exactly with a word in the wordlist.
// 2. **Case-Insensitive Match**: If the lowercase form of the query matches a
//    word in the wordlist.
// 3. **Vowel-Insensitive Match**: If after replacing all vowels ('a','e','i','o','u')
//    with '*', the query matches a word in the wordlist.
// 4. If none of the above match, return an empty string for that query.
//
// Approach:
// - Use an unordered_set for exact matches.
// - Use an unordered_map for case-insensitive matches (first occurrence priority).
// - Use another unordered_map for vowel-insensitive matches (first occurrence priority).
// - Normalize vowels by replacing them with '*'.
// - For each query, check in order: exact -> case-insensitive -> vowel-insensitive.
//
//==============================================================================

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  vector<string> spellchecker(vector<string> &wordlist, vector<string> &queries)
  {
    // Exact matches
    unordered_set<string> exactMatchSet(wordlist.begin(), wordlist.end());

    // Case-insensitive and vowel-insensitive maps
    unordered_map<string, string> caseInsensitiveMap;
    unordered_map<string, string> vowelInsensitiveMap;

    // Helper lambda: replace vowels with '*'
    auto normalizeVowels = [](const string &word)
    {
      string res = word;
      for (char &c : res)
      {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        {
          c = '*';
        }
      }
      return res;
    };

    // Build maps
    for (string &word : wordlist)
    {
      string lowerWord = word;
      transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), ::tolower);

      // Store first occurrence for case-insensitive match
      if (!caseInsensitiveMap.count(lowerWord))
      {
        caseInsensitiveMap[lowerWord] = word;
      }

      // Store first occurrence for vowel-insensitive match
      string vowelNormalized = normalizeVowels(lowerWord);
      if (!vowelInsensitiveMap.count(vowelNormalized))
      {
        vowelInsensitiveMap[vowelNormalized] = word;
      }
    }

    vector<string> results;

    // Process queries
    for (string &query : queries)
    {
      // Rule 1: Exact match
      if (exactMatchSet.count(query))
      {
        results.push_back(query);
        continue;
      }

      // Rule 2: Case-insensitive match
      string lowerQuery = query;
      transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);
      if (caseInsensitiveMap.count(lowerQuery))
      {
        results.push_back(caseInsensitiveMap[lowerQuery]);
        continue;
      }

      // Rule 3: Vowel-insensitive match
      string vowelNormalized = normalizeVowels(lowerQuery);
      if (vowelInsensitiveMap.count(vowelNormalized))
      {
        results.push_back(vowelInsensitiveMap[vowelNormalized]);
        continue;
      }

      // Rule 4: No match
      results.push_back("");
    }

    return results;
  }
};

//==============================================================================
// Complexity Analysis:
// - Preprocessing (wordlist):
//   Time: O(W * L), Space: O(W * L)
//   where W = number of words, L = average word length.
// - Query processing:
//   Time: O(Q * L), Space: O(1)
//   where Q = number of queries.
//==============================================================================

/*
Example Usage:
--------------
Solution sol;
vector<string> wordlist = {"KiTe","kite","hare","Hare"};
vector<string> queries = {"kite","Kite","KiTe","Hare","HARE","Hear","hear","keti","keet","keto"};
vector<string> result = sol.spellchecker(wordlist, queries);

// Expected Output:
// ["kite","KiTe","KiTe","Hare","hare","","","KiTe","","KiTe"]
*/

//==============================================================================
// Problem: Maximum Number of Words You Can Type
//
// Task:
// Given a string `text` representing a sentence and a string `brokenLetters`
// representing broken keyboard letters, return the number of words in `text`
// that can be typed fully without using broken letters.
//
// Approach:
// 1. Store all broken letters in an unordered_set for O(1) lookup.
// 2. Split the text into words using stringstream.
// 3. For each word, check if it contains any broken letter.
//    - If yes, mark the word as "broken" and skip it.
//    - If no, increment the count.
// 4. Return the total count.
//
//==============================================================================

class Solution
{
public:
  int canBeTypedWords(string text, string brokenLetters)
  {
    stringstream ss(text);
    unordered_set<char> brokenSet(brokenLetters.begin(), brokenLetters.end());

    string word;
    int count = 0;

    while (ss >> word)
    {
      bool broken = false;
      for (char ch : word)
      {
        if (brokenSet.find(ch) != brokenSet.end())
        { // FIXED condition
          broken = true;
          break;
        }
      }
      if (!broken)
        count++;
    }

    return count;
  }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(N + M), where N = total characters in text, M = brokenLetters length
// - Space: O(M), for the unordered_set of broken letters
//==============================================================================

/*
Example Usage:
--------------
Solution sol;
string text = "hello world leetcode";
string brokenLetters = "ad";
int result = sol.canBeTypedWords(text, brokenLetters);

// Expected Output: 1
// Only "world" can be typed fully.
*/

//==============================================================================
// Problem: Replace Non-Coprime Numbers in Array
//
// Task:
// You are given an array of integers `nums`. Replace adjacent non-coprime
// numbers with their LCM until no such adjacent pair remains.
// Return the final array.
//
// Approach:
// 1. Use a stack to maintain processed numbers.
// 2. For each number in `nums`:
//    - While the stack is not empty and the top of stack shares a gcd > 1
//      with the current number, merge them into their LCM.
//    - Push the merged number back into the stack.
// 3. At the end, the stack contains the final array.
//
// Key Idea:
// - Adjacent non-coprimes can "cascade" merges, so we keep merging backwards
//   until no gcd > 1 remains.
// - LCM(a, b) = (a / gcd(a, b)) * b.
//
//==============================================================================

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  // Utility function to compute gcd
  int gcd(int a, int b)
  {
    return b == 0 ? a : gcd(b, a % b);
  }

  vector<int> replaceNonCoprimes(vector<int> &nums)
  {
    vector<int> st;
    for (int num : nums)
    {
      // Keep merging until gcd == 1
      while (!st.empty())
      {
        int top = st.back();
        int g = gcd(top, num);
        if (g == 1)
          break;

        st.pop_back();
        long long merged = (long long)top / g * num; // avoid overflow
        num = (int)merged;
      }
      st.push_back(num);
    }
    return st;
  }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(N log A), where N = nums.size(), A = max element (due to gcd calls).
// - Space: O(N), for the stack.
//==============================================================================

/*
Example Usage:
--------------
Solution sol;
vector<int> nums = {6, 4, 3, 2, 7, 6, 2};
vector<int> result = sol.replaceNonCoprimes(nums);

// Expected Output: [12, 7, 6]
// Explanation:
// (6, 4) → merge into 12
// (12, 3, 2) → merge (12, 3) → 12; merge (12, 2) → 12
// Leftover sequence → [12, 7, 6]
*/

class FoodRatings
{
  unordered_map<string, string> foodToCuisine;                  // food -> cuisine
  unordered_map<string, int> foodToRating;                      // food -> rating
  unordered_map<string, set<pair<int, string>>> cuisineToFoods; // cuisine -> set of { -rating, food }

public:
  // Constructor
  FoodRatings(vector<string> &foods, vector<string> &cuisines, vector<int> &ratings)
  {
    for (int i = 0; i < foods.size(); ++i)
    {
      foodToCuisine[foods[i]] = cuisines[i];
      foodToRating[foods[i]] = ratings[i];
      cuisineToFoods[cuisines[i]].insert({-ratings[i], foods[i]});
    }
  }

  // Change the rating of a given food
  void changeRating(string food, int newRating)
  {
    string cuisine = foodToCuisine[food];
    int oldRating = foodToRating[food];

    // Remove old entry
    cuisineToFoods[cuisine].erase({-oldRating, food});

    // Insert new entry
    cuisineToFoods[cuisine].insert({-newRating, food});
    foodToRating[food] = newRating;
  }

  // Return the highest rated food for a cuisine
  string highestRated(string cuisine)
  {
    return cuisineToFoods[cuisine].begin()->second;
  }
};

//==============================================================================
// Problem: Task Manager
//
// Task:
// Implement a task manager that supports the following operations:
// 1. Initialize with a list of tasks (each with userId, taskId, priority).
// 2. Add a new task.
// 3. Edit the priority of an existing task.
// 4. Remove a task.
// 5. Execute the highest-priority task.
//
// Approach:
// - Use a max-heap (`priority_queue`) to always retrieve the task with the
//   highest priority quickly.
// - Maintain hash maps:
//   * taskPriority[taskId] → current priority (or -1 if removed).
//   * taskOwner[taskId]   → user who owns the task.
// - Lazy deletion: when popping from the heap, check if the priority matches
//   the latest one in `taskPriority`. If not, skip it.
// - This avoids costly heap updates.
//
// Key Idea:
// - The heap may store outdated entries due to edits/removals.
// - Validity is ensured by checking `taskPriority` when popping.
//==============================================================================

class TaskManager
{
  priority_queue<pair<int, int>> tasks; // (priority, taskId)
  unordered_map<int, int> taskPriority; // taskId → priority
  unordered_map<int, int> taskOwner;    // taskId → userId

public:
  // Constructor: initialize from list of tasks
  TaskManager(vector<vector<int>> &tasksList)
  {
    for (const auto &task : tasksList)
    {
      add(task[0], task[1], task[2]);
    }
  }

  // Add a new task
  void add(int userId, int taskId, int priority)
  {
    tasks.push({priority, taskId});
    taskPriority[taskId] = priority;
    taskOwner[taskId] = userId;
  }

  // Edit priority of an existing task
  void edit(int taskId, int newPriority)
  {
    tasks.push({newPriority, taskId});
    taskPriority[taskId] = newPriority;
  }

  // Remove a task (mark as invalid)
  void rmv(int taskId)
  {
    taskPriority[taskId] = -1;
  }

  // Execute the highest-priority valid task
  int execTop()
  {
    while (!tasks.empty())
    {
      const auto task = tasks.top();
      tasks.pop();

      if (task.first == taskPriority[task.second])
      {
        taskPriority[task.second] = -1; // mark as executed
        return taskOwner[task.second];
      }
    }
    return -1; // No valid task left
  }
};

//==============================================================================
// Complexity Analysis:
// - Add/Edit: O(log N) for heap insertion
// - Remove: O(1) (lazy removal)
// - Execute: O(log N) amortized (skips outdated tasks as needed)
// - Space: O(N) for heap + hash maps
//==============================================================================

/*
Example Usage:
--------------
vector<vector<int>> tasks = {
  {1, 101, 5},   // user 1, task 101, priority 5
  {2, 102, 3},   // user 2, task 102, priority 3
  {1, 103, 7}    // user 1, task 103, priority 7
};

TaskManager tm(tasks);
tm.add(3, 104, 6);       // Add new task
tm.edit(101, 8);         // Update priority of task 101
cout << tm.execTop();    // Executes task 101 (priority 8) → outputs 1 (userId)
*/
//==============================================================================

//==============================================================================
// Problem: Router Packet Manager
//
// Task:
// Design a Router class with limited memory to manage packets. It should support:
// 1. addPacket(source, destination, timestamp) → Add a new packet.
//    - Reject duplicate packets.
//    - If memory is full, forward (remove) the oldest packet first.
// 2. forwardPacket() → Remove and return the oldest packet in memory.
// 3. getCount(destination, startTime, endTime) →
//    Return the count of packets sent to `destination` whose timestamps
//    fall within the inclusive range [startTime, endTime].
//
// Approach:
// - Encode (source, destination, timestamp) into a unique key using bit shifting.
// - Maintain:
//   * `packets`: stores packet metadata mapped by unique key.
//   * `counts[destination]`: maintains sorted timestamps of packets per destination.
//   * `q`: queue to track packet insertion order (for FIFO forwarding).
// - Use binary search (`lower_bound`, `upper_bound`) to efficiently count timestamps
//   within a given time window.
//
// Key Idea:
// - Packets are uniquely identified by (source, destination, timestamp).
// - Memory management follows FIFO (queue).
// - Efficient timestamp queries achieved via binary search on sorted lists.
//==============================================================================

class Router
{
private:
  int size;                                      // memory limit
  unordered_map<long long, vector<int>> packets; // key → {source, destination, timestamp}
  unordered_map<int, vector<int>> counts;        // destination → timestamps
  queue<long long> q;                            // maintain FIFO order

  // Encode (source, destination, timestamp) into a 64-bit key
  long long encode(int source, int destination, int timestamp)
  {
    return ((long long)source << 40) | ((long long)destination << 20) | timestamp;
  }

  // Lower bound helper
  int lowerBound(vector<int> &list, int target)
  {
    return (int)(lower_bound(list.begin(), list.end(), target) - list.begin());
  }

  // Upper bound helper
  int upperBound(vector<int> &list, int target)
  {
    return (int)(upper_bound(list.begin(), list.end(), target) - list.begin());
  }

public:
  // Constructor
  Router(int memoryLimit)
  {
    size = memoryLimit;
  }

  // Add a new packet
  bool addPacket(int source, int destination, int timestamp)
  {
    long long key = encode(source, destination, timestamp);

    if (packets.find(key) != packets.end())
      return false; // duplicate packet

    if ((int)packets.size() >= size)
      forwardPacket(); // memory full → forward oldest

    packets[key] = {source, destination, timestamp};
    q.push(key);
    counts[destination].push_back(timestamp);

    return true;
  }

  // Forward (remove) the oldest packet
  vector<int> forwardPacket()
  {
    if (packets.empty())
      return {};

    long long key = q.front();
    q.pop();

    vector<int> packet = packets[key];
    packets.erase(key);

    int dest = packet[1];
    counts[dest].erase(counts[dest].begin()); // remove earliest timestamp

    return packet;
  }

  // Get count of packets for a destination in a time window
  int getCount(int destination, int startTime, int endTime)
  {
    auto it = counts.find(destination);
    if (it == counts.end() || it->second.empty())
      return 0;

    vector<int> &list = it->second;

    int left = lowerBound(list, startTime);
    int right = upperBound(list, endTime);

    return right - left;
  }
};

//==============================================================================
// Complexity Analysis:
// - addPacket: O(1) average (hash map insert) + O(1) amortized for queue
// - forwardPacket: O(1) average (hash erase) + O(1) for queue
// - getCount: O(log N) per query (binary search)
// - Space: O(N) for storing packets and timestamps
//==============================================================================

/*
Example Usage:
--------------
Router router(3);

router.addPacket(1, 2, 10);   // true
router.addPacket(2, 3, 15);   // true
router.addPacket(1, 2, 20);   // true
router.addPacket(3, 4, 25);   // true (evicts oldest: {1,2,10})

cout << router.getCount(2, 5, 30) << endl; // Output: 1 (only timestamp 20 remains)

vector<int> pkt = router.forwardPacket();
// pkt = {2, 3, 15} (oldest remaining packet)
*/
//==============================================================================

//==============================================================================
// Problem: Movie Renting System
//
// Task:
// Design a system to manage renting and reporting of movies across shops.
// Implement the following operations:
// 1. search(movie) → Return up to 5 shops offering the movie at the lowest price.
//    - If tie: choose shop with smaller id.
// 2. rent(shop, movie) → Mark the movie as rented from the shop.
// 3. drop(shop, movie) → Mark the movie as returned to the shop.
// 4. report() → Return up to 5 rented movies sorted by:
//    - Lowest price, then shop id, then movie id.
//
// Approach:
// - Define a `Node` struct with fields (shop, movie, price) and custom comparator.
// - Maintain:
//   * `byPair`: mapping (shop, movie) → Node
//   * `availableByMovie`: map from movie id → set of available shops (sorted by Node rules)
//   * `rentedSet`: global set of rented movies (sorted by Node rules)
//
// Key Idea:
// - Use `set<Node>` to maintain sorted order for both available movies per title
//   and globally rented movies.
// - Use a unique key encoding `(shop, movie)` for O(1) lookup in maps.
//==============================================================================
struct Node
{
  int shop, movie, price;
  bool operator<(const Node &other) const
  {
    if (price != other.price)
      return price < other.price;
    if (shop != other.shop)
      return shop < other.shop;
    return movie < other.movie;
  }
};

class MovieRentingSystem
{
  unordered_map<long long, Node> byPair;          // (shop, movie) → Node
  unordered_map<int, set<Node>> availableByMovie; // movie → set of available shops
  set<Node> rentedSet;                            // globally rented movies

  // Encode (shop, movie) pair into unique 64-bit key
  long long key(int shop, int movie)
  {
    return ((long long)shop << 32) ^ movie;
  }

public:
  // Constructor: load all entries
  MovieRentingSystem(int n, vector<vector<int>> &entries)
  {
    for (auto &e : entries)
    {
      int shop = e[0], movie = e[1], price = e[2];
      Node node{shop, movie, price};
      byPair[key(shop, movie)] = node;
      availableByMovie[movie].insert(node);
    }
  }

  // Search top 5 cheapest shops for a given movie
  vector<int> search(int movie)
  {
    vector<int> res;
    if (availableByMovie.count(movie) == 0)
      return res;

    auto &s = availableByMovie[movie];
    int count = 0;
    for (auto it = s.begin(); it != s.end() && count < 5; ++it, ++count)
    {
      res.push_back(it->shop);
    }
    return res;
  }

  // Rent a movie from a shop
  void rent(int shop, int movie)
  {
    long long k = key(shop, movie);
    Node node = byPair[k];
    availableByMovie[movie].erase(node);
    rentedSet.insert(node);
  }

  // Drop (return) a movie to a shop
  void drop(int shop, int movie)
  {
    long long k = key(shop, movie);
    Node node = byPair[k];
    rentedSet.erase(node);
    availableByMovie[movie].insert(node);
  }

  // Report top 5 rented movies
  vector<vector<int>> report()
  {
    vector<vector<int>> res;
    int count = 0;
    for (auto it = rentedSet.begin(); it != rentedSet.end() && count < 5; ++it, ++count)
    {
      res.push_back({it->shop, it->movie});
    }
    return res;
  }
};

//==============================================================================
// Complexity Analysis:
// - search: O(log N + K), where K ≤ 5 (top results).
// - rent/drop: O(log N), due to set insert/erase.
// - report: O(K), where K ≤ 5.
// - Space: O(N), storing all movies in maps and sets.
//==============================================================================

/*
Example Usage:
--------------
vector<vector<int>> entries = {
    {0, 1, 5}, {0, 2, 6}, {0, 3, 7},
    {1, 1, 4}, {1, 2, 7}, {2, 1, 5}
};

MovieRentingSystem system(3, entries);

system.search(1);       // → [1, 0, 2]  (sorted by price then shop)
system.rent(1, 1);      // rent movie 1 from shop 1
system.report();        // → [[1, 1]]   (shop 1, movie 1)
system.drop(1, 1);      // return movie 1 to shop 1
system.search(1);       // → [1, 0, 2]
*/
//==============================================================================

//==============================================================================
// Problem: Maximum Frequency Elements
// Task   : Given an integer array `nums`, return the sum of the frequencies
//          of the most frequent elements.
// Approach:
//   - Use a frequency array (since constraints are small, values ≤ 100).
//   - Track max frequency as we count.
//   - Maintain running sum of elements having that max frequency.
// Complexity:
//   - Time: O(n) where n = nums.size()
//   - Space: O(1) since frequency array size is constant (101).
//==============================================================================

class Solution
{
public:
  int maxFrequencyElements(vector<int> &nums)
  {
    uint8_t freq[101] = {0}; // frequency array for values [0..100]
    uint8_t maxFreq = 0;     // track maximum frequency
    uint8_t result = 0;      // sum of frequencies of max elements

    for (int n : nums)
    {
      uint8_t f = ++freq[n]; // increment frequency of element
      if (f > maxFreq)
      {
        maxFreq = f; // new maximum frequency found
        result = f;  // reset result to current frequency
      }
      else if (f == maxFreq)
      {
        result += f; // add to result if frequency matches max
      }
    }

    return result;
  }
};

//==============================================================================
// Example Usage:
//
// Input: nums = [1,2,2,3,1,4]
// Output: 4
// Explanation:
//   - Frequencies: 1 -> 2, 2 -> 2, 3 -> 1, 4 -> 1
//   - Max frequency = 2
//   - Elements with max frequency: 1 and 2
//   - Result = 2 + 2 = 4
//==============================================================================

//==============================================================================
// Problem: Compare Version Numbers
// Task   : Given two version numbers version1 and version2, compare them.
//          Return:
//             -1 if version1 < version2
//              1 if version1 > version2
//              0 if they are equal.
// Approach:
//   - Use stringstream to split both version strings by '.'.
//   - Compare each corresponding integer part.
//   - Treat missing parts as 0.
//   - If a difference is found, return immediately.
//   - Otherwise, return 0 at the end.
// Complexity:
//   - Time: O(n + m), where n and m are lengths of version1 and version2.
//   - Space: O(1) (only uses a few variables).
//==============================================================================

class Solution
{
public:
  int compareVersion(string version1, string version2)
  {
    stringstream s1(version1), s2(version2);
    string token1, token2;

    // Process until both streams are exhausted
    while (getline(s1, token1, '.') || getline(s2, token2, '.'))
    {
      int num1 = token1.empty() ? 0 : stoi(token1);
      int num2 = token2.empty() ? 0 : stoi(token2);

      if (num1 < num2)
        return -1;
      if (num1 > num2)
        return 1;

      // reset tokens for next iteration
      token1.clear();
      token2.clear();
    }
    return 0;
  }
};

//==============================================================================
// Example Usage:
//
// Input: version1 = "1.01", version2 = "1.001"
// Output: 0
// Explanation: Both represent the same version (1.1).
//
// Input: version1 = "1.0", version2 = "1.0.0"
// Output: 0
//
// Input: version1 = "0.1", version2 = "1.1"
// Output: -1
//==============================================================================

//==============================================================================
// Problem: Fraction to Recurring Decimal
// Task   : Given two integers numerator and denominator, return the fraction's
//          decimal string representation. If the fractional part is repeating,
//          enclose the repeating part in parentheses.
// Approach:
//   1. Handle sign separately (negative if numerator and denominator differ).
//   2. Use long long to avoid overflow when taking abs().
//   3. Append integer part: dividend / divisor.
//   4. If remainder = 0, return result (no fractional part).
//   5. Otherwise, process fractional part:
//        - Use a hash map to store each remainder’s position in the string.
//        - If remainder repeats, we found the recurring cycle → insert "(" and append ")".
//   6. Continue until remainder becomes 0 or repetition is detected.
// Complexity:
//   - Time: O(n), where n is the length of the recurring cycle (bounded by divisor).
//   - Space: O(n) for the hash map storing remainders.
//==============================================================================

class Solution
{
public:
  std::string fractionToDecimal(int numerator, int denominator)
  {
    if (numerator == 0)
      return "0";

    std::string fraction;

    // Handle sign
    if ((numerator < 0) ^ (denominator < 0))
      fraction += "-";

    // Convert to long long to handle abs(INT_MIN)
    long long dividend = std::llabs((long long)numerator);
    long long divisor = std::llabs((long long)denominator);

    // Append integer part
    fraction += std::to_string(dividend / divisor);

    long long remainder = dividend % divisor;
    if (remainder == 0)
    {
      return fraction;
    }

    // Process fractional part
    fraction += ".";
    std::unordered_map<long long, int> seen;

    while (remainder != 0)
    {
      if (seen.count(remainder))
      {
        fraction.insert(seen[remainder], "(");
        fraction += ")";
        break;
      }
      seen[remainder] = fraction.size();
      remainder *= 10;
      fraction += std::to_string(remainder / divisor);
      remainder %= divisor;
    }

    return fraction;
  }
};

//==============================================================================
// Example Usage:
//
// Input: numerator = 1, denominator = 2
// Output: "0.5"
//
// Input: numerator = 2, denominator = 3
// Output: "0.(6)"
//
// Input: numerator = 4, denominator = 333
// Output: "0.(012)"
//
// Input: numerator = 1, denominator = 5
// Output: "0.2"
//==============================================================================

//==============================================================================
// Problem: Triangle Minimum Path Sum
// Task   : Given a triangle array, return the minimum path sum from top to
//          bottom. At each step, you may move to an adjacent number in the
//          row below.
// Approach (Bottom-Up DP):
//   1. Initialize a DP table of size n x n.
//   2. Base case: Fill the last row of DP with the last row of the triangle.
//   3. Transition:
//        dp[r][c] = triangle[r][c] + min(dp[r+1][c], dp[r+1][c+1])
//   4. Iterate from bottom to top, computing the minimal path sums.
//   5. Result: dp[0][0] contains the minimum path sum.
// Complexity:
//   - Time: O(n^2), where n is the number of rows in the triangle.
//   - Space: O(n^2) for the DP table.
//==============================================================================

class Solution
{
public:
  int minimumTotal(vector<vector<int>> &triangle)
  {
    int n = triangle.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // Base case: last row
    for (int j = 0; j < triangle[n - 1].size(); ++j)
    {
      dp[n - 1][j] = triangle[n - 1][j];
    }

    // Bottom-up DP
    for (int r = n - 2; r >= 0; --r)
    {
      for (int c = 0; c < triangle[r].size(); ++c)
      {
        int down = dp[r + 1][c];
        int diag = dp[r + 1][c + 1];
        dp[r][c] = triangle[r][c] + min(down, diag);
      }
    }

    return dp[0][0];
  }
};

//==============================================================================
// Example Usage:
//
// Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
// Output: 11
// Explanation: The path 2 → 3 → 5 → 1 gives the minimum sum = 11.
//==============================================================================

//==============================================================================
// Problem: Valid Triangle Number
//
// Task:
// Given an integer array `nums`, return the number of triplets chosen from the
// array that can form a triangle if we take them as side lengths.
//
// Approach (Two Pointers + Sorting):
// 1. Sort the array in non-decreasing order.
// 2. Fix the largest element of the triplet (nums[i]) by iterating from the end.
// 3. Use two pointers (`left`, `right`) to find valid pairs such that:
//       nums[left] + nums[right] > nums[i]
//    - If true, all elements between left and right form valid pairs with nums[i].
//      Increase count by (right - left), then move `right--`.
//    - Otherwise, move `left++`.
// 4. Continue until all triplets are checked.
//
// Key Idea:
// - After sorting, only need to check triangle inequality for the largest side.
//
// Complexity:
// - Time: O(n^2), where n = nums.size()
//   (Sorting O(n log n) + Two-pointer iteration O(n^2))
// - Space: O(1), in-place operations.
//==============================================================================

class Solution
{
public:
  int triangleNumber(vector<int> &nums)
  {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    int count = 0;

    // Fix the largest element nums[i]
    for (int i = n - 1; i >= 2; i--)
    {
      int left = 0, right = i - 1;
      while (left < right)
      {
        if (nums[left] + nums[right] > nums[i])
        {
          // All elements between left and right form valid triangles
          count += right - left;
          right--;
        }
        else
        {
          left++;
        }
      }
    }
    return count;
  }
};

//==============================================================================
// Example Usage:
//
// Input: nums = [2, 2, 3, 4]
// Output: 3
// Explanation: Valid triangles are: (2,3,4), (2,3,4), (2,2,3)
//==============================================================================

//==============================================================================
// Problem: Largest Perimeter Triangle
//
// Task:
// Given an integer array `nums`, return the largest perimeter of a triangle with
// a non-zero area, formed from three of these numbers. If it is impossible to
// form any triangle, return 0.
//
// Approach:
// 1. Sort the array in descending order.
// 2. Iterate through the array, checking consecutive triples (nums[i], nums[i+1], nums[i+2]).
// 3. For a valid triangle, the sum of the two smaller sides must be greater
//    than the largest side: nums[i+1] + nums[i+2] > nums[i].
// 4. The first valid triple encountered (since sorted descending) gives the
//    maximum possible perimeter.
// 5. If no valid triple is found, return 0.
//
// Key Idea:
// - Sorting descending ensures that the first valid triangle found has the
//   largest possible perimeter.
//
// Complexity:
// - Time: O(n log n), due to sorting.
// - Space: O(1), in-place sorting and checks.
//==============================================================================

class Solution
{
public:
  int largestPerimeter(vector<int> &nums)
  {
    // Sort in descending order
    sort(nums.begin(), nums.end(), greater<int>());

    // Check consecutive triples
    for (int i = 0; i < nums.size() - 2; i++)
    {
      if (nums[i + 1] + nums[i + 2] > nums[i])
      {
        return nums[i] + nums[i + 1] + nums[i + 2];
      }
    }
    return 0;
  }
};

//==============================================================================
// Example Usage:
//
// Input: nums = [2, 1, 2]
// Output: 5
// Explanation: The numbers 2, 1, and 2 can form a triangle with perimeter 5.
//
// Input: nums = [1, 2, 1]
// Output: 0
// Explanation: No valid triangle can be formed.
//==============================================================================

//==============================================================================
// Problem: Minimum Score Triangulation of Polygon
//
// Task:
// You are given an integer array `values` of length n, representing the vertices
// of a convex polygon. The vertices are numbered in order, and the value of each
// vertex is values[i]. The score of a triangle is the product of its three vertices.
// Return the minimum total score achievable by triangulating the polygon.
//
// Approach (DP - Memoization):
// 1. Use recursion with memoization (`dp[i][j]`) to store the minimum score of
//    triangulating the subpolygon from vertex i to j.
// 2. Base case: If there are less than 3 vertices (j - i < 2), no triangle can be formed.
// 3. Transition:
//    - For each possible middle point `k` between `i` and `j`, form a triangle (i, k, j).
//    - Compute: dp[i][j] = min(dp[i][j], dp[i][k] + values[i]*values[k]*values[j] + dp[k][j]).
// 4. The answer is dp[0][n-1].
//
// Key Idea:
// - Divide-and-conquer approach: pick one triangle (i, k, j), then recursively solve the two sub-polygons.
// - Memoization ensures overlapping subproblems are solved only once.
//
// Complexity:
// - Time: O(n³), since we try every pair (i, j) with every possible k in between.
// - Space: O(n²), for the dp table.
//==============================================================================

class Solution
{
public:
  int dp[50][50] = {}; // memoization table

  int minScoreTriangulation(vector<int> &values, int i = 0, int j = 0, int res = 0)
  {
    if (j == 0)
      j = values.size() - 1; // initialize j on first call
    if (dp[i][j] != 0)
      return dp[i][j];

    for (int k = i + 1; k < j; ++k)
    {
      res = min(res == 0 ? INT_MAX : res,
                minScoreTriangulation(values, i, k) +
                    values[i] * values[k] * values[j] +
                    minScoreTriangulation(values, k, j));
    }
    return dp[i][j] = res;
  }
};

//==============================================================================
// Example Usage:
//
// Input: values = [1,2,3]
// Output: 6
// Explanation: Only one triangle can be formed: 1*2*3 = 6
//
// Input: values = [3,7,4,5]
// Output: 144
// Explanation: Minimum triangulation is (3,4,5) + (3,7,5) = 60 + 84 = 144
//==============================================================================

//==============================================================================
// Problem: Triangular Sum of an Array
//
// Task:
// You are given an integer array `nums`. Repeatedly replace each element with
// the sum of itself and the next element, modulo 10, until only one element remains.
// Return that single element.
//
// Example:
// Input: nums = [1,2,3,4,5]
// Process:
//   [1,2,3,4,5]
//   [3,5,7,9]
//   [8,2,6]
//   [0,8]
//   [8]
// Output: 8
//
// Approach (Simulation):
// 1. Start with the given array `nums`.
// 2. At each step, update nums[i] = (nums[i] + nums[i+1]) % 10 for all valid i.
// 3. Shrink the array size by 1 each time.
// 4. Continue until size reduces to 1.
// 5. Return nums[0] as the triangular sum.
//
// Key Idea:
// - This is a straightforward simulation problem.
// - We overwrite elements in-place to save space.
//
// Complexity:
// - Time: O(n²), since we perform (n-1) updates in the first pass, (n-2) in the next, etc.
// - Space: O(1), as the computation is done in-place.
//==============================================================================

#include <vector>
using namespace std;

class Solution
{
public:
  int triangularSum(vector<int> &nums)
  {
    int n = nums.size();
    for (int size = n; size > 1; --size)
    {
      for (int i = 0; i < size - 1; ++i)
      {
        nums[i] = (nums[i] + nums[i + 1]) % 10;
      }
    }
    return nums[0];
  }
};

//==============================================================================
// Example Usage:
// Solution sol;
// vector<int> nums = {1,2,3,4,5};
// int result = sol.triangularSum(nums); // Output: 8
//==============================================================================

//==============================================================================
// Problem: Maximum Bottles Drunk
//
// Task:
// You are given two integers:
// - `numBottles`: the number of full bottles initially.
// - `x`: the number of empty bottles required to exchange for one full bottle.
//
// Rules:
// - You can drink a full bottle, which gives you one empty bottle.
// - You can exchange exactly `x` empty bottles for one new full bottle.
// - After each exchange, `x` increases by 1 (making the next exchange harder).
//
// Return the maximum number of bottles you can drink.
//
// Example:
// Input: numBottles = 13, x = 6
// Process:
//   - Drink 13 bottles → 13 empties
//   - Exchange 6 empties for 1 full → 8 empties left, x = 7
//   - Drink 1 full → 9 empties
//   - Exchange 7 empties for 1 full → 2 empties left, x = 8
//   - Drink 1 full → 3 empties, cannot exchange further
// Total = 15
// Output: 15
//
// Approach (Simulation):
// 1. Start with `ans = numBottles` (all initially full bottles drunk).
// 2. While you can still exchange (`numBottles >= x`):
//    - Subtract (x - 1) from `numBottles` (since you give x empties and gain back 1).
//    - Increment `x` (exchange requirement grows).
//    - Increment `ans` (another bottle drunk).
// 3. Return total drunk bottles.
//
// Complexity:
// - Time: O(numBottles / x) worst-case, since exchanges reduce bottles gradually.
// - Space: O(1), constant extra space.
//==============================================================================

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  int maxBottlesDrunk(int numBottles, int x)
  {
    int ans = numBottles;
    while (numBottles >= x)
    {
      numBottles -= (x - 1); // exchange x, get 1 back
      x++;
      ans++;
    }
    return ans;
  }
};

//==============================================================================
// Example Usage:
// Solution sol;
// int result = sol.maxBottlesDrunk(13, 6);
// // Output: 15
//==============================================================================

//==============================================================================
// Problem: Trapping Rain Water II
//
// Task:
// Given a 2D elevation map (matrix of non-negative integers) where each cell
// represents the height at that position, compute the total amount of water
// that can be trapped after raining.
//
// Example:
// Input:
//   heightMap = [
//     [1,4,3,1,3,2],
//     [3,2,1,3,2,4],
//     [2,3,3,2,3,1]
//   ]
// Output: 4
//
// Explanation:
// - Water is trapped in low-height inner cells surrounded by taller boundary walls.
//
// Approach (Priority Queue + BFS):
// 1. Use a **min-heap (priority_queue)** to always expand from the lowest
//    current boundary cell.
// 2. Initialize by inserting all boundary cells into the min-heap and marking
//    them as visited.
// 3. Repeatedly pop the cell with the minimum height (the lowest boundary).
// 4. For each unvisited neighbor:
//    - If its height is less than the current boundary height, water can be trapped.
//    - Add trapped water volume = boundary height - neighbor height.
//    - Push the neighbor into the heap with height = max(neighbor, boundary).
// 5. Continue until heap is empty.
//
// Why this works:
// - The algorithm ensures we always "flood" from the lowest boundary inward.
// - The max() step ensures we maintain the correct effective boundary height.
//
// Complexity:
// - Time: O(m * n * log(m * n)), since each cell is pushed into the priority queue once.
// - Space: O(m * n), for visited matrix + heap storage.
//==============================================================================

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  int trapRainWater(vector<vector<int>> &heightMap)
  {
    // Edge case: empty map
    if (heightMap.empty() || heightMap[0].empty())
      return 0;

    // Direction arrays (left, right, up, down)
    int dRow[4] = {0, 0, -1, 1};
    int dCol[4] = {-1, 1, 0, 0};

    int numOfRows = heightMap.size();
    int numOfCols = heightMap[0].size();

    // Track visited cells
    vector<vector<bool>> visited(numOfRows, vector<bool>(numOfCols, false));

    // Min-heap priority queue for boundary processing
    priority_queue<Cell> boundary;

    // Add left and right boundaries
    for (int i = 0; i < numOfRows; i++)
    {
      boundary.push(Cell(heightMap[i][0], i, 0));
      boundary.push(Cell(heightMap[i][numOfCols - 1], i, numOfCols - 1));
      visited[i][0] = visited[i][numOfCols - 1] = true;
    }

    // Add top and bottom boundaries
    for (int j = 0; j < numOfCols; j++)
    {
      boundary.push(Cell(heightMap[0][j], 0, j));
      boundary.push(Cell(heightMap[numOfRows - 1][j], numOfRows - 1, j));
      visited[0][j] = visited[numOfRows - 1][j] = true;
    }

    int totalWaterVolume = 0;

    // Process cells in order of boundary height
    while (!boundary.empty())
    {
      Cell currentCell = boundary.top();
      boundary.pop();

      int currentRow = currentCell.row;
      int currentCol = currentCell.col;
      int minBoundaryHeight = currentCell.height;

      // Explore neighbors
      for (int dir = 0; dir < 4; dir++)
      {
        int neighborRow = currentRow + dRow[dir];
        int neighborCol = currentCol + dCol[dir];

        if (isValidCell(neighborRow, neighborCol, numOfRows, numOfCols) &&
            !visited[neighborRow][neighborCol])
        {

          int neighborHeight = heightMap[neighborRow][neighborCol];

          // Trap water if neighbor is lower
          if (neighborHeight < minBoundaryHeight)
          {
            totalWaterVolume += minBoundaryHeight - neighborHeight;
          }

          // Push updated neighbor (effective boundary height)
          boundary.push(Cell(max(neighborHeight, minBoundaryHeight),
                             neighborRow, neighborCol));
          visited[neighborRow][neighborCol] = true;
        }
      }
    }

    return totalWaterVolume;
  }

private:
  // Cell struct for heap
  class Cell
  {
  public:
    int height;
    int row;
    int col;

    Cell(int h, int r, int c) : height(h), row(r), col(c) {}

    // Custom comparator to make priority_queue a min-heap
    bool operator<(const Cell &other) const
    {
      return height >= other.height; // reverse order
    }
  };

  // Validity check
  bool isValidCell(int row, int col, int numOfRows, int numOfCols)
  {
    return row >= 0 && col >= 0 && row < numOfRows && col < numOfCols;
  }
};

//==============================================================================
// Example Usage:
// Solution sol;
// vector<vector<int>> heightMap = {
//     {1,4,3,1,3,2},
//     {3,2,1,3,2,4},
//     {2,3,3,2,3,1}
// };
// int result = sol.trapRainWater(heightMap);
// // Output: 4
//==============================================================================

//==============================================================================
// Problem: Container With Most Water
//
// Task:
// You are given an integer array `height` of length n. There are n vertical lines
// drawn such that the two endpoints of the i-th line are (i, 0) and (i, height[i]).
// Find two lines that together with the x-axis form a container such that it holds
// the maximum amount of water.
//
// Note: You may not slant the container.
//
// Example:
// Input:  height = [1,8,6,2,5,4,8,3,7]
// Output: 49
//
// Explanation:
// The lines at indices 1 and 8 form the container with the largest area:
// width = 8 - 1 = 7, height = min(8, 7) = 7 → area = 49.
//
// Approach (Two Pointers):
// 1. Start with two pointers: one at the leftmost index and one at the rightmost.
// 2. Compute area = width * min(height[left], height[right]).
// 3. Update maxArea if this area is larger.
// 4. Move the pointer with the smaller height inward (since moving the taller
//    one cannot increase the area).
// 5. Repeat until pointers meet.
//
// Complexity:
// - Time: O(n), since each pointer moves at most n steps.
// - Space: O(1).
//==============================================================================

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  int maxArea(vector<int> &height)
  {
    int maxArea = 0;
    int left = 0;
    int right = height.size() - 1;

    while (left < right)
    {
      // Calculate the area formed by the two pointers
      int width = right - left;
      int h = min(height[left], height[right]);
      maxArea = max(maxArea, width * h);

      // Move the pointer at the smaller height inward
      if (height[left] < height[right])
      {
        left++;
      }
      else
      {
        right--;
      }
    }

    return maxArea;
  }
};

//==============================================================================
// Example Usage:
//
// Solution sol;
// vector<int> height = {1,8,6,2,5,4,8,3,7};
// int result = sol.maxArea(height);
// // Output: 49
//==============================================================================

//==============================================================================
// Problem: Pacific Atlantic Water Flow
//
// Task:
// Given an m x n matrix of non-negative integers `heights`, where heights[r][c]
// represents the height of each cell, determine the list of coordinates where
// water can flow to both the Pacific and Atlantic oceans.
//
// The Pacific ocean touches the left and top edges of the matrix,
// and the Atlantic ocean touches the right and bottom edges.
//
// Water can only flow from a cell to another with height equal or lower.
//
// Example:
// Input: heights = [
//   [1,2,2,3,5],
//   [3,2,3,4,4],
//   [2,4,5,3,1],
//   [6,7,1,4,5],
//   [5,1,1,2,4]
// ]
// Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
//
// Approach (Reverse DFS):
// 1. Instead of simulating flow from each cell to the oceans, we reverse the flow.
// 2. Start DFS from all Pacific-border cells and mark cells reachable from Pacific.
// 3. Do the same for Atlantic-border cells.
// 4. Cells visited in both Pacific and Atlantic traversals are the result.
//
// Complexity:
// - Time: O(m * n) — Each cell is visited at most twice.
// - Space: O(m * n) — For visited matrices and recursion stack.
//
//==============================================================================

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  int m, n;
  vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

  vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights)
  {
    m = heights.size();
    n = heights[0].size();

    // Track visited cells for both oceans
    vector<vector<bool>> pacific(m, vector<bool>(n, false));
    vector<vector<bool>> atlantic(m, vector<bool>(n, false));

    // Run DFS for Pacific (top and left edges)
    for (int j = 0; j < n; j++)
      dfs(0, j, heights, pacific);
    for (int i = 0; i < m; i++)
      dfs(i, 0, heights, pacific);

    // Run DFS for Atlantic (bottom and right edges)
    for (int j = 0; j < n; j++)
      dfs(m - 1, j, heights, atlantic);
    for (int i = 0; i < m; i++)
      dfs(i, n - 1, heights, atlantic);

    // Find common cells that can reach both oceans
    vector<vector<int>> result;
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (pacific[i][j] && atlantic[i][j])
        {
          result.push_back({i, j});
        }
      }
    }

    return result;
  }

private:
  //==============================================================================
  // DFS Helper: Mark all reachable cells from the given ocean
  //==============================================================================
  void dfs(int i, int j, vector<vector<int>> &heights, vector<vector<bool>> &visited)
  {
    visited[i][j] = true;

    for (auto &d : directions)
    {
      int x = i + d[0];
      int y = j + d[1];

      // Skip invalid or already visited cells
      if (x < 0 || x >= m || y < 0 || y >= n)
        continue;
      if (visited[x][y])
        continue;

      // Water can only flow from lower to higher or equal height
      if (heights[x][y] < heights[i][j])
        continue;

      dfs(x, y, heights, visited);
    }
  }
};

//==============================================================================
// Example Usage:
//
// Solution sol;
// vector<vector<int>> heights = {
//     {1,2,2,3,5},
//     {3,2,3,4,4},
//     {2,4,5,3,1},
//     {6,7,1,4,5},
//     {5,1,1,2,4}
// };
// vector<vector<int>> result = sol.pacificAtlantic(heights);
// // Expected Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
//==============================================================================

//==============================================================================
// Problem: Swim in Rising Water
//
// Task:
// You are given an n x n integer matrix `grid` where each value represents
// the elevation at that cell. Initially, at time t = 0, you are at the
// top-left cell (0,0). At every time t, you can swim to a neighboring cell
// if the elevation of both the current and target cell is ≤ t.
//
// You must return the minimum time t such that you can reach the bottom-right
// cell (n-1, n-1).
//
// Approach (Kruskal’s MST / Union-Find):
// 1. Treat each cell as a node in a graph.
// 2. Create edges between adjacent cells with weights = max(height1, height2).
// 3. Sort all edges by weight.
// 4. Use Union-Find to connect cells by increasing elevation.
// 5. The first time the start and end become connected, that weight is the answer.
//
// Complexity:
// - Time: O(n² log n²) = O(n² log n)
// - Space: O(n²)
//
//==============================================================================

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  int swimInWater(vector<vector<int>> &grid)
  {
    int m = grid.size();
    int n = grid[0].size();

    vector<tuple<int, int, int>> edges; // {cost, u, v}

    //======================================================================
    // Step 1: Build all possible edges between adjacent cells
    //======================================================================
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (i > 0)
          edges.push_back({max(grid[i][j], grid[i - 1][j]), i * n + j, (i - 1) * n + j});
        if (j > 0)
          edges.push_back({max(grid[i][j], grid[i][j - 1]), i * n + j, i * n + j - 1});
      }
    }

    //======================================================================
    // Step 2: Sort edges by elevation cost
    //======================================================================
    sort(edges.begin(), edges.end());

    //======================================================================
    // Step 3: Initialize Union-Find (Disjoint Set Union)
    //======================================================================
    vector<int> parent(m * n);
    iota(parent.begin(), parent.end(), 0);

    function<int(int)> find = [&](int x) -> int
    {
      return parent[x] == x ? x : parent[x] = find(parent[x]);
    };

    auto unite = [&](int x, int y)
    {
      parent[find(x)] = find(y);
    };

    //======================================================================
    // Step 4: Connect edges in increasing order of cost
    //======================================================================
    for (auto [cost, u, v] : edges)
    {
      unite(u, v);
      // If start (0) and end (m*n-1) are connected, return current cost
      if (find(0) == find(m * n - 1))
        return cost;
    }

    // Edge case: single cell
    return grid[0][0];
  }
};

//==============================================================================
// Example Usage:
//
// Solution sol;
// vector<vector<int>> grid = {
//     {0, 2},
//     {1, 3}
// };
// int result = sol.swimInWater(grid);
// // Expected Output: 3
//==============================================================================

//==============================================================================
// Problem: Avoid Flood in The City
//
// Task:
// You are given an array `rain` where:
// - rain[i] > 0 → lake rain[i] gets rain on day i.
// - rain[i] == 0 → you may choose one lake to dry that day.
//
// Return an array representing the action taken each day:
// - res[i] = -1 if it rains on day i.
// - res[i] = lake number to dry on that day if no rain.
// If it’s impossible to prevent flooding, return an empty array.
//
// Approach (Union-Find Optimization):
// ----------------------------------
// - We use Union-Find to efficiently find the *next available dry day*.
// - When it rains on lake X:
//     • If lake X has been filled before, find the next dry day after that
//       previous rain day using Union-Find.
//     • If no dry day is available → flood occurs → return {}.
// - Each time a day is used (either raining or drying), we mark it as “used”
//   by uniting it with the next day.
//
// Complexity:
// - Time: O(N α(N)), where α(N) is the inverse Ackermann (almost constant)
// - Space: O(N)
//
//==============================================================================

#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Union-Find Data Structure to Manage Available Dry Days
//==============================================================================
class UnionFind
{
public:
  vector<int> parent;

  UnionFind(int size) : parent(size + 1)
  {
    iota(parent.begin(), parent.end(), 0);
  }

  // Path Compression
  int find(int i)
  {
    if (i == parent[i])
      return i;
    return parent[i] = find(parent[i]);
  }

  // Mark a day as used (link it to next day)
  void unite(int i)
  {
    parent[i] = find(i + 1);
  }
};

//==============================================================================
// Solution Class
//==============================================================================
class Solution
{
public:
  vector<int> avoidFlood(vector<int> &rain)
  {
    int n = rain.size();
    UnionFind uf(n + 1);
    unordered_map<int, int> lastRainDay; // lake → last rained index
    vector<int> res(n, 1);               // default = 1 for dry days

    //======================================================================
    // Main Simulation Loop
    //======================================================================
    for (int i = 0; i < n; i++)
    {
      int lake = rain[i];

      // Case 1: Dry day → skip for now (default res[i] = 1)
      if (lake == 0)
        continue;

      // Case 2: It rains today
      res[i] = -1;
      uf.unite(i); // mark this day as used

      // If this lake has rained before, we must dry it before now
      if (lastRainDay.count(lake))
      {
        int prev = lastRainDay[lake];
        int dryDay = uf.find(prev + 1);

        // If no available dry day exists before today → flood
        if (dryDay >= i)
          return {};

        // Use the found dry day to dry this lake
        res[dryDay] = lake;
        uf.unite(dryDay); // mark dry day as used
        lastRainDay[lake] = i;
      }
      else
      {
        lastRainDay[lake] = i;
      }
    }

    return res;
  }
};

//==============================================================================
// Example Usage:
//==============================================================================
//
// Solution sol;
// vector<int> rain = {1, 2, 0, 0, 2, 1};
// vector<int> res = sol.avoidFlood(rain);
//
// Expected Output: [-1, -1, 2, 1, -1, -1]
// Explanation:
// - Day 0: Lake 1 fills.
// - Day 1: Lake 2 fills.
// - Day 2: Dry lake 2.
// - Day 3: Dry lake 1.
// - Day 4: Lake 2 refills safely.
// - Day 5: Lake 1 refills safely.
//
//==============================================================================

//==============================================================================
// Problem: Successful Pairs of Spells and Potions
//------------------------------------------------------------------------------
// You are given two integer arrays `spells` and `potions`, and an integer
// `success`. A pair (spell, potion) is considered successful if
// spell * potion >= success.
//
// For each spell, find how many potions form a successful pair with it.
//
// Approach:
// - Sort the potions array.
// - For each spell, use binary search to find the smallest potion
//   that satisfies the condition spell * potion >= success.
// - The count of valid potions = total potions - index found.
//
// Complexity Analysis:
// - Time:  O(n log m) where n = spells.size(), m = potions.size()
// - Space: O(1)
//==============================================================================

class Solution
{
public:
  vector<int> successfulPairs(vector<int> &spells, vector<int> &potions, long long success)
  {
    // Sort the potions to apply binary search
    sort(potions.begin(), potions.end());

    int n = spells.size();
    vector<int> ans(n);

    for (int i = 0; i < n; i++)
    {
      int idx = binarySearch(potions, spells[i], success);
      if (idx != -1)
        ans[i] = potions.size() - idx;
      else
        ans[i] = 0;
    }

    return ans;
  }

private:
  //------------------------------------------------------------------------------
  // Helper Function: Binary Search
  // Finds the first index where potions[mid] * strength >= success
  //------------------------------------------------------------------------------
  int binarySearch(vector<int> &potions, long long strength, long long success)
  {
    int low = 0, high = potions.size() - 1, idx = -1;

    while (low <= high)
    {
      int mid = low + (high - low) / 2;

      if (1LL * potions[mid] * strength >= success)
      {
        idx = mid;
        high = mid - 1; // Try to find a smaller potion that still works
      }
      else
      {
        low = mid + 1;
      }
    }

    return idx;
  }
};

//==============================================================================
// Problem: Minimum Time to Complete All Skills
//------------------------------------------------------------------------------
// You are given two integer arrays:
//   - skill[]: represents the skill value of each task.
//   - mana[] : represents the multiplier (or effort/time factor) for each round.
//
// Each round j contributes to increasing the cumulative time for each skill i
// based on: done[i + 1] = max(done[i + 1], done[i]) + (mana[j] * skill[i])
//
// After each round, adjustments are made by iterating backward to ensure
// the proper ordering and dependency between tasks.
//
// The final answer is done[n] after processing all rounds.
//
//------------------------------------------------------------------------------
// Approach:
// - Initialize a `done` array to store cumulative results.
// - For each mana round:
//     → Forward pass: accumulate increasing time costs.
//     → Backward pass: balance dependencies in reverse order.
// - Return the total cumulative time done[n].
//
//------------------------------------------------------------------------------
// Complexity Analysis:
// - Time:  O(m * n)    → double nested loop over skills and mana
// - Space: O(n)        → single vector for DP state
//==============================================================================

class Solution
{
public:
  long long minTime(vector<int> &skill, vector<int> &mana)
  {
    int n = skill.size(), m = mana.size();
    vector<long long> done(n + 1, 0); // DP array to store cumulative time

    // Process each mana level (round)
    for (int j = 0; j < m; ++j)
    {
      // Forward accumulation pass
      for (int i = 0; i < n; ++i)
      {
        done[i + 1] = max(done[i + 1], done[i]) + 1LL * mana[j] * skill[i];
      }

      // Backward balancing pass
      for (int i = n - 1; i > 0; --i)
      {
        done[i] = done[i + 1] - 1LL * mana[j] * skill[i];
      }
    }

    return done[n];
  }
};

//==============================================================================
// ⚡ Problem: Maximum Energy
//------------------------------------------------------------------------------
// You are given an integer array `energy` and an integer `k`.
// You can move from index `i` to `i + k` repeatedly, collecting the total sum
// of energies along the way. The goal is to determine the maximum total energy
// that can be collected starting from any index.
//
//------------------------------------------------------------------------------
// Approach:
// - Start iterating from the end of the array backward.
// - For each index `i`, if `i + k` is within bounds, accumulate the energy
//   from `energy[i + k]` to `energy[i]`.
// - Track the maximum accumulated value during traversal.
//
//------------------------------------------------------------------------------
// Complexity Analysis:
// - Time:  O(n)    → single reverse traversal
// - Space: O(1)    → in-place update of the `energy` array
//==============================================================================

class Solution
{
public:
  int maximumEnergy(vector<int> &energy, int k)
  {
    int n = energy.size();
    int max_energy = INT_MIN;

    // Traverse array in reverse and accumulate jump-based energy
    for (int i = n - 1; i >= 0; i--)
    {
      if (i + k < n)
        energy[i] += energy[i + k];

      max_energy = max(max_energy, energy[i]);
    }

    return max_energy;
  }
};

//==============================================================================
// ⚔️ Problem: Maximum Total Damage
//------------------------------------------------------------------------------
// You are given an array `power` representing the attack power of enemies.
// When you attack enemies with power `x`, all enemies with power `x - 2`,
// `x - 1`, `x + 1`, and `x + 2` are also affected (cannot be attacked again).
// Your task is to choose attacks to maximize the total damage dealt.
//
//------------------------------------------------------------------------------
// 🔹 Approach:
// 1. Aggregate all enemies with the same power — store the total damage
//    for each unique power in a map: `mp[power] += power`.
// 2. Convert the map into a sorted vector of `{power, total_damage}` pairs.
// 3. Use recursion with memoization (Top-Down DP):
//    - Either skip the current power value.
//    - Or take it and jump to the next valid index `j` such that
//      `v[j].first > v[idx].first + 2` (since adjacent powers are blocked).
// 4. Return the maximum of both choices.
//
//------------------------------------------------------------------------------
// ⏱️ Complexity Analysis:
// - Time:  O(n log n) → due to sorting and map operations
// - Space: O(n)       → for recursion stack and DP memoization
//==============================================================================

class Solution
{
public:
  // Recursive DP function to compute maximum total damage
  long long solve(int idx, vector<pair<long long, long long>> &v, vector<long long> &dp)
  {
    if (idx >= v.size())
      return 0;

    if (dp[idx] != -1)
      return dp[idx];

    // Option 1: Skip current element
    long long skip = solve(idx + 1, v, dp);

    // Option 2: Take current element and move to next valid index
    int j = idx + 1;
    while (j < v.size() && v[j].first <= v[idx].first + 2)
      j++;

    long long consider = v[idx].second + solve(j, v, dp);

    // Store and return the best option
    return dp[idx] = max(skip, consider);
  }

  long long maximumTotalDamage(vector<int> &power)
  {
    int n = power.size();
    map<long long, long long> mp;

    // Aggregate total damage for each unique power
    for (int i = 0; i < n; i++)
      mp[power[i]] += power[i];

    // Convert map to sorted vector
    vector<pair<long long, long long>> v;
    for (auto it : mp)
      v.push_back({it.first, it.second});

    sort(v.begin(), v.end());

    // DP memoization array
    vector<long long> dp(v.size(), -1);

    // Compute maximum total damage
    return solve(0, v, dp);
  }
};

//==============================================================================
//  Problem: Magical Sum
//------------------------------------------------------------------------------
// You are given integers `m`, `k`, and an array `nums`.
// The task is to compute a "magical sum" based on the following recursive
// process involving binary carries, combinatorial coefficients, and modular
// arithmetic.
//
// The exact meaning of the problem depends on its hidden mathematical
// formulation (like summing bit-carry configurations). However, the given code
// essentially computes — under modular arithmetic — the total number of
// configurations where exactly `k` ones appear in the binary representation of
// the result of combining terms based on `nums[i]^cnt`, with total exponent sum
// `m`.
//
//------------------------------------------------------------------------------
//  Key Ideas / Steps:
// 1. **Precompute Powers:**
//    For every `nums[i]`, precompute `nums[i]^j` for all `j ≤ m` (mod MOD).
//
// 2. **Precompute Combinations (nCr):**
//    Using Pascal’s Triangle to efficiently compute binomial coefficients
//    modulo MOD.
//
// 3. **4D Dynamic Programming with Memoization:**
//    DP state: `dp[pos][carry][used][ones]`
//    - `pos`   → current index in `nums`
//    - `carry` → carry-over bits from binary sum
//    - `used`  → how many powers have been used so far
//    - `ones`  → number of 1-bits accumulated so far
//
// 4. **Recursive DFS Transition:**
//    Try all possible counts `cnt` of times to use `nums[pos]`,
//    update carry and bits, multiply by combination counts and power terms.
//
//------------------------------------------------------------------------------
//  Complexity Analysis:
// - Time:  O(n * m³) in worst case (since 4D DP with bounded ranges)
// - Space: O(n * m³) due to dp and visited arrays
//------------------------------------------------------------------------------
// ⚡ Constants:
// - MOD = 1e9 + 7
//==============================================================================

#define ll long long
const int MOD = 1e9 + 7;

class Solution
{
public:
  int magicalSum(int m, int k, vector<int> &nums)
  {
    int n = nums.size();

    //--------------------------------------------------------------------------
    // STEP 1: Precompute all powers nums[i]^j (mod MOD)
    //--------------------------------------------------------------------------
    vector<vector<ll>> powNum(n, vector<ll>(m + 1, 1));
    for (int i = 0; i < n; i++)
    {
      for (int j = 1; j <= m; j++)
      {
        powNum[i][j] = (powNum[i][j - 1] * nums[i]) % MOD;
      }
    }

    //--------------------------------------------------------------------------
    // STEP 2: Precompute binomial coefficients C[i][j] = i choose j (mod MOD)
    //--------------------------------------------------------------------------
    vector<vector<ll>> C(m + 1, vector<ll>(m + 1, 0));
    for (int i = 0; i <= m; i++)
    {
      C[i][0] = C[i][i] = 1;
      for (int j = 1; j < i; j++)
      {
        C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
      }
    }

    //--------------------------------------------------------------------------
    // STEP 3: DP memoization arrays
    //--------------------------------------------------------------------------
    static ll dp[55][35][35][35];
    static bool vis[55][35][35][35];
    memset(vis, 0, sizeof(vis));

    //--------------------------------------------------------------------------
    // STEP 4: Recursive DFS with memoization
    //--------------------------------------------------------------------------
    function<ll(int, int, int, int)> dfs = [&](int pos, int carry, int used, int ones) -> ll
    {
      // Base Case: All elements processed
      if (pos == n)
      {
        int extra = 0;
        int c = carry;
        while (c)
        {
          if (c & 1)
            extra++;
          c >>= 1;
        }
        return (used == m && ones + extra == k) ? 1 : 0;
      }

      // Memoized result
      if (vis[pos][carry][used][ones])
        return dp[pos][carry][used][ones];
      vis[pos][carry][used][ones] = 1;

      ll ans = 0;

      // Try all possible counts for current number
      for (int cnt = 0; cnt + used <= m; cnt++)
      {
        int total = carry + cnt;
        int bit = total & 1;
        int ncarry = total >> 1;
        int nones = ones + bit;

        ll sub = dfs(pos + 1, ncarry, used + cnt, nones);
        if (!sub)
          continue;

        ll ways = C[m - used][cnt];
        ll prod = powNum[pos][cnt];

        ans = (ans + sub * ways % MOD * prod) % MOD;
      }

      return dp[pos][carry][used][ones] = ans;
    };

    //--------------------------------------------------------------------------
    // STEP 5: Compute and return result
    //--------------------------------------------------------------------------
    return static_cast<int>(dfs(0, 0, 0, 0));
  }
};

//==============================================================================
//  Problem: Remove Anagrams
//------------------------------------------------------------------------------
// Given an array of words, remove consecutive words that are anagrams of each
// other. Return the resulting array after all such removals.
//
// Example:
// Input  : ["abba", "baba", "bbaa", "cd", "cd"]
// Output : ["abba", "cd"]
//
//------------------------------------------------------------------------------
//  Approach:
// 1. Maintain a frequency map (26-length vector) for each word.
// 2. Compare the frequency map of the current word with the last accepted one.
// 3. If they are the same, skip (as it’s an anagram of the previous).
// 4. Otherwise, push it into the result and update the reference frequency map.
//
//------------------------------------------------------------------------------
//  Complexity Analysis:
// Time  : O(N * K)  — where N = number of words, K = average word length
// Space : O(26) ≈ O(1)
//==============================================================================

class Solution
{
public:
  vector<string> removeAnagrams(vector<string> &words)
  {
    vector<int> prevFreq(26, 0), currFreq(26, 0);
    vector<string> result;

    // Iterate through each word
    for (auto &word : words)
    {
      // Compute frequency count of the current word
      for (auto ch : word)
        currFreq[ch - 'a']++;

      // Compare with previous frequency map
      if (currFreq == prevFreq)
      {
        // Same as previous → anagram → skip
        fill(currFreq.begin(), currFreq.end(), 0);
      }
      else
      {
        // New unique word → accept
        prevFreq = currFreq;
        result.push_back(word);
        fill(currFreq.begin(), currFreq.end(), 0);
      }
    }

    return result;
  }
};

// ============================================================================
//  💡 Problem: Has Increasing Subarrays (LeetCode)
//  🧩 Task:
//      Given an integer array nums and an integer k, check whether there exist
//      two increasing subarrays of length k such that the second subarray
//      starts after the first ends.
//
//  🧠 Approach:
//      1️⃣ Use a DP-like array `inc[i]` to store the length of the current
//          increasing subarray ending at index i.
//      2️⃣ Traverse the array once to fill `inc`.
//      3️⃣ Then, check if there exist two segments of length ≥ k separated by k.
//
//  ⏱️ Time Complexity:  O(n)
//  💾 Space Complexity: O(n)
// ============================================================================

class Solution
{
public:
  bool hasIncreasingSubarrays(vector<int> &nums, int k)
  {
    int n = nums.size();
    if (n < 2 * k)
      return false;

    vector<int> inc(n, 1);

    // Build increasing subarray lengths
    for (int i = 1; i < n; i++)
      if (nums[i] > nums[i - 1])
        inc[i] = inc[i - 1] + 1;

    // Check for two valid increasing subarrays
    for (int i = k - 1; i + k < n; i++)
      if (inc[i] >= k && inc[i + k] >= k)
        return true;

    return false;
  }
};

// ============================================================================
//  💡 Problem: Maximum Increasing Subarrays (LeetCode)
//  🧩 Task:
//      Given an integer array `nums`, find the maximum possible length `k`
//      such that there exist two increasing subarrays of length `k` where
//      the second subarray starts immediately after the first ends.
//
//  🧠 Approach:
//      1️⃣ Maintain two counters:
//          - `up`: length of the current increasing sequence.
//          - `preUp`: length of the previous increasing sequence.
//      2️⃣ When the increasing order breaks, store `up` into `preUp` and reset.
//      3️⃣ For every step, the possible valid length `k` can be:
//          - `half = up / 2` (if a single long increasing run exists), or
//          - `min(preUp, up)` (if two adjacent runs exist).
//      4️⃣ Track the maximum among these candidates.
//
//  ⏱️ Time Complexity:  O(n)
//  💾 Space Complexity: O(1)
// ============================================================================

class Solution
{
public:
  int maxIncreasingSubarrays(vector<int> &nums)
  {
    int n = nums.size();
    int up = 1, preUp = 0, res = 0;

    for (int i = 1; i < n; i++)
    {
      if (nums[i] > nums[i - 1])
        up++;
      else
      {
        preUp = up;
        up = 1;
      }

      int half = up >> 1;           // half of current sequence
      int m = min(preUp, up);       // adjacent sequence overlap
      int candidate = max(half, m); // best possible segment length

      res = max(res, candidate);
    }

    return res;
  }
};

// ============================================================================
//  💡 Problem: Find the Smallest Integer in Array After Operations (LeetCode)
//  🧩 Task:
//      You are given an integer array `nums` and an integer `value`.
//      You can add or subtract `value` from any element of `nums` any number of times.
//      Return the smallest non-negative integer that cannot be represented as a
//      possible result of any number after the allowed operations.
//
//  🧠 Approach:
//      1️⃣ Each number `x` is equivalent to its remainder modulo `value`.
//          Normalize as: (x % value + value) % value  → handles negatives too.
//      2️⃣ Count the frequency of each remainder.
//      3️⃣ Starting from `i = 0`, check remainder `i % value`:
//          - If frequency of that remainder is 0 → return `i`.
//          - Otherwise, use one instance (decrement count) and continue.
//
//  ⏱️ Time Complexity:  O(n)
//  💾 Space Complexity: O(value)
// ============================================================================

class Solution
{
public:
  int findSmallestInteger(vector<int> &nums, int value)
  {
    unordered_map<int, int> freq;

    // Step 1: Compute frequency of each remainder (normalized)
    for (auto x : nums)
      freq[(x % value + value) % value]++;

    // Step 2: Find smallest i that cannot be represented
    for (int i = 0;; i++)
    {
      int rem = i % value;

      if (freq[rem] == 0)
        return i;

      freq[rem]--; // use one occurrence of this remainder
    }
  }
};

// ============================================================================
//  💡 Problem: Lexicographically Smallest String After Applying Operations
//  🧩 Task:
//      You are given a string `s` consisting of digits, and two integers `a` and `b`.
//      You can repeatedly perform either of the following operations any number of times:
//          1️⃣ Add `a` to all digits at odd indices (mod 10).
//          2️⃣ Rotate the string to the right by `b` positions.
//      Return the lexicographically smallest string obtainable after any sequence of operations.
//
//  🧠 Approach:
//      1️⃣ Since rotation repeats every `n` steps, use a visited array `vis` to track starting positions.
//      2️⃣ Try all possible rotations generated by repeatedly rotating by `b`.
//      3️⃣ For each rotation, simulate all possible additions to digits:
//          - Add `a` * j to odd indices (j ∈ [0, 9]).
//          - If `b` is odd, also try all additions `k ∈ [0, 9]` to even indices
//            (because odd/even digit positions swap after each rotation).
//      4️⃣ Compare each transformed string lexicographically and update result.
//
//  ⏱️ Time Complexity:  O(10 * 10 * n) ≈ O(n)
//  💾 Space Complexity: O(n)
// ============================================================================

class Solution
{
public:
  string findLexSmallestString(string s, int a, int b)
  {
    int n = s.size();
    vector<int> vis(n, 0);
    string res = s;

    // Duplicate string for easy rotation handling
    s += s;

    // Step 1: Explore all distinct rotation start positions
    for (int i = 0; vis[i] == 0; i = (i + b) % n)
    {
      vis[i] = 1;

      // Step 2: Try all possible additions for odd indices
      for (int j = 0; j < 10; j++)
      {
        // If b is odd, both even and odd indices can change
        int k_limit = (b % 2 == 0) ? 0 : 9;

        // Step 3: Try all possible additions for even indices
        for (int k = 0; k <= k_limit; k++)
        {
          string t = s.substr(i, n);

          // Modify odd indices
          for (int p = 1; p < n; p += 2)
            t[p] = '0' + (t[p] - '0' + j * a) % 10;

          // Modify even indices (only relevant if b is odd)
          for (int p = 0; p < n; p += 2)
            t[p] = '0' + (t[p] - '0' + k * a) % 10;

          // Track lexicographically smallest string
          res = min(res, t);
        }
      }
    }

    return res;
  }
};

class Solution
{
public:
  int finalValueAfterOperations(vector<string> &operations)
  {
    int x = 0;
    for (auto &op : operations)
    {
      if (op == "X++" || op == "++X")
      {
        x++;
      }
      else
      {
        x--;
      }
    }
    return x;
  }
};

// ============================================================================
//  💡 Problem: Maximize Frequency After Limited Operations
//  🧩 Task:
//      You are given an array `nums`, and two integers `k` and `numOperations`.
//      You can perform at most `numOperations` operations, where each operation
//      allows you to change a number `x` to any value within the range `[x - k, x + k]`.
//      Your goal is to maximize the frequency of any number after performing these operations.
//
//  🧠 Approach:
//      1️⃣ Determine the maximum possible element value after adding `k` to the largest element.
//      2️⃣ Build a frequency array `freq` to count occurrences of each number up to `max_ele`.
//      3️⃣ Compute prefix sums over `freq` to allow range frequency queries in O(1).
//      4️⃣ For each potential target value `t`:
//          - Compute its valid range `[t - k, t + k]`.
//          - Count how many elements can be converted to `t` (using prefix sums).
//          - Calculate the result as:
//              `current_frequency + min(numOperations, convertible_count - current_frequency)`
//      5️⃣ Track the maximum achievable frequency.
//
//  ⏱️ Time Complexity:  O(M)   (where M = max_element + k)
//  💾 Space Complexity: O(M)
// ============================================================================

class Solution
{
public:
  int maxFrequency(vector<int> &nums, int k, int numOperations)
  {
    // Step 1️⃣: Precompute max possible element value
    int max_ele = *max_element(begin(nums), end(nums)) + k;

    // Step 2️⃣: Build frequency array
    vector<int> freq(max_ele + 1, 0);
    for (int &num : nums)
      freq[num]++;

    // Step 3️⃣: Prefix sum of frequencies
    for (int i = 1; i <= max_ele; i++)
      freq[i] += freq[i - 1];

    // Step 4️⃣: Iterate over possible targets
    int ans = 0;
    for (int target = 0; target <= max_ele; target++)
    {
      if (freq[target] == 0)
        continue;

      // Define range that can be converted into target
      int l = max(0, target - k);
      int r = min(max_ele, target + k);

      // Total elements within range [l, r]
      int cnt = freq[r] - ((l > 0) ? freq[l - 1] : 0);

      // Frequency of the exact target
      int target_cnt = freq[target] - ((target > 0) ? freq[target - 1] : 0);

      // Step 5️⃣: Compute max achievable frequency for this target
      int res = target_cnt + min(numOperations, cnt - target_cnt);
      ans = max(ans, res);
    }

    return ans;
  }
};

class Solution
{
public:
  string solve(string s)
  {
    int n = s.length();
    string ans = "";
    for (int i = 0; i < n - 1; i++)
    {
      ans += (((s[i] - '0') + (s[i + 1] - '0')) % 10);
    }
    return ans;
  }

  bool hasSameDigits(string s)
  {
    int n = s.length();
    string ans = s;
    while (1)
    {
      if (ans.length() == 2)
        break;
      ans = solve(ans);
    }
    return ((ans[0] == ans[1]) ? true : false);
  }
};

class Solution
{
public:
  bool is_balanced(int n)
  {
    vector<int> freq(10, 0);
    while (n != 0)
    {
      freq[n % 10]++;
      n /= 10;
    }
    for (int i = 0; i < 10; i++)
    {
      if (freq[i] > 0 && freq[i] != i)
        return false;
    }
    return true;
  }

  int nextBeautifulNumber(int n)
  {
    for (int i = n + 1; i <= 1224444; i++)
    {
      if (is_balanced(i))
        return i;
    }
    return -1;
  }
};

// ============================================================================
// 💡 Problem: Design a Bank System
// ----------------------------------------------------------------------------
// 🧩 Task:
//      Implement a Bank system that supports the following operations:
//        1️⃣ transfer(from, to, amount)  → transfer money between accounts
//        2️⃣ deposit(account, amount)    → deposit money into an account
//        3️⃣ withdraw(account, amount)   → withdraw money from an account
//
//      Return `true` if the operation succeeds, otherwise `false`.
//
// ----------------------------------------------------------------------------
// 🧠 Approach:
//      • Maintain account balances in a vector `bal`.
//      • Validate all account numbers before performing operations.
//      • Ensure sufficient balance before transfers and withdrawals.
//      • Indexing: accounts are 1-indexed externally, but 0-indexed internally.
//
// ----------------------------------------------------------------------------
// ⏱️ Time Complexity:  O(1) per operation
// 💾 Space Complexity: O(n) for storing balances
// ============================================================================

class Bank
{
private:
  // ------------------------------------------------------------------------
  // 🔹 Data Members
  // ------------------------------------------------------------------------
  vector<long long> bal; // Account balances
  int n;                 // Total number of accounts

  // ------------------------------------------------------------------------
  // 🔸 Helper Function: Validate account index
  // ------------------------------------------------------------------------
  bool valid(int acc)
  {
    return acc > 0 && acc <= n;
  }

public:
  // ------------------------------------------------------------------------
  // 🏦 Constructor: Initialize bank with balances
  // ------------------------------------------------------------------------
  Bank(vector<long long> &balance)
  {
    bal = balance;
    n = balance.size();
  }

  // ------------------------------------------------------------------------
  // 💸 Operation 1: Transfer amount from one account to another
  // ------------------------------------------------------------------------
  bool transfer(int from, int to, long long amt)
  {
    if (!valid(from) || !valid(to) || bal[from - 1] < amt)
      return false;

    bal[from - 1] -= amt;
    bal[to - 1] += amt;
    return true;
  }

  // ------------------------------------------------------------------------
  // 💰 Operation 2: Deposit amount into an account
  // ------------------------------------------------------------------------
  bool deposit(int acc, long long amt)
  {
    if (!valid(acc))
      return false;

    bal[acc - 1] += amt;
    return true;
  }

  // ------------------------------------------------------------------------
  // 💳 Operation 3: Withdraw amount from an account
  // ------------------------------------------------------------------------
  bool withdraw(int acc, long long amt)
  {
    if (!valid(acc) || bal[acc - 1] < amt)
      return false;

    bal[acc - 1] -= amt;
    return true;
  }
};

// ============================================================================
// ✅ Example Usage:
//
//   vector<long long> balance = {1000, 500, 200};
//   Bank bank(balance);
//
//   bank.deposit(2, 300);          // Account 2 → +300
//   bank.withdraw(1, 200);         // Account 1 → -200
//   bank.transfer(2, 3, 400);      // Transfer 400 from 2 → 3
// ============================================================================

class Solution
{
public:
  int numberOfBeams(vector<string> &bank)
  {
    int ans = 0, prev = 0;
    for (auto &row : bank)
    {
      int device = count(row.begin(), row.end(), '1');
      if (device > 0)
      {
        ans += device * prev;
        prev = device;
      }
    }
    return ans;
  }
};

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution
{
public:
  ListNode *modifiedList(vector<int> &nums, ListNode *head)
  {
    unordered_set<int> mpp(nums.begin(), nums.end());

    while (head && mpp.count(head->val))
      head = head->next;

    ListNode *curr = head;
    while (curr && curr->next)
    {
      while (curr->next && mpp.count(curr->next->val))
      {
        curr->next = curr->next->next;
      }
      curr = curr->next;
    }
    return head;
  }
};

class Solution
{
public:
  void dfs(int r, int c, string dir, vector<vector<int>> &vis, map<pair<int, int>, int> &mp)
  {
    int n = vis.size();
    int m = vis[0].size();
    if (r < 0 || c < 0 || r >= n || c >= m)
      return;
    if (mp.find({r, c}) != mp.end())
      return;
    else
      vis[r][c] = 1;

    if (dir == "r")
    {
      dfs(r, c + 1, "r", vis, mp);
    }
    if (dir == "l")
    {
      dfs(r, c - 1, "l", vis, mp);
    }
    if (dir == "u")
    {
      dfs(r - 1, c, "u", vis, mp);
    }
    if (dir == "d")
    {
      dfs(r + 1, c, "d", vis, mp);
    }
  }
  int countUnguarded(int m, int n, vector<vector<int>> &guards, vector<vector<int>> &walls)
  {
    vector<vector<int>> vis(m, vector<int>(n));
    queue<pair<int, int>> q;
    map<pair<int, int>, int> mp;
    for (auto it : guards)
    {
      q.push({it[0], it[1]});
      mp[{it[0], it[1]}]++;
      vis[it[0]][it[1]] = 1;
    }
    for (auto it : walls)
    {
      mp[{it[0], it[1]}]++;
      vis[it[0]][it[1]] = 1;
    }
    for (auto it : guards)
    {
      int r = it[0];
      int c = it[1];
      dfs(r, c + 1, "r", vis, mp);
      dfs(r, c - 1, "l", vis, mp);
      dfs(r + 1, c, "d", vis, mp);
      dfs(r - 1, c, "u", vis, mp);
    }
    int cnt = 0;
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (vis[i][j] == 0)
          cnt++;
      }
    }
    return cnt;
  }
};

class Solution
{
public:
  int minCost(string colors, vector<int> &neededTime)
  {
    int n = colors.length();
    int time = 0;
    priority_queue<int, vector<int>, greater<int>> pq;
    pq.push(neededTime[0]);
    for (int i = 1; i < n; i++)
    {
      if (colors[i] != colors[i - 1])
      {
        int size = pq.size();
        for (int i = 0; i < size - 1; i++)
        {
          int x = pq.top();
          time += x;
          pq.pop();
        }
        pq.pop();
      }
      pq.push(neededTime[i]);
    }
    int size = pq.size();
    for (int i = 0; i < size - 1; i++)
    {
      int x = pq.top();
      time += x;
      pq.pop();
    }
    pq.pop();
    return time;
  }
};

class Solution
{
public:
  vector<long long> findXSum(vector<int> &nums, int k, int x)
  {
    map<int, int> freq;
    multiset<pair<int, int>> top, rest;
    long long top_sum = 0;
    vector<long long> ans;

    auto balance = [&]()
    {
      while ((int)top.size() < x && !rest.empty())
      {
        auto it = prev(rest.end());
        top.insert(*it);
        top_sum += 1LL * it->first * it->second;
        rest.erase(it);
      }
      while ((int)top.size() > x)
      {
        auto it = top.begin();
        top_sum -= 1LL * it->first * it->second;
        rest.insert(*it);
        top.erase(it);
      }
      while (!rest.empty() && !top.empty() && *prev(rest.end()) > *top.begin())
      {
        auto it1 = prev(rest.end());
        auto it2 = top.begin();
        top_sum += 1LL * it1->first * it1->second - 1LL * it2->first * it2->second;
        rest.insert(*it2);
        top.insert(*it1);
        rest.erase(it1);
        top.erase(it2);
      }
    };

    auto add = [&](int num)
    {
      pair<int, int> old = {freq[num], num};
      if (top.find(old) != top.end())
      {
        top.erase(top.find(old));
        top_sum -= 1LL * old.first * old.second;
      }
      else if (rest.find(old) != rest.end())
      {
        rest.erase(rest.find(old));
      }
      freq[num]++;
      rest.insert({freq[num], num});
      balance();
    };

    auto remove = [&](int num)
    {
      pair<int, int> old = {freq[num], num};
      if (top.find(old) != top.end())
      {
        top.erase(top.find(old));
        top_sum -= 1LL * old.first * old.second;
      }
      else
      {
        rest.erase(rest.find(old));
      }
      freq[num]--;
      if (freq[num] > 0)
        rest.insert({freq[num], num});
      else
        freq.erase(num);
      balance();
    };

    for (int i = 0; i < k; ++i)
      add(nums[i]);
    ans.push_back(top_sum);

    for (int i = k; i < (int)nums.size(); ++i)
    {
      remove(nums[i - k]);
      add(nums[i]);
      ans.push_back(top_sum);
    }

    return ans;
  }
};

class Solution
{
public:
  vector<int> processQueries(int c, vector<vector<int>> &connections, vector<vector<int>> &queries)
  {
    vector<int> parent(c + 1);
    iota(parent.begin(), parent.end(), 0);

    function<int(int)> find = [&](int x)
    {
      while (parent[x] != x)
      {
        parent[x] = parent[parent[x]];
        x = parent[x];
      }
      return x;
    };

    for (auto &conn : connections)
    {
      int a = conn[0], b = conn[1];
      int ra = find(a), rb = find(b);
      if (ra != rb)
        parent[rb] = ra;
    }

    vector<int> next_node(c + 1, 0), comp_min(c + 1, 0), last(c + 1, 0);
    for (int i = 1; i <= c; ++i)
    {
      int r = find(i);
      if (comp_min[r] == 0)
      {
        comp_min[r] = i;
      }
      else
      {
        next_node[last[r]] = i;
      }
      last[r] = i;
    }

    vector<bool> offline(c + 1, false);
    vector<int> res;

    for (auto &q : queries)
    {
      int t = q[0], x = q[1];

      if (t == 1)
      {
        if (!offline[x])
        {
          res.push_back(x);
        }
        else
        {
          int r = find(x);
          res.push_back(comp_min[r] ? comp_min[r] : -1);
        }
      }
      else
      {
        if (!offline[x])
        {
          offline[x] = true;
          int r = find(x);
          if (comp_min[r] == x)
          {
            int y = next_node[x];
            while (y && offline[y])
              y = next_node[y];
            comp_min[r] = y ? y : 0;
          }
        }
      }
    }

    return res;
  }
};

class Solution
{
public:
  long long maxPower(vector<int> &stations, int r, int k)
  {
    long left = ranges::min(stations);
    long right = accumulate(stations.begin(), stations.end(), 0L) + k + 1;
    while (left < right)
    {
      const long mid = (left + right) / 2;
      if (check(stations, r, k, mid))
        left = mid + 1;
      else
        right = mid;
    }
    return left - 1;
  }

private:
  bool check(vector<int> stations, int r, int additionalStations,
             long minPower)
  {
    const int n = stations.size();
    long power = accumulate(stations.begin(), stations.begin() + r, 0L);

    for (int i = 0; i < n; ++i)
    {
      if (i + r < n)
        power += stations[i + r];
      if (power < minPower)
      {
        const long requiredPower = minPower - power;
        if (requiredPower > additionalStations)
          return false;
        stations[min(n - 1, i + r)] += requiredPower;
        additionalStations -= requiredPower;
        power += requiredPower;
      }
      if (i - r >= 0)
        power -= stations[i - r];
    }
    return true;
  }
};

class Solution
{
public:
  int minimumOneBitOperations(int n)
  {
    int res = 0;
    while (n)
    {
      res ^= n;
      n >>= 1;
    }
    return res;
  }
};

class Solution
{
public:
  int minOperations(vector<int> &nums)
  {
    vector<int> stack(nums.size() + 1, 0);
    int top = 0, ans = 0;
    for (int num : nums)
    {
      while (stack[top] > num)
      {
        top--;
        ans++;
      }
      if (stack[top] != num)
        stack[++top] = num;
    }
    return ans + top;
  }
};

class Solution
{
public:
  int minOperations(vector<int> &nums)
  {
    const int n = nums.size();
    int res = INT_MAX, cnt1 = 0;
    for (int i = 0; i < n; ++i)
      cnt1 += (nums[i] == 1);
    if (cnt1)
      return n - cnt1;
    for (int i = 0; i < n; ++i)
    {
      int g = nums[i];
      for (int j = i + 1; j < n; ++j)
      {
        g = __gcd(g, nums[j]);
        if (g == 1)
        {
          res = min(res, j - i + n - 1);
          break;
        }
      }
    }
    return res == INT_MAX ? -1 : res;
  }
};

class Solution
{
public:
  int numberOfSubstrings(string s)
  {
    vector<int> c1 = {0};
    int counts[2] = {0, 0};
    int ret = 0;
    for (const char c : s)
    {
      ++counts[c - '0'];
      if (c == '0')
        c1.push_back(counts[1]);
      ret += counts[1] - c1[counts[0]];
      for (int c0 = counts[0] - 1; c0 >= 0; --c0)
      {
        const int num0 = counts[0] - c0;
        if (num0 * num0 > counts[1])
          break;
        const int hi = counts[1] - c1[c0];
        const int lo = counts[1] - c1[c0 + 1];
        if (hi < num0 * num0)
          continue;
        else
          ret += max(0, hi - max(lo, num0 * num0) + 1);
      }
    }
    return ret;
  }
};

class Solution
{
public:
  int MOD = 1000000007;
  int numSub(string s)
  {
    long long len = 0, res = 0;
    int i = 0;
    while (i < s.size())
    {
      while (i < s.size() && s[i] == '1')
      {
        len++;
        i++;
      }
      res += (((len) * (len + 1) % MOD) / 2);
      len = 0;
      i++;
    }
    return res % MOD;
  }
};

class Solution
{
public:
  bool kLengthApart(vector<int> &nums, int k)
  {
    int n = nums.size();
    int last_one = -1;
    for (int i = 0; i < n; i++)
    {
      if (last_one != -1 && nums[i] == 1 && (i - last_one - 1) < k)
        return false;
      if (nums[i] == 1)
        last_one = i;
    }
    return true;
  }
};

class Solution
{
public:
  bool isOneBitCharacter(vector<int> &bits)
  {
    int n = bits.size();
    int i = 0;
    while (i < n - 1)
      i += bits[i] + 1;

    if (i == n - 1)
      return true;
    else
      return false;
  }
};

class Solution
{
public:
  int findFinalValue(vector<int> &nums, int k)
  {
    int bits = 0;
    for (auto &n : nums)
    {
      if (n % k != 0)
        continue;
      n /= k;
      if ((n & (n - 1)) == 0)
        bits |= n;
    }
    bits++;
    return k * (bits & -bits);
  }
};

class Solution
{
public:
  static int intersectionSizeTwo(vector<vector<int>> &I)
  {
    sort(I.begin(), I.end(), [](vector<int> &X, vector<int> &Y)
         {
            int x0=X[0], x1=X[1], y0=Y[0], y1=Y[1];
            return (x1==y1)?x0>y0:x1<y1; });

    int cnt = 2, n = I.size();
    int b = I[0][1], a = b - 1;
    for (int i = 1; i < n; i++)
    {
      int L = I[i][0], R = I[i][1];
      if (a >= L)
        continue;
      bool NO = L > b;
      cnt += 1 + NO;
      a = (NO) ? R - 1 : b;
      b = R;
    }
    return cnt;
  }
};

class Solution
{
public:
  int countPalindromicSubsequence(string s)
  {
    int n = s.size();
    map<char, vector<int>> mpp;
    map<string, int> final;
    for (int i = 0; i < n; i++)
    {
      mpp[s[i]].push_back(i);
    }
    for (int i = 0; i < 26; i++)
    {
      if (mpp[i + 'a'].size() <= 1)
      {
        continue;
      }
      int st = mpp[i + 'a'][0];
      int en = mpp[i + 'a'].back();
      for (int j = st + 1; j < en; j++)
      {
        string ans = "";
        ans.push_back((char)(i + 'a'));
        ans.push_back(s[j]);
        ans.push_back((char)(i + 'a'));
        final[ans]++;
      }
    }
    return final.size();
  }
};
