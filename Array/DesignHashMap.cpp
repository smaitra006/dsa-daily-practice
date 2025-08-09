/* ==============================================================================
 * Problem: Design HashMap
 *
 * Task:
 * - Implement a HashMap without using built-in hash table libraries.
 * - Operations:
 *     1. `put(key, value)` — Insert or update the value for a given key.
 *     2. `get(key)`        — Retrieve the value mapped to `key`, or -1 if not present.
 *     3. `remove(key)`     — Remove the mapping for a given key.
 *
 * Approach:
 * - Since constraints guarantee keys are in range [0, 10^6],
 *   we can use a fixed-size vector to directly store values by their keys.
 * - Initialize all positions with `-1` to indicate no mapping.
 *
 * Time Complexity  : O(1) for all operations (direct indexing).
 * Space Complexity : O(1e6) = O(1) fixed extra space.
 * ============================================================================== */

#include <bits/stdc++.h>
using namespace std;

class MyHashMap {
private:
    vector<int> map;  // Direct mapping: key → value

public:
    // Initialize data structure with default values (-1 means key not present)
    MyHashMap() : map(1000001, -1) {}

    // Insert or update the key-value pair
    void put(int key, int value)
    {
        map[key] = value;
    }

    // Retrieve the value for the key; return -1 if not present
    int get(int key)
    {
        return map[key];
    }

    // Remove the key by resetting its value to -1
    void remove(int key)
    {
        map[key] = -1;
    }
};

/* ==============================================================================
 * Example Usage:
 *
 * int main() {
 *     MyHashMap hashMap;
 *     hashMap.put(1, 1);
 *     hashMap.put(2, 2);
 *     cout << hashMap.get(1) << endl;  // Output: 1
 *     cout << hashMap.get(3) << endl;  // Output: -1
 *     hashMap.put(2, 1);               // Update value for key 2
 *     cout << hashMap.get(2) << endl;  // Output: 1
 *     hashMap.remove(2);
 *     cout << hashMap.get(2) << endl;  // Output: -1
 *
 *     return 0;
 * }
 * ============================================================================== */
