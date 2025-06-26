//* Recursion
//? This is scenario where function calls itself. To stop this recursion being
//infinte we set a base case and the recursion logic always leads to the base
// case.

//? We will try to implement solution for a part of the problem and call the
//function recursively for the rest of the part to be solved. We take a leap of
// faith, have belief and call the function.

//* Recurrance Relation
//? This is a mathematical relation we use to find time complexity of recursion

//* Tail Recursive
//? A recursive function where the last step is a recursion call
// Like the printReverse is tail recursion but factorial is not tail recursion
// as the last step in factorial is multiplication

#include <bits/stdc++.h>
using namespace std;

//? Print from n to 1
void printReverse(int n) {
  // Base case
  if (n < 1) {
    return;
  }
  // Recursive logic
  cout << n << " ";
  printReverse(n - 1);
}

//? f(n) = print + f(n-1) => O(n) = O(1) + O(n-1) -> Recurrance relation

//? N factorial
int factorial(int n) {
  // Base case
  if (n == 0) {
    return 1;
  }
  // Recursive call
  return (n * factorial(n - 1));
}

//? f(n) = multiply + f(n-1) => O(n) = O(1) + O(n-1)
/*
f(n)   = k + f(n-1)
f(n-1) = k + f(n-2)
f(n-2) = k + f(n-3)
.      = . + .
.      = . + .
.      = . + .
f(1)   = k + f(1)

After cutting from both sides we get
f(n) = k * n
*/
//! Time complexity: O(n)
//! Space complexity: O(n)

//! Always reccurance relation is not so intuitive. So we use the recursion
//! tree. Space complexity SC = Depth of recurssion tree * memeory in each call
//! / SC = Height of callstack
//! * memory in each call

//? Sum of n numbers
int sumTillN(int n) {
  // Base case
  if (n == 0) {
    return 0;
  }
  // Recursive call
  return (n + sumTillN(n - 1));
}

//! TC: O(n)
//! SC: O(n)

//? Nth Fibonacci -> 0, 1, 1, 2, 3, 5, 8, 13, ...  f(n) = f(n-1) + f(n-2)
int fibonacci(int n) {
  // Base case
  if (n == 1 || n == 0) {
    return n;
  }
  // Recursive call
  return fibonacci(n - 1) + fibonacci(n - 2);
}

//! TC: O(2^n)
//! SC: O(n)

//? Check if array is sorted
bool isSortedAsc(vector<int> nums, int n) {
  // Base case
  if (n == 0 || n == 1) {
    return true;
  }
  // Recursive call
  return (nums[n - 1] >= nums[n - 2]) && isSortedAsc(nums, n - 1);
}

//! TC: O(n)
//! SC: O(n)

//? Recursive Binary search
int recursiveBinarySearch(vector<int> nums, int target, int start, int end) {
  // Recursive call
  if (start <= end) {
    int mid = start + (end - start) / 2;
    if (target < nums[mid]) {
      return recursiveBinarySearch(nums, target, start, mid - 1);
    } else if (target > nums[mid]) {
      return recursiveBinarySearch(nums, target, mid + 1, end);
    } else {
      return mid;
    }
  } else {
    return -1;
  }
}

//! TC: O(log(n))
//! SC: O(log(n))

//? Merge Sort
void merge(vector<int> &nums, int start, int mid, int end) {
  vector<int> temp; // Store the sorted elements in this array
  int i = start, j = mid + 1;
  // Same as joining two sorted arrays into one sorted array
  while (i <= mid && j <= end) {
    if (nums[i] <= nums[j]) {
      temp.push_back(nums[i]);
      i++;
    } else if (nums[j] < nums[i]) {
      temp.push_back(nums[j]);
      j++;
    }
  }
  while (i <= mid) {
    temp.push_back(nums[i]);
    i++;
  }
  while (j <= end) {
    temp.push_back(nums[j]);
    j++;
  }
  // Bring back the sorted elements from temp to actual nums array
  for (int m = 0; m < temp.size(); m++) {
    nums[start + m] = temp[m];
  }
}

void mergeSort(vector<int> &nums, int start, int end) {
  // Base case
  if (start >= end)
    return; // Case when just one element remains
  int mid = start + (end - start) / 2;
  mergeSort(nums, start, mid);   // Recursive call for left half
  mergeSort(nums, mid + 1, end); // Recursive call for right half
  // Call the merge function
  merge(nums, start, mid, end);
}

//! TC: O(n * (logn))
//! SC: (n * log(n)) -> If we globally declare temp then its O(n)

//? Quick Sort
int partitioning(vector<int> &nums, int start, int end, int pivot) {
  int idx = -1, j = 0;
  while (j <= end - 1) {         // We work till before the pivot element
    if (nums[j] < nums[pivot]) { // If we find an element smaller than the pivot
      // Make space for the smaller element on left
      idx++;
      swap(nums[idx], nums[j]); // Bring the smaller element to the left
    }
    j++;
  }
  // Now its time to place the pivot element. idx is pointing to the last
  // smaller element and j is pointing to the pivot
  idx++;                    // Make space for pivot
  swap(nums[idx], nums[j]); // Place the pivot element
  return idx; // Return the index of pivot element after other elements are
              // arranged
}

void quickSort(vector<int> &nums, int start, int end) {
  // Base case
  if (start >= end) {
    return;
  }
  int pivot = end;
  int pivotIdx =
      partitioning(nums, start, end,
                   pivot); // Find the correct pivot position is smaller
                           // elements to left and larger to right
  quickSort(nums, start, pivotIdx - 1); // Call for left half
  quickSort(nums, pivot + 1, end);      // Call for right half
}

//! TC: Avg(n * (logn)) , Worst(n^2)
//! SC: AVg(logn) , Worst(n)

//? Inversion Count
// This is a variation of merge sort
int mergeInv(vector<int> &arr, int low, int mid, int high) {
  vector<int> temp;    // temporary array
  int left = low;      // starting index of left half of arr
  int right = mid + 1; // starting index of right half of arr
  // Modification 1: cnt variable to count the pairs:
  int cnt = 0;
  // storing elements in the temporary array in a sorted manner//
  while (left <= mid && right <= high) {
    if (arr[left] <= arr[right]) {
      temp.push_back(arr[left]);
      left++;
    } else {
      temp.push_back(arr[right]);
      cnt += (mid - left + 1); // Modification 2
      right++;
    }
  }
  // if elements on the left half are still left //
  while (left <= mid) {
    temp.push_back(arr[left]);
    left++;
  }
  //  if elements on the right half are still left //
  while (right <= high) {
    temp.push_back(arr[right]);
    right++;
  }
  // transfering all elements from temporary to arr //
  for (int i = low; i <= high; i++) {
    arr[i] = temp[i - low];
  }
  return cnt; // Modification 3
}

int mergeSortInv(vector<int> &arr, int low, int high) {
  int cnt = 0;
  if (low >= high)
    return cnt;
  int mid = (low + high) / 2;
  cnt += mergeSortInv(arr, low, mid);      // left half
  cnt += mergeSortInv(arr, mid + 1, high); // right half
  cnt += mergeInv(arr, low, mid, high);    // merging sorted halves
  return cnt;
}

int numberOfInversions(vector<int> &a, int n) {
  // Count the number of pairs:
  return mergeSortInv(a, 0, n - 1);
}

//* Backtracking
//? This is actually the coming back through the path in the call stack that we
//travelled during the recursive calls and doing something while coming back.

//? Print all subsets (Concept of Subsets) -> used in many questions
// For any vector having n elements there exits 2^n number of subsets. Now every
// element has an option to either enter the subset or not enter. If we have a
// vector with suppose 1 element [1], then finding subsets is very easy its
// either {1} or {}. This choice will give us the hint of backtracking.
void printSubsets(
    vector<int> nums, vector<int> &result,
    int i) // sending vector by reference so that changes are saved
{
  // Base case
  if (i == nums.size()) {
    for (auto i : result) {
      cout << i;
    }
    cout << endl;
    return;
  }
  // If we want to include
  result.push_back(nums[i]);
  // Recursive call with the current element included
  printSubsets(nums, result, i + 1);

  // If we dont want to include (so while coming back during backtracking)
  result.pop_back();
  // Recursive call without the current element included after popping
  printSubsets(nums, result, i + 1);
}

//! TC: O((2^n) * n)
//! SC: O((2^n) * n)

//? Find all permutations (Concept of permutation)
// Here also at each blank we have choice of having any one of the number or not
// having it. A vector with n elements have n! number of permutations
void printPermutations(vector<int> nums, int n, vector<int> &temp,
                       vector<vector<int>> &result, unordered_set<int> &st) {
  // Base case
  if (temp.size() == n) {
    result.push_back(temp);
    return;
  }
  // We always start looping from the first and keep on checking it the element
  // is already used
  for (int i = 0; i < n; i++) {
    // If element is not there in temp only then we
    if (st.find(nums[i]) == st.end()) {
      temp.push_back(nums[i]);
      st.insert(nums[i]); // We insert the used element in set to keep check if
                          // its used
      // Recursive call after including
      printPermutations(nums, n, temp, result, st);
      // Exclude the element
      temp.pop_back();
      st.erase(nums[i]); // Erase it from the set because now we can include it
    }
  }
}

//* TC: O(n * n!)
//* SC: O(n + n!) -> O(n!)

//? Rat in a maze.
//? Return all possible paths to solve the maze, rat can travel only through
//places marked 1, cannot revisit a visited square, start is top left and finish
// is bottom right.
void solveMaze(vector<vector<int>> &maze, string &direction,
               vector<string> &result, int row, int col, int n) {
  // Base case
  if (row == n - 1 && col == n - 1) {
    result.push_back(direction);
    return;
  }
  if (row < 0 || row >= n || col < 0 || col >= n || maze[row][col] == 0) {
    return;
  }

  maze[row][col] = 0; // Mark current cell as visited

  // Down, Left, Right, Up (DLRU order)
  if (row + 1 < n && maze[row + 1][col] == 1) {
    direction += 'D';
    solveMaze(maze, direction, result, row + 1, col, n);
    direction.pop_back();
  }
  if (col - 1 >= 0 && maze[row][col - 1] == 1) {
    direction += 'L';
    solveMaze(maze, direction, result, row, col - 1, n);
    direction.pop_back();
  }
  if (col + 1 < n && maze[row][col + 1] == 1) {
    direction += 'R';
    solveMaze(maze, direction, result, row, col + 1, n);
    direction.pop_back();
  }
  if (row - 1 >= 0 && maze[row - 1][col] == 1) {
    direction += 'U';
    solveMaze(maze, direction, result, row - 1, col, n);
    direction.pop_back();
  }

  maze[row][col] = 1; // Backtrack
}

int main() {
  // printReverse(50);
  // cout << factorial(5) << endl;
  // cout << sumTillN(5) << endl;
  // cout << fibonacci(7) << endl;
  vector<int> nums = {4, 2, 5, 1, 3};
  int n = nums.size();
  // cout << isSortedAsc(nums, n) << endl;
  // cout << recursiveBinarySearch(nums, 4, 0, n - 1) << endl;
  // cout << recursiveBinarySearch(nums, 10, 0, n - 1) << endl;
  // vector<int> result;
  // printSubsets(nums, result, 0);
  // vector<vector<int>> result;
  // unordered_set<int> st;
  // vector<int> temp;
  // printPermutations(nums, n, temp, result, st);
  // mergeSort(nums, 0, n - 1);
  // for (auto i : nums)
  // {
  //   cout << i << " ";
  // }
  // quickSort(nums, 0, n - 1);

  return 0;
}
