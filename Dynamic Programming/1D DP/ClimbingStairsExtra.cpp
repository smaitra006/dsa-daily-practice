// Competitive Programming Template (C++)
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back
#define all(v) v.begin(), v.end()
#define endl '\n'
#define fast_io ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

#ifdef LOCAL
#define debug(x) cerr << #x << " = " << x << endl
#else
#define debug(x)
#endif

const int MOD = 1e9 + 7;
const int INF = 1e18;
typedef vector<int> vi;
typedef pair<int, int> pii;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int lcm(int a, int b) { return a / gcd(a, b) * b; }

int recur(int level, int n)
{ // Ways to reach n from current level

    // Pruning
    if (level > n) {
        return 0;
    }

    // Base case
    if (level == n) {
        return 1;
    }

    // Choice -> 1step, 2 step, 3 step
    // Check
    int step1 = 0, step2 = 0, step3 = 0;
    if (level + 1 <= n) {
        step1 = recur(level + 1, n);
    }
    if (level + 2 <= n) {
        step2 = recur(level + 2, n);
    }
    if (level + 3 <= n) {
        step3 = recur(level + 3, n);
    }

    return step1 + step2 + step3;

}

void solve()
{
    // Your logic here
    int n;
    cin >> n;
    cout << recur(0, n) << endl;
}

int32_t main()
{
    fast_io
        int t = 1;
    // cin >> t; // Uncomment if multiple test cases
    while (t--) solve();
    return 0;
}
