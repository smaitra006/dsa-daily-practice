//* LeetCode Questions on Monotonic Stacks

#include <bits/stdc++.h>
using namespace std;

//? 739. Daily Temperatures
//? Given an array of integers temperatures represents the daily temperatures,
//return an array
// answer such that answer[i] is the number of days you have to wait after the
// ith day to get a warmer temperature. If there is no future day for which this
// is possible, keep answer[i] == 0 instead.

//* Topics : Stack, Monotonic stack

//* Intuition :
// Here we need to return the number of days what we have to wait to get e
// warmer temperature. So we need to wait till we get a greater temperature to
// the right of our current temperature. So this resembles next greater element
// to the right. Just a twist that here we need to return the number of days
// between them, so we store the indices and do the calculation accordingly.

//* Solution

class Solution {
public:
  vector<int> dailyTemperatures(vector<int> &temperatures) {
    int n = temperatures.size(); // Size of the given array
    vector<int> result(n,
                       0); // Acoording to question if no such day found then 0
    stack<int> st;         // This will be our monotonically decreasing stack

    for (int i = n - 1; i >= 0; i--) { // Traverse from right to left

      // Pop elements smaller than the current element
      while (!st.empty() && temperatures[i] >= temperatures[st.top()]) {
        st.pop();
      }
      // If stack is not empty (i.e a day is found) then at that location of the
      // result vector put the indices difference
      if (!st.empty()) {
        result[i] = st.top() - i;
      }
      // Push the current element into the stack
      st.push(i);
    }
    return result;
  }
};

//* Time Complexity : O(n)
//* Space Complexity : O(n)

// ------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------

//? 84. Largest Rectangle in Histogram
//? Given an array of integers heights representing the histogram's bar height
//where the width of
// each bar is 1, return the area of the largest rectangle in the histogram.

// TODO : REVISION IS A MUST

//* Topics : Stack, Monotonic stack

//* Intuition of brute force approach :
// Here I will find all the possible rectangles, their area, and their find the
// maximum among them

//* Solution :

class Solution {
public:
  int largestRectangleArea(vector<int> &heights) {
    int n = heights.size();
    int maxArea = 0;

    for (int i = 0; i < n; i++) {
      int minHeight = heights[i];

      // Expand to the left and right from index i
      for (int j = i; j < n; j++) {
        minHeight = min(minHeight, heights[j]);
        int width = j - i + 1;
        int area = minHeight * width;
        maxArea = max(maxArea, area);
      }
    }

    return maxArea;
  }
};

//* Time Complexity : O(n^2)
//* Space Complexity : O(1)

//* Intuition of optimized approach :
// Here I need the rectangle with maximum area. Now for each bar I will try to
// find the maximum possible area and find the maximum among them. Now for this
// currArea the height will be the height of my bar. The main twist is the
// width, for width I need the next smallest element left to the current element
// which will be my start and I also need the next smallest element right to the
// current element which will be my end. Now this (end - start -1) will be my
// width. Then my maxArea will be the maximum of maxArea and currArea;

//* Solution :

class Solution {
public:
  void findEnd(
      vector<int> &heights,
      vector<int> &end) { // Find the start (Next smallest element to the left)
    int n = heights.size();
    stack<int> st;

    for (int i = n - 1; i >= 0; i--) {
      while (!st.empty() && heights[i] <= heights[st.top()]) {
        st.pop();
      }
      if (!st.empty()) {
        end[i] = (st.top());
      }
      st.push(i);
    }
  }

  void findStart(
      vector<int> &heights,
      vector<int> &start) { // Find the end (Next smallest element to the right)
    int n = heights.size();
    stack<int> st;

    for (int i = 0; i < n; i++) {
      while (!st.empty() && heights[i] <= heights[st.top()]) {
        st.pop();
      }
      if (!st.empty()) {
        start[i] = (st.top());
      }
      st.push(i);
    }
  }

  int largestRectangleArea(vector<int> &heights) {
    int maxArea = 0; // Maximum area
    int n = heights.size();
    vector<int> end(n, n);    // Will contain the end index for each height
    vector<int> start(n, -1); // Will contain the start index for each height

    findStart(heights, start);
    findEnd(heights, end);

    for (int i = 0; i < n; i++) { // Iterate through each height
      int currArea = heights[i] * (end[i] - start[i] - 1); // Current area
      maxArea = max(maxArea, currArea); // Updating maximum area
    }
    return maxArea;
  }
};

//* Time Complexity : O(n)
//* Space Complexity : O(n)

// ------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------

//? 907. Sum of Subarray Minimums
//? Given an array of integers arr, find the sum of min(b), where b ranges over
//every (contiguous)
// subarray of arr. Since the answer may be large, return the answer modulo 109

//* Topics : Stack, Monotonic stack

//* Intuition of brute force approach :
// Find all the subarrays, find minimum in each of them and add it to the

//* Solution :
class Solution {
public:
  int sumSubarrayMins(vector<int> &arr) {
    const int MOD = 1e9 + 7;
    long long ans = 0, n = arr.size();

    for (int i = 0; i < n; i++) {
      for (int j = i; j < n; j++) {
        int min = INT_MAX;
        for (int k = i; k <= j; k++) {
          if (arr[k] < min)
            min = arr[k];
        }
        ans += min;
      }
    }
    return (ans % MOD);
  }
};

//* Time Complexity : O(n^3) - n^2 for finding all subarray and another n for
//finding minimum each
// time
//* Space Complexity : O(1)

//* Intuition of Optimal approach :
// Here in a range where the current element in the smallest element , any
// subarray formed in that range including the current element will have the
// current element at its minimum element. Hence to the left of the current
// element we find the left smallest element and to the right to the current
// element we find the next smallest element. In between these two , any
// subarray we form including the current element will have current element as
// minimum. So that number of subarrays will be (number of elements in left) *
// (numbers of elements in right) and the contiribution of the element in the
// total sum will be (number of elements in left) * (numbers of elements in
// right) * (curr element value).

//* Solution :

class Solution {
public:
  // Find the previous smaller element's index for each element
  void findPrevSmaller(vector<int> &arr, vector<int> &prevSmaller) {
    int n = arr.size();
    stack<int> st; // Stack stores indices, not values

    for (int i = 0; i < n; i++) {
      // Pop elements that are >= current element
      while (!st.empty() && arr[st.top()] >= arr[i]) {
        st.pop();
      }

      // If stack is not empty, top contains index of previous smaller element
      if (!st.empty()) {
        prevSmaller[i] = st.top();
      }
      // If stack is empty, no previous smaller element exists (stays -1)

      st.push(i); // Push current index
    }
  }

  // Find the next smaller OR EQUAL element's index for each element
  void findNextSmaller(vector<int> &arr, vector<int> &nextSmaller) {
    int n = arr.size();
    stack<int> st; // Stack stores indices, not values

    for (int i = n - 1; i >= 0; i--) {
      // Pop elements that are > current element (strict inequality)
      while (!st.empty() && arr[st.top()] > arr[i]) {
        st.pop();
      }

      // If stack is not empty, top contains index of next smaller/equal element
      if (!st.empty()) {
        nextSmaller[i] = st.top();
      }
      // If stack is empty, no next smaller/equal element exists (stays n)

      st.push(i); // Push current index
    }
  }

  int sumSubarrayMins(vector<int> &arr) {
    const int MOD = 1e9 + 7; // For handling large numbers
    int n = arr.size();

    // Initialize with boundary values
    vector<int> prevSmaller(n, -1); // -1 means no previous smaller element
    vector<int> nextSmaller(n, n);  // n means no next smaller element

    // Find previous and next smaller elements
    findPrevSmaller(arr, prevSmaller);
    findNextSmaller(arr, nextSmaller);

    long long ans = 0;

    for (int i = 0; i < n; i++) {
      // Calculate number of subarrays where arr[i] is the minimum
      // Left side: elements from (prevSmaller[i] + 1) to i
      int leftCount = i - prevSmaller[i];

      // Right side: elements from i to (nextSmaller[i] - 1)
      int rightCount = nextSmaller[i] - i;

      // Total subarrays where arr[i] is minimum = leftCount * rightCount
      long long contribution = (1LL * arr[i] * leftCount * rightCount) % MOD;
      ans = (ans + contribution) % MOD;
    }

    return ans;
  }
};

//* Time Complexity : O(n)
//* Space Complexity : O(n)
