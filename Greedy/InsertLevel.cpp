#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Insert Interval (LeetCode 57)
//
// Task:
// You are given an array of non-overlapping intervals where intervals[i] = [start, end]
// represent the start and end of an interval, and intervals is sorted in ascending
// order by start. You are also given a new interval newInterval = [start, end].
//
// Insert newInterval into intervals such that the intervals remain sorted in
// ascending order by start, and merge overlapping intervals if necessary.
// Return the resulting list of intervals.
//
// Example:
//   Input:  intervals = [[1,3],[6,9]], newInterval = [2,5]
//   Output: [[1,5],[6,9]]
//
//   Input:  intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
//   Output: [[1,2],[3,10],[12,16]]
//
// Approach:
// 1. Append the new interval to the list.
// 2. Sort intervals by starting time.
// 3. Initialize result with the first interval.
// 4. Iterate through all intervals:
//      - If current interval overlaps with the last in result, merge them.
//      - Otherwise, push the current interval into result.
// 5. Return result after merging.
//==============================================================================

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval)
    {
        intervals.push_back(newInterval);
        sort(intervals.begin(), intervals.end());

        vector<vector<int>> res;
        res.push_back(intervals[0]);

        for (int i = 1; i < intervals.size(); ++i) {
            if (res.back()[1] >= intervals[i][0]) {
                // Merge overlapping intervals
                res.back()[1] = max(res.back()[1], intervals[i][1]);
            }
            else {
                res.push_back(intervals[i]);
            }
        }

        return res;
    }
};

//==============================================================================
// Complexity Analysis:
// - Sorting: O(N log N), where N = number of intervals + 1 (after adding newInterval).
// - Merging: O(N), linear scan of intervals.
// - Total: O(N log N).
// - Space: O(N) for storing result.
//
// Example Walkthrough:
// Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
// Step1: Append → [[1,3],[6,9],[2,5]]
// Step2: Sort   → [[1,3],[2,5],[6,9]]
// Step3: Merge  → [[1,5],[6,9]]
// Output: [[1,5],[6,9]]
//==============================================================================
