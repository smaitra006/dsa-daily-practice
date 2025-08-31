#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Task Scheduler (LeetCode 621)
//
// Task:
// Given a char array `tasks` representing tasks CPU needs to do, and an integer `n`
// representing the cooldown period between two same tasks, return the least number
// of units of times the CPU will take to finish all the tasks.
//
// Example:
//   Input:  tasks = ['A','A','A','B','B','B'], n = 2
//   Output: 8
//   Explanation: A -> B -> idle -> A -> B -> idle -> A -> B
//
//   Input:  tasks = ['A','A','A','B','B','B'], n = 0
//   Output: 6
//
// Approach (Greedy + Max Heap):
// 1. Count the frequency of each task.
// 2. Push all non-zero frequencies into a max-heap (priority_queue).
// 3. Process tasks in cycles of length n+1 (cooldown period + 1):
//      - Assign the most frequent tasks first.
//      - If a task has remaining frequency, store it to be pushed back into heap.
//      - Increment time for each task executed or idle slot.
// 4. Repeat until all tasks are completed.
//==============================================================================

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n)
    {
        priority_queue<int> pq;
        vector<int> mp(26, 0);

        // Count frequency of each task
        for (char i : tasks) {
            mp[i - 'A']++;
        }

        // Push all task frequencies into max-heap
        for (int i = 0; i < 26; ++i) {
            if (mp[i]) pq.push(mp[i]);
        }

        int time = 0; // total time taken

        // Process tasks
        while (!pq.empty()) {
            vector<int> remain;
            int cycle = n + 1; // cycle length including cooldown

            while (cycle && !pq.empty()) {
                int max_freq = pq.top();
                pq.pop();

                if (max_freq > 1) {
                    remain.push_back(max_freq - 1); // push remaining frequency back
                }

                ++time;
                --cycle;
            }

            // Push remaining tasks back into heap
            for (int count : remain) {
                pq.push(count);
            }

            if (pq.empty()) break; // all tasks completed
            time += cycle;          // count idle time if any
        }

        return time;
    }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(N + T log T), where N = number of tasks, T = number of unique tasks.
// - Space: O(T), for max-heap and frequency map.
//
// Example Walkthrough:
// Input: tasks = ['A','A','A','B','B','B'], n=2
// Frequencies: A=3, B=3 → max-heap: [3,3]
// Cycle1: A,B → idle → time=3
// Cycle2: A,B → idle → time=6
// Cycle3: A,B → time=8
// Output: 8
//==============================================================================
