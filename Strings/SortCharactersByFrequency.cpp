#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string frequencySort(string s)
    {
        unordered_map<char, int> freq;
        for (char c : s) freq[c]++;

        vector<pair<char, int>> arr(freq.begin(), freq.end());

        sort(arr.begin(), arr.end(), [](auto& a, auto& b) {
            return a.second > b.second;
            });

        string result;
        for (auto& p : arr) {
            result.append(p.second, p.first);
        }
        return result;
    }
};
