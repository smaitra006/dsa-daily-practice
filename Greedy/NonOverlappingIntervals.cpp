#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Non-overlapping Intervals (LeetCode 435)
//
// Task:
// Given an array of intervals intervals where intervals[i] = [starti, endi],
// return the minimum number of intervals you need to remove to make the rest
// of the intervals non-overlapping.
//
// Example:
//   Input:  intervals = [[1,2],[2,3],[3,4],[1,3]]
//   Output: 1
//   Explanation: Remove [1,3] to make the rest non-overlapping.
//
//   Input:  intervals = [[1,2],[1,2],[1,2]]
//   Output: 2
//
//   Input:  intervals = [[1,2],[2,3]]
//   Output: 0
//
// Approach (Greedy - Sort by End Time):
// 1. Sort intervals by their end time in ascending order.
// 2. Initialize lastEnd with the end of the first interval.
// 3. Traverse intervals from the second one onward:
//      - If the current interval starts before lastEnd → overlap → remove it (cnt++).
//      - Otherwise, update lastEnd to the current interval's end.
// 4. Return cnt (minimum removals).
//==============================================================================

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals)
    {
        if (intervals.empty()) return 0;

        // Sort intervals by their end time
        sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
            return a[1] < b[1];
            });

        int cnt = 0;                  // count of removed intervals
        int lastEnd = intervals[0][1]; // end of last non-overlapping interval

        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] < lastEnd) {
                // Overlap → remove current interval
                cnt++;
            }
            else {
                // No overlap → update boundary
                lastEnd = intervals[i][1];
            }
        }

        return cnt;
    }
};

//==============================================================================
// Complexity Analysis:
// - Sorting: O(N log N), where N = number of intervals.
// - Traversal: O(N).
// - Total: O(N log N).
// - Space: O(1) (in-place sort).
//
// Example Walkthrough:
// Input:  [[1,2],[2,3],[3,4],[1,3]]
// Sorted: [[1,2],[1,3],[2,3],[3,4]]
// Step1: lastEnd = 2
// Step2: [1,3] overlaps → cnt=1
// Step3: [2,3] does not overlap → update lastEnd=3
// Step4: [3,4] does not overlap → update lastEnd=4
// Output: 1
//==============================================================================
