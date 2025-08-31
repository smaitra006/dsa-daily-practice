#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Word Break (LeetCode 139)
//
// Task:
// Given a string `s` and a dictionary of strings `wordDict`, determine if `s`
// can be segmented into a space-separated sequence of one or more dictionary words.
//
// Example:
//   Input:  s = "leetcode", wordDict = ["leet","code"]
//   Output: true
//
//   Input:  s = "applepenapple", wordDict = ["apple","pen"]
//   Output: true
//
// Approach (Trie + Memoization):
// 1. Build a Trie for all words in wordDict for efficient prefix checking.
// 2. Use recursive search starting from position 0:
//      - For each prefix matching a word in Trie, recursively check the remaining string.
//      - Memoize results to avoid recomputation (memo[pos] = true/false).
// 3. If any path leads to end of string → return true.
//==============================================================================

class Trie {
public:
    struct trieNode {
        bool isEnd;
        trieNode* children[26];
    };

    trieNode* root;

    Trie()
    {
        root = new trieNode();
        root->isEnd = false;
        for (int i = 0; i < 26; i++) root->children[i] = nullptr;
    }

    void insert(const string& word)
    {
        trieNode* crawler = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (crawler->children[idx] == nullptr) {
                crawler->children[idx] = new trieNode();
                crawler->children[idx]->isEnd = false;
            }
            crawler = crawler->children[idx];
        }
        crawler->isEnd = true;
    }

    bool search(const string& s, int pos, vector<int>& memo)
    {
        if (pos == s.size()) return true;
        if (memo[pos] != -1) return memo[pos];

        trieNode* crawler = root;
        for (int i = pos; i < s.size(); i++) {
            int idx = s[i] - 'a';
            if (crawler->children[idx] == nullptr) break;
            crawler = crawler->children[idx];
            if (crawler->isEnd) {
                if (search(s, i + 1, memo)) {
                    return memo[pos] = true;
                }
            }
        }
        return memo[pos] = false;
    }
};

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict)
    {
        Trie trie;
        for (const string& word : wordDict) trie.insert(word);

        vector<int> memo(s.size(), -1); // -1 = unvisited
        return trie.search(s, 0, memo);
    }
};

//==============================================================================
// Complexity Analysis:
// - Building Trie: O(M), where M = total characters in wordDict.
// - Search with memoization: O(N^2), N = length of s (each substring checked once).
// - Space: O(M + N) for Trie + memo array.
//
// Example Walkthrough:
// Input: s="leetcode", wordDict=["leet","code"]
// Trie built: "leet" and "code"
// search(s,0):
//   match "leet" → search(s,4):
//     match "code" → search(s,8)=true
// Output: true
//==============================================================================
