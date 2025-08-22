#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: Accounts Merge (LeetCode 721)
================================================================================
Task:
    Given a list of accounts where each element accounts[i] is a list of strings,
    where the first element accounts[i][0] is a name, and the rest are emails
    belonging to that account. Merge accounts that belong to the same person
    (if any email is shared across accounts).

--------------------------------------------------------------------------------
Key Insight:
    - Build a graph where each email is a node.
    - Add an edge between the first email in an account and all other emails.
    - Perform DFS to collect all connected emails → one connected component = one person.

--------------------------------------------------------------------------------
Approach (Graph + DFS):
    1. Construct adjacency list for all emails.
    2. Traverse emails using DFS to collect connected components.
    3. For each connected component:
        - Add account holder's name.
        - Sort the emails lexicographically.
    4. Push result.

--------------------------------------------------------------------------------
Complexity Analysis:
    Let N = total number of accounts, M = total number of emails.

    Time Complexity:  O(M log M)
        - Each email is visited once (DFS → O(M))
        - Sorting emails in each component → O(M log M)

    Space Complexity: O(M)
        - Adjacency list, visited set, recursion stack.
================================================================================
*/

class Solution {
public:
    // DFS to collect all connected emails of the same account
    void dfs(unordered_map<string, vector<string>>& adj,
        unordered_set<string>& visited,
        vector<string>& same_email,
        string curr_email)
    {
        visited.insert(curr_email);
        same_email.push_back(curr_email);

        for (auto neighbour : adj[curr_email]) {
            if (!visited.contains(neighbour)) {
                dfs(adj, visited, same_email, neighbour);
            }
        }
    }

    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts)
    {
        unordered_map<string, vector<string>> adj;

        // Step 1: Build graph (connect first email to all others in same account)
        for (auto& acc : accounts) {
            string first_email = acc[1];
            for (int i = 2; i < acc.size(); i++) {
                adj[first_email].push_back(acc[i]);
                adj[acc[i]].push_back(first_email);
            }
        }

        // Step 2: Traverse graph to get connected components
        vector<vector<string>> result;
        unordered_set<string> visited;

        for (auto& acc : accounts) {
            string first_email = acc[1];
            if (!visited.contains(first_email)) {
                vector<string> same_email;
                same_email.push_back(acc[0]);  // account holder's name
                dfs(adj, visited, same_email, first_email);

                // Sort collected emails (skip name at index 0)
                sort(same_email.begin() + 1, same_email.end());

                result.push_back(same_email);
            }
        }

        return result;
    }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    accounts = [
        ["John","johnsmith@mail.com","john_newyork@mail.com"],
        ["John","johnsmith@mail.com","john00@mail.com"],
        ["Mary","mary@mail.com"],
        ["John","johnnybravo@mail.com"]
    ]

Output:
    [
        ["John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"],
        ["Mary","mary@mail.com"],
        ["John","johnnybravo@mail.com"]
    ]

Explanation:
    - "johnsmith@mail.com" connects the first two accounts.
    - They merge into one component with all John's emails.
================================================================================
*/
