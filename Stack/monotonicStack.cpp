//* Monotonic Stack in C++

//? What is a Monotonic Stack?
// A monotonic stack is a stack that is either:
//  Monotonically increasing (top element is always greater or equal)
//  Monotonically decreasing (top element is always smaller or equal)

// It helps to solve problems like:
//  Next Greater Element
//  Next Smaller Element
//  Stock Span
//  Largest Rectangle in Histogram
//  Daily Temperatures

// Time Complexity:
//  Each element is pushed & popped once ➝ O(N)

#include <bits/stdc++.h>
using namespace std;

//* Template 1 : Next Smaller element

// Example: Find the next smaller element to the left for each element in the
// array

vector<int> nextSmallerToLeft(vector<int> &nums) {
  int n = nums.size();
  vector<int> ans(n, -1); // Initialize with -1
  stack<int> st;          // Stores indices (or values directly)

  for (int i = 0; i < n; i++) { // Traverse from left to right
    // Pop greater or equal elements from stack
    while (!st.empty() && st.top() >= nums[i]) {
      st.pop();
    }

    // If stack is not empty then top is the next smaller, else -1 (already
    // initialised)
    if (!st.empty()) {
      ans[i] = st.top();
    }

    // Push current element to stack
    st.push(nums[i]);
  }

  return ans;
}

// INTUITION: Stack stores potential "next smaller" elements. We scan from left
// to right. Greater elements are useless for future ones ➝ we pop them. Stack
// is now a monotonically increasing.

// For next smaller element to right just traverse from right to left with same
// logic

//* Template 2 : Next greater element to the right

// Example: Find next greater element to the right for each element in the array

vector<int> nextGreaterToRight(vector<int> &nums) {
  int n = nums.size();
  vector<int> ans(n, -1);
  stack<int> st;

  for (int i = n - 1; i >= 0; --i) { // Traverse from right to left
    // Pop smaller or equal elements from stack
    while (!st.empty() && st.top() <= nums[i]) {
      st.pop();
    }

    // If stack is not empty, top is the next greater
    if (!st.empty()) {
      ans[i] = st.top();
    }

    // Push current element to stack
    st.push(nums[i]);
  }

  return ans;
}

// INTUITION: Stack stores potential "next greater" elements. We scan from right
// to left. Smaller elements are useless for future ones ➝ we pop them. Stack is
// now a monotonically decreasing.

// For next greater element to the left traverse from left to right with same
// logic

int main() {
  vector<int> nums = {2, 1, 2, 4, 3};
  vector<int> greaterResult = nextGreaterToRight(nums);
  vector<int> smallerResult = nextSmallerToLeft(nums);

  for (int val : greaterResult) {
    cout << val << " ";
  }

  cout << endl;

  for (int val : smallerResult) {
    cout << val << " ";
  }

  return 0;
}
