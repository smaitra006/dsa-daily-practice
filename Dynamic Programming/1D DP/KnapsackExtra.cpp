// Competitive Programming Template (C++)
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back
#define all(v) v.begin(), v.end()
#define endl '\n'
#define fast_io ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

const int MOD = 1e9+7;
const int INF = 1e18;
typedef vector<int> vi;
typedef pair<int, int> pii;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int lcm(int a, int b) { return a / gcd(a, b) * b; }

int t[1001];
int s[1001];

int recur(int item, int n, int x, int k, int ans) {
    // Max skill i can make from current item -> n - 1

    // Base case
    if(item == n) { // Used up all items
        return 0;
    }

    // Choice -> Take or not take
    // Check -> if its under time bound x, under k and under n
    int not_take = recur(item + 1, n, x, k, ans);
    int take = 0;
    if(item + 1 <= n && (x - t[item]) >= 0 && (k - 1) >= 0) {
        take = recur(item + 1, n, x - t[item], k - 1, ans + s[item]);
    }
    return max(take, not_take);
}

void solve() {
    // Your logic here
    int n, x, k;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> t[i];
    }
    for(int i = 0; i < n; i++) {
        cin >> s[i];
    }
    cin >> x >> k;
    cout << recur(0, n, x, k, 0);
}

int32_t main() {
    fast_io
    int t = 1;
    // cin >> t; // Uncomment if multiple test cases
    while(t--) solve();
    return 0;
}
