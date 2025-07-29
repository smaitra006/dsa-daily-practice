#include <bits/stdc++.h>
using namespace std;

/* ===================================================================
 * NINJA'S TRAINING (DP - NOT DOING SAME ACTIVITY ON TWO CONSECUTIVE DAYS)
 * =================================================================== */

 /**
  * @brief Given a points matrix of size n x 3 (n days, 3 activities),
  *        return the maximum points the ninja can accumulate over n days
  *        such that he does NOT repeat the same activity on consecutive days.
  *
  * Recurrence:
  * -----------
  * dp[day][last] = max(
  *     points[day][i] + dp[day-1][i] for all i != last
  * )
  *
  * TIME COMPLEXITY: O(n * 4 * 3) = O(n)
  * SPACE COMPLEXITY: O(n * 4) or O(1) if optimized
  */

class Solution
{
public:
    /* ---------------------------------------------------------------
     * METHOD 1: Plain Recursion (Exponential Time)
     * --------------------------------------------------------------- */
    int recur(int day, int last, vector<vector<int>>& points)
    {
        if (day == 0) {
            int maxPoint = 0;
            for (int i = 0; i < 3; ++i) {
                if (i != last)
                    maxPoint = max(maxPoint, points[0][i]);
            }
            return maxPoint;
        }

        int maxPoint = 0;
        for (int i = 0; i < 3; ++i) {
            if (i != last) {
                int point = points[day][i] + recur(day - 1, i, points);
                maxPoint = max(maxPoint, point);
            }
        }
        return maxPoint;
    }

    /* ---------------------------------------------------------------
     * METHOD 2: Memoization (Top-Down DP)
     * TIME: O(n * 4), SPACE: O(n * 4)
     * --------------------------------------------------------------- */
    int memo(int day, int last, vector<vector<int>>& points, vector<vector<int>>& dp)
    {
        if (day == 0) {
            int maxPoint = 0;
            for (int i = 0; i < 3; ++i) {
                if (i != last)
                    maxPoint = max(maxPoint, points[0][i]);
            }
            return dp[0][last] = maxPoint;
        }

        if (dp[day][last] != -1)
            return dp[day][last];

        int maxPoint = 0;
        for (int i = 0; i < 3; ++i) {
            if (i != last) {
                int point = points[day][i] + memo(day - 1, i, points, dp);
                maxPoint = max(maxPoint, point);
            }
        }

        return dp[day][last] = maxPoint;
    }

    /* ---------------------------------------------------------------
     * METHOD 3: Tabulation (Bottom-Up DP)
     * TIME: O(n * 4), SPACE: O(n * 4)
     * --------------------------------------------------------------- */
    int tabulation(vector<vector<int>>& points)
    {
        int n = points.size();
        vector<vector<int>> dp(n, vector<int>(4, 0));

        // Base case for day 0
        dp[0][0] = max(points[0][1], points[0][2]);                 // last = 0
        dp[0][1] = max(points[0][0], points[0][2]);                 // last = 1
        dp[0][2] = max(points[0][0], points[0][1]);                 // last = 2
        dp[0][3] = max({ points[0][0], points[0][1], points[0][2] }); // last = 3 (no restriction)

        for (int day = 1; day < n; ++day) {
            for (int last = 0; last < 4; ++last) {
                dp[day][last] = 0;
                for (int i = 0; i < 3; ++i) {
                    if (i != last) {
                        int point = points[day][i] + dp[day - 1][i];
                        dp[day][last] = max(dp[day][last], point);
                    }
                }
            }
        }

        return dp[n - 1][3];
    }

    /* ---------------------------------------------------------------
     * METHOD 4: Space Optimized Tabulation (O(1) space)
     * TIME: O(n * 4), SPACE: O(4)
     * --------------------------------------------------------------- */
    int ninjaTraining(vector<vector<int>>& points)
    {
        int n = points.size();
        vector<int> prev(4, 0);

        // Base case
        prev[0] = max(points[0][1], points[0][2]);
        prev[1] = max(points[0][0], points[0][2]);
        prev[2] = max(points[0][0], points[0][1]);
        prev[3] = max({ points[0][0], points[0][1], points[0][2] });

        for (int day = 1; day < n; ++day) {
            vector<int> temp(4, 0);

            for (int last = 0; last < 4; ++last) {
                temp[last] = 0;
                for (int i = 0; i < 3; ++i) {
                    if (i != last) {
                        int point = points[day][i] + prev[i];
                        temp[last] = max(temp[last], point);
                    }
                }
            }

            prev = temp;
        }

        return prev[3];
    }
};
