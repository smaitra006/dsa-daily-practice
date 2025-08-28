#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Maximum XOR of Two Numbers in an Array (Leetcode 421)
//------------------------------------------------------------------------------
// Task:
// Given an array of integers `nums`, return the maximum result of `nums[i] XOR nums[j]`.
//
// Approach (Trie-Based):
// 1. Build a Binary Trie (each node has two children: 0 (left) and 1 (right)).
// 2. Insert every number into the trie, bit by bit (from MSB to LSB).
// 3. To maximize XOR for a number `x`:
//    - At each bit, greedily try to go to the opposite bit branch (for maximum XOR).
//    - If opposite branch exists, add `2^i` to result.
//    - Otherwise, move along the same bit branch.
// 4. Traverse all numbers, compute maximum XOR with trie.
//
// Complexity Analysis:
// - Insert Operation: O(32) ≈ O(1) per number
// - Query Operation: O(32) ≈ O(1) per number
// - Total: O(N) time, O(N*32) = O(N) space
//==============================================================================

#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Trie Node Structure
//==============================================================================
class Trie {
public:
    struct trieNode {
        trieNode* left;   // represents bit 0
        trieNode* right;  // represents bit 1
    };

    trieNode* root;

    // Create a new Trie node
    trieNode* getNode()
    {
        trieNode* newNode = new trieNode;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

    // Constructor
    Trie()
    {
        root = getNode();
    }

    // Insert number into Trie (store 32-bit representation)
    void insert(int num)
    {
        trieNode* crawler = root;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (bit == 1) {
                if (crawler->right == nullptr)
                    crawler->right = getNode();
                crawler = crawler->right;
            }
            else {
                if (crawler->left == nullptr)
                    crawler->left = getNode();
                crawler = crawler->left;
            }
        }
    }

    // Find max XOR for a number with existing numbers in Trie
    int findMaxXOR(int x)
    {
        trieNode* crawler = root;
        int maxNum = 0;
        for (int i = 31; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if (bit == 1) {
                if (crawler->left) {          // prefer opposite branch
                    maxNum |= (1 << i);
                    crawler = crawler->left;
                }
                else {
                    crawler = crawler->right;
                }
            }
            else {
                if (crawler->right) {         // prefer opposite branch
                    maxNum |= (1 << i);
                    crawler = crawler->right;
                }
                else {
                    crawler = crawler->left;
                }
            }
        }
        return maxNum;
    }
};

//==============================================================================
// Solution Class
//==============================================================================
class Solution {
public:
    int findMaximumXOR(vector<int>& nums)
    {
        Trie trie;

        // Step 1: Insert all numbers into trie
        for (int num : nums) {
            trie.insert(num);
        }

        // Step 2: Find max XOR for each number
        int maxXOR = 0;
        for (int num : nums) {
            int curXOR = trie.findMaxXOR(num);
            maxXOR = max(maxXOR, curXOR);
        }
        return maxXOR;
    }
};

/**
 * Example Usage:
 * vector<int> nums = {3, 10, 5, 25, 2, 8};
 * Solution sol;
 * int result = sol.findMaximumXOR(nums); // Output: 28
 */
