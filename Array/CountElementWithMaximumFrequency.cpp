#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  int maxFrequencyElements(vector<int> &nums)
  {
    int n = nums.size();
    unordered_map<int, int> mp;
    int max_frequency = 0, ans = -1;
    for (int i = 0; i < n; i++)
    {
      if (mp.count(nums[i]) == 0)
      {
        max_frequency = max(max_frequency, 1);
      }
      else
      {
        max_frequency = max(max_frequency, mp[nums[i]] + 1);
      }
      mp[nums[i]]++;
    }
  }
};
