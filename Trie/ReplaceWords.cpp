#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Replace Words
//
// You are given a dictionary of words (roots) and a sentence. Replace all words
// in the sentence that have a root in the dictionary with the shortest possible
// root from the dictionary.
//
// Approach:
// - Use a Trie to store all dictionary roots.
// - For each word in the sentence, search in the Trie for the shortest prefix
//   that matches a root.
// - If found, replace the word with this root; otherwise keep the word as is.
//
// Complexity:
// - Building the Trie: O(N * L), where N = number of dictionary words,
//   L = max length of a word.
// - Processing the sentence: O(M * K), where M = number of words in sentence,
//   K = max length of a word in the sentence.
//==============================================================================

class Trie {
public:
    struct TrieNode {
        bool isEnd;
        TrieNode* children[26];
    };

    TrieNode* root;

    // Create a new Trie node
    TrieNode* getNode()
    {
        TrieNode* newNode = new TrieNode;
        newNode->isEnd = false;
        for (int i = 0; i < 26; i++) {
            newNode->children[i] = NULL;
        }
        return newNode;
    }

    // Constructor
    Trie()
    {
        root = getNode();
    }

    // Insert a word (root) into the Trie
    void insert(const string& word)
    {
        TrieNode* crawler = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (crawler->children[idx] == NULL) {
                crawler->children[idx] = getNode();
            }
            crawler = crawler->children[idx];
        }
        crawler->isEnd = true;
    }

    // Search for the shortest prefix root for a given word
    string search(const string& word)
    {
        TrieNode* crawler = root;
        string prefix = "";

        for (char ch : word) {
            int idx = ch - 'a';

            // If this character path doesn't exist, no root found → return word
            if (crawler->children[idx] == NULL) {
                return word;
            }

            crawler = crawler->children[idx];
            prefix += ch;

            // If a root ends here → return prefix as replacement
            if (crawler->isEnd) {
                return prefix;
            }
        }

        return word; // no shorter root found
    }
};

//==============================================================================
// Solution class
//==============================================================================

class Solution {
public:
    string replaceWords(vector<string>& dictionary, string sentence)
    {
        Trie trie;

        // Insert all dictionary roots into Trie
        for (const string& word : dictionary) {
            trie.insert(word);
        }

        // Process sentence word by word
        stringstream ss(sentence);
        string word, result;
        while (getline(ss, word, ' ')) {
            result += trie.search(word) + ' ';
        }

        result.pop_back(); // remove trailing space
        return result;
    }
};

//==============================================================================
// Example Usage:
// Input: dictionary = ["cat","bat","rat"], sentence = "the cattle was rattled by the battery"
// Output: "the cat was rat by the bat"
//==============================================================================
