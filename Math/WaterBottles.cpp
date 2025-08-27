#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Water Bottles
//------------------------------------------------------------------------------
// Task:
// Given two integers numBottles and numExchange, you have numBottles full bottles of water.
// After drinking a bottle, you can exchange numExchange empty bottles for one full bottle.
// Return the maximum number of water bottles you can drink.
//
// Approach:
// 1. Start with numBottles full bottles and 0 empty bottles.
// 2. While there are full bottles available:
//    - Drink all full bottles (add to max_drink).
//    - Convert them into empty bottles.
//    - Exchange empty bottles into full bottles whenever possible.
// 3. Continue until no more exchanges can be made.
//
// Complexity Analysis:
// - Time: O(log(numBottles)) (since bottles decrease geometrically via exchanges).
// - Space: O(1), using only counters.
//==============================================================================

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numWaterBottles(int numBottles, int numExchange)
    {
        int full_bottles = numBottles;   // initially all full
        int empty_bottles = 0;           // initially none empty
        int max_drink = 0;               // total bottles drunk

        // Continue while we have full bottles to drink
        while (full_bottles != 0) {
            max_drink += full_bottles;                  // drink them all
            empty_bottles += full_bottles;              // now they’re empty

            full_bottles = empty_bottles / numExchange; // exchange empties
            empty_bottles = empty_bottles % numExchange;// remainder empties
        }

        return max_drink;
    }
};

//==============================================================================
// Example Usage:
// Input:  numBottles = 9, numExchange = 3
// Output: 13
// Explanation:
// - Drink 9 (9 full → 9 empty)
// - Exchange 9 empty → 3 full (drink → 3 empty, total = 12)
// - Exchange 3 empty → 1 full (drink → 1 empty, total = 13)
// - Only 1 empty left, cannot exchange further.
//==============================================================================
