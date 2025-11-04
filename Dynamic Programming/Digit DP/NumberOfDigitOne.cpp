#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  int memo[10][2][10];
  int solve(string &n, int idx, bool tight, int cnt)
  {
    if (idx == n.size())
      return cnt;
    if (memo[idx][tight][cnt] != -1)
      return memo[idx][tight][cnt];
    int limit = (tight == true) ? n[idx] - '0' : 9;
    int ans = 0;
    for (int i = 0; i <= limit; i++)
    {
      int updatedCnt = (i == 1) ? cnt + 1 : cnt;
      ans += solve(n, idx + 1, (i == n[idx]), updatedCnt);
    }
    return ans;
  }
  int countDigitOne(int n)
  {
    string s = to_string(n);
    memset(memo, -1, sizeof(memo));
    return solve(s, 0, 1, 0);
  }
};
