#include <bits/stdc++.h>
using namespace std;

/* ===================================================================
 * LEETCODE 433: MINIMUM GENETIC MUTATION
 * =================================================================== */

 /**
  * @brief Find the minimum number of mutations to transform startGene to endGene
  *
  * PROBLEM STATEMENT:
  * A gene string is a string of length 8, consisting of characters 'A', 'C', 'G', and 'T'.
  * A **mutation** involves changing a single character to any of the other three choices.
  *
  * You are given:
  * - A start gene string `startGene`
  * - A target gene string `endGene`
  * - A bank of valid intermediate gene strings `bank`
  *
  * Return the **minimum number of mutations** needed to transform startGene to endGene.
  * Each intermediate mutation must be present in the `bank`.
  * If no such mutation path exists, return -1.
  *
  * Input:
  * - string startGene: starting gene (length = 8)
  * - string endGene: target gene (length = 8)
  * - vector<string> bank: valid intermediate genes
  *
  * Output:
  * - Integer: Minimum number of mutations, or -1 if not possible
  *
  * ALGORITHM (BFS - Shortest Path in Unweighted Graph):
  * - Treat each gene string as a node
  * - Two gene strings are connected if they differ by exactly one character
  * - Use BFS to find the shortest path from startGene to endGene
  *
  * COMPLEXITY:
  * - Time: O(N * 8 * 4), where N = bank size, 8 is gene length, 4 is number of possible bases
  * - Space: O(N) for visited and bank set
  */

class Solution
{
public:
    int minMutation(string startGene, string endGene, vector<string>& bank)
    {
        // Initialize queue for BFS
        queue<string> q;

        // Convert bank to set for O(1) lookup
        unordered_set<string> bankset(begin(bank), end(bank));
        unordered_set<string> visited;

        q.push(startGene);
        visited.insert(startGene);

        int level = 0; // Level indicates number of mutations

        while (!q.empty()) {
            int size = q.size();

            while (size--) {
                string curr = q.front();
                q.pop();

                // If we reach the target gene
                if (curr == endGene)
                    return level;

                // Try mutating each position with A, T, G, C
                for (char ch : "ATGC") {
                    for (int i = 0; i < curr.length(); i++) {
                        string neighbour = curr;
                        neighbour[i] = ch;

                        // Only consider valid mutations
                        if (visited.find(neighbour) == visited.end() && bankset.find(neighbour) != bankset.end()) {
                            q.push(neighbour);
                            visited.insert(neighbour);
                        }
                    }
                }
            }

            level++; // Move to next level (next mutation)
        }

        return -1; // Mutation not possible
    }
};
