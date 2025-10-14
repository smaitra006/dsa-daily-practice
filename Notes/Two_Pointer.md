# Study Guide: The Two Pointers Technique

The **Two Pointers** technique is a fundamental and highly efficient algorithmic pattern used to process data in arrays, strings, or linked lists. It involves using two integer pointers to iterate through a data structure until they meet or satisfy a certain condition.

The primary advantage of this technique is its ability to reduce the time complexity of solving problems, often transforming a brute-force $O(n^2)$ or $O(n^3)$ solution into a much faster linear $O(n)$ or near-linear $O(n \log n)$ solution. 🚀

This guide is structured into four main patterns:

1.  **Running from Both Ends of an Array**
2.  **Slow & Fast Pointers**
3.  **Running from the Beginning of 2 Arrays**
4.  **Split & Merge of an Array**

---

## 1\. Running from Both Ends of an Array

This is a classic pattern where two pointers, let's call them `left` and `right`, are initialized at the opposite ends of a collection (like an array or string). They then move towards the center, processing elements and narrowing the search space at each step. This is especially effective on **sorted** arrays.

### 2 Sum Problem

This sub-category involves finding pairs or tuples of numbers in a sorted array that sum up to a target value. The core idea is to adjust the pointers based on whether the current sum is too small or too large.

#### (\*) [Two Sum II - Input Array Is Sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/)

**Approach Summary**: With `left` at the start and `right` at the end, calculate `sum = numbers[left] + numbers[right]`. If `sum < target`, increment `left` to get a larger sum. If `sum > target`, decrement `right` for a smaller sum. If `sum == target`, you've found the pair.

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0, right = numbers.size() - 1;
        while (left < right) {
            int sum = numbers[left] + numbers[right];
            if (sum == target) {
                return {left + 1, right + 1};
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
        return {};
    }
};
```

#### [3Sum](https://leetcode.com/problems/3sum/)

**Approach Summary**: First, sort the array. Then, iterate through the array with a pointer `i`. For each `nums[i]`, use the two-pointer approach on the rest of the array (`left = i + 1`, `right = n - 1`) to find a pair that sums to `-nums[i]`. Skip duplicate elements to avoid duplicate triplets in the result.

```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        int n = nums.size();
        for (int i = 0; i < n - 2; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            int left = i + 1, right = n - 1;
            int target = -nums[i];
            while (left < right) {
                int sum = nums[left] + nums[right];
                if (sum == target) {
                    result.push_back({nums[i], nums[left], nums[right]});
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    while (left < right && nums[right] == nums[right - 1]) right--;
                    left++;
                    right--;
                } else if (sum < target) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        return result;
    }
};
```

#### [4Sum](https://leetcode.com/problems/4sum/)

**Approach Summary**: This extends the 3Sum approach. Sort the array. Use two nested loops with pointers `i` and `j`. For each pair `(nums[i], nums[j])`, use the two-pointer approach (`left = j + 1`, `right = n - 1`) on the rest of the array to find a pair that sums to `target - nums[i] - nums[j]`. Skip duplicates for all four pointers.

```cpp
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            for (int j = i + 1; j < n; ++j) {
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;
                int left = j + 1, right = n - 1;
                long long new_target = (long long)target - nums[i] - nums[j];
                while (left < right) {
                    long long sum = nums[left] + nums[right];
                    if (sum == new_target) {
                        result.push_back({nums[i], nums[j], nums[left], nums[right]});
                        while (left < right && nums[left] == nums[left + 1]) left++;
                        while (left < right && nums[right] == nums[right - 1]) right--;
                        left++;
                        right--;
                    } else if (sum < new_target) {
                        left++;
                    } else {
                        right--;
                    }
                }
            }
        }
        return result;
    }
};
```

#### [Number of Subsequences That Satisfy the Given Sum Condition](https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/)

**Approach Summary**: Sort `nums`. Use two pointers `left` and `right`. For a fixed `left`, find the largest `right` such that `nums[left] + nums[right] <= target`. Since the array is sorted, `nums[left]` is the minimum. It can form a valid subsequence with any combination of elements between `left+1` and `right`. There are `2^(right - left)` such subsequences. Add this to the total and increment `left`. Pre-calculate powers of 2 to avoid re-computation.

```cpp
class Solution {
public:
    int numSubseq(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int left = 0, right = n - 1;
        int result = 0;
        int mod = 1e9 + 7;
        vector<int> powers(n + 1, 1);
        for (int i = 1; i <= n; ++i) {
            powers[i] = (powers[i - 1] * 2) % mod;
        }

        while (left <= right) {
            if (nums[left] + nums[right] <= target) {
                result = (result + powers[right - left]) % mod;
                left++;
            } else {
                right--;
            }
        }
        return result;
    }
};
```

#### [Two Sum IV - Input is a BST](https://leetcode.com/problems/two-sum-iv-input-is-a-bst/)

**Approach Summary**: Perform an in-order traversal of the BST to get a sorted array of its elements. Then, apply the standard two-pointer "2 Sum" algorithm on this sorted array.

```cpp
class Solution {
public:
    void inorder(TreeNode* root, vector<int>& sorted_nodes) {
        if (!root) return;
        inorder(root->left, sorted_nodes);
        sorted_nodes.push_back(root->val);
        inorder(root->right, sorted_nodes);
    }

    bool findTarget(TreeNode* root, int k) {
        vector<int> sorted_nodes;
        inorder(root, sorted_nodes);
        int left = 0, right = sorted_nodes.size() - 1;
        while (left < right) {
            int sum = sorted_nodes[left] + sorted_nodes[right];
            if (sum == k) {
                return true;
            } else if (sum < k) {
                left++;
            } else {
                right--;
            }
        }
        return false;
    }
};
```

#### [Sum of Square Numbers](https://leetcode.com/problems/sum-of-square-numbers/)

**Approach Summary**: Use two pointers. Let `left = 0` and `right` be the integer part of `sqrt(c)`. Check if `left^2 + right^2` equals `c`. If the sum is too small, increment `left`. If it's too large, decrement `right`.

```cpp
class Solution {
public:
    bool judgeSquareSum(int c) {
        long left = 0, right = (long)sqrt(c);
        while (left <= right) {
            long sum = left * left + right * right;
            if (sum == c) {
                return true;
            } else if (sum < c) {
                left++;
            } else {
                right--;
            }
        }
        return false;
    }
};
```

#### [Boats to Save People](https://leetcode.com/problems/boats-to-save-people/)

**Approach Summary**: Sort the `people` array. Use `left` for the lightest person and `right` for the heaviest. Each boat takes one or two people. Always place the heaviest person (`people[right]`) in a boat. If the lightest person (`people[left]`) can fit with them (`people[left] + people[right] <= limit`), pair them up and increment `left`. In either case, decrement `right` and increment the boat count.

```cpp
class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());
        int left = 0, right = people.size() - 1;
        int boats = 0;
        while (left <= right) {
            if (people[left] + people[right] <= limit) {
                left++;
            }
            right--;
            boats++;
        }
        return boats;
    }
};
```

#### [Minimize Maximum Pair Sum in Array](https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/)

**Approach Summary**: To minimize the maximum pair sum, you must pair the smallest elements with the largest ones. Sort the array. Use two pointers, `left` at the start and `right` at the end. The pairs will be `(nums[left], nums[right])`. Calculate the sum for each such pair as you move the pointers inward and find the maximum among them.

```cpp
class Solution {
public:
    int minPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int left = 0, right = nums.size() - 1;
        int maxPairSum = 0;
        while (left < right) {
            maxPairSum = max(maxPairSum, nums[left] + nums[right]);
            left++;
            right--;
        }
        return maxPairSum;
    }
};
```

#### [3Sum With Multiplicity](https://leetcode.com/problems/3sum-with-multiplicity/)

**Approach Summary**: Sort the array. Iterate with a pointer `i`. For each `nums[i]`, use two pointers `left` and `right` to find pairs that sum to `target - nums[i]`. When `nums[left] + nums[right]` equals the new target, you must handle duplicates carefully.

- If `nums[left] != nums[right]`, count how many times `nums[left]` and `nums[right]` repeat, multiply these counts, and add to the result. Then move `left` and `right` past all duplicates.
- If `nums[left] == nums[right]`, you need to choose 2 from the `N` identical numbers, which is `N * (N-1) / 2`.

<!-- end list -->

```cpp
class Solution {
public:
    int threeSumMulti(vector<int>& arr, int target) {
        sort(arr.begin(), arr.end());
        long result = 0;
        int n = arr.size();
        int mod = 1e9 + 7;
        for (int i = 0; i < n; ++i) {
            int new_target = target - arr[i];
            int left = i + 1, right = n - 1;
            while (left < right) {
                int sum = arr[left] + arr[right];
                if (sum < new_target) {
                    left++;
                } else if (sum > new_target) {
                    right--;
                } else {
                    if (arr[left] != arr[right]) {
                        int left_count = 1, right_count = 1;
                        while (left + 1 < right && arr[left] == arr[left + 1]) {
                            left_count++;
                            left++;
                        }
                        while (right - 1 > left && arr[right] == arr[right - 1]) {
                            right_count++;
                            right--;
                        }
                        result += (long)left_count * right_count;
                        left++;
                        right--;
                    } else {
                        long count = right - left + 1;
                        result += (count * (count - 1)) / 2;
                        break;
                    }
                }
            }
        }
        return result % mod;
    }
};
```

### Trapping Water

This pattern involves finding the amount of water that can be trapped between bars of a histogram. The amount of water above any bar is determined by the height of the walls to its left and right.

#### (\*) [Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/)

**Approach Summary**: Use two pointers, `left` and `right`, at the ends of the array, and two variables, `left_max` and `right_max`, to track the tallest bar seen so far from each end. If `left_max < right_max`, it means the water level at the `left` pointer is determined by `left_max`. Calculate the trapped water `left_max - height[left]` and move `left` inward. Otherwise, do the same for the `right` pointer.

```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int left_max = 0, right_max = 0;
        int water = 0;
        while (left < right) {
            if (height[left] < height[right]) {
                if (height[left] >= left_max) {
                    left_max = height[left];
                } else {
                    water += left_max - height[left];
                }
                left++;
            } else {
                if (height[right] >= right_max) {
                    right_max = height[right];
                } else {
                    water += right_max - height[right];
                }
                right--;
            }
        }
        return water;
    }
};
```

#### [Container With Most Water](https://leetcode.com/problems/container-with-most-water/)

**Approach Summary**: Start with `left` at the beginning and `right` at the end. The area is `min(height[left], height[right]) * (right - left)`. To find a potentially larger area, you must increase either the width or the height. Since we can only decrease the width by moving pointers, we must try to find a taller height. Therefore, always move the pointer that points to the shorter of the two lines inward.

```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int max_area = 0;
        while (left < right) {
            int current_area = min(height[left], height[right]) * (right - left);
            max_area = max(max_area, current_area);
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        return max_area;
    }
};
```

### Next Permutation

This pattern involves finding the next lexicographically greater permutation of a sequence. It uses a combination of searching from the right and then reversing a subarray.

#### (\*) [Next Permutation](https://leetcode.com/problems/next-permutation/)

**Approach Summary**:

1.  Scan from right to left to find the first element `nums[k]` that is smaller than the element to its right. This is the "pivot".
2.  If no such element exists, the array is in descending order. Reverse the whole array to get the smallest permutation.
3.  Otherwise, scan again from right to left to find the first element `nums[l]` that is larger than the pivot `nums[k]`.
4.  Swap `nums[k]` and `nums[l]`.
5.  Reverse the subarray from `k + 1` to the end of the array. This reversal can be done with two pointers.

<!-- end list -->

```cpp
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int k = -1;
        for (int i = n - 2; i >= 0; i--) {
            if (nums[i] < nums[i + 1]) {
                k = i;
                break;
            }
        }
        if (k == -1) {
            reverse(nums.begin(), nums.end());
            return;
        }
        int l = -1;
        for (int i = n - 1; i > k; i--) {
            if (nums[i] > nums[k]) {
                l = i;
                break;
            }
        }
        swap(nums[k], nums[l]);
        reverse(nums.begin() + k + 1, nums.end());
    }
};
```

#### [Next Greater Element III](https://leetcode.com/problems/next-greater-element-iii/)

**Approach Summary**: Convert the number to a string or a vector of digits. Apply the "Next Permutation" algorithm. Convert the result back to a number. Check for overflow; if the result is larger than a 32-bit integer, return -1.

```cpp
class Solution {
public:
    int nextGreaterElement(int n) {
        string s = to_string(n);
        next_permutation(s.begin(), s.end());
        long long result = stoll(s);
        return (result > INT_MAX || result <= n) ? -1 : result;
    }
};
```

#### [Minimum Adjacent Swaps to Reach the Kth Smallest Number](https://leetcode.com/problems/minimum-adjacent-swaps-to-reach-the-kth-smallest-number/)

**Approach Summary**: First, find the K-th smallest number by applying the "Next Permutation" algorithm `k` times to the initial number string. This gives you the target permutation. Then, calculate the minimum swaps to transform the original string into the target string. This second part is a separate problem: count the swaps needed to match one permutation to another. A greedy approach works: for each position, find the required character in the remainder of the string and bring it to the front with adjacent swaps.

```cpp
class Solution {
public:
    int getMinSwaps(string num, int k) {
        string original_num = num;
        for (int i = 0; i < k; ++i) {
            next_permutation(num.begin(), num.end());
        }

        int swaps = 0;
        int n = num.length();
        for (int i = 0; i < n; ++i) {
            if (original_num[i] != num[i]) {
                int j = i + 1;
                while (original_num[j] != num[i]) {
                    j++;
                }
                while (j > i) {
                    swap(original_num[j], original_num[j - 1]);
                    swaps++;
                    j--;
                }
            }
        }
        return swaps;
    }
};
```

### Reversing / Swapping

This is the most straightforward two-pointer pattern. Pointers `left` and `right` start at the ends and move inward, swapping elements as they go until they meet or cross. Variations involve adding conditions to the swap.

#### [Valid Palindrome](https://leetcode.com/problems/valid-palindrome/)

**Approach Summary**: Use `left` and `right` pointers. Move them inward, skipping any non-alphanumeric characters. At each step, compare the lowercase versions of the characters at `left` and `right`. If they don't match, return `false`. If the pointers cross, it's a palindrome.

```cpp
class Solution {
public:
    bool isPalindrome(string s) {
        int left = 0, right = s.length() - 1;
        while (left < right) {
            while (left < right && !isalnum(s[left])) left++;
            while (left < right && !isalnum(s[right])) right--;
            if (tolower(s[left]) != tolower(s[right])) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
};
```

#### (\*) [Reverse String](https://leetcode.com/problems/reverse-string/)

**Approach Summary**: The quintessential two-pointer swap. With `left` at the start and `right` at the end, swap `s[left]` and `s[right]`. Then increment `left` and decrement `right`. Repeat until `left >= right`.

```cpp
class Solution {
public:
    void reverseString(vector<char>& s) {
        int left = 0, right = s.size() - 1;
        while (left < right) {
            swap(s[left], s[right]);
            left++;
            right--;
        }
    }
};
```

#### [Reverse Vowels of a String](https://leetcode.com/problems/reverse-vowels-of-a-string/)

**Approach Summary**: Use two pointers, `left` and `right`. Move `left` forward until it points to a vowel. Move `right` backward until it points to a vowel. Swap them. Repeat until the pointers cross.

```cpp
class Solution {
public:
    string reverseVowels(string s) {
        int left = 0, right = s.length() - 1;
        auto isVowel = [](char c) {
            c = tolower(c);
            return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
        };
        while (left < right) {
            while (left < right && !isVowel(s[left])) left++;
            while (left < right && !isVowel(s[right])) right--;
            swap(s[left], s[right]);
            left++;
            right--;
        }
        return s;
    }
};
```

#### [Valid Palindrome II](https://leetcode.com/problems/valid-palindrome-ii/)

**Approach Summary**: Use two pointers. When you find the first mismatch at `s[left]` and `s[right]`, you have one chance to delete a character. Check if the remaining substring is a palindrome after either deleting `s[left]` (check `s[left+1...right]`) or deleting `s[right]` (check `s[left...right-1]`). If either of those checks passes, return `true`.

```cpp
class Solution {
public:
    bool isPalindromeRange(string s, int i, int j) {
        while (i < j) {
            if (s[i] != s[j]) return false;
            i++;
            j--;
        }
        return true;
    }
    bool validPalindrome(string s) {
        int left = 0, right = s.length() - 1;
        while (left < right) {
            if (s[left] != s[right]) {
                return isPalindromeRange(s, left + 1, right) || isPalindromeRange(s, left, right - 1);
            }
            left++;
            right--;
        }
        return true;
    }
};
```

#### [Reverse Only Letters](https://leetcode.com/problems/reverse-only-letters/)

**Approach Summary**: Identical logic to "Reverse Vowels", but the condition is whether a character is an English letter instead of a vowel.

```cpp
class Solution {
public:
    string reverseOnlyLetters(string s) {
        int left = 0, right = s.length() - 1;
        while (left < right) {
            while (left < right && !isalpha(s[left])) left++;
            while (left < right && !isalpha(s[right])) right--;
            swap(s[left], s[right]);
            left++;
            right--;
        }
        return s;
    }
};
```

#### [Remove Element](https://leetcode.com/problems/remove-element/)

**Approach Summary**: Use two pointers. `left` will be the "write" pointer, tracking the end of the array without the target value. `right` will be the "read" pointer. Iterate `right` through the array. If `nums[right]` is not the value to be removed, copy it to `nums[left]` and increment `left`. Return `left`.

```cpp
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int left = 0;
        for (int right = 0; right < nums.size(); ++right) {
            if (nums[right] != val) {
                nums[left] = nums[right];
                left++;
            }
        }
        return left;
    }
};
```

#### [Sort Colors](https://leetcode.com/problems/sort-colors/)

**Approach Summary**: This is the Dutch National Flag problem. Use three pointers: `low`, `mid`, and `high`.

- `low`: Boundary for 0s.
- `mid`: The current element being considered.
- `high`: Boundary for 2s.
  Iterate with `mid`. If `nums[mid] == 0`, swap with `nums[low]` and increment both `low` and `mid`. If `nums[mid] == 2`, swap with `nums[high]` and decrement `high`. If `nums[mid] == 1`, just increment `mid`.

<!-- end list -->

```cpp
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int low = 0, mid = 0, high = nums.size() - 1;
        while (mid <= high) {
            if (nums[mid] == 0) {
                swap(nums[low], nums[mid]);
                low++;
                mid++;
            } else if (nums[mid] == 1) {
                mid++;
            } else { // nums[mid] == 2
                swap(nums[mid], nums[high]);
                high--;
            }
        }
    }
};
```

#### [Flipping an Image](https://leetcode.com/problems/flipping-an-image/)

**Approach Summary**: For each row, first reverse it using the standard two-pointer swap. Then, iterate through the reversed row and invert each bit (0 becomes 1, 1 becomes 0). You can combine these steps: as you swap `image[i][left]` and `image[i][right]`, invert them immediately.

```cpp
class Solution {
public:
    vector<vector<int>> flipAndInvertImage(vector<vector<int>>& image) {
        for (auto& row : image) {
            int left = 0, right = row.size() - 1;
            while (left <= right) {
                int temp = row[left];
                row[left] = 1 - row[right];
                row[right] = 1 - temp;
                left++;
                right--;
            }
        }
        return image;
    }
};
```

#### [Squares of a Sorted Array](https://leetcode.com/problems/squares-of-a-sorted-array/)

**Approach Summary**: The largest squared value will come from either the most negative number or the most positive number. Use two pointers, `left` at the start and `right` at the end of the input array. Compare `abs(nums[left])` and `abs(nums[right])`. The larger square is placed at the end of the result array, and the corresponding pointer is moved inward. A third pointer tracks where to write in the result array, starting from the end.

```cpp
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n);
        int left = 0, right = n - 1;
        for (int i = n - 1; i >= 0; i--) {
            if (abs(nums[left]) > abs(nums[right])) {
                result[i] = nums[left] * nums[left];
                left++;
            } else {
                result[i] = nums[right] * nums[right];
                right--;
            }
        }
        return result;
    }
};
```

#### [Sort Array By Parity](https://leetcode.com/problems/sort-array-by-parity/)

**Approach Summary**: Use two pointers, `left` and `right`. `left` seeks the first odd number from the start, and `right` seeks the first even number from the end. When they are found, swap them. Continue until the pointers cross. This partitions the array into evens followed by odds.

```cpp
class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            while (left < right && nums[left] % 2 == 0) left++;
            while (left < right && nums[right] % 2 != 0) right--;
            swap(nums[left], nums[right]);
        }
        return nums;
    }
};
```

#### [Sort Array By Parity II](https://leetcode.com/problems/sort-array-by-parity-ii/)

**Approach Summary**: Use two pointers, `even` starting at index 0 and `odd` at index 1. `even` seeks the first misplaced odd number at an even index. `odd` seeks the first misplaced even number at an odd index. Both pointers advance by 2 at each step. When both are found, swap the elements.

```cpp
class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& nums) {
        int even = 0, odd = 1;
        int n = nums.size();
        while (even < n && odd < n) {
            while (even < n && nums[even] % 2 == 0) even += 2;
            while (odd < n && nums[odd] % 2 != 0) odd += 2;
            if (even < n && odd < n) {
                swap(nums[even], nums[odd]);
            }
        }
        return nums;
    }
};
```

#### [Pancake Sorting](https://leetcode.com/problems/pancake-sorting/)

**Approach Summary**: This is a greedy approach. In each step, find the largest unsorted number, say `x`.

1.  Find the index `i` of `x`.
2.  Flip the prefix of length `i+1` to bring `x` to the front.
3.  Flip the prefix of length `x` to move `x` to its correct final position.
    Repeat this for `x = n, n-1, ..., 1`. The "flip" operation is a reverse, which can be done with two pointers.

<!-- end list -->

```cpp
class Solution {
public:
    vector<int> pancakeSort(vector<int>& arr) {
        vector<int> result;
        int n = arr.size();
        for (int valToSort = n; valToSort > 0; --valToSort) {
            int idx = find(arr.begin(), arr.end(), valToSort) - arr.begin();
            if (idx == valToSort - 1) continue;
            if (idx != 0) {
                reverse(arr.begin(), arr.begin() + idx + 1);
                result.push_back(idx + 1);
            }
            reverse(arr.begin(), arr.begin() + valToSort);
            result.push_back(valToSort);
        }
        return result;
    }
};
```

#### [Reverse Prefix of Word](https://leetcode.com/problems/reverse-prefix-of-word/)

**Approach Summary**: First, find the index of the first occurrence of the character `ch`. If it's not found, return the original word. If it is found at index `idx`, use a two-pointer approach (`left=0`, `right=idx`) to reverse the prefix of the word up to and including that index.

```cpp
class Solution {
public:
    string reversePrefix(string word, char ch) {
        int idx = -1;
        for (int i = 0; i < word.length(); ++i) {
            if (word[i] == ch) {
                idx = i;
                break;
            }
        }
        if (idx != -1) {
            int left = 0, right = idx;
            while (left < right) {
                swap(word[left], word[right]);
                left++;
                right--;
            }
        }
        return word;
    }
};
```

#### [Reverse String II](https://leetcode.com/problems/reverse-string-ii/)

**Approach Summary**: Iterate through the string with a step of `2k`. For each segment, determine the start and end of the sub-segment to be reversed. This will be from the current position `i` to `min(i + k - 1, n - 1)`. Use a standard two-pointer reverse on this sub-segment.

```cpp
class Solution {
public:
    string reverseStr(string s, int k) {
        int n = s.length();
        for (int i = 0; i < n; i += 2 * k) {
            int left = i;
            int right = min(i + k - 1, n - 1);
            while (left < right) {
                swap(s[left], s[right]);
                left++;
                right--;
            }
        }
        return s;
    }
};
```

#### [Reverse Words in a String](https://leetcode.com/problems/reverse-words-in-a-string/)

**Approach Summary**: This is a multi-step two-pointer problem.

1.  Reverse the entire string.
2.  Use two pointers, `start` and `end`, to find each word in the reversed string.
3.  Reverse each individual word in place.
4.  Clean up any extra spaces.

<!-- end list -->

```cpp
class Solution {
public:
    string reverseWords(string s) {
        reverse(s.begin(), s.end());
        int store_idx = 0;
        for (int start = 0; start < s.length(); ++start) {
            if (s[start] != ' ') {
                if (store_idx != 0) s[store_idx++] = ' ';
                int end = start;
                while (end < s.length() && s[end] != ' ') {
                    s[store_idx++] = s[end++];
                }
                reverse(s.begin() + store_idx - (end - start), s.begin() + store_idx);
                start = end;
            }
        }
        s.erase(s.begin() + store_idx, s.end());
        return s;
    }
};
```

#### [Reverse Words in a String III](https://leetcode.com/problems/reverse-words-in-a-string-iii/)

**Approach Summary**: Iterate through the string to identify the boundaries of each word (words are separated by spaces). For each word found, use a two-pointer approach to reverse it in place.

```cpp
class Solution {
public:
    string reverseWords(string s) {
        int last_space = -1;
        int n = s.length();
        for (int i = 0; i <= n; ++i) {
            if (i == n || s[i] == ' ') {
                int left = last_space + 1;
                int right = i - 1;
                while (left < right) {
                    swap(s[left], s[right]);
                    left++;
                    right--;
                }
                last_space = i;
            }
        }
        return s;
    }
};
```

### Others

#### [Bag of Tokens](https://leetcode.com/problems/bag-of-tokens/)

**Approach Summary**: This is a greedy problem. Sort the tokens. Use two pointers, `left` and `right`.

- To gain score, you must play the smallest token face-up (`power >= tokens[left]`).
- To gain power, you must play the largest token face-down (`score > 0`).
  Always try to gain score first. If you can't, but you could potentially gain more score later, gain power.

<!-- end list -->

```cpp
class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        sort(tokens.begin(), tokens.end());
        int left = 0, right = tokens.size() - 1;
        int score = 0, maxScore = 0;
        while (left <= right) {
            if (power >= tokens[left]) {
                power -= tokens[left];
                score++;
                left++;
                maxScore = max(maxScore, score);
            } else if (score > 0) {
                power += tokens[right];
                score--;
                right--;
            } else {
                break;
            }
        }
        return maxScore;
    }
};
```

#### [DI String Match](https://leetcode.com/problems/di-string-match/)

**Approach Summary**: We need to construct a permutation of `[0...n]`. Use two pointers, `low = 0` and `high = n`, representing the smallest and largest available numbers. Iterate through the string `s`. If `s[i] == 'I'` (increase), we need a small number, so use `low` and increment it. If `s[i] == 'D'` (decrease), we need a large number, so use `high` and decrement it. Append the final remaining number at the end.

```cpp
class Solution {
public:
    vector<int> diStringMatch(string s) {
        int n = s.length();
        int low = 0, high = n;
        vector<int> result;
        for (char c : s) {
            if (c == 'I') {
                result.push_back(low++);
            } else {
                result.push_back(high--);
            }
        }
        result.push_back(low);
        return result;
    }
};
```

#### [Minimum Length of String After Deleting Similar Ends](https://leetcode.com/problems/minimum-length-of-string-after-deleting-similar-ends/)

**Approach Summary**: Use two pointers, `left` and `right`. If `s[left]` and `s[right]` are different, we can't delete anything, so the answer is `right - left + 1`. If they are the same, store the character. Move `left` forward as long as it points to the same character. Move `right` backward as long as it points to the same character. Repeat this process. The final answer is the length of the remaining substring.

```cpp
class Solution {
public:
    int minimumLength(string s) {
        int left = 0, right = s.length() - 1;
        while (left < right && s[left] == s[right]) {
            char c = s[left];
            while (left <= right && s[left] == c) left++;
            while (left <= right && s[right] == c) right--;
        }
        return right - left + 1;
    }
};
```

#### [Sentence Similarity III](https://leetcode.com/problems/sentence-similarity-iii/)

**Approach Summary**: Split the sentences into words. Use two pointers `left1`, `right1` for `sentence1` and `left2`, `right2` for `sentence2`. Match common prefixes by moving the `left` pointers. Then match common suffixes by moving the `right` pointers. If `left2 > right2`, it means all words in `sentence2` were matched either as a prefix or a suffix of `sentence1`, so it's a valid insertion.

```cpp
class Solution {
public:
    bool areSentencesSimilar(string sentence1, string sentence2) {
        deque<string> words1, words2;
        string word;
        stringstream ss1(sentence1);
        while (ss1 >> word) words1.push_back(word);
        stringstream ss2(sentence2);
        while (ss2 >> word) words2.push_back(word);

        if (words1.size() < words2.size()) swap(words1, words2);

        while (!words2.empty() && words1.front() == words2.front()) {
            words1.pop_front();
            words2.pop_front();
        }
        while (!words2.empty() && words1.back() == words2.back()) {
            words1.pop_back();
            words2.pop_back();
        }

        return words2.empty();
    }
};
```

#### [Find K Closest Elements](https://leetcode.com/problems/find-k-closest-elements/)

**Approach Summary**: Use two pointers, `left` and `right`, to define a window of size greater than `k`. The goal is to shrink this window to size `k` by removing the element that is farther from `x`. If `x - arr[left]` is greater than `arr[right] - x`, the left element is farther, so increment `left`. Otherwise, decrement `right`. Repeat until the window size is `k`.

```cpp
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int left = 0, right = arr.size() - 1;
        while (right - left + 1 > k) {
            if (x - arr[left] > arr[right] - x) {
                left++;
            } else {
                right--;
            }
        }
        return vector<int>(arr.begin() + left, arr.begin() + right + 1);
    }
};
```

#### [Shortest Distance to a Character](https://leetcode.com/problems/shortest-distance-to-a-character/)

**Approach Summary**: This can be solved with two passes, which is a form of two-pointer thinking.

1.  **Left-to-Right Pass**: Iterate from left to right. Keep track of the index of the most recently seen `C`, say `prev`. The distance for the current cell `i` is `i - prev`.
2.  **Right-to-Left Pass**: Iterate from right to left. Again, track the most recent `prev`. The distance is `prev - i`.
    The final answer for each cell is the minimum of the distances calculated in the two passes.

<!-- end list -->

```cpp
class Solution {
public:
    vector<int> shortestToChar(string s, char c) {
        int n = s.length();
        vector<int> result(n, n);
        int prev = -n;

        for (int i = 0; i < n; ++i) {
            if (s[i] == c) prev = i;
            result[i] = i - prev;
        }

        prev = 2 * n;
        for (int i = n - 1; i >= 0; --i) {
            if (s[i] == c) prev = i;
            result[i] = min(result[i], prev - i);
        }

        return result;
    }
};
```

---

## 2\. Slow & Fast Pointers

In this pattern, two pointers move through the data at different speeds. They typically both start from the left end. The `fast` pointer advances to explore the data, while the `slow` pointer advances under specific conditions, often to a position determined by the `fast` pointer. This is famously used for cycle detection (Floyd's Tortoise and Hare algorithm).

### Linked List Operations

This is the most common application of the slow & fast pointer technique.

#### (\*) [Linked List Cycle](https://leetcode.com/problems/linked-list-cycle/)

**Approach Summary**: Use a `slow` pointer that moves one step at a time and a `fast` pointer that moves two steps. If there is a cycle, the `fast` pointer will eventually lap the `slow` pointer, and they will meet. If `fast` reaches `nullptr`, there is no cycle.

```cpp
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                return true;
            }
        }
        return false;
    }
};
```

#### [Linked List Cycle II](https://leetcode.com/problems/linked-list-cycle-ii/)

**Approach Summary**: First, use the slow & fast pointer method to detect a cycle and find the meeting point. Once they meet, reset one pointer (e.g., `slow`) back to the `head`. Then, move both `slow` and `fast` one step at a time. The point where they meet again is the start of the cycle.

```cpp
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                slow = head;
                while (slow != fast) {
                    slow = slow->next;
                    fast = fast->next;
                }
                return slow;
            }
        }
        return nullptr;
    }
};
```

#### [Remove Nth Node From End of List](https://leetcode.com/problems/remove-nth-node-from-end-of-list/)

**Approach Summary**: Use two pointers, `fast` and `slow`. First, advance the `fast` pointer `n` steps ahead of `slow`. Then, move both pointers one step at a time until `fast` reaches the end of the list. At this point, `slow` will be pointing to the node _just before_ the one to be deleted.

```cpp
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0, head);
        ListNode* slow = dummy, *fast = dummy;
        for (int i = 0; i < n; ++i) {
            fast = fast->next;
        }
        while (fast->next) {
            slow = slow->next;
            fast = fast->next;
        }
        slow->next = slow->next->next;
        return dummy->next;
    }
};
```

#### [Rotate List](https://leetcode.com/problems/rotate-list/)

**Approach Summary**: First, find the length of the list and connect the tail to the head to form a cycle. The new tail will be at position `length - (k % length) - 1`. The new head will be the node after the new tail. Use a pointer to traverse to the new tail, break the cycle, and return the new head.

```cpp
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head || !head->next || k == 0) return head;
        int len = 1;
        ListNode* tail = head;
        while (tail->next) {
            tail = tail->next;
            len++;
        }
        tail->next = head; // Form a cycle

        int steps_to_new_tail = len - (k % len) - 1;
        ListNode* new_tail = head;
        for (int i = 0; i < steps_to_new_tail; ++i) {
            new_tail = new_tail->next;
        }

        ListNode* new_head = new_tail->next;
        new_tail->next = nullptr; // Break the cycle
        return new_head;
    }
};
```

#### [Reorder List](https://leetcode.com/problems/reorder-list/)

**Approach Summary**: This is a three-step process:

1.  **Find Middle**: Use a slow and fast pointer to find the middle of the linked list.
2.  **Reverse Second Half**: Reverse the second half of the list starting from the node after the middle.
3.  **Merge**: Merge the first half and the reversed second half by interleaving their nodes.

<!-- end list -->

```cpp
class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head || !head->next) return;
        // 1. Find middle
        ListNode *slow = head, *fast = head;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // 2. Reverse second half
        ListNode *prev = nullptr, *curr = slow->next;
        slow->next = nullptr;
        while (curr) {
            ListNode* next_temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next_temp;
        }

        // 3. Merge lists
        ListNode *first = head, *second = prev;
        while (second) {
            ListNode *temp1 = first->next, *temp2 = second->next;
            first->next = second;
            second->next = temp1;
            first = temp1;
            second = temp2;
        }
    }
};
```

#### [Palindrome Linked List](https://leetcode.com/problems/palindrome-linked-list/)

**Approach Summary**: Similar to "Reorder List". Find the middle, reverse the second half, and then use two pointers (one at the head, one at the start of the reversed second half) to compare the node values.

```cpp
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) return true;
        ListNode *slow = head, *fast = head;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode *prev = nullptr, *curr = slow->next;
        while (curr) {
            ListNode* next_temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next_temp;
        }

        ListNode *p1 = head, *p2 = prev;
        while (p2) {
            if (p1->val != p2->val) return false;
            p1 = p1->next;
            p2 = p2->next;
        }
        return true;
    }
};
```

### Cyclic Detection

This pattern uses the logic from linked list cycles to find duplicates or cycles in arrays. The array indices act like pointers. `arr[i]` tells you the next "node" to visit.

#### (\*) [Find the Duplicate Number](https://leetcode.com/problems/find-the-duplicate-number/)

**Approach Summary**: Treat the array as a linked list where `nums[i]` points to the next index. Since there's a duplicate number, there must be a cycle. Use the slow & fast pointer algorithm (Floyd's cycle-finding) to find the meeting point, then another pointer from the start to find the cycle's entry point, which is the duplicate number.

```cpp
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = nums[0];
        int fast = nums[0];
        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);

        slow = nums[0];
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};
```

#### [Circular Array Loop](https://leetcode.com/problems/circular-array-loop/)

**Approach Summary**: Iterate through each element of the array. For each element, use a slow and fast pointer to check for a cycle. The "next" index is calculated as `(current_index + nums[current_index]) % n`. Be careful with negative numbers. A valid cycle must have a length \> 1 and all its elements must have the same sign (all positive or all negative steps).

```cpp
class Solution {
public:
    int getNextIndex(vector<int>& nums, int i) {
        int n = nums.size();
        return (i + nums[i] % n + n) % n;
    }

    bool circularArrayLoop(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            if (nums[i] == 0) continue;

            int slow = i, fast = i;
            bool is_forward = nums[i] > 0;

            do {
                slow = getNextIndex(nums, slow);
                if ((nums[slow] > 0) != is_forward) break;

                fast = getNextIndex(nums, fast);
                if ((nums[fast] > 0) != is_forward) break;
                fast = getNextIndex(nums, fast);
                if ((nums[fast] > 0) != is_forward) break;

            } while (slow != fast);

            if (slow == fast && (nums[getNextIndex(nums, slow)] > 0) == is_forward) {
                 if (slow != getNextIndex(nums, slow)) {
                     return true;
                 }
            }
        }
        return false;
    }
};
```

Of course. Here is the continuation and completion of the detailed study guide on the **Two Pointers** technique, following the exact structure and format you requested.

---

#### [Reverse Prefix of Word](https://leetcode.com/problems/reverse-prefix-of-word/)

**Approach Summary**: First, find the index of the first occurrence of the character `ch`. If it's not found, return the original word. If it is found at index `idx`, use a two-pointer approach (`left=0`, `right=idx`) to reverse the prefix of the word up to and including that index.

```cpp
class Solution {
public:
    string reversePrefix(string word, char ch) {
        int idx = -1;
        for (int i = 0; i < word.length(); ++i) {
            if (word[i] == ch) {
                idx = i;
                break;
            }
        }
        if (idx != -1) {
            int left = 0, right = idx;
            while (left < right) {
                swap(word[left], word[right]);
                left++;
                right--;
            }
        }
        return word;
    }
};
```

#### [Reverse String II](https://leetcode.com/problems/reverse-string-ii/)

**Approach Summary**: Iterate through the string with a step of `2k`. For each segment, determine the start and end of the sub-segment to be reversed. This will be from the current position `i` to `min(i + k - 1, n - 1)`. Use a standard two-pointer reverse on this sub-segment.

```cpp
class Solution {
public:
    string reverseStr(string s, int k) {
        int n = s.length();
        for (int i = 0; i < n; i += 2 * k) {
            int left = i;
            int right = min(i + k - 1, n - 1);
            while (left < right) {
                swap(s[left], s[right]);
                left++;
                right--;
            }
        }
        return s;
    }
};
```

#### [Reverse Words in a String](https://leetcode.com/problems/reverse-words-in-a-string/)

**Approach Summary**: This is a multi-step two-pointer problem.

1.  Reverse the entire string.
2.  Use two pointers, `start` and `end`, to find each word in the reversed string.
3.  Reverse each individual word in place.
4.  Clean up any extra spaces.

<!-- end list -->

```cpp
class Solution {
public:
    string reverseWords(string s) {
        reverse(s.begin(), s.end());
        int store_idx = 0;
        for (int start = 0; start < s.length(); ++start) {
            if (s[start] != ' ') {
                if (store_idx != 0) s[store_idx++] = ' ';
                int end = start;
                while (end < s.length() && s[end] != ' ') {
                    s[store_idx++] = s[end++];
                }
                reverse(s.begin() + store_idx - (end - start), s.begin() + store_idx);
                start = end;
            }
        }
        s.erase(s.begin() + store_idx, s.end());
        return s;
    }
};
```

#### [Reverse Words in a String III](https://leetcode.com/problems/reverse-words-in-a-string-iii/)

**Approach Summary**: Iterate through the string to identify the boundaries of each word (words are separated by spaces). For each word found, use a two-pointer approach to reverse it in place.

```cpp
class Solution {
public:
    string reverseWords(string s) {
        int last_space = -1;
        int n = s.length();
        for (int i = 0; i <= n; ++i) {
            if (i == n || s[i] == ' ') {
                int left = last_space + 1;
                int right = i - 1;
                while (left < right) {
                    swap(s[left], s[right]);
                    left++;
                    right--;
                }
                last_space = i;
            }
        }
        return s;
    }
};
```

### Others

#### [Bag of Tokens](https://leetcode.com/problems/bag-of-tokens/)

**Approach Summary**: This is a greedy problem. Sort the tokens. Use two pointers, `left` and `right`.

- To gain score, you must play the smallest token face-up (`power >= tokens[left]`).
- To gain power, you must play the largest token face-down (`score > 0`).
  Always try to gain score first. If you can't, but you could potentially gain more score later, gain power.

<!-- end list -->

```cpp
class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        sort(tokens.begin(), tokens.end());
        int left = 0, right = tokens.size() - 1;
        int score = 0, maxScore = 0;
        while (left <= right) {
            if (power >= tokens[left]) {
                power -= tokens[left];
                score++;
                left++;
                maxScore = max(maxScore, score);
            } else if (score > 0) {
                power += tokens[right];
                score--;
                right--;
            } else {
                break;
            }
        }
        return maxScore;
    }
};
```

#### [DI String Match](https://leetcode.com/problems/di-string-match/)

**Approach Summary**: We need to construct a permutation of `[0...n]`. Use two pointers, `low = 0` and `high = n`, representing the smallest and largest available numbers. Iterate through the string `s`. If `s[i] == 'I'` (increase), we need a small number, so use `low` and increment it. If `s[i] == 'D'` (decrease), we need a large number, so use `high` and decrement it. Append the final remaining number at the end.

```cpp
class Solution {
public:
    vector<int> diStringMatch(string s) {
        int n = s.length();
        int low = 0, high = n;
        vector<int> result;
        for (char c : s) {
            if (c == 'I') {
                result.push_back(low++);
            } else {
                result.push_back(high--);
            }
        }
        result.push_back(low);
        return result;
    }
};
```

#### [Minimum Length of String After Deleting Similar Ends](https://leetcode.com/problems/minimum-length-of-string-after-deleting-similar-ends/)

**Approach Summary**: Use two pointers, `left` and `right`. If `s[left]` and `s[right]` are different, we can't delete anything, so the answer is `right - left + 1`. If they are the same, store the character. Move `left` forward as long as it points to the same character. Move `right` backward as long as it points to the same character. Repeat this process. The final answer is the length of the remaining substring.

```cpp
class Solution {
public:
    int minimumLength(string s) {
        int left = 0, right = s.length() - 1;
        while (left < right && s[left] == s[right]) {
            char c = s[left];
            while (left <= right && s[left] == c) left++;
            while (left <= right && s[right] == c) right--;
        }
        return right - left + 1;
    }
};
```

#### [Sentence Similarity III](https://leetcode.com/problems/sentence-similarity-iii/)

**Approach Summary**: Split the sentences into words. Use two pointers `left1`, `right1` for `sentence1` and `left2`, `right2` for `sentence2`. Match common prefixes by moving the `left` pointers. Then match common suffixes by moving the `right` pointers. If `left2 > right2`, it means all words in `sentence2` were matched either as a prefix or a suffix of `sentence1`, so it's a valid insertion.

```cpp
class Solution {
public:
    bool areSentencesSimilar(string sentence1, string sentence2) {
        deque<string> words1, words2;
        string word;
        stringstream ss1(sentence1);
        while (ss1 >> word) words1.push_back(word);
        stringstream ss2(sentence2);
        while (ss2 >> word) words2.push_back(word);

        if (words1.size() < words2.size()) swap(words1, words2);

        while (!words2.empty() && words1.front() == words2.front()) {
            words1.pop_front();
            words2.pop_front();
        }
        while (!words2.empty() && words1.back() == words2.back()) {
            words1.pop_back();
            words2.pop_back();
        }

        return words2.empty();
    }
};
```

#### [Find K Closest Elements](https://leetcode.com/problems/find-k-closest-elements/)

**Approach Summary**: Use two pointers, `left` and `right`, to define a window of size greater than `k`. The goal is to shrink this window to size `k` by removing the element that is farther from `x`. If `x - arr[left]` is greater than `arr[right] - x`, the left element is farther, so increment `left`. Otherwise, decrement `right`. Repeat until the window size is `k`.

```cpp
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int left = 0, right = arr.size() - 1;
        while (right - left + 1 > k) {
            if (x - arr[left] > arr[right] - x) {
                left++;
            } else {
                right--;
            }
        }
        return vector<int>(arr.begin() + left, arr.begin() + right + 1);
    }
};
```

#### [Shortest Distance to a Character](https://leetcode.com/problems/shortest-distance-to-a-character/)

**Approach Summary**: This can be solved with two passes, which is a form of two-pointer thinking.

1.  **Left-to-Right Pass**: Iterate from left to right. Keep track of the index of the most recently seen `C`, say `prev`. The distance for the current cell `i` is `i - prev`.
2.  **Right-to-Left Pass**: Iterate from right to left. Again, track the most recent `prev`. The distance is `prev - i`.
    The final answer for each cell is the minimum of the distances calculated in the two passes.

<!-- end list -->

```cpp
class Solution {
public:
    vector<int> shortestToChar(string s, char c) {
        int n = s.length();
        vector<int> result(n, n);
        int prev = -n;

        for (int i = 0; i < n; ++i) {
            if (s[i] == c) prev = i;
            result[i] = i - prev;
        }

        prev = 2 * n;
        for (int i = n - 1; i >= 0; --i) {
            if (s[i] == c) prev = i;
            result[i] = min(result[i], prev - i);
        }

        return result;
    }
};
```

---

## 2\. Slow & Fast Pointers

In this pattern, two pointers move through the data at different speeds. They typically both start from the left end. The `fast` pointer advances to explore the data, while the `slow` pointer advances under specific conditions, often to a position determined by the `fast` pointer. This is famously used for cycle detection (Floyd's Tortoise and Hare algorithm).

### Linked List Operations

This is the most common application of the slow & fast pointer technique.

#### (\*) [Linked List Cycle](https://leetcode.com/problems/linked-list-cycle/)

**Approach Summary**: Use a `slow` pointer that moves one step at a time and a `fast` pointer that moves two steps. If there is a cycle, the `fast` pointer will eventually lap the `slow` pointer, and they will meet. If `fast` reaches `nullptr`, there is no cycle.

```cpp
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                return true;
            }
        }
        return false;
    }
};
```

#### [Linked List Cycle II](https://leetcode.com/problems/linked-list-cycle-ii/)

**Approach Summary**: First, use the slow & fast pointer method to detect a cycle and find the meeting point. Once they meet, reset one pointer (e.g., `slow`) back to the `head`. Then, move both `slow` and `fast` one step at a time. The point where they meet again is the start of the cycle.

```cpp
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                slow = head;
                while (slow != fast) {
                    slow = slow->next;
                    fast = fast->next;
                }
                return slow;
            }
        }
        return nullptr;
    }
};
```

#### [Remove Nth Node From End of List](https://leetcode.com/problems/remove-nth-node-from-end-of-list/)

**Approach Summary**: Use two pointers, `fast` and `slow`. First, advance the `fast` pointer `n` steps ahead of `slow`. Then, move both pointers one step at a time until `fast` reaches the end of the list. At this point, `slow` will be pointing to the node _just before_ the one to be deleted.

```cpp
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0, head);
        ListNode* slow = dummy, *fast = dummy;
        for (int i = 0; i < n; ++i) {
            fast = fast->next;
        }
        while (fast->next) {
            slow = slow->next;
            fast = fast->next;
        }
        slow->next = slow->next->next;
        return dummy->next;
    }
};
```

#### [Rotate List](https://leetcode.com/problems/rotate-list/)

**Approach Summary**: First, find the length of the list and connect the tail to the head to form a cycle. The new tail will be at position `length - (k % length) - 1`. The new head will be the node after the new tail. Use a pointer to traverse to the new tail, break the cycle, and return the new head.

```cpp
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head || !head->next || k == 0) return head;
        int len = 1;
        ListNode* tail = head;
        while (tail->next) {
            tail = tail->next;
            len++;
        }
        tail->next = head; // Form a cycle

        int steps_to_new_tail = len - (k % len) - 1;
        ListNode* new_tail = head;
        for (int i = 0; i < steps_to_new_tail; ++i) {
            new_tail = new_tail->next;
        }

        ListNode* new_head = new_tail->next;
        new_tail->next = nullptr; // Break the cycle
        return new_head;
    }
};
```

#### [Reorder List](https://leetcode.com/problems/reorder-list/)

**Approach Summary**: This is a three-step process:

1.  **Find Middle**: Use a slow and fast pointer to find the middle of the linked list.
2.  **Reverse Second Half**: Reverse the second half of the list starting from the node after the middle.
3.  **Merge**: Merge the first half and the reversed second half by interleaving their nodes.

<!-- end list -->

```cpp
class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head || !head->next) return;
        // 1. Find middle
        ListNode *slow = head, *fast = head;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // 2. Reverse second half
        ListNode *prev = nullptr, *curr = slow->next;
        slow->next = nullptr;
        while (curr) {
            ListNode* next_temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next_temp;
        }

        // 3. Merge lists
        ListNode *first = head, *second = prev;
        while (second) {
            ListNode *temp1 = first->next, *temp2 = second->next;
            first->next = second;
            second->next = temp1;
            first = temp1;
            second = temp2;
        }
    }
};
```

#### [Palindrome Linked List](https://leetcode.com/problems/palindrome-linked-list/)

**Approach Summary**: Similar to "Reorder List". Find the middle, reverse the second half, and then use two pointers (one at the head, one at the start of the reversed second half) to compare the node values.

```cpp
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) return true;
        ListNode *slow = head, *fast = head;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode *prev = nullptr, *curr = slow->next;
        while (curr) {
            ListNode* next_temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next_temp;
        }

        ListNode *p1 = head, *p2 = prev;
        while (p2) {
            if (p1->val != p2->val) return false;
            p1 = p1->next;
            p2 = p2->next;
        }
        return true;
    }
};
```

### Cyclic Detection

This pattern uses the logic from linked list cycles to find duplicates or cycles in arrays. The array indices act like pointers. `arr[i]` tells you the next "node" to visit.

#### (\*) [Find the Duplicate Number](https://leetcode.com/problems/find-the-duplicate-number/)

**Approach Summary**: Treat the array as a linked list where `nums[i]` points to the next index. Since there's a duplicate number, there must be a cycle. Use the slow & fast pointer algorithm (Floyd's cycle-finding) to find the meeting point, then another pointer from the start to find the cycle's entry point, which is the duplicate number.

```cpp
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = nums[0];
        int fast = nums[0];
        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);

        slow = nums[0];
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};
```

#### [Circular Array Loop](https://leetcode.com/problems/circular-array-loop/)

**Approach Summary**: Iterate through each element of the array. For each element, use a slow and fast pointer to check for a cycle. The "next" index is calculated as `(current_index + nums[current_index]) % n`. Be careful with negative numbers. A valid cycle must have a length \> 1 and all its elements must have the same sign (all positive or all negative steps).

```cpp
class Solution {
public:
    int getNextIndex(vector<int>& nums, int i) {
        int n = nums.size();
        return (i + nums[i] % n + n) % n;
    }

    bool circularArrayLoop(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            if (nums[i] == 0) continue;

            int slow = i, fast = i;
            bool is_forward = nums[i] > 0;

            do {
                slow = getNextIndex(nums, slow);
                if ((nums[slow] > 0) != is_forward) break;

                fast = getNextIndex(nums, fast);
                if ((nums[fast] > 0) != is_forward) break;
                fast = getNextIndex(nums, fast);
                if ((nums[fast] > 0) != is_forward) break;

            } while (slow != fast);

            if (slow == fast && (nums[getNextIndex(nums, slow)] > 0) == is_forward) {
                 if (slow != getNextIndex(nums, slow)) {
                     return true;
                 }
            }
        }
        return false;
    }
};
```

Of course. Here is the final part of your detailed study guide on the **Two Pointers** technique, covering Sections 3 and 4.

---

## 3\. Running from Beginning of 2 Arrays / Merging 2 Arrays

In this pattern, you are given two separate collections (arrays, lists, etc.), and you use a pointer for each one, typically starting from the beginning. These pointers advance through their respective collections based on comparisons between the elements they point to. This is the core logic behind merging sorted lists, finding intersections, and comparing subsequences.

### Sorted arrays

When both arrays are sorted, this pattern is incredibly efficient. The pointers advance based on which element is smaller, allowing you to process both arrays in a single, combined pass.

#### (\*) [Merge Sorted Array](https://leetcode.com/problems/merge-sorted-array/)

**Approach Summary**: Since `nums1` has space at the end, we can merge the arrays in reverse to avoid overwriting elements. Use three pointers: `p1` at the end of `nums1`'s initial elements, `p2` at the end of `nums2`, and `p_write` at the very end of `nums1`'s allocated space. Compare `nums1[p1]` and `nums2[p2]` and place the larger one at `p_write`. Decrement the pointers accordingly.

```cpp
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int p1 = m - 1;
        int p2 = n - 1;
        int p_write = m + n - 1;

        while (p2 >= 0) {
            if (p1 >= 0 && nums1[p1] > nums2[p2]) {
                nums1[p_write] = nums1[p1];
                p1--;
            } else {
                nums1[p_write] = nums2[p2];
                p2--;
            }
            p_write--;
        }
    }
};
```

#### [Heaters](https://leetcode.com/problems/heaters/)

**Approach Summary**: Sort both `houses` and `heaters`. For each house, we need to find the closest heater. This can be the heater just to its left or just to its right. Use a pointer `i` for heaters. For each `house`, advance `i` as long as `heaters[i]` is to the left or at the same position of the `house`. The closest distance for that house will be `min(house - heaters[i-1], heaters[i] - house)`. The answer is the maximum of these minimum distances over all houses.

```cpp
class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        int max_radius = 0;
        int i = 0;
        for (int house : houses) {
            while (i + 1 < heaters.size() && heaters[i + 1] <= house) {
                i++;
            }
            int dist1 = abs(house - heaters[i]);
            int dist2 = (i + 1 < heaters.size()) ? abs(heaters[i + 1] - house) : INT_MAX;
            max_radius = max(max_radius, min(dist1, dist2));
        }
        return max_radius;
    }
};
```

#### [Find the Distance Value Between Two Arrays](https://leetcode.com/problems/find-the-distance-value-between-two-arrays/)

**Approach Summary**: For each element `x` in `arr1`, we need to check if there is any element `y` in `arr2` such that `|x - y| <= d`. To do this efficiently, sort `arr2`. Then for each `x` in `arr1`, use binary search (or two pointers) on `arr2` to quickly check if such a `y` exists.

```cpp
class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        sort(arr2.begin(), arr2.end());
        int distance_value = 0;
        for (int val : arr1) {
            int left = 0, right = arr2.size() - 1;
            bool found = false;
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (abs(val - arr2[mid]) <= d) {
                    found = true;
                    break;
                } else if (arr2[mid] < val) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            if (!found) {
                distance_value++;
            }
        }
        return distance_value;
    }
};
```

### Intersections/LCA like

This pattern involves finding common elements or meeting points between two data structures.

#### (\*) [Intersection of Two Linked Lists](https://leetcode.com/problems/intersection-of-two-linked-lists/)

**Approach Summary**: A clever trick. Use two pointers, `p1` starting at `headA` and `p2` at `headB`. Traverse the lists. When a pointer reaches the end of its list, redirect it to the head of the _other_ list. This equalizes the path length they travel. If they intersect, they will meet at the intersection node. If they don't, they will both reach `nullptr` at the same time.

```cpp
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *p1 = headA;
        ListNode *p2 = headB;
        while (p1 != p2) {
            p1 = p1 ? p1->next : headB;
            p2 = p2 ? p2->next : headA;
        }
        return p1;
    }
};
```

#### [Intersection of Two Arrays](https://leetcode.com/problems/intersection-of-two-arrays/)

**Approach Summary**: Sort both arrays. Use a pointer `i` for `nums1` and `j` for `nums2`.

- If `nums1[i] < nums2[j]`, increment `i`.
- If `nums1[i] > nums2[j]`, increment `j`.
- If they are equal, you've found an intersection. Add it to the result and increment both pointers, making sure to skip any further duplicates.

<!-- end list -->

```cpp
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        int i = 0, j = 0;
        vector<int> result;
        while (i < nums1.size() && j < nums2.size()) {
            if (nums1[i] < nums2[j]) {
                i++;
            } else if (nums1[i] > nums2[j]) {
                j++;
            } else {
                if (result.empty() || result.back() != nums1[i]) {
                    result.push_back(nums1[i]);
                }
                i++;
                j++;
            }
        }
        return result;
    }
};
```

#### [Intersection of Two Arrays II](https://leetcode.com/problems/intersection-of-two-arrays-ii/)

**Approach Summary**: The same as the previous problem, but we don't skip duplicates. When `nums1[i] == nums2[j]`, add the element to the result and increment both pointers. This correctly handles multiple occurrences.

```cpp
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        int i = 0, j = 0;
        vector<int> result;
        while (i < nums1.size() && j < nums2.size()) {
            if (nums1[i] < nums2[j]) {
                i++;
            } else if (nums1[i] > nums2[j]) {
                j++;
            } else {
                result.push_back(nums1[i]);
                i++;
                j++;
            }
        }
        return result;
    }
};
```

### SubString

This pattern uses two pointers to check if one string is a subsequence or substring of another.

#### (\*) [Implement strStr()](https://leetcode.com/problems/implement-strstr/)

**Approach Summary**: A naive approach uses two pointers. The outer loop pointer `i` iterates through `haystack`. The inner loop pointer `j` iterates through `needle`. For each `i`, we check if the substring `haystack[i...i+len(needle)-1]` matches `needle`. More advanced algorithms like KMP are more efficient but the two-pointer concept is the base.

```cpp
class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty()) return 0;
        int h_len = haystack.length();
        int n_len = needle.length();
        for (int i = 0; i <= h_len - n_len; ++i) {
            int j = 0;
            for (; j < n_len; ++j) {
                if (haystack[i + j] != needle[j]) {
                    break;
                }
            }
            if (j == n_len) {
                return i;
            }
        }
        return -1;
    }
};
```

#### [Longest Word in Dictionary through Deleting](https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/)

**Approach Summary**: Iterate through each word in the `dictionary`. For each word, use two pointers to check if it's a subsequence of `s`. One pointer `i` for `s` and one pointer `j` for the `word`. If `s[i] == word[j]`, increment `j`. Always increment `i`. If `j` reaches the end of the `word`, it's a valid subsequence. Keep track of the longest valid word found (with lexicographical tie-breaking).

```cpp
class Solution {
public:
    bool isSubsequence(const string& s, const string& word) {
        int i = 0, j = 0;
        while (i < s.length() && j < word.length()) {
            if (s[i] == word[j]) {
                j++;
            }
            i++;
        }
        return j == word.length();
    }

    string findLongestWord(string s, vector<string>& dictionary) {
        string longest_word = "";
        for (const string& word : dictionary) {
            if (isSubsequence(s, word)) {
                if (word.length() > longest_word.length() ||
                   (word.length() == longest_word.length() && word < longest_word)) {
                    longest_word = word;
                }
            }
        }
        return longest_word;
    }
};
```

#### [Long Pressed Name](https://leetcode.com/problems/long-pressed-name/)

**Approach Summary**: Use two pointers, `i` for `name` and `j` for `typed`. If `name[i] == typed[j]`, increment both. If they are different, check if `typed[j]` is a "long press" of the previous character in `name` (`typed[j] == name[i-1]`). If it is, just increment `j`. Otherwise, it's a mismatch. Finally, ensure all remaining characters in `typed` are long presses of the last character of `name`.

```cpp
class Solution {
public:
    bool isLongPressedName(string name, string typed) {
        int i = 0, j = 0;
        while (j < typed.length()) {
            if (i < name.length() && name[i] == typed[j]) {
                i++;
                j++;
            } else if (j > 0 && typed[j] == typed[j - 1]) {
                j++;
            } else {
                return false;
            }
        }
        return i == name.length();
    }
};
```

---

(Note: Some problems like Median Finder, Meet-in-the-middle, and others listed are very advanced and often rely on more than just the basic two-pointer pattern, frequently combining it with heaps, binary search, or complex data structures.)

---

## 4\. Split & Merge of an Array / Divide & Conquer

This pattern involves breaking a data structure (usually a linked list) into two parts, processing them individually (often recursively or with other pointer techniques), and then merging the results back together.

### Partition

#### (\*) [Partition List](https://leetcode.com/problems/partition-list/)

**Approach Summary**: Use two "dummy" head nodes, `less_head` and `greater_head`, to build two separate lists. Iterate through the original list with a pointer `curr`. If `curr->val < x`, append it to the `less` list. Otherwise, append it to the `greater` list. Finally, connect the tail of the `less` list to the head of the `greater` list and null-terminate the `greater` list.

```cpp
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode less_head(0);
        ListNode greater_head(0);
        ListNode* less_tail = &less_head;
        ListNode* greater_tail = &greater_head;

        ListNode* curr = head;
        while (curr) {
            if (curr->val < x) {
                less_tail->next = curr;
                less_tail = less_tail->next;
            } else {
                greater_tail->next = curr;
                greater_tail = greater_tail->next;
            }
            curr = curr->next;
        }

        greater_tail->next = nullptr;
        less_tail->next = greater_head.next;

        return less_head.next;
    }
};
```

### Sorting

#### (\*) [Sort List](https://leetcode.com/problems/sort-list/)

**Approach Summary**: This is a classic Merge Sort for a linked list.

1.  **Split**: Use a slow and fast pointer to find the middle of the list and split it into two halves.
2.  **Conquer**: Recursively call `sortList` on both halves.
3.  **Merge**: Use a standard two-pointer merge algorithm to merge the two now-sorted halves into a single sorted list.

<!-- end list -->

```cpp
class Solution {
public:
    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        tail->next = l1 ? l1 : l2;
        return dummy.next;
    }

    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }
        // 1. Split list
        ListNode *slow = head, *fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode* mid = slow->next;
        slow->next = nullptr;

        // 2. Conquer
        ListNode* left = sortList(head);
        ListNode* right = sortList(mid);

        // 3. Merge
        return merge(left, right);
    }
};
```
