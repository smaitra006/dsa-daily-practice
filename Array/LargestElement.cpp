#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int maxEle = INT_MIN;
    for(int i = 0; i < n; i++) {
        if(arr[i] > maxEle) maxEle = arr[i];
    }
    cout << maxEle << endl;

    return 0;
}
