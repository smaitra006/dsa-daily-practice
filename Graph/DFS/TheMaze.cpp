#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: The Maze (LeetCode 490)
================================================================================
Task:
    There is a ball in a maze represented by a binary grid.
    The ball can go through empty spaces (0) and cannot go through walls (1).

    The ball can roll up, down, left, or right, but it will not stop rolling
    until hitting a wall. When the ball stops, it can choose the next direction.

    Given the ball's start position, the destination, and the maze grid,
    determine whether the ball can stop at the destination.

--------------------------------------------------------------------------------
Approach (DFS / BFS with Rolling Simulation):
    1. Use DFS (or BFS) to simulate ball movement.
    2. From a given position, roll the ball in one of the four directions until
       it hits a wall.
    3. The stopping cell before the wall becomes the next node in the search.
    4. Keep a visited set to avoid reprocessing the same stop positions.
    5. If the ball can stop at the destination, return true; otherwise, false.

--------------------------------------------------------------------------------
Complexity Analysis:
    Time Complexity:  O(M * N)
        - Each cell is visited at most once as a stopping point.
    Space Complexity: O(M * N)
        - Visited matrix + recursion/BFS queue.
================================================================================
*/

class Solution {
public:
    int m, n;
    vector<pair<int, int>> directions = { {1,0}, {0,1}, {-1,0}, {0,-1} }; // 4 directions

    bool dfs(vector<vector<int>>& maze, vector<int>& start, vector<int>& dest, vector<vector<int>>& visited)
    {
        if (visited[start[0]][start[1]]) return false;
        if (start == dest) return true;
        visited[start[0]][start[1]] = 1;

        for (auto dir : directions) {
            int r = start[0];
            int c = start[1];

            // Roll until hitting a wall
            while (r + dir.first >= 0 && r + dir.first < m &&
                c + dir.second >= 0 && c + dir.second < n &&
                maze[r + dir.first][c + dir.second] == 0) {
                r += dir.first;
                c += dir.second;
            }

            vector<int> newPos = { r, c };
            if (dfs(maze, newPos, dest, visited)) return true;
        }
        return false;
    }

    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination)
    {
        m = maze.size();
        n = maze[0].size();
        vector<vector<int>> visited(m, vector<int>(n, 0));
        return dfs(maze, start, destination, visited);
    }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    maze = [
      [0,0,1,0,0],
      [0,0,0,0,0],
      [0,0,0,1,0],
      [1,1,0,1,1],
      [0,0,0,0,0]
    ]
    start = [0,4]
    destination = [4,4]
Output:
    true

--------------------------------------------------------------------------------
Input:
    maze = [
      [0,0,1,0,0],
      [0,0,0,0,0],
      [0,0,0,1,0],
      [1,1,0,1,1],
      [0,0,0,0,0]
    ]
    start = [0,4]
    destination = [3,2]
Output:
    false
================================================================================
*/

