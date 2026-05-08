// ============================================================
//  Balanced String - Non-Recursive Algorithm (Brute Force)
//  Algorithm: Check all possible substrings
//  Time Complexity: O(n^3)
//  Space Complexity: O(n)
// ============================================================

#include <iostream>
#include <string>
#include <set>
using namespace std;

// ── Helper: check if a string is "balanced" ──────────────────
// A string is balanced if:
//   1. It contains exactly 2 distinct characters
//   2. Both characters appear the same number of times
bool isBalanced(const string& s) {
    set<char> distinct(s.begin(), s.end());   // Step 1: O(n)
    if (distinct.size() != 2)                 // Must have exactly 2 chars
        return false;

    char c1 = *distinct.begin();
    char c2 = *next(distinct.begin());

    int cnt1 = 0, cnt2 = 0;
    for (char c : s) {                        // Step 2: count each char O(n)
        if (c == c1) cnt1++;
        else         cnt2++;
    }
    return cnt1 == cnt2;                      // Step 3: equal counts?
}

// ── Main algorithm: Non-Recursive (Brute Force) ──────────────
// Enumerate every substring S[i..j] and keep track of the
// longest one that passes isBalanced().
int longestBalancedNonRecursive(const string& S) {
    int n = S.length();
    int maxLen = 0;

    // Outer loop  — starting index i:  O(n)
    for (int i = 0; i < n; i++) {
        // Inner loop — ending index j (exclusive): O(n)
        for (int j = i + 2; j <= n; j += 2) {   // step 2: odd len can't be balanced
            string sub = S.substr(i, j - i);     // O(n) copy
            if (isBalanced(sub)) {               // O(n) check
                maxLen = max(maxLen, (int)sub.length());
            }
        }
    }
    return maxLen;  // Total: O(n^3)
}

// ── Entry point ──────────────────────────────────────────────
int main() {
    // --- Test cases from the task sheet ---
    string tests[] = {"cabbacc", "abababa", "aaaaaaa"};
    int expected[]  = {4,         6,         0};

    cout << "=== Balanced String — Non-Recursive Algorithm ===" << endl;
    cout << "-------------------------------------------------" << endl;

    for (int t = 0; t < 3; t++) {
        int result = longestBalancedNonRecursive(tests[t]);
        cout << "Input    : \"" << tests[t]   << "\""  << endl;
        cout << "Output   : "  << result               << endl;
        cout << "Expected : "  << expected[t]          << endl;
        cout << "Status   : "  << (result == expected[t] ? "PASS ✓" : "FAIL ✗") << endl;
        cout << "-------------------------------------------------" << endl;
    }

    // --- Interactive input ---
    cout << "\nEnter a string to test: ";
    string input;
    cin >> input;
    cout << "Longest balanced substring length = "
         << longestBalancedNonRecursive(input) << endl;

    return 0;
}
