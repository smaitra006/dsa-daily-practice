#include <bits/stdc++.h>
using namespace std;

// ============================================================================
//  Problem: Maximum Product Subarray
//  Task: Find the contiguous subarray within an array which has the largest product.
//
//  Approach:
//  - Unlike maximum sum subarray, product subarray needs to track both the
//    maximum and minimum products at each step because:
//      1. A large positive product can come from multiplying two large positives.
//      2. A large positive product can also come from multiplying two negatives.
//  - At each step, compute:
//      - currMax: The largest product ending at current index
//      - currMin: The smallest product ending at current index
//    Then update the answer accordingly.
//
//  Steps:
//    1. Initialize currMax, currMin, ans with nums[0].
//    2. Iterate from index 1 to n-1:
//         - Store old currMax in temp (needed for currMin computation).
//         - Update currMax as the maximum of {nums[i], nums[i] * currMax, nums[i] * currMin}.
//         - Update currMin as the minimum of {nums[i], nums[i] * temp, nums[i] * currMin}.
//         - Update ans if currMax is greater.
//    3. Return ans.
//
//  Time Complexity: O(n)   -> Single pass through the array
//  Space Complexity: O(1)  -> Constant extra space
// ============================================================================

class Solution {
public:
    int maxProduct(vector<int>& nums)
    {
        long long currMax = nums[0];
        long long currMin = nums[0];
        long long ans = nums[0];

        for (int i = 1; i < nums.size(); i++) {
            long long temp = currMax;  // Store before updating
            currMax = max({ (long long)nums[i],
                           nums[i] * currMax,
                           nums[i] * currMin });
            currMin = min({ (long long)nums[i],
                           nums[i] * temp,
                           nums[i] * currMin });
            ans = max(ans, currMax);
        }

        return (int)ans;
    }
};

