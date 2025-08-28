#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Longest Common Prefix Between Two Arrays
//
// You are given two integer arrays arr1 and arr2.
// The task is to find the length of the longest common prefix among any
// number in arr1 and any number in arr2.
//
// Approach:
// - Use a Trie (digits 0-9) to store all numbers from arr1 as strings.
// - For each number in arr2, search in the Trie to count the length of
//   the longest prefix it shares with any number in arr1.
// - Track the maximum prefix length across all comparisons.
//
// Complexity:
// - Insertion: O(N * L), where N = |arr1|, L = max digits per number.
// - Search: O(M * L), where M = |arr2|.
// - Overall efficient since max digits per number ≤ 10^9 → length ≤ 10.
//==============================================================================

//==============================================================================
// Trie Data Structure for Numbers
//==============================================================================

class Trie {
public:
    struct TrieNode {
        bool isEnd;
        TrieNode* children[10];  // digits 0-9
    };

    TrieNode* root;

    // Create a new Trie node
    TrieNode* getNode()
    {
        TrieNode* newNode = new TrieNode;
        newNode->isEnd = false;
        for (int i = 0; i < 10; i++) {
            newNode->children[i] = NULL;
        }
        return newNode;
    }

    // Constructor
    Trie()
    {
        root = getNode();
    }

    // Insert a number string into the Trie
    void insert(const string& num)
    {
        TrieNode* crawler = root;
        for (char ch : num) {
            int idx = ch - '0';
            if (crawler->children[idx] == NULL) {
                crawler->children[idx] = getNode();
            }
            crawler = crawler->children[idx];
        }
        crawler->isEnd = true;
    }

    // Search longest prefix length between given num string and Trie
    int search(const string& num)
    {
        TrieNode* crawler = root;
        int cnt = 0;

        for (char ch : num) {
            int idx = ch - '0';
            if (crawler->children[idx] == NULL) {
                return cnt; // mismatch → stop
            }
            cnt++;
            crawler = crawler->children[idx];
        }
        return cnt;
    }
};

//==============================================================================
// Solution Class
//==============================================================================

class Solution {
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2)
    {
        Trie trie;

        // Insert all numbers from arr1 into Trie
        for (int num : arr1) {
            trie.insert(to_string(num));
        }

        int maxCnt = 0;

        // For each number in arr2, check longest prefix
        for (int num : arr2) {
            int cnt = trie.search(to_string(num));
            maxCnt = max(maxCnt, cnt);
        }

        return maxCnt;
    }
};

//==============================================================================
// Example Usage:
// Input: arr1 = [123, 456, 789], arr2 = [1245, 4567, 781]
// Output: 3
// Explanation:
// - "123" and "1245" share prefix "12" → length 2
// - "456" and "4567" share prefix "456" → length 3 (maximum)
//==============================================================================
