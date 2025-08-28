#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Implement Trie II (Prefix Tree with Count & Erase)
//------------------------------------------------------------------------------
// Task:
// Implement a Trie that supports:
// 1. insert(word) - insert a word into the trie
// 2. countWordsEqualTo(word) - return number of times the exact word was inserted
// 3. countWordsStartingWith(prefix) - return number of words with given prefix
// 4. erase(word) - remove one occurrence of the word
//
// Approach:
// 1. Each node stores:
//    - `countEnd`   : number of words ending at this node
//    - `countPrefix`: number of words passing through this node (including this node)
//    - `children[26]` : child pointers for lowercase letters
// 2. insert(word) - increment countPrefix for all nodes, increment countEnd at last node
// 3. countWordsEqualTo(word) - traverse nodes, return countEnd of last node
// 4. countWordsStartingWith(prefix) - traverse nodes, return countPrefix of last node
// 5. erase(word) - decrement countPrefix for all nodes, decrement countEnd at last node
//
// Complexity Analysis:
// - Time: O(L) per operation, where L = length of word/prefix
// - Space: O(N*26) in worst case, N = total characters inserted
//==============================================================================

#include <bits/stdc++.h>
using namespace std;

class Trie {
public:
    struct trieNode {
        int countEnd;            // number of words ending here
        int countPrefix;         // number of words passing through
        trieNode* children[26];  // child pointers
    };

    trieNode* root;

    // Create a new trie node
    trieNode* getNode()
    {
        trieNode* newNode = new trieNode;
        newNode->countEnd = 0;
        newNode->countPrefix = 0;
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
            if (crawler->children[idx] == nullptr)
                crawler->children[idx] = getNode();
            crawler = crawler->children[idx];
            crawler->countPrefix++;
        }
        crawler->countEnd++;
    }

    // Count number of words equal to the given word
    int countWordsEqualTo(string word)
    {
        trieNode* crawler = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (crawler->children[idx] == nullptr) return 0;
            crawler = crawler->children[idx];
        }
        return crawler->countEnd;
    }

    // Count number of words starting with the given prefix
    int countWordsStartingWith(string prefix)
    {
        trieNode* crawler = root;
        for (char ch : prefix) {
            int idx = ch - 'a';
            if (crawler->children[idx] == nullptr) return 0;
            crawler = crawler->children[idx];
        }
        return crawler->countPrefix;
    }

    // Erase one occurrence of a word
    void erase(string word)
    {
        trieNode* crawler = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (crawler->children[idx] == nullptr) return;  // word not present
            crawler = crawler->children[idx];
            crawler->countPrefix--;
        }
        crawler->countEnd--;
    }
};

/**
 * Example Usage:
 * Trie* obj = new Trie();
 * obj->insert("apple");
 * int cnt1 = obj->countWordsEqualTo("apple");    // 1
 * int cnt2 = obj->countWordsStartingWith("app"); // 1
 * obj->erase("apple");
 * int cnt3 = obj->countWordsEqualTo("apple");    // 0
 */
