#include <bits/stdc++.h>
using namespace std;

/* ==============================================================================
 * LeetCode 349: Intersection of Two Arrays
 * ==============================================================================
 * Problem:
 * Given two integer arrays `nums1` and `nums2`, return their intersection. Each
 * element in the result must be unique, and the result can be in any order.
 *
 * Approach 1: HashSet for Lookup
 * - Insert all elements of `nums1` into a set `st1`.
 * - Traverse `nums2` and if an element exists in `st1`, add it to result set `st2`.
 * - Convert `st2` to a vector.
 *
 * Time Complexity: O(n + m)
 * Space Complexity: O(n + m)
 * ============================================================================= */

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2)
    {
        unordered_set<int> st1, st2;

        for (int num : nums1) {
            st1.insert(num);
        }

        for (int num : nums2) {
            if (st1.count(num)) {
                st2.insert(num);
            }
        }

        return vector<int>(st2.begin(), st2.end());
    }
};

/* ==============================================================================
 * Approach 2: One Set + Erase Optimization
 * - Use one unordered set for `nums1`.
 * - As soon as a matching element is found in `nums2`, add to result and erase
 *   from the set to avoid duplicates.
 *
 * Time Complexity: O(n + m)
 * Space Complexity: O(n)
 * ============================================================================= */

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2)
    {
        unordered_set<int> st(nums1.begin(), nums1.end());
        vector<int> ans;

        for (int num : nums2) {
            if (st.count(num)) {
                ans.push_back(num);
                st.erase(num);  // Ensure uniqueness
            }
        }

        return ans;
    }
};

/* ==============================================================================
 * Approach 3: Sorting + Two-Pointer
 * - Sort both arrays and use two pointers to find matching elements.
 * - Skip duplicates to maintain uniqueness.
 *
 * Time Complexity: O(n log n + m log m)
 * Space Complexity: O(1) extra (not counting output)
 * ============================================================================= */

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2)
    {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());

        int i = 0, j = 0;
        vector<int> ans;

        while (i < nums1.size() && j < nums2.size()) {
            if (nums1[i] == nums2[j]) {
                if (ans.empty() || ans.back() != nums1[i]) {
                    ans.push_back(nums1[i]);
                }
                i++; j++;
            }
            else if (nums1[i] < nums2[j]) {
                i++;
            }
            else {
                j++;
            }
        }

        return ans;
    }
};

/* ==============================================================================
 * Approach 4: Binary Search (when one array is much larger & sorted)
 * - Sort the larger array.
 * - For each unique element in the smaller array, binary search for existence.
 *
 * Time Complexity: O(n log m) where m is the size of the sorted array
 * Space Complexity: O(1) extra
 * ============================================================================= */

class Solution {
public:
    bool binarySearch(vector<int>& arr, int target)
    {
        int low = 0, high = arr.size() - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (arr[mid] == target) return true;
            else if (arr[mid] < target) low = mid + 1;
            else high = mid - 1;
        }
        return false;
    }

    vector<int> intersection(vector<int>& nums1, vector<int>& nums2)
    {
        if (nums1.size() > nums2.size()) swap(nums1, nums2);

        sort(nums2.begin(), nums2.end());
        unordered_set<int> result;

        for (int num : nums1) {
            if (binarySearch(nums2, num)) {
                result.insert(num);
            }
        }

        return vector<int>(result.begin(), result.end());
    }
};

