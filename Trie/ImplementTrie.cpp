#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Implement Trie (Prefix Tree)
//------------------------------------------------------------------------------
// Task:
// Implement a Trie with insert, search, and startsWith operations for lowercase
// English letters.
//
// Approach:
// 1. Each node stores a boolean `isEnd` and an array of 26 child pointers.
// 2. `insert(word)` - traverse characters, create nodes if missing, mark end.
// 3. `search(word)` - traverse characters, return true if last node exists and isEnd.
// 4. `startsWith(prefix)` - traverse characters, return true if all prefix nodes exist.
//
// Complexity Analysis:
// - Time:
//     Insert/Search/StartsWith: O(L) where L is the length of the word/prefix.
// - Space:
//     O(N*26) in worst case where N is the total number of characters inserted.
//==============================================================================

#include <bits/stdc++.h>
using namespace std;

class Trie {
public:
    struct trieNode {
        bool isEnd;
        trieNode* children[26];
    };

    trieNode* root;

    // Create a new trie node
    trieNode* getNode()
    {
        trieNode* newNode = new trieNode;
        newNode->isEnd = false;
        for (int i = 0; i < 26; i++) newNode->children[i] = nullptr;
        return newNode;
    }

    // Constructor
    Trie()
    {
        root = getNode();
    }

    // Insert a word into the trie
    void insert(string word)
    {
        trieNode* crawler = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (crawler->children[idx] == nullptr) {
                crawler->children[idx] = getNode();
            }
            crawler = crawler->children[idx];
        }
        crawler->isEnd = true;
    }

    // Search a word in the trie
    bool search(string word)
    {
        trieNode* crawler = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (crawler->children[idx] == nullptr) return false;
            crawler = crawler->children[idx];
        }
        return crawler != nullptr && crawler->isEnd;
    }

    // Check if there is any word starting with the given prefix
    bool startsWith(string prefix)
    {
        trieNode* crawler = root;
        for (char ch : prefix) {
            int idx = ch - 'a';
            if (crawler->children[idx] == nullptr) return false;
            crawler = crawler->children[idx];
        }
        return true;
    }
};

/**
 * Example Usage:
 * Trie* obj = new Trie();
 * obj->insert("apple");
 * bool found = obj->search("apple");       // true
 * bool prefix = obj->startsWith("app");    // true
 */
