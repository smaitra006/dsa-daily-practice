#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Word Ladder II
// Link: https://leetcode.com/problems/word-ladder-ii/
//
// Task:
// Given two words (beginWord and endWord), and a dictionary wordList,
// find all shortest transformation sequences from beginWord to endWord,
// such that:
//   - Only one letter can be changed at a time
//   - Each transformed word must exist in wordList
//
// Approach:
// 1. Use BFS to compute the shortest distance (depth) of each word from beginWord.
// 2. Use DFS (backtracking) starting from endWord to reconstruct all valid
//    shortest transformation sequences.
//
// Complexity:
// - BFS: O(N * wordLen * 26), where N = size of wordList
// - DFS: O(#paths * pathLen)
// - Space: O(N) for depthMap and recursion stack
//==============================================================================

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList)
    {
        unordered_map<string, int> depthMap;              // stores min depth for each word
        vector<vector<string>> ans;                       // stores all valid sequences

        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (!wordSet.count(endWord)) return ans;          // early exit if endWord not present

        // BFS to compute depth of each word
        queue<string> q;
        q.push(beginWord);
        depthMap[beginWord] = 1;
        wordSet.erase(beginWord);

        while (!q.empty()) {
            string word = q.front();
            q.pop();
            int steps = depthMap[word];

            if (word == endWord) break;                   // found shortest distance to endWord

            for (int i = 0; i < word.size(); ++i) {
                char original = word[i];
                for (char ch = 'a'; ch <= 'z'; ++ch) {
                    word[i] = ch;
                    if (wordSet.count(word)) {
                        q.push(word);
                        wordSet.erase(word);
                        depthMap[word] = steps + 1;
                    }
                }
                word[i] = original; // restore word
            }
        }

        // If we found a path to endWord, run DFS backtracking to construct sequences
        if (depthMap.count(endWord)) {
            vector<string> seq = { endWord };
            dfs(endWord, beginWord, seq, depthMap, ans);
        }

        return ans;
    }

private:
    void dfs(string word, string beginWord,
        vector<string>& seq,
        unordered_map<string, int>& depthMap,
        vector<vector<string>>& ans)
    {
        if (word == beginWord) {
            reverse(seq.begin(), seq.end());
            ans.push_back(seq);
            reverse(seq.begin(), seq.end());
            return;
        }

        int steps = depthMap[word];
        for (int i = 0; i < word.size(); ++i) {
            char original = word[i];
            for (char ch = 'a'; ch <= 'z'; ++ch) {
                word[i] = ch;
                if (depthMap.count(word) && depthMap[word] + 1 == steps) {
                    seq.push_back(word);
                    dfs(word, beginWord, seq, depthMap, ans);
                    seq.pop_back();
                }
            }
            word[i] = original; // restore word
        }
    }
};
