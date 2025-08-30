#include<bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Lemonade Change (LeetCode 860)
//
// Task:
// At a lemonade stand, each lemonade costs $5. Customers are standing in a queue
// to buy from you and order one at a time (in the order specified by the bills array).
// Each customer will only buy one lemonade and pay with either a $5, $10, or $20 bill.
//
// You must provide correct change to each customer. Initially, you have no change.
// Return true if you can provide change to every customer, otherwise return false.
//
// Example:
//   Input:  bills = [5,5,5,10,20]
//   Output: true
//
//   Input:  bills = [5,5,10,10,20]
//   Output: false
//
// Approach (Greedy):
// 1. Keep track of the number of $5 and $10 bills.
// 2. If customer pays with $5 → no change needed, just increase count of $5.
// 3. If customer pays with $10 → must give one $5 as change. If not possible, return false.
// 4. If customer pays with $20 → must give change of $15.
//      - Prefer one $10 + one $5 (to save $5 bills for future).
//      - Otherwise, use three $5 bills.
//      - If neither possible, return false.
// 5. Continue until all customers are processed.
//==============================================================================

class Solution {
public:
    bool lemonadeChange(vector<int>& bills)
    {
        int five_cnt = 0, ten_cnt = 0;

        for (auto i : bills) {
            if (i == 5) {
                five_cnt++;
            }
            else if (i == 10) {
                if (five_cnt == 0) return false;
                five_cnt--;
                ten_cnt++;
            }
            else { // i == 20
                if (five_cnt > 0 && ten_cnt > 0) {
                    five_cnt--;
                    ten_cnt--;
                }
                else if (five_cnt >= 3) {
                    five_cnt -= 3;
                }
                else {
                    return false;
                }
            }
        }
        return true;
    }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(N), where N = number of customers (each bill processed once).
// - Space: O(1), only counters used.
//
// Example Walkthrough:
// Input:  bills = [5,5,5,10,20]
// Step1: pay 5 → five_cnt=1
// Step2: pay 5 → five_cnt=2
// Step3: pay 5 → five_cnt=3
// Step4: pay 10 → change 5 → five_cnt=2, ten_cnt=1
// Step5: pay 20 → change 10+5 → five_cnt=1, ten_cnt=0
// Output: true
//==============================================================================
