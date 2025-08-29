#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Sum of Prefix Scores of Strings (LeetCode 2416)
//
// Task:
// Given an array of strings `words`, compute for each word the sum of scores
// of its prefixes, where the score of a string is the number of words in the
// array that contain that string as a prefix.
//
// Approach:
// - Use a Trie data structure to store all words.
// - Each node maintains a `counter` storing how many words pass through it.
// - Insert all words into the Trie, incrementing counters for each character.
// - To compute score of a word, traverse it in the Trie and sum up the counters.
//==============================================================================

class Solution {
public:
    //=============================
    // Trie Node Structure
    //=============================
    struct trieNode {
        trieNode* children[26]; // Pointers to child nodes (for 'a' to 'z')
        int counter;            // Count of words passing through this node
    };

    //=============================
    // Create New Node
    //=============================
    trieNode* getNode()
    {
        trieNode* temp = new trieNode();
        temp->counter = 0;
        for (int i = 0; i < 26; i++) {
            temp->children[i] = nullptr;
        }
        return temp;
    }

    // Root of Trie
    trieNode* root = getNode();

    //=============================
    // Insert Word into Trie
    //=============================
    void insert(string word)
    {
        trieNode* crawl = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (crawl->children[idx] == nullptr) {
                crawl->children[idx] = getNode();
            }
            crawl = crawl->children[idx];
            crawl->counter++; // Increment counter for prefix passing here
        }
    }

    //=============================
    // Search Word and Sum Prefix Scores
    //=============================
    int search(string word)
    {
        trieNode* crawl = root;
        int ans = 0;
        for (char ch : word) {
            int idx = ch - 'a';
            if (crawl->children[idx]) {
                crawl = crawl->children[idx];
                ans += crawl->counter; // Add count for current prefix
            }
        }
        return ans;
    }

    //=============================
    // Main Function
    //=============================
    vector<int> sumPrefixScores(vector<string>& words)
    {
        // Step 1: Insert all words
        for (auto& word : words) {
            insert(word);
        }

        // Step 2: Calculate prefix scores for each word
        int n = words.size();
        vector<int> result(n);
        for (int i = 0; i < n; i++) {
            result[i] = search(words[i]);
        }
        return result;
    }
};

//==============================================================================
// Complexity Analysis:
// - Insert: O(N * L)   (N = number of words, L = average length of words)
// - Search: O(N * L)
// - Space:  O(26 * N * L) for Trie nodes
//
// Example:
// Input:  words = ["abc","ab","bc","b"]
// Output: [5, 4, 3, 2]
//==============================================================================
