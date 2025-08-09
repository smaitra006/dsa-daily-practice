/* ==============================================================================
 * Problem: Design HashSet
 *
 * Task:
 * - Implement a HashSet without using built-in hash table libraries.
 * - Operations:
 *     1. `add(key)`     — Insert the value `key` into the HashSet.
 *     2. `remove(key)`  — Remove the value `key` from the HashSet.
 *     3. `contains(key)`— Return true if the HashSet contains the value `key`.
 *
 * Approach:
 * - Since the constraints guarantee keys are in range [0, 10^6],
 *   we can use a fixed-size boolean vector to directly map keys to existence.
 * - Index = key, Value = presence status.
 *
 * Time Complexity  : O(1) for all operations (direct indexing).
 * Space Complexity : O(1e6) = O(1) fixed extra space.
 * ============================================================================== */

#include <bits/stdc++.h>
using namespace std;

class MyHashSet {
private:
    vector<bool> data;  // Direct mapping from key → presence

public:
    // Initialize the data structure with maximum key size
    MyHashSet() : data(1000001, false) {}

    // Insert the key into the set
    void add(int key)
    {
        data[key] = true;
    }

    // Remove the key from the set
    void remove(int key)
    {
        data[key] = false;
    }

    // Check if the set contains the key
    bool contains(int key)
    {
        return data[key];
    }
};

/* ==============================================================================
 * Example Usage:
 *
 * int main() {
 *     MyHashSet hashSet;
 *     hashSet.add(1);
 *     hashSet.add(2);
 *     cout << boolalpha << hashSet.contains(1) << endl; // Output: true
 *     cout << boolalpha << hashSet.contains(3) << endl; // Output: false
 *     hashSet.add(2);
 *     cout << boolalpha << hashSet.contains(2) << endl; // Output: true
 *     hashSet.remove(2);
 *     cout << boolalpha << hashSet.contains(2) << endl; // Output: false
 *
 *     return 0;
 * }
 * ============================================================================== */
