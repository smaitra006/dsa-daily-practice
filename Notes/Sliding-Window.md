# Study Guide: The Sliding Window Technique

The **Sliding Window** is a foundational algorithmic technique for efficiently processing contiguous data in arrays or strings. It's a clever optimization that transforms a brute-force approach with nested loops (often $O(n^2)$) into a far more efficient single-pass approach (usually $O(n)$).

This is achieved by maintaining a "window"—a contiguous subarray or substring—defined by two pointers. This window slides over the data, expanding by moving the end pointer and shrinking by moving the start pointer, all while tracking data that satisfies a specific condition. 🧑‍💻

### When to Use the Sliding Window Technique?

This pattern is a perfect fit for problems that involve:

- **Input Data:** An array, list, or string.
- **Problem Type:** Finding a contiguous subarray or substring that is the **longest**, **shortest**, or satisfies a **target value/condition**.
- **Keywords:** "subarray", "substring", "contiguous", "longest", "shortest", "maximum/minimum".

### Core Components

- **Two Pointers:** Two pointers, often named `left` and `right` (or `start`/`end`, `i`/`j`), define the boundaries of the current window.
- **Hashing:** A hash map or frequency array is commonly used to track the elements and their counts within the window, enabling $O(1)$ lookups and updates.

---

## Section 1: Fixed-Size Window

In these problems, the size of the window, `k`, is predetermined and **remains constant** throughout the execution. The window moves across the data one step at a time.

### Template

The core logic is to first build an initial window of size `k`. Then, in a single loop, you slide the window by adding the next element and removing the first element of the previous window, updating your result at each step.

```cpp
// Generic Template for Fixed-Size Window
void fixed_window_template(vector<int>& arr, int k) {
    // 1. Process the first window of size k separately.
    // ... calculate initial state (e.g., sum, hashmap) ...
    // ... update answer ...

    // 2. Slide the window from k to the end.
    for (int i = k; i < arr.size(); ++i) {
        // a. Add the new element entering the window (arr[i]).
        // b. Remove the old element leaving the window (arr[i - k]).
        // c. Update the answer based on the new window state.
    }
}
```

### Problems on Fixed-Size Window

#### [Substrings of Size Three with Distinct Characters](https://leetcode.com/problems/substrings-of-size-three-with-distinct-characters/)

**Approach Summary**: The window size is fixed at 3. Slide a window of this size across the string. For each window, check if all three characters are distinct. A simple way is to check `s[i] != s[i+1] && s[i+1] != s[i+2] && s[i] != s[i+2]`.

```cpp
class Solution {
public:
    int countGoodSubstrings(string s) {
        if (s.length() < 3) return 0;
        int count = 0;
        // Slide a window of size 3
        for (int i = 0; i <= s.length() - 3; ++i) {
            if (s[i] != s[i+1] && s[i+1] != s[i+2] && s[i] != s[i+2]) {
                count++;
            }
        }
        return count;
    }
};
```

#### [Substring with Concatenation of All Words](https://leetcode.com/problems/substring-with-concatenation-of-all-words/)

**Approach Summary**: This is a complex fixed-window problem. The window size is fixed at `num_words * word_len`. We must also account for different starting offsets. We iterate `word_len` times for starting points `0, 1, ..., word_len-1`. Inside, we use a sliding window. We maintain a frequency map of words seen in the current window and compare it to a reference map of the words in the `words` list.

```cpp
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        if (s.empty() || words.empty()) return {};
        int wordLen = words[0].length();
        int numWords = words.size();
        int windowSize = wordLen * numWords;
        unordered_map<string, int> wordFreq;
        for (const string& word : words) {
            wordFreq[word]++;
        }

        vector<int> result;
        if (s.length() < windowSize) return result;

        for (int i = 0; i < wordLen; ++i) {
            unordered_map<string, int> seenWords;
            int left = i, count = 0;
            for (int j = i; j <= s.length() - wordLen; j += wordLen) {
                string word = s.substr(j, wordLen);
                if (wordFreq.count(word)) {
                    seenWords[word]++;
                    count++;
                    while (seenWords[word] > wordFreq[word]) {
                        string leftWord = s.substr(left, wordLen);
                        seenWords[leftWord]--;
                        count--;
                        left += wordLen;
                    }
                    if (count == numWords) {
                        result.push_back(left);
                    }
                } else {
                    seenWords.clear();
                    count = 0;
                    left = j + wordLen;
                }
            }
        }
        return result;
    }
};
```

#### [Maximum Number of Vowels in a Substring of Given Length](https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/)

**Approach Summary**: The window size is fixed at `k`. First, count the vowels in the initial window of size `k`. Then, slide the window one position at a time. In each step, check if the character leaving is a vowel (decrement count) and if the character entering is a vowel (increment count). Keep track of the maximum vowel count seen.

```cpp
class Solution {
public:
    int maxVowels(string s, int k) {
        auto isVowel = [](char c) {
            return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
        };

        int currentVowels = 0;
        // 1. Build the first window
        for (int i = 0; i < k; ++i) {
            if (isVowel(s[i])) currentVowels++;
        }
        int maxVowels = currentVowels;

        // 2. Slide the window
        for (int i = k; i < s.length(); ++i) {
            if (isVowel(s[i])) currentVowels++; // Add entering character
            if (isVowel(s[i - k])) currentVowels--; // Remove leaving character
            maxVowels = max(maxVowels, currentVowels);
        }
        return maxVowels;
    }
};
```

#### [Maximum Number of Occurrences of a Substring](https://leetcode.com/problems/maximum-number-of-occurrences-of-a-substring/)

**Approach Summary**: We need to find the max frequency of any substring that satisfies three conditions. We iterate through all possible window sizes from `minSize` to `maxSize`. For each size, we slide a window, and if the substring in the window has `unique_chars <= maxLetters`, we add it to a frequency map. Finally, we find the max frequency in the map.

```cpp
class Solution {
public:
    int maxFreq(string s, int maxLetters, int minSize, int maxSize) {
        unordered_map<string, int> substrFreq;
        int n = s.length();
        int maxCount = 0;

        for (int i = 0; i <= n - minSize; ++i) {
            string sub = s.substr(i, minSize);
            unordered_set<char> uniqueChars;
            for (char c : sub) {
                uniqueChars.insert(c);
            }
            if (uniqueChars.size() <= maxLetters) {
                substrFreq[sub]++;
                maxCount = max(maxCount, substrFreq[sub]);
            }
        }
        return maxCount;
    }
};
```

#### [Maximum Average Subarray I](https://leetcode.com/problems/maximum-average-subarray-i/)

**Approach Summary**: The window size is fixed at `k`. Calculate the sum of the first `k` elements. Then, slide the window. In each step, add the new element and subtract the leaving element to maintain the window sum efficiently. Track the maximum sum, and return `max_sum / k`.

```cpp
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        double currentSum = 0;
        // 1. Build the first window
        for (int i = 0; i < k; ++i) {
            currentSum += nums[i];
        }
        double maxSum = currentSum;

        // 2. Slide the window
        for (int i = k; i < nums.size(); ++i) {
            currentSum += nums[i] - nums[i - k];
            maxSum = max(maxSum, currentSum);
        }
        return maxSum / k;
    }
};
```

#### [Maximum Points You Can Obtain from Cards](https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/)

**Approach Summary**: This is a clever twist. Taking `k` cards from the ends is the same as leaving a contiguous subarray of size `n-k` in the middle. The problem then becomes: find the subarray of size `n-k` with the **minimum sum**. The answer is `total_sum - min_sum_of_middle_subarray`. This can be solved with a fixed-size sliding window.

```cpp
class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n = cardPoints.size();
        int windowSize = n - k;
        long long totalSum = 0;
        for (int point : cardPoints) {
            totalSum += point;
        }
        if (n == k) return totalSum;

        long long minSubarraySum = -1;
        long long currentSum = 0;

        // Find the minimum sum subarray of size n-k
        for (int i = 0; i < n; ++i) {
            currentSum += cardPoints[i];
            if (i >= windowSize) {
                currentSum -= cardPoints[i - windowSize];
            }
            if (i >= windowSize - 1) {
                if (minSubarraySum == -1 || currentSum < minSubarraySum) {
                    minSubarraySum = currentSum;
                }
            }
        }
        return totalSum - minSubarraySum;
    }
};
```

#### [Find All Anagrams in a String](https://leetcode.com/problems/find-all-anagrams-in-a-string/)

**Approach Summary**: The window size is fixed at `p.length()`. Use two frequency arrays (size 26) to store character counts of `p` and the current window in `s`. Compare the frequency arrays for the first window. Then slide, updating the window's frequency array by decrementing the leaving character's count and incrementing the entering character's count. If the arrays match, add the start index to the result.

```cpp
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        if (p.size() > s.size()) return {};
        vector<int> pFreq(26, 0), windowFreq(26, 0);
        vector<int> result;

        // 1. Build frequency map for p and the first window
        for (int i = 0; i < p.size(); ++i) {
            pFreq[p[i] - 'a']++;
            windowFreq[s[i] - 'a']++;
        }
        if (pFreq == windowFreq) result.push_back(0);

        // 2. Slide the window
        for (int i = p.size(); i < s.size(); ++i) {
            windowFreq[s[i] - 'a']++;
            windowFreq[s[i - p.size()] - 'a']--;
            if (pFreq == windowFreq) {
                result.push_back(i - p.size() + 1);
            }
        }
        return result;
    }
};
```

#### [K Radius Subarray Averages](https://leetcode.com/problems/k-radius-subarray-averages/)

**Approach Summary**: A subarray of radius `k` has a fixed size of `2k+1`. We can use a sliding window of this size. Maintain a running sum. As you slide, add the new element and subtract the old one. Once the window is fully formed, calculate the average and place it in the result array. Cells that cannot be the center of a full-radius subarray get `-1`.

```cpp
class Solution {
public:
    vector<int> getAverages(vector<int>& nums, int k) {
        int n = nums.size();
        int windowSize = 2 * k + 1;
        vector<int> avgs(n, -1);
        if (n < windowSize) return avgs;

        long long currentSum = 0;
        // 1. Build the first window
        for (int i = 0; i < windowSize; ++i) {
            currentSum += nums[i];
        }
        avgs[k] = currentSum / windowSize;

        // 2. Slide the window
        for (int i = windowSize; i < n; ++i) {
            currentSum += nums[i] - nums[i - windowSize];
            avgs[i - k] = currentSum / windowSize;
        }
        return avgs;
    }
};
```

#### [Number of Sub-arrays of Size K and Average Greater than or Equal to Threshold](https://leetcode.com/problems/number-of-sub-arrays-of-size-k-and-average-greater-than-or-equal-to-threshold/)

**Approach Summary**: The window size is fixed at `k`. The condition `avg >= threshold` is the same as `sum >= threshold * k`. Slide a window of size `k`, maintain the `sum`, and at each step, check if the sum meets the target sum condition.

```cpp
class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        long long targetSum = (long long)k * threshold;
        long long currentSum = 0;
        int count = 0;

        // 1. Build the first window
        for (int i = 0; i < k; ++i) {
            currentSum += arr[i];
        }
        if (currentSum >= targetSum) count++;

        // 2. Slide the window
        for (int i = k; i < arr.size(); ++i) {
            currentSum += arr[i] - arr[i - k];
            if (currentSum >= targetSum) count++;
        }
        return count;
    }
};
```

---

## Section 2: Variable-Size Window

In these problems, the window size is **dynamic**. It expands and shrinks based on a specific condition. The goal is usually to find the **longest** or **shortest** subarray that satisfies this condition.

### Template

This template uses two pointers, `left` and `right`. The `right` pointer always moves forward to expand the window. The `left` pointer only moves forward to shrink the window when the window's state becomes invalid.

```cpp
// Generic Template for Variable-Size Window
void variable_window_template(vector<int>& arr) {
    int left = 0;
    // ... other variables to track window state ...
    // ... variable for the answer (e.g., maxLength) ...

    for (int right = 0; right < arr.size(); ++right) {
        // 1. EXPAND the window by including arr[right]
        // ... update window state ...

        // 2. While the window is INVALID, SHRINK it from the left
        while (/* condition is violated */) {
            // ... update window state by removing arr[left] ...
            left++;
        }

        // 3. Now the window is VALID. Update the answer.
        // ... ans = max/min(ans, current_window_size) ...
    }
}
```

### Problems on Variable-Size Window

#### [Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/)

**Approach Summary**: The condition is that the window must contain unique characters. Use a hash set or frequency map. Expand the window with `right`. If a character `s[right]` is already in the set, the window is invalid. Shrink it by moving `left` and removing `s[left]` from the set until the duplicate is gone. Update the max length at each valid step.

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> charSet;
        int left = 0, maxLength = 0;

        for (int right = 0; right < s.length(); ++right) {
            // 2. Shrink window if character is repeated
            while (charSet.count(s[right])) {
                charSet.erase(s[left]);
                left++;
            }
            // 1. Expand window
            charSet.insert(s[right]);
            // 3. Update answer
            maxLength = max(maxLength, right - left + 1);
        }
        return maxLength;
    }
};
```

#### [Longest Repeating Character Replacement](https://leetcode.com/problems/longest-repeating-character-replacement/)

**Approach Summary**: The condition to maintain is `window_length - max_frequency <= k`. The `max_frequency` is the count of the most frequent character in the current window. Expand with `right`, updating frequencies. If the condition is violated, shrink with `left`. The max length seen is the answer, as we only care about the largest valid window ever found.

```cpp
class Solution {
public:
    int characterReplacement(string s, int k) {
        vector<int> counts(26, 0);
        int left = 0, maxFreq = 0, maxLength = 0;

        for (int right = 0; right < s.length(); ++right) {
            // 1. Expand window
            counts[s[right] - 'A']++;
            maxFreq = max(maxFreq, counts[s[right] - 'A']);

            // 2. Shrink window if invalid
            if ((right - left + 1) - maxFreq > k) {
                counts[s[left] - 'A']--;
                left++;
            }

            // 3. Update answer
            maxLength = max(maxLength, right - left + 1);
        }
        return maxLength;
    }
};
```

#### [Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/)

**Approach Summary**: This is a special case that requires a helper data structure, a **deque (double-ended queue)**, to find the max in $O(1)$ time for each window. The deque stores indices of elements, and is always kept in decreasing order of element values. As we slide, we remove indices from the front that are out of bounds and remove indices from the back that correspond to values smaller than the current element. The front of the deque is always the index of the maximum element in the window.

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq;
        vector<int> result;

        for (int i = 0; i < nums.size(); ++i) {
            // Remove indices out of the current window
            if (!dq.empty() && dq.front() == i - k) {
                dq.pop_front();
            }
            // Maintain decreasing order in deque
            while (!dq.empty() && nums[dq.back()] < nums[i]) {
                dq.pop_back();
            }
            dq.push_back(i);

            // Add to result once the window is full
            if (i >= k - 1) {
                result.push_back(nums[dq.front()]);
            }
        }
        return result;
    }
};
```

#### [Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/)

**Approach Summary**: A classic. The condition is: "does the window contain all characters of `t` with required frequencies?". Use two frequency maps (`t`'s map and the window's map). Also track `required` (unique chars in `t`) vs. `formed` (unique chars in window that meet `t`'s frequency). Expand with `right`. Once `formed == required`, the window is valid. Now shrink with `left` as much as possible while it remains valid, updating the minimum window seen.

```cpp
class Solution {
public:
    string minWindow(string s, string t) {
        if (t.size() > s.size()) return "";
        unordered_map<char, int> tFreq, windowFreq;
        for (char c : t) tFreq[c]++;

        int left = 0, minLen = INT_MAX, startIdx = 0;
        int required = tFreq.size(), formed = 0;

        for (int right = 0; right < s.size(); ++right) {
            // 1. Expand window
            char c = s[right];
            windowFreq[c]++;
            if (tFreq.count(c) && windowFreq[c] == tFreq[c]) formed++;

            // 2. Shrink window
            while (left <= right && formed == required) {
                // 3. Update answer
                if (right - left + 1 < minLen) {
                    minLen = right - left + 1;
                    startIdx = left;
                }
                char leftChar = s[left];
                windowFreq[leftChar]--;
                if (tFreq.count(leftChar) && windowFreq[leftChar] < tFreq[leftChar]) formed--;
                left++;
            }
        }
        return minLen == INT_MAX ? "" : s.substr(startIdx, minLen);
    }
};
```

#### [Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/)

**Approach Summary**: The condition is `sum >= target`. Expand the window with `right`, adding to `currentSum`. Once the condition is met, the window is valid. Record its length, and then shrink from the `left` until the condition is broken, updating the minimum length at each valid step.

```cpp
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int left = 0, minLength = INT_MAX;
        long long currentSum = 0;

        for (int right = 0; right < nums.size(); ++right) {
            // 1. Expand window
            currentSum += nums[right];

            // 2. Shrink window while valid
            while (currentSum >= target) {
                // 3. Update answer
                minLength = min(minLength, right - left + 1);
                currentSum -= nums[left];
                left++;
            }
        }
        return (minLength == INT_MAX) ? 0 : minLength;
    }
};
```

#### [Minimum Consecutive Cards to Pick Up](https://leetcode.com/problems/minimum-consecutive-cards-to-pick-up/)

**Approach Summary**: We need the shortest subarray with a pair of matching cards. This means the shortest window that starts and ends with the same number. Use a hash map to store the last seen index of each card number. As we iterate with `right`, if we see a card that's in the map, we have found a valid window. The length is `right - map[card] + 1`. Keep track of the minimum such length.

```cpp
class Solution {
public:
    int minimumCardPickup(vector<int>& cards) {
        unordered_map<int, int> lastSeen;
        int minLength = INT_MAX;

        for (int i = 0; i < cards.size(); ++i) {
            if (lastSeen.count(cards[i])) {
                minLength = min(minLength, i - lastSeen[cards[i]] + 1);
            }
            lastSeen[cards[i]] = i;
        }
        return (minLength == INT_MAX) ? -1 : minLength;
    }
};
```

#### [Maximum Erasure Value](https://leetcode.com/problems/maximum-erasure-value/)

**Approach Summary**: This is "longest subarray with unique elements", but we need to maximize the sum. The logic is identical to "Longest Substring Without Repeating Characters". Use a set to track uniqueness and a variable for `currentSum`. Expand with `right`, adding to the set and sum. If a duplicate is found, shrink with `left`, removing from the set and sum, until the window is valid again.

```cpp
class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        unordered_set<int> seen;
        int left = 0, maxSum = 0;
        long long currentSum = 0;

        for (int right = 0; right < nums.size(); ++right) {
            // 2. Shrink window if invalid
            while (seen.count(nums[right])) {
                currentSum -= nums[left];
                seen.erase(nums[left]);
                left++;
            }
            // 1. Expand window
            currentSum += nums[right];
            seen.insert(nums[right]);
            // 3. Update answer
            maxSum = max(maxSum, (int)currentSum);
        }
        return maxSum;
    }
};
```

#### [Fruit Into Baskets](https://leetcode.com/problems/fruit-into-baskets/)

**Approach Summary**: This translates to "longest subarray with at most 2 distinct elements". Use a frequency map for the types of fruit in the window (the baskets). Expand with `right`. If `map.size() > 2`, the window is invalid. Shrink with `left`, decrementing fruit counts and removing from the map if a count hits zero, until `map.size() <= 2`.

```cpp
class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        unordered_map<int, int> basket;
        int left = 0, maxPicked = 0;

        for (int right = 0; right < fruits.size(); ++right) {
            // 1. Expand window
            basket[fruits[right]]++;

            // 2. Shrink window if invalid
            while (basket.size() > 2) {
                basket[fruits[left]]--;
                if (basket[fruits[left]] == 0) {
                    basket.erase(fruits[left]);
                }
                left++;
            }
            // 3. Update answer
            maxPicked = max(maxPicked, right - left + 1);
        }
        return maxPicked;
    }
};
```

#### The "At Most K" Pattern

For problems asking for subarrays with **exactly K** of something, a direct sliding window is difficult. The trick is to solve a simpler problem: finding subarrays with **at most K**. The final answer is then:
`count(at most K) - count(at most K - 1)`

#### [Count Number of Nice Subarrays](https://leetcode.com/problems/count-number-of-nice-subarrays/)

**Approach Summary**: We need subarrays with exactly `k` odd numbers. We use the "At Most K" pattern. Create a helper function `atMost(k)` that counts subarrays with at most `k` odd numbers using a standard variable-size window. The window is always valid. The number of new subarrays ending at `right` is `right - left + 1`. The final answer is `atMost(k) - atMost(k - 1)`.

```cpp
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        return atMost(nums, k) - atMost(nums, k - 1);
    }
private:
    int atMost(vector<int>& nums, int k) {
        int left = 0, count = 0, oddCount = 0;
        for (int right = 0; right < nums.size(); ++right) {
            if (nums[right] % 2 != 0) {
                oddCount++;
            }
            while (oddCount > k) {
                if (nums[left] % 2 != 0) {
                    oddCount--;
                }
                left++;
            }
            count += (right - left + 1);
        }
        return count;
    }
};
```

#### [Subarrays with K Different Integers](https://leetcode.com/problems/subarrays-with-k-different-integers/)

**Approach Summary**: This is another classic "At Most K" problem. Find the number of subarrays with exactly `k` distinct integers. Create a helper `atMost(k)` that uses a variable window to count subarrays with at most `k` distinct integers. The final answer is `atMost(k) - atMost(k - 1)`.

```cpp
class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return atMost(nums, k) - atMost(nums, k - 1);
    }
private:
    int atMost(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        int left = 0, count = 0;
        for (int right = 0; right < nums.size(); ++right) {
            freq[nums[right]]++;
            while (freq.size() > k) {
                freq[nums[left]]--;
                if (freq[nums[left]] == 0) {
                    freq.erase(nums[left]);
                }
                left++;
            }
            count += (right - left + 1);
        }
        return count;
    }
};
```

#### [Arithmetic Slices](https://leetcode.com/problems/arithmetic-slices/)

**Approach Summary**: A slice is arithmetic if it has at least 3 elements with the same difference. We can use a window to represent the _current_ continuous arithmetic slice. Iterate from `i = 2`. If `A[i] - A[i-1] == A[i-1] - A[i-2]`, we extend the current slice. A slice of length `L` contains `(L-1)*(L-2)/2` arithmetic subarrays of length 3 or more. We add to our total count based on the length of the current slice.

```cpp
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        if (nums.size() < 3) return 0;
        int count = 0, total = 0;
        for (int i = 2; i < nums.size(); ++i) {
            if ((long)nums[i] - nums[i-1] == (long)nums[i-1] - nums[i-2]) {
                count++;
            } else {
                total += (count * (count + 1)) / 2;
                count = 0;
            }
        }
        total += (count * (count + 1)) / 2;
        return total;
    }
};
```
