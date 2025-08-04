#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int maxEle = INT_MIN, secondMaxEle = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (arr[i] > maxEle) {
            secondMaxEle = maxEle;
            maxEle = arr[i];
        }
        else if (arr[i] > secondMaxEle && arr[i] != maxEle) {
            secondMaxEle = arr[i];
        }
    }
    if (secondMaxEle == INT_MIN) {
        cout << "No second maximum exists" << endl;
    }
    else {
        cout << secondMaxEle << endl;
    }

    return 0;
}
