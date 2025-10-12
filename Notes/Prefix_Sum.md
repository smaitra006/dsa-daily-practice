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

#### Code

```cpp
class NumArray
{
public:
  vector<int> prefix_arr;
  NumArray(vector<int> &nums)
  {
    prefix_arr.push_back(0);
    int n = nums.size();
    int prefix_sum = 0;
    for (int i = 0; i < n; i++)
    {
      prefix_sum += nums[i];
      prefix_arr.push_back(prefix_sum);
    }
  }

  int sumRange(int left, int right)
  {
    return prefix_arr[right + 1] - prefix_arr[left];
  }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */
```

### [560. Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/)

The classic problem described in the introduction. Find the total count of subarrays that sum to $K$.

#### Code

```cpp
class Solution
{
public:
  int subarraySum(vector<int> &nums, int k)
  {
    int n = nums.size();
    int prefix_sum = 0;
    unordered_map<int,int> mp;
    mp[0] = 1;
    int count = 0;
    for (int i = 0; i < n; i++)
    {
      prefix_sum += nums[i];
      int complement = prefix_sum - k;
      if(mp.find(complement) != mp.end()) count += mp[complement];
      mp[prefix_sum]++;
    }
    return count;
  }
};
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

For minimum size use min in place of max and always update the index in map.

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

#### Code

```cpp
class Solution
{
public:
  int numberOfSubarrays(vector<int> &nums, int k)
  {
    int n = nums.size();
    unordered_map<int, int> mp;
    mp[0] = 1;
    int prefix_count = 0, count = 0;
    for (int i = 0; i < n; i++)
    {
      if (nums[i] % 2 == 1)
      {
        prefix_count++;
        if (mp.find(prefix_count - k) != mp.end())
          count += mp[prefix_count - k];
      }
      else
      {
        if (mp.find(prefix_count - k) != mp.end())
          count += mp[prefix_count - k];
      }
      mp[prefix_count]++;
    }
    return count;
  }
};
```

### [930. Binary Subarrays With Sum](https://leetcode.com/problems/binary-subarrays-with-sum/)

This problem is exactly the same as 560, but the input is guaranteed to be a binary array.

#### Code

```cpp
class Solution {
public:
  int numSubarraysWithSum(vector<int>& nums, int goal) {
    int n = nums.size();
    unordered_map<int, int> mp;
    mp[0] = 1;
    int prefix_count = 0, count = 0;
    for (int i = 0; i < n; i++) {
      if (nums[i] % 2 == 1) {
          prefix_count++;
          if (mp.find(prefix_count - goal) != mp.end())
              count += mp[prefix_count - goal];
      } else {
          if (mp.find(prefix_count - goal) != mp.end())
              count += mp[prefix_count - goal];
      }
      mp[prefix_count]++;
    }
    return count;
  }
};
```

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

### [2575. Find the Divisibility Array of a String](https://leetcode.com/problems/find-the-divisibility-array-of-a-string/)

This problem asks us to check the divisibility of each prefix of a number given as a string. A major challenge is that the number represented by the prefix can quickly exceed the capacity of even a `long long` integer, leading to overflow.

The solution lies in a property of modular arithmetic. When we compute the number for the $(i+1)$-th prefix, we are essentially doing `prefix_num = (previous_prefix_num * 10) + new_digit`. The key insight is:
$$(A \times 10 + B) \pmod m = ((A \pmod m) \times 10 + B) \pmod m$$
This means we don't need to store the full `previous_prefix_num`. We only need its remainder modulo $m$. By applying the modulo operation at each step, we keep the running prefix sum within a manageable range and prevent overflow.

#### Code

```cpp
vector<int> divisibilityArray(string word, int m) {
    int n = word.size();
    vector<int> ans(n, 0);
    long long psum = 0;

    for(int i = 0; i < n; ++i) {
        psum = psum * 10 + (word[i] - '0');
        psum %= m;
        if(psum == 0) {
            ans[i] = 1;
        }
    }
    return ans;
}
```

---

### [2845. Count of Interesting Subarrays](https://leetcode.com/problems/count-of-interesting-subarrays/)

This problem can be simplified into a more familiar pattern with a two-step approach. An array is "interesting" if the number of elements `nums[i]` where `nums[i] % modulo == k` satisfies a divisibility condition.

1.  **Transform the Input Array**: First, convert the input `nums` into a binary array. An element becomes `1` if `nums[i] % modulo == k`, and `0` otherwise. This simplifies the problem to dealing with counts of `1`s.

2.  **Apply Prefix Sum with Modulo**: After the transformation, the problem is to find the number of subarrays where the **count of 1s**, let's call it `count`, satisfies `count % modulo == k`. This is a variation of the classic "Subarray Sums Divisible by K" problem.
    Let $P_i$ be the prefix sum (count of 1s) up to index $i$. We are looking for subarrays from $j+1$ to $i$ such that:
    $$(P_i - P_j) \pmod{modulo} = k$$
    By rearranging, we get the condition for the prefix sum we need to find in our map:
    $$P_j \pmod{modulo} = (P_i - k) \pmod{modulo}$$
    We iterate through the binary array, maintain the prefix sum of 1s, and use a hash map to count the occurrences of each prefix sum's remainder.

#### Code

```cpp
long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) {
    int n = nums.size();
    // Step 1: Convert input array to binary
    for(int i = 0; i < n; ++i) {
        nums[i] = (nums[i] % modulo) == k ? 1 : 0;
    }

    // Step 2: Apply prefix sum with modulo logic
    unordered_map<long long, long long> countMap;
    countMap[0] = 1;
    long long pSum = 0;
    long long ans = 0;

    for(int i = 0; i < n; ++i) {
        pSum += nums[i];
        long long currentRem = pSum % modulo;
        long long targetRem = (currentRem - k + modulo) % modulo;
        if (countMap.count(targetRem)) {
            ans += countMap[targetRem];
        }
        countMap[currentRem]++;
    }
    return ans;
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

This class of problems can often be identified when the question involves subarrays with **even/odd occurrences** of elements or properties. The core idea is to leverage the property of the XOR operation: $A \oplus A = 0$. We can use a **bitmask** to track the parity (even or odd count) of different elements. Each bit in the mask corresponds to an element. Flipping a bit (using XOR) indicates its count has changed from even to odd, or vice-versa.

The prefix sum, in this case, becomes a **prefix XOR mask**. The XOR of a subarray from index $j+1$ to $i$ is calculated as $prefix\_xor_i \oplus prefix\_xor_j$.

### [1442. Count Triplets That Can Form Two Arrays of Equal XOR](https://leetcode.com/problems/count-triplets-that-can-form-two-arrays-of-equal-xor/)

The condition `arr[i] ^ ... ^ arr[j-1] == arr[j] ^ ... ^ arr[k]` is equivalent to the XOR sum of the subarray from `i` to `k` being zero. This means we are looking for subarrays `[i...k]` where the total XOR is 0. Using the prefix XOR logic, this translates to finding pairs of indices `i-1` and `k` such that $prefix\_xor_{k} = prefix\_xor_{i-1}$. For each such pair, any `j` between `i` and `k` forms a valid triplet, so we add `k - i` to our answer.

### [1915. Number of Wonderful Substrings](https://leetcode.com/problems/number-of-wonderful-substrings/)

A "wonderful" substring has at most one character with an odd frequency. The input consists of characters 'a' through 'j'.

At first, a sliding window approach seems tempting. However, a subarray that is invalid might become valid later. For example, in `"abb"`, the prefix `"ab"` is invalid (two odd counts), but `"abb"` is valid (one odd count for 'a', even for 'b').

**Approach**:
We use a 10-bit mask to track the parity of each character 'a' through 'j'. We iterate through the string, maintaining a running `prefix_mask`. For each index `i`:

1.  **Even Occurrences (Zero odd counts)**: A substring from $j+1$ to $i$ has all even character counts if its total XOR mask is 0. This means $prefix\_mask_i \oplus prefix\_mask_j = 0$, which implies $prefix\_mask_i = prefix\_mask_j$. We look up the current `prefix_mask` in our frequency map. If we've seen it `c` times before, it means we can form `c` new wonderful substrings ending at `i`.

2.  **At-most One Odd Occurrence**: A substring has exactly one character with an odd count if its total XOR mask has only one bit set to 1. This means $prefix\_mask_i \oplus prefix\_mask_j = 2^k$ for some character $k$. Rearranging, we need to find a previous mask $prefix\_mask_j = prefix\_mask_i \oplus 2^k$. So, for the current `prefix_mask`, we check our map for the count of every possible mask that differs by only one bit.

#### Code

```cpp
long long wonderfulSubstrings(string word) {
    unordered_map<int, int> countMap;
    countMap[0] = 1; // For substrings starting from the beginning
    int mask = 0;
    long long ans = 0;

    for (char c : word) {
        mask ^= (1 << (c - 'a'));

        // Case 1: All characters have even counts
        if (countMap.count(mask)) {
            ans += countMap[mask];
        }

        // Case 2: One character has an odd count
        for (int i = 0; i < 10; ++i) {
            int targetMask = mask ^ (1 << i);
            if (countMap.count(targetMask)) {
                ans += countMap[targetMask];
            }
        }

        countMap[mask]++;
    }
    return ans;
}
```

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

## The Difference Array (Imos Method)

This guide introduces the **Difference Array** technique, also known as the Imos Method. It's a clever and efficient way to handle multiple range update queries on an array or grid.

### Relationship to Prefix Sum

The Difference Array and Prefix Sum are **inverse operations**.

- The **prefix sum** of a difference array gives you back the original array.
- The **difference array** of a prefix sum array also gives you back the original array.

Understanding this relationship is key to mastering the technique\! 💡

---

## The Problem: Multiple Range Updates

Imagine you have an array, and you're given a list of queries. Each query asks you to **add a certain value to all elements within a specific range `[l, r]`**. After all queries are processed, you need to report the final state of the array.

**Naive Approach**: For each query, iterate from index `l` to `r` and add the value. If you have $Q$ queries and the array size is $N$, this approach takes $O(Q \cdot N)$ time, which is often too slow.

**Efficient Approach**: The Difference Array technique handles all updates first and then reconstructs the final array in a single pass. The total time complexity is a much better $O(N + Q)$.

---

## Section 1: 1D Difference Array

### Core Concept

A difference array, $D$, is constructed from an original array, $A$, such that:

- $D[0] = A[0]$
- $D[i] = A[i] - A[i-1]$ for $i > 0$

The magic lies in how we perform range updates. To add a value `val` to the range `[l, r]` in the original array `A`, we only need to make **two** modifications to the difference array `D`:

1.  **`D[l] += val`**
2.  **`D[r+1] -= val`** (if `r+1` is within bounds)

**Why does this work?**
Remember that `A` is the prefix sum of `D`.

- When we add `val` to `D[l]`, the prefix sum calculation will add `val` to `A[l]`, `A[l+1]`, `A[l+2]`, and so on, effectively raising the value of the entire suffix of the array starting from `l`.
- To stop this effect after index `r`, we subtract `val` at `D[r+1]`. This cancels out the initial addition for all elements from `r+1` onwards when the prefix sum is calculated. The net effect is that only the range `[l, r]` is updated.

### Template & Algorithm

1.  **Initialization**: Create a difference array `D` of size `n` (or `n+1`), initialized to zeros.
2.  **Process Queries**: For each query `(l, r, val)`:
    - `D[l] += val`
    - If `r + 1 < n`, then `D[r + 1] -= val`
3.  **Reconstruct**: After processing all queries, reconstruct the final array by taking the prefix sum of `D`.
    - `A[0] = D[0]`
    - `A[i] = A[i-1] + D[i]` for $i > 0$

#### Code

```cpp
// A is the initial array (can be all zeros)
// n is the size of the array
// queries is a vector of {l, r, val}
vector<int> processRangeUpdates(int n, vector<vector<int>>& queries) {
    vector<int> diff(n, 0);

    // Step 1: Apply all updates to the difference array
    for (const auto& query : queries) {
        int l = query[0];
        int r = query[1];
        int val = query[2];

        diff[l] += val;
        if (r + 1 < n) {
            diff[r + 1] -= val;
        }
    }

    // Step 2: Reconstruct the final array by taking the prefix sum
    vector<int> finalArray(n);
    finalArray[0] = diff[0];
    for (int i = 1; i < n; ++i) {
        finalArray[i] = finalArray[i - 1] + diff[i];
    }

    return finalArray;
}
```

---

## Section 2: 2D Difference Array

The same logic can be extended to a 2D grid for updating rectangular subregions. This is incredibly useful for problems involving grid manipulations.

### Core Concept & Range Updates

To add a value `val` to a rectangular subgrid with top-left corner `(r1, c1)` and bottom-right corner `(r2, c2)`, we need to modify **four** points in the 2D difference grid `diff`:

1.  **`diff[r1][c1] += val`**: Starts the effect at the top-left corner.
2.  **`diff[r1][c2 + 1] -= val`**: Cancels the effect for everything to the right of the rectangle.
3.  **`diff[r2 + 1][c1] -= val`**: Cancels the effect for everything below the rectangle.
4.  **`diff[r2 + 1][c2 + 1] += val`**: Corrects for the double cancellation that occurred in the region outside the bottom-right corner of the rectangle.

### Template & Algorithm

1.  **Initialization**: Create a 2D difference grid `diff` of size `(rows+1) x (cols+1)`, initialized to zeros.
2.  **Process Queries**: For each query `(r1, c1, r2, c2, val)`:
    - `diff[r1][c1] += val`
    - `diff[r1][c2 + 1] -= val`
    - `diff[r2 + 1][c1] -= val`
    - `diff[r2 + 1][c2 + 1] += val`
3.  **Reconstruct**: After all queries, reconstruct the final grid by performing a 2D prefix sum on `diff`.
    - `grid[i][j] = diff[i][j] + grid[i-1][j] + grid[i][j-1] - grid[i-1][j-1]`

#### Code

```cpp
// m = rows, n = cols
// queries is a vector of {r1, c1, r2, c2, val}
vector<vector<int>> process2DRangeUpdates(int m, int n, vector<vector<int>>& queries) {
    // Use slightly larger grid to avoid bounds checks
    vector<vector<int>> diff(m + 1, vector<int>(n + 1, 0));

    // Step 1: Apply all updates
    for (const auto& query : queries) {
        int r1 = query[0], c1 = query[1];
        int r2 = query[2], c2 = query[3];
        int val = query[4];

        diff[r1][c1] += val;
        diff[r1][c2 + 1] -= val;
        diff[r2 + 1][c1] -= val;
        diff[r2 + 1][c2 + 1] += val;
    }

    // Step 2: Reconstruct the final grid with a 2D prefix sum
    vector<vector<int>> finalGrid(m, vector<int>(n));
    finalGrid[0][0] = diff[0][0];

    // First row
    for (int j = 1; j < n; ++j) finalGrid[0][j] = finalGrid[0][j-1] + diff[0][j];
    // First col
    for (int i = 1; i < m; ++i) finalGrid[i][0] = finalGrid[i-1][0] + diff[i][0];

    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            finalGrid[i][j] = diff[i][j] + finalGrid[i - 1][j] + finalGrid[i][j - 1] - finalGrid[i - 1][j - 1];
        }
    }

    return finalGrid;
}
```

---

## Section 3: Applications & Problems

This technique is a lifesaver in competitive programming and interviews. Look for problems with "multiple updates on ranges" where the final state is needed only once.

### Problem Examples

- **[1109. Corporate Flight Bookings](https://leetcode.com/problems/corporate-flight-bookings/)**: A textbook 1D difference array problem. Each booking is a range update `[first, last]` with `seats` as the value.

- **[2132. Stamping the Grid](https://leetcode.com/problems/stamping-the-grid/)**: A more complex problem that uses a 2D difference array to keep track of which cells have been "covered" by a stamp. After finding all possible stamp locations, you mark them on the difference grid and reconstruct to see if all empty cells are covered.

- **[Range Update Query Problem (Generic)](https://www.google.com/search?q=https://www.geeksforgeeks.org/difference-array-range-update-query-in-o1/)**: The fundamental problem this technique is designed to solve.

### 2D-Difference Array: The "Imos Method"

This is a powerful but less intuitive technique for applying updates to rectangular subregions of a grid in $O(1)$ time per update. After all updates are marked, a single $O(N \times M)$ pass (a 2D prefix sum calculation) reveals the final state of the grid.

Let's say we have a $3 \times 3$ grid and want to increment the subgrid from $(0,0)$ to $(1,1)$ by 1. We create a difference grid (often one size larger) and mark four points:

- **`diff[r1][c1]++`**: Add `1` at the top-left corner. This starts the increment effect for all cells to the right and down.
- **`diff[r1][c2+1]--`**: Subtract `1` just outside the right boundary. This cancels the effect of the first mark for all columns past `c2`.
- **`diff[r2+1][c1]--`**: Subtract `1` just outside the bottom boundary. This cancels the effect for all rows past `r2`.
- **`diff[r2+1][c2+1]++`**: Add `1` at the corner just outside the bottom-right. This corrects for the double subtraction that occurred at this point from the previous two marks.

**Example:** To update the subgrid from $(0,0)$ to $(1,1)$ in a $3 \times 3$ matrix, we modify a difference array `diff`:
`diff[0][0] += 1`
`diff[0][2] -= 1` (since $c2=1$, $c2+1=2$)
`diff[2][0] -= 1` (since $r2=1$, $r2+1=2$)
`diff[2][2] += 1`

The difference array looks like this:

```
[ 1,  0, -1 ]
[ 0,  0,  0 ]
[-1,  0,  1 ]
```

Now, if we compute the 2D prefix sum of this difference array, we get the final updated grid:

```
[ 1, 1, 0 ]
[ 1, 1, 0 ]
[ 0, 0, 0 ]
```

As you can see, the subgrid from $(0,0)$ to $(1,1)$ has been incremented, just as we wanted\!

---

### [2132. Stamping the Grid](https://leetcode.com/problems/stamping-the-grid/)

This advanced problem is a perfect use case for the 2D Difference Array. The goal is to cover all empty cells (`0`) with stamps of size `h x w`.

**Approach:**

1.  **Find Stampable Regions**: First, compute a 2D prefix sum of the original grid. This allows us to quickly check if any `h x w` rectangle contains an obstacle (`1`). If the sum of a rectangle is `0`, it's a valid place for a stamp.
2.  **Mark Coverage with Difference Array**: For every `h x w` region that is stampable, we mark its coverage using a 2D difference array. We increment the region by 1, signifying it has been covered.
3.  **Compute Final Coverage**: After marking all possible stamp placements, we run a single 2D prefix sum calculation on our difference array. The resulting grid tells us how many stamps cover each cell.
4.  **Verify**: Finally, iterate through the original grid. If any cell is empty (`grid[i][j] == 0`) but its coverage count is zero, it means that cell was impossible to stamp. In this case, we return `false`. If all empty cells are covered, we return `true`.

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

        auto get_psum = [&](int r1, int c1, int r2, int c2) {
            return psum[r2 + 1][c2 + 1] - psum[r1][c2 + 1] - psum[r2 + 1][c1] + psum[r1][c1];
        };

        // 2. Create difference array to mark where stamps can go
        vector<vector<int>> diff(m + 2, vector<int>(n + 2, 0));
        for (int i = 0; i <= m - h; ++i) {
            for (int j = 0; j <= n - w; ++j) {
                if (get_psum(i, j, i + h - 1, j + w - 1) == 0) {
                    diff[i + 1][j + 1]++;
                    diff[i + 1][j + w + 1]--;
                    diff[i + h + 1][j + 1]--;
                    diff[i + h + 1][j + w + 1]++;
                }
            }
        }

        // 3. Compute the coverage map from the difference array
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
            }
        }

        // 4. Verify that every empty cell is covered
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0 && diff[i + 1][j + 1] == 0) {
                    return false;
                }
            }
        }

        return true;
    }
};
```

---

### [221. Maximal Square](https://leetcode.com/problems/maximal-square/)

This is a classic Dynamic Programming problem. The goal is to find the largest square of `1`s. The DP state `dp[i][j]` will store the side length of the largest square whose **bottom-right corner** is at `(i-1, j-1)`.

**Approach:**
If `matrix[i-1][j-1]` is a `0`, no square can end there, so `dp[i][j] = 0`.
If `matrix[i-1][j-1]` is a `1`, a square can be formed. The size of this square is limited by the squares ending at its neighbors: to the left (`dp[i][j-1]`), above (`dp[i-1][j]`), and diagonally top-left (`dp[i-1][j-1]`). The new side length will be `1 + min(left, up, diag)`.

#### Code

```cpp
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        int maxSide = 0;

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (matrix[i - 1][j - 1] == '1') {
                    dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
                    maxSide = max(maxSide, dp[i][j]);
                }
            }
        }
        return maxSide * maxSide;
    }
};
```

---

### [2201. Count Artifacts That Can Be Extracted](https://leetcode.com/problems/count-artifacts-that-can-be-extracted/)

This problem is a direct application of 2D range sum queries. An artifact can be extracted only if every single cell it occupies has been excavated.

**Approach:**

1.  **Create an Excavation Grid**: Convert the `dig` locations into a binary grid where `1` represents an excavated cell and `0` otherwise.
2.  **Compute Prefix Sum**: Build a 2D prefix sum array from this excavation grid.
3.  **Check Each Artifact**: For each artifact, calculate its total area (`(r2 - r1 + 1) * (c2 - c1 + 1)`). Then, use the prefix sum array to find the sum of the excavated cells within that artifact's bounding box.
4.  If the excavated sum equals the artifact's total area, it means the entire artifact is uncovered, so we increment our answer count.

#### Code

```cpp
class Solution {
public:
    int digArtifacts(int n, vector<vector<int>>& artifacts, vector<vector<int>>& dig) {
        vector<vector<int>> grid(n, vector<int>(n, 0));
        for (auto& d : dig) {
            grid[d[0]][d[1]] = 1;
        }

        vector<vector<int>> psum(n + 1, vector<int>(n + 1, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                psum[i + 1][j + 1] = grid[i][j] + psum[i][j + 1] + psum[i + 1][j] - psum[i][j];
            }
        }

        int ans = 0;
        for (auto& a : artifacts) {
            int r1 = a[0], c1 = a[1], r2 = a[2], c2 = a[3];
            int artifact_size = (r2 - r1 + 1) * (c2 - c1 + 1);
            int excavated_size = psum[r2 + 1][c2 + 1] - psum[r1][c2 + 1] - psum[r2 + 1][c1] + psum[r1][c1];

            if (artifact_size == excavated_size) {
                ans++;
            }
        }
        return ans;
    }
};
```

---

### [3148. Maximum Difference Score in a Grid](https://leetcode.com/problems/maximum-difference-score-in-a-grid/)

The score for a path is the sum of differences between consecutive cells. A path like $c_1 \to c_2 \to ... \to c_k$ has a score of $(c_2 - c_1) + (c_3 - c_2) + ... + (c_k - c_{k-1})$. This is a telescoping sum that simplifies to just $c_k - c_1$.

To maximize this score, for any destination cell `grid[i][j]`, we need to find the path that started at the minimum possible value reachable before `grid[i][j]`.

**Approach:**
We can use a DP-like approach to build a **prefix minimum** grid, `pmin`.
`pmin[i][j]` will store the minimum value in the rectangle from `(0,0)` to `(i-1, j-1)`.
The recurrence is: `pmin[i][j] = min(grid[i-1][j-1], pmin[i-1][j], pmin[i][j-1])`.

For each cell `grid[i-1][j-1]`, the best score ending here is its value minus the minimum value encountered on any valid path leading to it. This minimum starting value would be `min(pmin[i-1][j], pmin[i][j-1])`.

#### Code

```cpp
class Solution {
public:
    int maxScore(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> pmin = grid;
        int ans = INT_MIN;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int prev_min = INT_MAX;
                if (i > 0) prev_min = min(prev_min, pmin[i - 1][j]);
                if (j > 0) prev_min = min(prev_min, pmin[i][j - 1]);

                if (prev_min != INT_MAX) {
                    ans = max(ans, grid[i][j] - prev_min);
                }

                pmin[i][j] = min(pmin[i][j], prev_min);
            }
        }
        return ans;
    }
};
```

---

### [2017. Grid Game](https://leetcode.com/problems/grid-game/)

This is a minimax problem. The first robot wants to choose a path to **minimize** the score the second robot can get. The second robot will then choose a path to **maximize** its own score from what's left.

**Approach:**
The first robot's path is determined by the column where it "turns down" from the top row to the bottom row. Let's say it turns at column `i`. It collects all points in `grid[0][0...i]` and `grid[1][i...n-1]`.

What's left for the second robot?

1.  The points in the top row: `grid[0][i+1...n-1]`.
2.  The points in the bottom row: `grid[1][0...i-1]`.

The second robot will choose whichever of these two paths has a larger sum. The first robot, knowing this, will choose the turn-down column `i` that minimizes this potential maximum score for the second robot.

We can precompute the prefix sums for both rows to find the sums of these segments in $O(1)$ time.

#### Code

```cpp
class Solution {
public:
    long long gridGame(vector<vector<int>>& grid) {
        int n = grid[0].size();
        vector<long long> psum1(n + 1, 0), psum2(n + 1, 0);

        for (int i = 0; i < n; ++i) {
            psum1[i + 1] = psum1[i] + grid[0][i];
            psum2[i + 1] = psum2[i] + grid[1][i];
        }

        long long minMaxScore = LLONG_MAX;

        for (int i = 0; i < n; ++i) {
            // Points left for robot 2 if robot 1 turns at column 'i'
            long long top_path = psum1[n] - psum1[i + 1]; // Sum of grid[0][i+1...n-1]
            long long bottom_path = psum2[i]; // Sum of grid[1][0...i-1]

            long long second_robot_score = max(top_path, bottom_path);
            minMaxScore = min(minMaxScore, second_robot_score);
        }

        return minMaxScore;
    }
};
```
