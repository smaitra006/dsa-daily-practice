# Study Guide: Dynamic Programming (DP)

**Dynamic Programming** is a powerful problem-solving technique that breaks down a complex problem into simpler, overlapping subproblems. The core idea is to solve each subproblem only once and store its result, typically in an array or hash map (a process called **memoization** or **tabulation**). When the same subproblem is encountered again, we simply look up the stored result instead of re-computing it.

This "store and reuse" strategy avoids redundant work and can dramatically improve efficiency, often reducing exponential time complexities ($O(2^n)$) to polynomial time ($O(n^2)$, $O(n^3)$, etc.).

DP problems almost always have two key properties:

1.  **Overlapping Subproblems**: The problem can be broken down into subproblems that are reused multiple times.
2.  **Optimal Substructure**: The optimal solution to the main problem can be constructed from the optimal solutions of its subproblems.

---

## 1\. Linear DP

This is the most fundamental form of DP, where the state `dp[i]` typically depends on a constant number of previous states, such as `dp[i-1]`, `dp[i-2]`, or `dp[j]` for some `j < i`. The state is represented by a 1D array, and the transitions form a linear sequence.

---

### [Climbing Stairs](https://leetcode.com/problems/climbing-stairs/)

**Approach Summary**: The number of ways to reach step `n`, `dp[n]`, is the sum of the ways to reach step `n-1` (and taking one step) and the ways to reach step `n-2` (and taking two steps). This is the Fibonacci sequence. `dp[i] = dp[i-1] + dp[i-2]`.

```cpp
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) return n;
        int prev2 = 1, prev1 = 2;
        for (int i = 3; i <= n; ++i) {
            int current = prev1 + prev2;
            prev2 = prev1;
            prev1 = current;
        }
        return prev1;
    }
};
```

### [Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)

**Approach Summary**: This is a simplified DP (Kadane's algorithm). We maintain two variables: `minPrice` (the lowest price seen so far) and `maxProfit` (the max profit seen). As we iterate through prices, we update `minPrice` and then update `maxProfit` with `max(maxProfit, currentPrice - minPrice)`.

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minPrice = INT_MAX;
        int maxProfit = 0;
        for (int price : prices) {
            minPrice = min(minPrice, price);
            maxProfit = max(maxProfit, price - minPrice);
        }
        return maxProfit;
    }
};
```

### [Min Cost Climbing Stairs](https://leetcode.com/problems/min-cost-climbing-stairs/)

**Approach Summary**: `dp[i]` is the minimum cost to reach step `i`. To reach step `i`, you can come from `i-1` or `i-2`. So, `dp[i] = cost[i] + min(dp[i-1], dp[i-2])`. The final answer is `min(dp[n-1], dp[n-2])` as you can end on either of the last two steps.

```cpp
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        int prev1 = cost[1], prev2 = cost[0];
        for (int i = 2; i < n; ++i) {
            int current = cost[i] + min(prev1, prev2);
            prev2 = prev1;
            prev1 = current;
        }
        return min(prev1, prev2);
    }
};
```

### [Divisor Game](https://leetcode.com/problems/divisor-game/)

**Approach Summary**: This is a game theory DP. `dp[i]` is whether the current player wins starting with number `i`. `dp[i]` is `true` if there exists any `x` (a divisor of `i`) such that `dp[i-x]` is `false` (meaning the _other_ player loses). `dp[1]` is false (base case). It turns out `dp[i]` is simply `true` if `i` is even and `false` if `i` is odd.

```cpp
class Solution {
public:
    bool divisorGame(int n) {
        return n % 2 == 0;
    }
};
```

### [Decode Ways](https://leetcode.com/problems/decode-ways/)

**Approach Summary**: `dp[i]` is the number of ways to decode the prefix of the string of length `i` (`s[0...i-1]`).

- The 1-digit case: If `s[i-1]` is not '0', we can add `dp[i-1]` ways.
- The 2-digit case: If `s[i-2...i-1]` forms a valid number (10-26), we can add `dp[i-2]` ways.
  `dp[i] = (ways from 1-digit) + (ways from 2-digit)`.

<!-- end list -->

```cpp
class Solution {
public:
    int numDecodings(string s) {
        int n = s.length();
        if (n == 0 || s[0] == '0') return 0;
        int prev2 = 1, prev1 = 1; // dp[i-2] and dp[i-1]

        for (int i = 2; i <= n; ++i) {
            int current = 0;
            int one_digit = stoi(s.substr(i - 1, 1));
            int two_digits = stoi(s.substr(i - 2, 2));

            if (one_digit >= 1 && one_digit <= 9) {
                current += prev1;
            }
            if (two_digits >= 10 && two_digits <= 26) {
                current += prev2;
            }
            prev2 = prev1;
            prev1 = current;
        }
        return prev1;
    }
};
```

### [Unique Binary Search Trees](https://leetcode.com/problems/unique-binary-search-trees/)

**Approach Summary**: This is the Catalan Number. Let `dp[n]` be the number of unique BSTs with `n` nodes. To build a BST with `n` nodes, we can pick any node `i` (from 1 to `n`) as the root. This leaves `i-1` nodes for the left subtree and `n-i` nodes for the right subtree. `dp[n] = sum(dp[i-1] * dp[n-i])` for `i` from 1 to `n`.

```cpp
class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j <= i; ++j) {
                dp[i] += dp[j - 1] * dp[i - j];
            }
        }
        return dp[n];
    }
};
```

### [House Robber](https://leetcode.com/problems/house-robber/)

**Approach Summary**: `dp[i]` is the maximum money robbed up to house `i`. To find `dp[i]`, we have two choices:

1.  Rob house `i`: The profit is `nums[i] + dp[i-2]` (since we can't rob `i-1`).
2.  Don't rob house `i`: The profit is `dp[i-1]`.
    `dp[i] = max(nums[i] + dp[i-2], dp[i-1])`.

<!-- end list -->

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];

        int prev2 = 0, prev1 = 0;
        for (int i = 0; i < n; ++i) {
            int current = max(nums[i] + prev2, prev1);
            prev2 = prev1;
            prev1 = current;
        }
        return prev1;
    }
};
```

### [Perfect Squares](https://leetcode.com/problems/perfect-squares/)

**Approach Summary**: `dp[i]` is the least number of perfect square numbers that sum to `i`. To find `dp[i]`, we try subtracting every possible square `j*j` from `i`. The answer is `dp[i] = 1 + min(dp[i - j*j])` for all `j*j <= i`.

```cpp
class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j * j <= i; ++j) {
                dp[i] = min(dp[i], 1 + dp[i - j * j]);
            }
        }
        return dp[n];
    }
};
```

### [Best Time to Buy and Sell Stock with Cooldown](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/)

**Approach Summary**: We use three states: `sold` (just sold, now in cooldown), `held` (holding a stock), and `reset` (can buy).

- `sold[i] = held[i-1] + price[i]`
- `held[i] = max(held[i-1], reset[i-1] - price[i])` (either hold or buy from reset)
- `reset[i] = max(reset[i-1], sold[i-1])` (either stay reset or come from cooldown)
  The answer is `max(sold[n-1], reset[n-1])`.

<!-- end list -->

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int sold = 0, held = INT_MIN, reset = 0;
        for (int price : prices) {
            int prev_sold = sold;
            sold = held + price;
            held = max(held, reset - price);
            reset = max(reset, prev_sold);
        }
        return max(sold, reset);
    }
};
```

### [Coin Change](https://leetcode.com/problems/coin-change/)

**Approach Summary**: `dp[i]` is the minimum number of coins to make amount `i`. To find `dp[i]`, we try using each `coin` in the `coins` array. `dp[i] = 1 + min(dp[i - coin])` for all `coin <= i`. Initialize `dp` with infinity and `dp[0] = 0`.

```cpp
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        for (int i = 1; i <= amount; ++i) {
            for (int coin : coins) {
                if (i - coin >= 0) {
                    dp[i] = min(dp[i], 1 + dp[i - coin]);
                }
            }
        }
        return (dp[amount] > amount) ? -1 : dp[amount];
    }
};
```

### [Counting Bits](https://leetcode.com/problems/counting-bits/)

**Approach Summary**: `dp[i]` is the number of set bits in `i`. We can find a pattern. `dp[i] = dp[i / 2] + (i % 2)`. This is because shifting `i` right (`i / 2`) removes the last bit. The number of bits is the same as the shifted number, plus 1 if the last bit was 1.

```cpp
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> dp(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            dp[i] = dp[i >> 1] + (i & 1);
        }
        return dp;
    }
};
```

### [Integer Break](https://leetcode.com/problems/integer-break/)

**Approach Summary**: `dp[i]` is the maximum product you can get by breaking integer `i` into a sum of at least two positive integers. To find `dp[i]`, we can try making the first break at `j`. This splits `i` into `j` and `i-j`. We can either use `i-j` as is or break it further (`dp[i-j]`). `dp[i] = max(j * (i-j), j * dp[i-j])` for all `j` from 1 to `i-1`.

```cpp
class Solution {
public:
    int integerBreak(int n) {
        vector<int> dp(n + 1, 0);
        dp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                dp[i] = max(dp[i], max(j * (i - j), j * dp[i - j]));
            }
        }
        return dp[n];
    }
};
```

### [Count Numbers with Unique Digits](https://leetcode.com/problems/count-numbers-with-unique-digits/)

**Approach Summary**: Let `f(k)` be the count of numbers with unique digits of length `k`.

- `f(1) = 10` (0-9)
- `f(2) = 9 * 9` (first digit can't be 0, second can be any of 9 remaining)
- `f(3) = 9 * 9 * 8`
- `f(k) = 9 * 9 * 8 * ... * (11 - k)`
  The answer for `n` is `f(1) + f(2) + ... + f(n)`.

<!-- end list -->

```cpp
class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        if (n == 0) return 1;
        int total_count = 10;
        int unique_digits_count = 9;
        int available_digits = 9;
        for (int i = 2; i <= n && available_digits > 0; ++i) {
            unique_digits_count = unique_digits_count * available_digits;
            total_count += unique_digits_count;
            available_digits--;
        }
        return total_count;
    }
};
```

### [Wiggle Subsequence](https://leetcode.com/problems/wiggle-subsequence/)

**Approach Summary**: We can track the length of the wiggle subsequence ending in a positive difference (`up`) and a negative difference (`down`).

- If `nums[i] > nums[i-1]`, we can extend a "down" sequence: `up = down + 1`.
- If `nums[i] < nums[i-1]`, we can extend an "up" sequence: `down = up + 1`.
- If they are equal, do nothing.
  The answer is `max(up, down)`.

<!-- end list -->

```cpp
class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return n;
        int up = 1, down = 1;
        for (int i = 1; i < n; ++i) {
            if (nums[i] > nums[i - 1]) {
                up = down + 1;
            } else if (nums[i] < nums[i - 1]) {
                down = up + 1;
            }
        }
        return max(up, down);
    }
};
```

### [Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/)

**Approach Summary**: This is a 0/1 Knapsack problem. First, check if the total `sum` is even. If not, return `false`. The target sum is `sum / 2`. Let `dp[i]` be a boolean representing whether a sum of `i` can be achieved. `dp[i]` is true if `dp[i - num]` is true for any `num` in `nums`. We iterate through `dp` array backwards to avoid using the same element multiple times.

```cpp
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (int num : nums) sum += num;
        if (sum % 2 != 0) return false;
        int target = sum / 2;

        vector<bool> dp(target + 1, false);
        dp[0] = true;

        for (int num : nums) {
            for (int i = target; i >= num; --i) {
                dp[i] = dp[i] || dp[i - num];
            }
        }
        return dp[target];
    }
};
```

### [Maximum Length of Pair Chain](https://leetcode.com/problems/maximum-length-of-pair-chain/)

**Approach Summary**: This is equivalent to the Activity Selection problem. Sort the pairs based on their _end_ time (`pair[1]`). Then, iterate through the sorted pairs. Keep track of the `current_end` time. If the current pair's `start` time is greater than `current_end`, it doesn't overlap. We can add it to our chain, increment the length, and update `current_end`.

```cpp
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        int count = 0;
        int current_end = INT_MIN;
        for (const auto& pair : pairs) {
            if (pair[0] > current_end) {
                count++;
                current_end = pair[1];
            }
        }
        return count;
    }
};
```

### [Best Time to Buy and Sell Stock with Transaction Fee](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/)

**Approach Summary**: We track two states at the end of day `i`:

1.  `cash`: The max profit if we do _not_ hold a stock.
2.  `held`: The max profit if we _do_ hold a stock.
    Transitions:

<!-- end list -->

- `cash = max(cash, held + price - fee)` (sell the held stock)
- `held = max(held, cash - price)` (buy a stock)

<!-- end list -->

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int cash = 0, held = -prices[0];
        for (int i = 1; i < prices.size(); ++i) {
            int prev_cash = cash;
            cash = max(cash, held + prices[i] - fee);
            held = max(held, prev_cash - prices[i]);
        }
        return cash;
    }
};
```

### [Delete and Earn](https://leetcode.com/problems/delete-and-earn/)

**Approach Summary**: This is "House Robber" in disguise. First, transform the `nums` array into a "points" array where `points[i]` is the total sum of all numbers equal to `i`. The rule is: if you take `i` (earning `points[i]`), you can't take `i-1` or `i+1`. This is exactly the House Robber problem: `dp[i] = max(points[i] + dp[i-2], dp[i-1])`.

```cpp
class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        int max_val = 0;
        for (int num : nums) max_val = max(max_val, num);

        vector<int> points(max_val + 1, 0);
        for (int num : nums) points[num] += num;

        int prev2 = 0, prev1 = 0;
        for (int i = 1; i <= max_val; ++i) {
            int current = max(points[i] + prev2, prev1);
            prev2 = prev1;
            prev1 = current;
        }
        return prev1;
    }
};
```

### [Domino and Tromino Tiling](https://leetcode.com/problems/domino-and-tromino-tiling/)

**Approach Summary**: This requires a more complex state. Let `dp[i][0]` be the ways to tile a `2 x i` board fully. Let `dp[i][1]` be the ways to tile a `2 x i` board with one "broken" tile at the end (L-shape).

- `dp[i][0] = (dp[i-1][0] + dp[i-2][0] + 2 * dp[i-1][1]) % mod`
- `dp[i][1] = (dp[i-1][0] + dp[i-1][1]) % mod`
  The answer is `dp[n][0]`.

<!-- end list -->

```cpp
class Solution {
public:
    int numTilings(int n) {
        if (n == 1) return 1;
        if (n == 2) return 2;
        vector<long> full(n + 1, 0);
        vector<long> partial(n + 1, 0);
        int mod = 1e9 + 7;

        full[1] = 1; full[2] = 2;
        partial[1] = 0; partial[2] = 1;

        for (int i = 3; i <= n; ++i) {
            full[i] = (full[i - 1] + full[i - 2] + 2 * partial[i - 1]) % mod;
            partial[i] = (full[i - 1] + partial[i - 1]) % mod;
        }
        return full[n];
    }
};
```

### [Knight Dialer](https://leetcode.com/problems/knight-dialer/)

**Approach Summary**: `dp[i][j]` is the number of ways to end on digit `j` after `i` moves. The transition is `dp[i][j] = sum(dp[i-1][k])` for all `k` that can jump to `j`. We can optimize space to use two arrays, `prev` and `curr`.

```cpp
class Solution {
public:
    int knightDialer(int n) {
        if (n == 1) return 10;
        int mod = 1e9 + 7;
        vector<vector<int>> moves = {
            {4, 6}, {6, 8}, {7, 9}, {4, 8}, {0, 3, 9},
            {}, {0, 1, 7}, {2, 6}, {1, 3}, {2, 4}
        };
        vector<long> prev(10, 1);

        for (int i = 2; i <= n; ++i) {
            vector<long> curr(10, 0);
            for (int j = 0; j <= 9; ++j) {
                for (int move : moves[j]) {
                    curr[j] = (curr[j] + prev[move]) % mod;
                }
            }
            prev = curr;
        }

        long total = 0;
        for (long count : prev) {
            total = (total + count) % mod;
        }
        return total;
    }
};
```

### [Minimum Cost For Tickets](https://leetcode.com/problems/minimum-cost-for-tickets/)

**Approach Summary**: `dp[i]` is the min cost to cover travel up to day `i`.

- If we don't travel on day `i`, `dp[i] = dp[i-1]`.
- If we do travel on day `i`, we have three choices:
  1.  Buy 1-day pass: `costs[0] + dp[i-1]`
  2.  Buy 7-day pass: `costs[1] + dp[i-7]`
  3.  Buy 30-day pass: `costs[2] + dp[i-30]`
      `dp[i] = min(choice1, choice2, choice3)`. We only need to compute `dp` for days in `days`.

<!-- end list -->

```cpp
class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        unordered_set<int> travel_days(days.begin(), days.end());
        vector<int> dp(366, 0);

        for (int i = 1; i <= 365; ++i) {
            if (travel_days.find(i) == travel_days.end()) {
                dp[i] = dp[i - 1];
            } else {
                dp[i] = dp[i - 1] + costs[0];
                dp[i] = min(dp[i], dp[max(0, i - 7)] + costs[1]);
                dp[i] = min(dp[i], dp[max(0, i - 30)] + costs[2]);
            }
        }
        return dp[days.back()];
    }
};
```

### [Partition Array for Maximum Sum](https://leetcode.com/problems/partition-array-for-maximum-sum/)

**Approach Summary**: `dp[i]` is the max sum we can get from the subarray `arr[0...i-1]`. To find `dp[i]`, we look back `k` steps. We can form the last partition of size `j` (from 1 to `k`). This partition's sum is `max_in_partition * j`. The total sum is `dp[i-j] + (max_in_partition * j)`. We take the max over all possible `j`.

```cpp
class Solution {
public:
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        int n = arr.size();
        vector<int> dp(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            int max_in_partition = 0;
            for (int j = 1; j <= k && i - j >= 0; ++j) {
                max_in_partition = max(max_in_partition, arr[i - j]);
                dp[i] = max(dp[i], dp[i - j] + max_in_partition * j);
            }
        }
        return dp[n];
    }
};
```

### [Filling Bookcase Shelves](https://leetcode.com/problems/filling-bookcase-shelves/)

**Approach Summary**: `dp[i]` is the minimum height to place the first `i` books. To find `dp[i]`, we try placing the last `j` books (from `i` back to `1`) on the current shelf. These books are `books[i-j...i-1]`. We find the `max_height` in this group. The total width must be `<= shelfWidth`. If it fits, the cost is `dp[i-j] + max_height`. We take the minimum over all possible `j`.

```cpp
class Solution {
public:
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        int n = books.size();
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;

        for (int i = 1; i <= n; ++i) {
            int current_width = 0;
            int max_height = 0;
            for (int j = i; j >= 1; --j) {
                current_width += books[j - 1][0];
                if (current_width > shelfWidth) break;
                max_height = max(max_height, books[j - 1][1]);
                dp[i] = min(dp[i], dp[j - 1] + max_height);
            }
        }
        return dp[n];
    }
};
```

### [Longest Arithmetic Subsequence of Given Difference](https://leetcode.com/problems/longest-arithmetic-subsequence-of-given-difference/)

**Approach Summary**: Use a hash map `dp` where `dp[x]` stores the length of the longest arithmetic subsequence ending with the value `x`. As we iterate through `arr[i]`, the new subsequence length is `1 + dp[arr[i] - difference]`. We update `dp[arr[i]]` with this new length and track the overall max.

```cpp
class Solution {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
        unordered_map<int, int> dp;
        int max_len = 0;
        for (int x : arr) {
            dp[x] = 1 + dp[x - difference];
            max_len = max(max_len, dp[x]);
        }
        return max_len;
    }
};
```

### [Greatest Sum Divisible by Three](https://leetcode.com/problems/greatest-sum-divisible-by-three/)

**Approach Summary**: We only need to track three states: `dp[0]`, `dp[1]`, and `dp[2]`, which are the max sums seen so far that have remainders 0, 1, and 2 when divided by 3. As we iterate through `nums`, we create a `temp_dp` to store new states based on the current `num`.

```cpp
class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        vector<int> dp = {0, 0, 0};
        for (int num : nums) {
            vector<int> temp_dp = dp;
            for (int sum : temp_dp) {
                int new_sum = sum + num;
                dp[new_sum % 3] = max(dp[new_sum % 3], new_sum);
            }
        }
        return dp[0];
    }
};
```

### [Best Time to Buy and Sell Stock III](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/)

**Approach Summary**: We need to track 4 states for at most 2 transactions:

- `buy1`: Max profit after the first buy.
- `sell1`: Max profit after the first sell.
- `buy2`: Max profit after the second buy.
- `sell2`: Max profit after the second sell.
  Transitions:
  `sell2 = max(sell2, buy2 + price)`
  `buy2 = max(buy2, sell1 - price)`
  `sell1 = max(sell1, buy1 + price)`
  `buy1 = max(buy1, -price)`

<!-- end list -->

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int buy1 = INT_MIN, sell1 = 0;
        int buy2 = INT_MIN, sell2 = 0;

        for (int price : prices) {
            buy1 = max(buy1, -price);
            sell1 = max(sell1, buy1 + price);
            buy2 = max(buy2, sell1 - price);
            sell2 = max(sell2, buy2 + price);
        }
        return sell2;
    }
};
```

### [Student Attendance Record II](https://leetcode.com/problems/student-attendance-record-ii/)

**Approach Summary**: This is a complex state DP. `dp[i][j][k]` is the number of valid records of length `i` with `j` absences ('A') and `k` consecutive lates ('L').

- `dp[i][j][0]` (ends in 'P'): `sum(dp[i-1][j][k])` for `k=0,1,2`
- `dp[i][j][1]` (ends in 'L'): `dp[i-1][j][0]`
- `dp[i][j][2]` (ends in 'L'): `dp[i-1][j][1]`
- `dp[i][1][0]` (ends in 'A'): `sum(dp[i-1][0][k])` for `k=0,1,2`
  Sum all `dp[n][j][k]` for the final answer. Can be space-optimized.

<!-- end list -->

```cpp
class Solution {
public:
    int checkRecord(int n) {
        int mod = 1e9 + 7;
        vector<vector<long>> dp(2, vector<long>(3, 0));

        dp[0][0] = 1; // dp[i-1][A][L]

        for (int i = 1; i <= n; ++i) {
            vector<vector<long>> next_dp(2, vector<long>(3, 0));
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 3; ++k) {
                    if (dp[j][k] == 0) continue;

                    // Add 'P'
                    next_dp[j][0] = (next_dp[j][0] + dp[j][k]) % mod;
                    // Add 'A'
                    if (j == 0) {
                        next_dp[j + 1][0] = (next_dp[j + 1][0] + dp[j][k]) % mod;
                    }
                    // Add 'L'
                    if (k < 2) {
                        next_dp[j][k + 1] = (next_dp[j][k + 1] + dp[j][k]) % mod;
                    }
                }
            }
            dp = next_dp;
        }

        long total = 0;
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 3; ++k) {
                total = (total + dp[j][k]) % mod;
            }
        }
        return total;
    }
};
```

### [Decode Ways II](https://leetcode.com/problems/decode-ways-ii/)

**Approach Summary**: An extension of "Decode Ways" with '\*'. `dp[i]` is the ways to decode `s[0...i-1]`. We consider 1-digit and 2-digit decodings.

- 1-digit ('\*'): 9 ways.
- 1-digit ('1'-'9'): 1 way.
- 2-digit ('\*\*'): 96 ways (11-19, 21-26, \*1-\*9). No, 15 ways (11-19, 21-26). Wait, 9 (1-9) + 6 (10-26). `*` is 1-9. `**` is 11-19 (9) + 21-26 (6) = 15.
  Let's re-think.
  `dp[i] = ways(s[i-1]) * dp[i-1] + ways(s[i-2], s[i-1]) * dp[i-2]`.
- `ways(c)`: 9 if `c=='*'`, 1 if `c!='0'`, 0 if `c=='0'`.
- `ways(c1, c2)`: If `c1=='*'`, `c2=='*'`: 15 ways (11-19, 21-26). If `c1=='1'`, `c2=='*'`: 9 ways. If `c1=='2'`, `c2=='*'`: 6 ways. ...and so on.

<!-- end list -->

```cpp
class Solution {
public:
    int numDecodings(string s) {
        int n = s.length();
        long mod = 1e9 + 7;
        vector<long> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = (s[0] == '*') ? 9 : (s[0] == '0' ? 0 : 1);

        for (int i = 2; i <= n; ++i) {
            char c1 = s[i - 2], c2 = s[i - 1];

            // 1-digit
            if (c2 == '*') {
                dp[i] = (dp[i] + 9 * dp[i - 1]) % mod;
            } else if (c2 != '0') {
                dp[i] = (dp[i] + dp[i - 1]) % mod;
            }

            // 2-digits
            if (c1 == '*') {
                if (c2 == '*') {
                    dp[i] = (dp[i] + 15 * dp[i - 2]) % mod;
                } else if (c2 <= '6') {
                    dp[i] = (dp[i] + 2 * dp[i - 2]) % mod;
                } else {
                    dp[i] = (dp[i] + dp[i - 2]) % mod;
                }
            } else if (c1 == '1') {
                if (c2 == '*') {
                    dp[i] = (dp[i] + 9 * dp[i - 2]) % mod;
                } else {
                    dp[i] = (dp[i] + dp[i - 2]) % mod;
                }
            } else if (c1 == '2') {
                if (c2 == '*') {
                    dp[i] = (dp[i] + 6 * dp[i - 2]) % mod;
                } else if (c2 <= '6') {
                    dp[i] = (dp[i] + dp[i - 2]) % mod;
                }
            }
        }
        return dp[n];
    }
};
```

### [Triples with Bitwise AND Equal To Zero](https://leetcode.com/problems/triples-with-bitwise-and-equal-to-zero/)

**Approach Summary**: First, use a hash map to count the number of pairs `(i, j)` for every possible `AND` result `k = A[i] & A[j]`. This is $O(n^2)$. Then, iterate through this map. For each `k` with `count`, iterate through all `A[l]`. If `k & A[l] == 0`, add `count` to the total result. This is $O(n \cdot 2^{16})$.

```cpp
class Solution {
public:
    int countTriplets(vector<int>& nums) {
        unordered_map<int, int> pair_and;
        for (int a : nums) {
            for (int b : nums) {
                pair_and[a & b]++;
            }
        }

        int count = 0;
        for (int c : nums) {
            for (auto const& [val, freq] : pair_and) {
                if ((c & val) == 0) {
                    count += freq;
                }
            }
        }
        return count;
    }
};
```

### [Maximum Profit in Job Scheduling](https://leetcode.com/problems/maximum-profit-in-job-scheduling/)

**Approach Summary**: Sort jobs by their `endTime`. `dp[i]` is the max profit using a subset of the first `i` jobs. To compute `dp[i]`, we have two choices for job `i`:

1.  Don't take job `i`: Profit is `dp[i-1]`.
2.  Take job `i`: Profit is `job[i].profit + dp[j]`, where `j` is the index of the last job that ends before `job[i].startTime`. We can find `j` using binary search.
    `dp[i] = max(choice1, choice2)`.

<!-- end list -->

```cpp
class Solution {
public:
    struct Job {
        int start, end, profit;
    };

    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<Job> jobs(n);
        for (int i = 0; i < n; ++i) {
            jobs[i] = {startTime[i], endTime[i], profit[i]};
        }

        sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
            return a.end < b.end;
        });

        vector<int> dp(n, 0);
        dp[0] = jobs[0].profit;

        for (int i = 1; i < n; ++i) {
            int current_profit = jobs[i].profit;
            int last_job_idx = -1;

            int l = 0, r = i - 1;
            while (l <= r) {
                int mid = l + (r - l) / 2;
                if (jobs[mid].end <= jobs[i].start) {
                    last_job_idx = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }

            if (last_job_idx != -1) {
                current_profit += dp[last_job_idx];
            }

            dp[i] = max(dp[i - 1], current_profit);
        }
        return dp[n - 1];
    }
};
```

### [Minimum Number of Taps to Open to Water a Garden](https://leetcode.com/problems/minimum-number-of-taps-to-open-to-water-a-garden/)

**Approach Summary**: This is a "Jump Game II" problem. First, convert the `ranges` array into a `max_reach` array. `max_reach[i]` is the farthest right point you can water if you open a tap at position `i`. Then, use a greedy DP approach. `dp[i]` is the min taps to water `[0...i]`. To find `dp[i]`, look back at all taps `j` that can water `i` (`j + range[j] >= i`). `dp[i] = 1 + min(dp[k])` where `k` is from `j - range[j]` to `i`.

```cpp
class Solution {
public:
    int minTaps(int n, vector<int>& ranges) {
        vector<int> dp(n + 1, n + 2);
        dp[0] = 0;

        for (int i = 0; i <= n; ++i) {
            int start = max(0, i - ranges[i]);
            int end = min(n, i + ranges[i]);

            for (int j = start; j <= end; ++j) {
                dp[j] = min(dp[j], dp[start] + 1);
            }
        }

        return dp[n] > n + 1 ? -1 : dp[n];
    }
};
```

### [Count All Valid Pickup and Delivery Options](https://leetcode.com/problems/count-all-valid-pickup-and-delivery-options/)

**Approach Summary**: This is a combinatorial problem. Let `dp[n]` be the count for `n` pairs. Consider the `n`-th pair, `(Pn, Dn)`. In a valid sequence of `2n` slots, `Pn` must come before `Dn`.
There are `2n * (2n - 1) / 2` ways to place `Pn` and `Dn`.
The remaining `2n-2` slots can be filled in `dp[n-1]` ways.
So, `dp[n] = dp[n-1] * (2n * (2n - 1) / 2)`.
`dp[n] = dp[n-1] * n * (2n - 1)`.

```cpp
class Solution {
public:
    int countOrders(int n) {
        long mod = 1e9 + 7;
        long count = 1;
        for (int i = 2; i <= n; ++i) {
            count = (count * i * (2 * i - 1)) % mod;
        }
        return count;
    }
};
```

### [Stone Game III](https://leetcode.com/problems/stone-game-iii/)

**Approach Summary**: This is a minimax DP. `dp[i]` is the maximum "score difference" (Alice's score - Bob's score) that Alice can get starting from pile `i`. Alice wants to maximize this, Bob wants to minimize it.
Alice can take 1, 2, or 3 stones.

- Take 1: `score = stone[i] - dp[i+1]` (Bob plays from `i+1`)
- Take 2: `score = stone[i] + stone[i+1] - dp[i+2]`
- Take 3: `score = stone[i] + ... + stone[i+2] - dp[i+3]`
  `dp[i] = max(take 1, take 2, take 3)`. The answer is based on `dp[0]`.

<!-- end list -->

```cpp
class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();
        vector<int> dp(n + 1, INT_MIN);
        dp[n] = 0;

        for (int i = n - 1; i >= 0; --i) {
            int current_sum = 0;
            for (int j = i; j < min(n, i + 3); ++j) {
                current_sum += stoneValue[j];
                dp[i] = max(dp[i], current_sum - (j + 1 <= n ? dp[j + 1] : 0));
            }
        }

        if (dp[0] > 0) return "Alice";
        if (dp[0] < 0) return "Bob";
        return "Tie";
    }
};
```

### [Restore the Array](https://leetcode.com/problems/restore-the-array/)

**Approach Summary**: `dp[i]` is the number of ways to decode the suffix of `s` starting at index `i`. To find `dp[i]`, we try to form a valid number starting at `i` and ending at `j`. This number must be between 1 and `k`. If `s[i...j]` is a valid number, we add `dp[j+1]` to `dp[i]`. `dp[n] = 1` (base case: one way to decode an empty string).

```cpp
class Solution {
public:
    int numberOfArrays(string s, int k) {
        int n = s.length();
        int mod = 1e9 + 7;
        vector<int> dp(n + 1, 0);
        dp[n] = 1;

        for (int i = n - 1; i >= 0; --i) {
            if (s[i] == '0') continue;
            long current_num = 0;
            for (int j = i; j < n; ++j) {
                current_num = current_num * 10 + (s[j] - '0');
                if (current_num > k) break;
                dp[i] = (dp[i] + dp[j + 1]) % mod;
            }
        }
        return dp[0];
    }
};
```

### [Form Largest Integer with Digits That Add Up to Target](https://leetcode.com/problems/form-largest-integer-with-digits-that-add-up-to-target/)

**Approach Summary**: This is a variation of Unbounded Knapsack. `dp[i]` stores the largest number (as a string) that can be formed with a total cost of `i`. To find `dp[i]`, we try appending each digit `d` (from 9 down to 1) with `cost[d-1]`. If `dp[i - cost[d-1]]` is a valid number, we can form a new number by appending `d`. We compare this new number with the current `dp[i]` and keep the "larger" one (longer string, or lexicographically larger if same length).

```cpp
class Solution {
public:
    string largestNumber(vector<int>& cost, int target) {
        vector<string> dp(target + 1, "0");
        dp[0] = "";

        for (int t = 1; t <= target; ++t) {
            for (int d = 0; d < 9; ++d) {
                if (t >= cost[d] && dp[t - cost[d]] != "0") {
                    string new_num = to_string(d + 1) + dp[t - cost[d]];
                    if (new_num.length() > dp[t].length() ||
                       (new_num.length() == dp[t].length() && new_num > dp[t])) {
                        dp[t] = new_num;
                    }
                }
            }
        }
        return dp[target] == "0" ? "0" : dp[target];
    }
};
```

### [Stone Game IV](https://leetcode.com/problems/stone-game-iv/)

**Approach Summary**: This is a game theory DP. `dp[i]` is whether Alice wins starting with `i` stones. Alice wins if she can make a move (remove `j*j` stones) to a state `i - j*j` where the _other_ player (Bob) loses. `dp[i] = true` if there exists any `j*j <= i` such that `dp[i - j*j] == false`.

```cpp
class Solution {
public:
    bool winnerSquareGame(int n) {
        vector<bool> dp(n + 1, false);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j * j <= i; ++j) {
                if (!dp[i - j * j]) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[n];
    }
};
```

### [Coin Change 2](https://leetcode.com/problems/coin-change-2/)

**Approach Summary**: This is an Unbounded Knapsack problem. `dp[i]` is the number of combinations to make up amount `i`. For each `coin`, we iterate through the `dp` array. For each amount `j` from `coin` to `amount`, we can add the ways to make `j - coin`. `dp[j] = dp[j] + dp[j - coin]`.

```cpp
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        vector<int> dp(amount + 1, 0);
        dp[0] = 1;
        for (int coin : coins) {
            for (int j = coin; j <= amount; ++j) {
                dp[j] += dp[j - coin];
            }
        }
        return dp[amount];
    }
};
```

### [Paint House](https://leetcode.com/problems/paint-house/)

**Approach Summary**: `dp[i][j]` is the min cost to paint up to house `i`, with house `i` painted in color `j` (0, 1, or 2).
`dp[i][0] = costs[i][0] + min(dp[i-1][1], dp[i-1][2])`
`dp[i][1] = costs[i][1] + min(dp[i-1][0], dp[i-1][2])`
`dp[i][2] = costs[i][2] + min(dp[i-1][0], dp[i-1][1])`
This can be space-optimized to $O(1)$ by just storing the 3 `prev` values.

```cpp
class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        if (costs.empty()) return 0;
        int prev_r = costs[0][0];
        int prev_g = costs[0][1];
        int prev_b = costs[0][2];

        for (int i = 1; i < costs.size(); ++i) {
            int curr_r = costs[i][0] + min(prev_g, prev_b);
            int curr_g = costs[i][1] + min(prev_r, prev_b);
            int curr_b = costs[i][2] + min(prev_r, prev_g);
            prev_r = curr_r;
            prev_g = curr_g;
            prev_b = curr_b;
        }

        return min({prev_r, prev_g, prev_b});
    }
};
```

## 2\. Knapsack

The **Knapsack** pattern is a fundamental DP category where the problem involves making an optimal selection of items given a "capacity" constraint. The core decision for each item is whether to include it in your "knapsack" or not. The goal is to maximize or minimize a value (like profit, count, or cost) while adhering to the knapsack's capacity (like weight, size, or target sum).

This pattern has several variations:

- **0/1 Knapsack**: For each item, you can either take it once or not at all.
- **Unbounded Knapsack**: You can take each item an unlimited number of times.
- **Multidimensional Knapsack**: The knapsack has multiple capacity constraints (e.g., max weight _and_ max volume).

---

### [House Robber II](https://leetcode.com/problems/house-robber-ii/)

**Approach Summary**: This is a twist on the standard "House Robber" problem. Since the first and last houses are now adjacent, we can't rob both. We solve this by breaking the problem into two separate linear cases:

1.  Max profit from robbing houses `[0...n-2]` (excluding the last house).
2.  Max profit from robbing houses `[1...n-1]` (excluding the first house).
    The final answer is the maximum of these two results.

<!-- end list -->

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];
        return max(robLinear(nums, 0, n - 2), robLinear(nums, 1, n - 1));
    }

    int robLinear(vector<int>& nums, int start, int end) {
        int prev2 = 0, prev1 = 0;
        for (int i = start; i <= end; ++i) {
            int current = max(nums[i] + prev2, prev1);
            prev2 = prev1;
            prev1 = current;
        }
        return prev1;
    }
};
```

### [Ones and Zeroes](https://leetcode.com/problems/ones-and-zeroes/)

**Approach Summary**: This is a classic **Multidimensional 0/1 Knapsack** problem. The "items" are the strings, and the "knapsack" has two capacities: `m` (max zeros) and `n` (max ones). `dp[i][j]` stores the max number of strings we can form using `i` zeros and `j` ones. We iterate through each string, count its zeros and ones, and update the DP table.

```cpp
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (const string& s : strs) {
            int zeros = 0, ones = 0;
            for (char c : s) {
                if (c == '0') zeros++;
                else ones++;
            }

            for (int i = m; i >= zeros; --i) {
                for (int j = n; j >= ones; --j) {
                    dp[i][j] = max(dp[i][j], 1 + dp[i - zeros][j - ones]);
                }
            }
        }
        return dp[m][n];
    }
};
```

### [Target Sum](https://leetcode.com/problems/target-sum/)

**Approach Summary**: This is a **0/1 Knapsack** problem in disguise. We need to find the number of ways to assign `+` or `-` to get a `target`. This is equivalent to finding a subset `P` of `nums` such that `sum(P) - (totalSum - sum(P)) = target`. This simplifies to finding the number of ways to form a subset with sum `(totalSum + target) / 2`. `dp[i]` will store the number of ways to form sum `i`.

```cpp
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int totalSum = 0;
        for (int num : nums) totalSum += num;

        if (abs(target) > totalSum || (totalSum + target) % 2 != 0) {
            return 0;
        }

        int subsetSum = (totalSum + target) / 2;
        vector<int> dp(subsetSum + 1, 0);
        dp[0] = 1;

        for (int num : nums) {
            for (int j = subsetSum; j >= num; --j) {
                dp[j] += dp[j - num];
            }
        }
        return dp[subsetSum];
    }
};
```

### [Shopping Offers](https://leetcode.com/problems/shopping-offers/)

**Approach Summary**: This is an **Unbounded Knapsack** problem best solved with memoization (top-down DP). The "state" is the `needs` vector. `dp(needs)` returns the min cost to fulfill those needs. The base case is buying all items individually. For the recursive step, try applying each special offer. If an offer can be applied (we need all its items), calculate the `next_needs` and find the minimum cost: `min(ans, offer_price + dp(next_needs))`.

```cpp
class Solution {
public:
    map<vector<int>, int> memo;

    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        return solve(price, special, needs);
    }

    int solve(vector<int>& price, vector<vector<int>>& special, vector<int> needs) {
        if (memo.count(needs)) return memo[needs];

        // Base case: buy all individually
        int cost = 0;
        for (int i = 0; i < needs.size(); ++i) {
            cost += needs[i] * price[i];
        }

        // Recursive step: try each offer
        for (const auto& offer : special) {
            vector<int> next_needs = needs;
            bool can_apply = true;
            for (int i = 0; i < needs.size(); ++i) {
                if (offer[i] > needs[i]) {
                    can_apply = false;
                    break;
                }
                next_needs[i] -= offer[i];
            }

            if (can_apply) {
                cost = min(cost, offer.back() + solve(price, special, next_needs));
            }
        }

        return memo[needs] = cost;
    }
};
```

### [2 Keys Keyboard](https://leetcode.com/problems/2-keys-keyboard/)

**Approach Summary**: `dp[i]` stores the minimum steps to get `i` 'A's. To get `i` 'A's, we must have copied `j` 'A's (where `j` is a divisor of `i`) and pasted `(i/j) - 1` times. This takes `dp[j]` steps to get `j`, 1 step to Copy, and `(i/j) - 1` steps to Paste. The total is `dp[j] + i/j`. We find the minimum over all divisors `j`.

```cpp
class Solution {
public:
    int minSteps(int n) {
        vector<int> dp(n + 1, 0);
        for (int i = 2; i <= n; ++i) {
            dp[i] = i; // Max steps (copy 1, paste i-1)
            for (int j = i / 2; j >= 1; --j) {
                if (i % j == 0) {
                    dp[i] = min(dp[i], dp[j] + (i / j));
                    break; // Largest divisor gives min steps
                }
            }
        }
        return dp[n];
    }
};
```

### [Minimum Swaps To Make Sequences Increasing](https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/)

**Approach Summary**: This is a choice-based DP. `dp[i][0]` is the min swaps up to `i` _without_ swapping at `i`. `dp[i][1]` is the min swaps _with_ swapping at `i`. The transitions depend on whether `(nums1[i], nums2[i])` are greater than the previous pair `(nums1[i-1], nums2[i-1])` both normally and when one pair is swapped.

```cpp
class Solution {
public:
    int minSwap(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int no_swap = 0;
        int swap = 1;

        for (int i = 1; i < n; ++i) {
            int next_no_swap = INT_MAX;
            int next_swap = INT_MAX;

            // Case 1: No swap at i
            if (nums1[i] > nums1[i-1] && nums2[i] > nums2[i-1]) {
                next_no_swap = min(next_no_swap, no_swap);
                next_swap = min(next_swap, swap + 1);
            }
            // Case 2: Swap at i
            if (nums1[i] > nums2[i-1] && nums2[i] > nums1[i-1]) {
                next_no_swap = min(next_no_swap, swap);
                next_swap = min(next_swap, no_swap + 1);
            }
            no_swap = next_no_swap;
            swap = next_swap;
        }
        return min(no_swap, swap);
    }
};
```

### [Best Team With No Conflicts](https://leetcode.com/problems/best-team-with-no-conflicts/)

**Approach Summary**: This is a **Longest Increasing Subsequence (LIS)** problem. First, create pairs of `(age, score)` and sort them. The primary sort key is `age`, and the secondary is `score`. Now, the problem is to find the LIS on the _scores_. `dp[i]` stores the max score of a valid team ending with player `i`. `dp[i] = pairs[i].score + max(dp[j])` for all `j < i` where `pairs[j].score <= pairs[i].score`.

```cpp
class Solution {
public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        int n = scores.size();
        vector<pair<int, int>> players(n);
        for (int i = 0; i < n; ++i) {
            players[i] = {ages[i], scores[i]};
        }
        sort(players.begin(), players.end());

        vector<int> dp(n, 0);
        int max_score = 0;
        for (int i = 0; i < n; ++i) {
            dp[i] = players[i].second;
            for (int j = 0; j < i; ++j) {
                if (players[j].second <= players[i].second) {
                    dp[i] = max(dp[i], players[i].second + dp[j]);
                }
            }
            max_score = max(max_score, dp[i]);
        }
        return max_score;
    }
};
```

### [Profitable Schemes](https://leetcode.com/problems/profitable-schemes/)

**Approach Summary**: This is a **Multidimensional 0/1 Knapsack** problem. `dp[i][j]` = number of schemes that generate at least `i` profit using at most `j` people. We iterate through each crime `(crime_profit, crime_group)`. For each crime, we update the DP table backwards: `dp[p][g] = (dp[p][g] + dp[p - crime_profit][g - crime_group])`. Profit `p` is capped at `minProfit`.

```cpp
class Solution {
public:
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        int mod = 1e9 + 7;
        vector<vector<int>> dp(minProfit + 1, vector<int>(n + 1, 0));
        dp[0][0] = 1;

        for (int k = 0; k < group.size(); ++k) {
            int g = group[k];
            int p = profit[k];
            for (int i = minProfit; i >= 0; --i) {
                for (int j = n; j >= g; --j) {
                    int new_profit = min(minProfit, i + p);
                    dp[new_profit][j] = (dp[new_profit][j] + dp[i][j - g]) % mod;
                }
            }
        }

        int total_schemes = 0;
        for (int j = 0; j <= n; ++j) {
            total_schemes = (total_schemes + dp[minProfit][j]) % mod;
        }
        return total_schemes;
    }
};
```

### [Tallest Billboard](https://leetcode.com/problems/tallest-billboard/)

**Approach Summary**: This is a challenging knapsack variant. `dp[d]` stores the maximum height of the _taller_ of two supports, where `d` is the difference between them. `d` is offset by 5000 to handle negative differences. Iterate through each `rod`. For a `dp[d]` with height `h`, we can:

1.  Add `rod` to the taller support: `new_diff = d + rod`, `new_height = h + rod`.
2.  Add `rod` to the shorter support: `new_diff = d - rod`, `new_height = h`.
    We update a `curr` DP table based on the `prev` DP table. The answer is `dp[5000]`.

<!-- end list -->

```cpp
class Solution {
public:
    int tallestBillboard(vector<int>& rods) {
        vector<int> dp(10001, -1);
        dp[5000] = 0;

        for (int rod : rods) {
            vector<int> curr = dp;
            for (int d = 0; d <= 10000; ++d) {
                if (dp[d] == -1) continue;

                // Add to taller
                if (d + rod <= 10000) {
                    curr[d + rod] = max(curr[d + rod], dp[d] + rod);
                }
                // Add to shorter
                if (d - rod >= 0) {
                    curr[d - rod] = max(curr[d - rod], dp[d]);
                }
            }
            dp = curr;
        }
        return dp[5000];
    }
};
```

### [Pizza With 3n Slices](https://leetcode.com/problems/pizza-with-3n-slices/)

**Approach Summary**: This is "House Robber II" but for `n` non-adjacent items instead of `n/2`. The array is circular, so we run the DP twice: once excluding the last slice (`[0...k-2]`) and once excluding the first slice (`[1...k-1]`). The linear problem is: "find max sum of `n` non-adjacent elements". `dp[i][j]` = max sum using `j` slices from the first `i` pizzas. `dp[i][j] = max(dp[i-1][j], dp[i-2][j-1] + slices[i])`.

```cpp
class Solution {
public:
    int maxSizeSlices(vector<int>& slices) {
        int n = slices.size();
        return max(solve(slices, 0, n - 2), solve(slices, 1, n - 1));
    }

    int solve(const vector<int>& slices, int start, int end) {
        int k = (end - start + 1);
        int num_slices = (k + 1) / 3;
        vector<vector<int>> dp(k + 1, vector<int>(num_slices + 1, 0));

        for (int i = 1; i <= k; ++i) {
            for (int j = 1; j <= num_slices; ++j) {
                int take = slices[start + i - 1];
                if (i > 1) {
                    take += dp[i - 2][j - 1];
                }
                int no_take = dp[i - 1][j];
                dp[i][j] = max(take, no_take);
            }
        }
        return dp[k][num_slices];
    }
};
```

### [Reducing Dishes](https://leetcode.com/problems/reducing-dishes/)

**Approach Summary**: This is a 0/1 Knapsack problem. The key insight is to sort the `satisfaction` array. This ensures we always consider doing more satisfying dishes later (with higher time multipliers). `dp[i][t]` is the max "like-time coefficient" from `dishes[i...]` with time starting at `t`.
`dp[i][t] = max(dp[i+1][t], satisfaction[i]*t + dp[i+1][t+1])`. (Skip dish `i` vs. Take dish `i`).

```cpp
class Solution {
public:
    vector<vector<int>> memo;
    int n;

    int solve(vector<int>& satisfaction, int index, int time) {
        if (index == n) {
            return 0;
        }
        if (memo[index][time] != -1) {
            return memo[index][time];
        }

        // Take dish
        int take = satisfaction[index] * time + solve(satisfaction, index + 1, time + 1);
        // Skip dish
        int skip = solve(satisfaction, index + 1, time);

        return memo[index][time] = max(take, skip);
    }

    int maxSatisfaction(vector<int>& satisfaction) {
        sort(satisfaction.begin(), satisfaction.end());
        n = satisfaction.size();
        memo.assign(n + 1, vector<int>(n + 2, -1));
        return solve(satisfaction, 0, 1);
    }
};
```

### [Painting the Walls](https://leetcode.com/problems/painting-the-walls/description/)

**Approach Summary**: This is a **0/1 Knapsack** problem. The "items" are the painters. The "knapsack capacity" is `n` walls. The "cost" to minimize is `cost[i]`. The "value" (walls painted) by a paid painter `i` is `1 + time[i]` (the wall they paint + the `time[i]` walls the free painter paints). `dp[i]` = min cost to paint at least `i` walls. `dp[i] = min(dp[i], dp[max(0, i - (1 + time[j]))] + cost[j])`.

```cpp
class Solution {
public:
    int paintWalls(vector<int>& cost, vector<int>& time) {
        int n = cost.size();
        vector<int> dp(n + 1, 1e9 + 7);
        dp[0] = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = n; j > 0; --j) {
                int walls_painted = 1 + time[i];
                dp[j] = min(dp[j], dp[max(0, j - walls_painted)] + cost[i]);
            }
        }
        return dp[n];
    }
};
```
