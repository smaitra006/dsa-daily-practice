#include <bits/stdc++.h>
using namespace std;

/* =============================================================================
 * PROBLEM 990: SATISFIABILITY OF EQUALITY EQUATIONS (LeetCode)
 * ============================================================================= */

 /**
  * @brief Determine if all given equality and inequality equations are satisfiable
  *
  * PROBLEM STATEMENT:
  * You are given an array of strings `equations` of length n representing relationships between variables.
  * Each equation is of the form "a==b" or "a!=b", where a and b are lowercase English letters.
  * Return true if it is possible to assign integers to variable names such that all equations are satisfied.
  *
  * EXAMPLE:
  * Input: ["a==b","b!=a"]
  * Output: false
  *
  * APPROACH:
  * - Use Disjoint Set Union (DSU) to group variables connected by equality (==).
  * - Then, for every inequality (!=), check if both variables belong to the same group.
  * - If they do, it's a contradiction → return false.
  *
  * ALGORITHM:
  * 1. Initialize DSU for 26 lowercase letters.
  * 2. Process all equations with `==` and perform union.
  * 3. Process all equations with `!=` and check for contradiction.
  *
  * COMPLEXITY:
  * Time: O(N * α(26)) ≈ O(N), where N = number of equations
  * Space: O(26)
  */

class Solution
{
public:
    vector<int> parent;
    vector<int> rank;

    // FIND operation with path compression
    int findParent(int x)
    {
        if (parent[x] == x)
            return x;
        return parent[x] = findParent(parent[x]);
    }

    // UNION operation by rank
    void Union(int x, int y)
    {
        int px = findParent(x);
        int py = findParent(y);

        if (px == py)
            return;

        if (rank[px] < rank[py]) {
            parent[px] = py;
        }
        else if (rank[px] > rank[py]) {
            parent[py] = px;
        }
        else {
            parent[py] = px;
            rank[px]++;
        }
    }

    bool equationsPossible(vector<string>& equations)
    {
        parent.resize(26);
        rank.resize(26, 0);

        // Step 1: Initialize parent of each variable to itself
        for (int i = 0; i < 26; i++) {
            parent[i] = i;
        }

        // Step 2: Union all equal variables
        for (const string& eq : equations) {
            if (eq[1] == '=') {
                int u = eq[0] - 'a';
                int v = eq[3] - 'a';
                Union(u, v);
            }
        }

        // Step 3: Check all not-equal constraints
        for (const string& eq : equations) {
            if (eq[1] == '!') {
                int u = eq[0] - 'a';
                int v = eq[3] - 'a';

                if (findParent(u) == findParent(v)) {
                    return false; // Contradiction found
                }
            }
        }

        return true; // No contradiction
    }
};
