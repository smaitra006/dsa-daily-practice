---

# Study Guide: Prefix Sum

This guide covers the **Prefix Sum** technique, a powerful tool for solving a variety of array and subarray-based problems in an efficient manner.

### Related Study Guides:

- Line Sweep Algorithms
- Solving k-th kind of problems
- BFS and its variations
- Binary Lifting Technique
- Binary Indexed Tree

---

## Introduction

Problems that require you to find the **count** or **length** (minimum/maximum) of a **subarray** based on a mathematical condition (like sum, divisibility, or vowel count) are often prime candidates for the prefix sum approach.

While you might initially think of using a **Sliding Window**, that technique often fails if the array contains negative elements or if the condition for shrinking the window isn't straightforward. For these kinds of problems, the Prefix Sum approach, often paired with a hash map, provides an elegant and efficient solution.

### Basic Idea

Let's understand the core concept with a classic problem: **560. Subarray Sum Equals K**. The goal is to find the number of contiguous subarrays whose elements sum up to a target value $K$.

We maintain a running sum, let's call it $psum_i$, which is the sum of elements from the start of the array up to index $i$. If, at some point, we have a prefix sum $psum_i$, we want to know if there was a previous prefix sum, $psum_j$ (where $j < i$), such that the sum of the elements between them is $K$.

This can be expressed as:
$$psum_i - psum_j = K$$

Rearranging this equation, we get the value we need to look for:
$$psum_j = psum_i - K$$

So, the strategy is to iterate through the array, calculate the current prefix sum ($psum_i$), and then check if we have previously seen a prefix sum equal to $psum_i - K$. A hash map is perfect for storing the frequencies of the prefix sums we've encountered.

### Template

1.  Initialize `prefix_sum = 0`.
2.  Initialize a hash map (e.g., `unordered_map` in C++) to store frequencies or indices of prefix sums.
3.  Initialize a variable `answer = 0`.
4.  **Crucially, initialize the map for a sum of 0.**
    - For **count**-based problems: `map[0] = 1`. This handles cases where a subarray starting from index 0 sums to $K$.
    - For **length**-based problems: `map[0] = -1`. This correctly calculates the length of a subarray starting from index 0 (length = $i - (-1) = i + 1$).
5.  Iterate through the array from $i = 0$ to $n-1$:
    - Update `prefix_sum` by adding the current element `nums[i]`.
    - Check if `prefix_sum - K` exists in the map. If it does, update your `answer` accordingly.
    - Update the map with the current `prefix_sum` and its frequency or index.

---

## Section 1: Standard Prefix Sum Problems

These problems follow the basic template closely, focusing on subarray sums or simple transformations.

### [303. Range Sum Query - Immutable](https://leetcode.com/problems/range-sum-query-immutable/)

A straightforward application where you precompute the prefix sum array to answer range sum queries in $O(1)$ time.

### [560. Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/)

The classic problem described in the introduction. Find the total count of subarrays that sum to $K$.

#### Code

```cpp
int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> countMap;
    int pSum = 0;
    int ans = 0;
    int n = nums.size();
    countMap[0] = 1;

    for(int i = 0; i < n; ++i) {
        pSum += nums[i];
        if(countMap.count(pSum - k) > 0) {
            ans += countMap[pSum - k];
        }
        countMap[pSum]++;
    }
    return ans;
}
```

### [2559. Count Vowel Strings in Ranges](https://leetcode.com/problems/count-vowel-strings-in-ranges/)

First, transform the input array into a binary array where `arr[i] = 1` if `words[i]` starts and ends with a vowel, and `0` otherwise. Then, build a prefix sum array on this binary array to answer the range queries in $O(1)$.

#### Code

```cpp
class Solution {
public:
    vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries) {
        int n = words.size();
        vector<int> arr(n, 0);
        for(int i = 0; i < n; ++i) {
            int l = words[i].size() - 1;
            char first = words[i][0];
            char last = words[i][l];
            if ((first == 'a' || first == 'e' || first == 'i' || first == 'o' || first == 'u') &&
                (last == 'a' || last == 'e' || last == 'i' || last == 'o' || last == 'u')) {
                arr[i] = 1;
            }
        }

        vector<int> psum(1 + n, 0);
        for (int i = 0; i < n; ++i) {
            psum[i + 1] = arr[i] + psum[i];
        }

        vector<int> ans(queries.size());
        for (int i = 0; i < queries.size(); ++i) {
            ans[i] = psum[queries[i][1] + 1] - psum[queries[i][0]];
        }
        return ans;
    }
};
```

### [325. Maximum Size Subarray Sum Equals k](https://leetcode.com/problems/maximum-size-subarray-sum-equals-k/)

This is similar to problem 560, but asks for the **longest** subarray length instead of the count. We initialize `lenMap[0] = -1` and only store the _first_ occurrence of a prefix sum in the map to maximize the length.

#### Code

```cpp
int maxSubArrayLen(vector<int>& nums, int k) {
    unordered_map<int, int> lenMap;
    int pSum = 0;
    int ans = 0;
    int n = nums.size();
    lenMap[0] = -1;

    for (int i = 0; i < n; ++i) {
        pSum += nums[i];
        if (lenMap.count(pSum - k) > 0) {
            ans = max(ans, i - lenMap[pSum - k]);
        }
        if (lenMap.find(pSum) == lenMap.end()) { // Update only if it doesn't exist
            lenMap[pSum] = i;
        }
    }
    return ans;
}
```

### [1248. Count Number of Nice Subarrays](https://leetcode.com/problems/count-number-of-nice-subarrays/)

Transform the input into a binary array (1 for odd, 0 for even). The problem then becomes "find the number of subarrays with a sum of $K$," which is identical to problem 560.

### [930. Binary Subarrays With Sum](https://leetcode.com/problems/binary-subarrays-with-sum/)

This problem is exactly the same as 560, but the input is guaranteed to be a binary array.

### [2364. Count Number of Bad Pairs](https://leetcode.com/problems/count-number-of-bad-pairs/)

A pair `(i, j)` is "good" if `j - nums[j] == i - nums[i]`. We can count the number of good pairs and subtract from the total number of pairs ($n \times (n-1) / 2$). To count good pairs, iterate through the array and use a map to store frequencies of the value $i - nums[i]$. For each element, the number of good pairs it forms with previous elements is the current count of $i - nums[i]$ in the map.

#### Code

```cpp
long long countBadPairs(vector<int>& nums) {
    long long n = nums.size();
    long long totalPairs = (n * (n - 1)) / 2;
    unordered_map<int, long long> m;
    long long goodPairs = 0;

    for(int i = 0; i < n; ++i) {
        int diff = i - nums[i];
        goodPairs += m[diff];
        m[diff]++;
    }
    return totalPairs - goodPairs;
}
```

### [1658. Minimum Operations to Reduce X to Zero](https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/)

This is a clever twist. Removing elements from the ends to get a sum of $X$ is equivalent to finding the **longest** subarray in the middle whose sum is `total_sum - X`. Once rephrased, this is exactly problem 325.

#### Code

```cpp
int minOperations(vector<int>& nums, int x) {
    long long totalSum = 0;
    for (int num : nums) {
        totalSum += num;
    }
    long long target = totalSum - x;
    int n = nums.size();

    if (target == 0) return n;
    if (target < 0) return -1;

    unordered_map<long long, int> lenMap;
    lenMap[0] = -1;
    long long pSum = 0;
    int maxLen = -1;

    for (int i = 0; i < n; ++i) {
        pSum += nums[i];
        if (lenMap.count(pSum - target)) {
            maxLen = max(maxLen, i - lenMap[pSum - target]);
        }
        if (lenMap.find(pSum) == lenMap.end()) {
            lenMap[pSum] = i;
        }
    }

    return maxLen == -1 ? -1 : n - maxLen;
}
```

---

## Section 2: Prefix Sum & Division/Modulo

These problems leverage modular arithmetic. A key insight is that a subarray sum from index $j+1$ to $i$ is divisible by $K$ if the prefix sums up to those points have the same remainder when divided by $K$.

> The sum of `nums[j+1...i]` is divisible by $K$ if:
> $$(psum_i - psum_j) \pmod K = 0$$
> which implies:
> $$psum_i \pmod K = psum_j \pmod K$$

**Handling Negative Remainders in C++:**
The `%` operator in C++ can produce negative results (e.g., `-5 % 3` is `-2`). To ensure a positive remainder as per the Euclidean division algorithm ($0 \le r < |b|$), use the formula `( (value % K) + K) % K`.

### [974. Subarray Sums Divisible by K](https://leetcode.com/problems/subarray-sums-divisible-by-k/)

Apply the modulo logic directly. Iterate through the array, calculate the prefix sum's remainder modulo $K$, and check the map for how many times you've seen this remainder before.

#### Code

```cpp
int subarraysDivByK(vector<int>& A, int K) {
    unordered_map<int, int> countMap;
    countMap[0] = 1;
    int pSum = 0;
    int ans = 0;

    for (int num : A) {
        pSum += num;
        int remainder = ((pSum % K) + K) % K;
        if (countMap.count(remainder)) {
            ans += countMap[remainder];
        }
        countMap[remainder]++;
    }
    return ans;
}
```

### [1590. Make Sum Divisible by P](https://leetcode.com/problems/make-sum-divisible-by-p/)

Let `totalSum` be the sum of all elements. We need to find the shortest subarray to remove whose sum, let's call it `sub_sum`, makes the remaining sum divisible by $P$. This means `(totalSum - sub_sum) % P = 0`. Let `k = totalSum % P`. The condition becomes `(k - sub_sum % P) % P = 0`, which means we are looking for the shortest subarray whose sum modulo $P$ is $k$. This is a "find shortest length" problem.

#### Code

```cpp
int minSubarray(vector<int>& nums, int p) {
    long long totalSum = 0;
    for(int num : nums) totalSum += num;

    int k = totalSum % p;
    if (k == 0) return 0;

    unordered_map<int, int> lenMap;
    lenMap[0] = -1;
    int pSum = 0;
    int n = nums.size();
    int ans = n;

    for (int i = 0; i < n; ++i) {
        pSum = (pSum + nums[i]) % p;
        int target = (pSum - k + p) % p;
        if (lenMap.count(target)) {
            ans = min(ans, i - lenMap[target]);
        }
        lenMap[pSum] = i;
    }
    return ans == n ? -1 : ans;
}
```

### [523. Continuous Subarray Sum](https://leetcode.com/problems/continuous-subarray-sum/)

Similar to 974, but we only need to find if at least one such subarray of length $\ge 2$ exists. Store the _index_ of the first time a remainder is seen. If we see the same remainder again at index $i$, we check if the subarray length ($i$ - `map[remainder]`) is at least 2.

#### Code

```cpp
bool checkSubarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> m; // key: remainder, value: index
    m[0] = -1;
    int sum = 0;
    int n = nums.size();

    for (int i = 0; i < n; ++i) {
        sum += nums[i];
        int remainder = sum % k;
        if (m.count(remainder)) {
            if (i - m[remainder] > 1) {
                return true;
            }
        } else {
            m[remainder] = i;
        }
    }
    return false;
}
```

---

## Section 3: Prefix Sum & XOR

XOR problems often involve finding subarrays where elements have an even or odd number of occurrences. The key property of XOR is that $a \oplus a = 0$. We can use a bitmask to track the parity (even/odd) of occurrences.

If the prefix XOR from $0$ to $i$ is $pxor_i$, and from $0$ to $j$ is $pxor_j$, then the XOR sum of the subarray from $j+1$ to $i$ is $pxor_i \oplus pxor_j$. If this subarray has all even occurrences, its XOR sum will be 0, which means $pxor_i = pxor_j$.

### [1371. Find the Longest Substring Containing Vowels in Even Counts](https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/)

Use a 5-bit mask to represent the parity of vowels ('a', 'e', 'i', 'o', 'u'). As we iterate through the string, we update the mask. We are looking for the longest substring where the parity of all vowels is even. This means the XOR mask of that substring must be 0. Thus, we look for two indices $i$ and $j$ where the prefix XOR mask is the same.

#### Code

```cpp
int findTheLongestSubstring(string s) {
    unordered_map<int, int> lenMap;
    lenMap[0] = -1;
    int mask = 0;
    int ans = 0;
    string vowels = "aeiou";

    for (int i = 0; i < s.size(); ++i) {
        for (int j = 0; j < vowels.size(); ++j) {
            if (s[i] == vowels[j]) {
                mask ^= (1 << j);
            }
        }
        if (lenMap.count(mask)) {
            ans = max(ans, i - lenMap[mask]);
        } else {
            lenMap[mask] = i;
        }
    }
    return ans;
}
```

### [1542. Find Longest Awesome Substring](https://leetcode.com/problems/find-longest-awesome-substring/)

An "awesome" substring can be rearranged into a palindrome. This means at most one digit can have an odd count. We use a 10-bit mask for digits 0-9. At each index $i$ with prefix mask `mask`:

1.  **All even:** Check for a previous occurrence of `mask`.
2.  **One odd:** Check for previous occurrences of `mask ^ (1 << j)` for each digit $j$ from 0 to 9. This finds a subarray where exactly one digit's parity differs, making it odd.

#### Code

```cpp
int longestAwesome(string s) {
    unordered_map<int, int> lenMap;
    lenMap[0] = -1;
    int mask = 0;
    int ans = 0;

    for (int i = 0; i < s.size(); ++i) {
        mask ^= (1 << (s[i] - '0'));

        // Case 1: All digits have even counts
        if (lenMap.count(mask)) {
            ans = max(ans, i - lenMap[mask]);
        }

        // Case 2: One digit has an odd count
        for (int j = 0; j < 10; ++j) {
            int targetMask = mask ^ (1 << j);
            if (lenMap.count(targetMask)) {
                ans = max(ans, i - lenMap[targetMask]);
            }
        }

        if (!lenMap.count(mask)) {
            lenMap[mask] = i;
        }
    }
    return ans;
}
```

---

## Section 4: 2D Prefix Sum Problems

The prefix sum concept can be extended to 2D matrices for answering submatrix sum queries efficiently. We create a prefix sum matrix `psum` (usually of size `(rows+1) x (cols+1)` for easier calculations).

**Compute Formula:**
The value at `psum[i+1][j+1]` represents the sum of the rectangle from `(0,0)` to `(i,j)`.
$$psum[i+1][j+1] = grid[i][j] + psum[i][j+1] + psum[i+1][j] - psum[i][j]$$
This works because we add the regions above and to the left, but this double-counts the top-left diagonal region, so we subtract it.

**Get (Query) Formula:**
To find the sum of a submatrix with top-left corner $(r1, c1)$ and bottom-right corner $(r2, c2)$:
$$sum = psum[r2+1][c2+1] - psum[r1][c2+1] - psum[r2+1][c1] + psum[r1][c1]$$
This formula includes the large rectangle up to $(r2, c2)$, subtracts the rectangles above and to the left of the desired region, and adds back the top-left part that was subtracted twice.

### [304. Range Sum Query 2D - Immutable](https://leetcode.com/problems/range-sum-query-2d-immutable/)

A direct implementation of the 2D prefix sum formulas described above.

#### Code

```cpp
class NumMatrix {
private:
    vector<vector<int>> psum;

public:
    NumMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        psum.resize(m + 1, vector<int>(n + 1, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                psum[i + 1][j + 1] = matrix[i][j] + psum[i][j + 1] + psum[i + 1][j] - psum[i][j];
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return psum[row2 + 1][col2 + 1] - psum[row1][col2 + 1] - psum[row2 + 1][col1] + psum[row1][col1];
    }
};
```

### [1314. Matrix Block Sum](https://leetcode.com/problems/matrix-block-sum/)

First, compute the 2D prefix sum of the entire matrix. Then, for each cell `(i, j)`, determine the coordinates of its block (from `r1, c1` to `r2, c2` bounded by the matrix dimensions) and use the `get` formula to find the sum of that block.

#### Code

```cpp
class Solution {
public:
    vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k) {
        int m = mat.size();
        int n = mat[0].size();
        vector<vector<int>> psum(m + 1, vector<int>(n + 1, 0));

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                psum[i + 1][j + 1] = mat[i][j] + psum[i][j + 1] + psum[i + 1][j] - psum[i][j];
            }
        }

        vector<vector<int>> ans(m, vector<int>(n));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int r1 = max(0, i - k);
                int c1 = max(0, j - k);
                int r2 = min(m - 1, i + k);
                int c2 = min(n - 1, j + k);

                ans[i][j] = psum[r2 + 1][c2 + 1] - psum[r1][c2 + 1] - psum[r2 + 1][c1] + psum[r1][c1];
            }
        }
        return ans;
    }
};
```

### [2132. Stamping the Grid](https://leetcode.com/problems/stamping-the-grid/)

This advanced problem uses a **2D Difference Array** (or "imos method").

1.  First, create a 2D prefix sum of the input grid to quickly check if a `h x w` region contains any obstacles (i.e., its sum is greater than 0).
2.  Create a difference array `diff` (size `(m+1) x (n+1)`). Iterate through all possible top-left corners `(i, j)` for a stamp. If the `h x w` region starting at `(i, j)` is empty, it _can_ be stamped. Mark this in the difference array: `diff[i][j]++`, `diff[i+h][j]--`, `diff[i][j+w]--`, `diff[i+h][j+w]++`.
3.  Convert the difference array back into a 2D prefix sum array. Now `psum[i][j]` will be non-zero if the cell `(i, j)` has been covered by at least one stamp.
4.  Finally, iterate through the original grid. If any cell is empty (`grid[i][j] == 0`) but was not covered (`psum[i][j] == 0`), return `false`. Otherwise, return `true`.

#### Code

```cpp
class Solution {
public:
    bool possibleToStamp(vector<vector<int>>& grid, int h, int w) {
        int m = grid.size();
        int n = grid[0].size();

        // 1. Prefix sum to find empty rectangles quickly
        vector<vector<int>> psum(m + 1, vector<int>(n + 1, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                psum[i + 1][j + 1] = grid[i][j] + psum[i][j + 1] + psum[i + 1][j] - psum[i][j];
            }
        }

        // 2. Create difference array for stamps
        vector<vector<int>> diff(m + 1, vector<int>(n + 1, 0));
        for (int i = 0; i <= m - h; ++i) {
            for (int j = 0; j <= n - w; ++j) {
                int r2 = i + h - 1;
                int c2 = j + w - 1;
                int subgridSum = psum[r2 + 1][c2 + 1] - psum[i][c2 + 1] - psum[r2 + 1][j] + psum[i][j];
                if (subgridSum == 0) { // Can place a stamp here
                    diff[i][j]++;
                    if (i + h < m) diff[i + h][j]--;
                    if (j + w < n) diff[i][j + w]--;
                    if (i + h < m && j + w < n) diff[i + h][j + w]++;
                }
            }
        }

        // 3. Convert difference array to a coverage map
        vector<vector<int>> coverage(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int up = (i > 0) ? coverage[i - 1][j] : 0;
                int left = (j > 0) ? coverage[i][j - 1] : 0;
                int diag = (i > 0 && j > 0) ? coverage[i - 1][j - 1] : 0;
                coverage[i][j] = diff[i][j] + up + left - diag;
            }
        }

        // 4. Check if all empty cells are covered
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0 && coverage[i][j] == 0) {
                    return false;
                }
            }
        }

        return true;
    }
};
```
