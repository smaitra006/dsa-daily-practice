#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: Word Ladder (LeetCode 127)
================================================================================
Task:
    Given two words (beginWord and endWord), and a dictionary's word list,
    find the length of the shortest transformation sequence from beginWord
    to endWord such that:

        1. Only one letter can be changed at a time.
        2. Each transformed word must exist in the word list.

    Return 0 if no such transformation sequence exists.

--------------------------------------------------------------------------------
Approach (BFS on Words):
    1. Use BFS to explore transformations level by level.
    2. Each level corresponds to one transformation step.
    3. At each step, generate all possible words by changing one character.
    4. If the generated word exists in the word list and is unvisited, enqueue it.
    5. Stop when we reach the `endWord`.

    Why BFS?
        - BFS guarantees the shortest path in an unweighted graph,
          where each transformation is considered as one edge.

--------------------------------------------------------------------------------
Complexity Analysis:
    Let L = length of each word, N = number of words in the word list.

    Time Complexity:  O(N * L * 26)
        - For each word, we attempt 26 possible replacements for each character.
    Space Complexity: O(N)
        - To store dictionary and visited set.
================================================================================
*/

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList)
    {
        queue<string> q;
        unordered_set<string> bank(wordList.begin(), wordList.end());

        // If endWord is not in dictionary or start == end, no solution
        if (bank.find(endWord) == bank.end() || beginWord == endWord) return 0;

        unordered_set<string> visited;
        q.push(beginWord);
        visited.insert(beginWord);

        int steps = 1; // Begin word counts as step 1

        while (!q.empty()) {
            int sz = q.size();
            while (sz--) {
                string curr = q.front();
                q.pop();

                if (curr == endWord) return steps;

                // Try changing each character
                for (int i = 0; i < curr.size(); i++) {
                    string temp = curr;
                    for (char ch = 'a'; ch <= 'z'; ch++) {
                        temp[i] = ch;
                        // If valid word and not visited
                        if (bank.find(temp) != bank.end() && visited.find(temp) == visited.end()) {
                            q.push(temp);
                            visited.insert(temp);
                        }
                    }
                }
            }
            steps++; // Move to next transformation step
        }

        return 0; // No transformation possible
    }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    beginWord = "hit"
    endWord = "cog"
    wordList = ["hot","dot","dog","lot","log","cog"]

Output:
    5

Explanation:
    One shortest transformation is:
    "hit" -> "hot" -> "dot" -> "dog" -> "cog"
    Length = 5

--------------------------------------------------------------------------------
Notes:
    - BFS ensures shortest sequence is found first.
    - Using unordered_set for word list and visited ensures O(1) lookups.
================================================================================
*/

