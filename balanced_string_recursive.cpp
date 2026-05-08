// ============================================================
//  Balanced String - Recursive Algorithm
//  Algorithm: Try every pair of characters, slide a window
//             recursively to find the longest balanced substring
//  Time Complexity: O(n^2 * k)  where k = number of char pairs
//  Space Complexity: O(n) — recursion stack depth
// ============================================================

#include <iostream>
#include <string>
#include <set>
#include <vector>
using namespace std;

// ── Recursive helper ─────────────────────────────────────────
// Scans S from index `start` keeping a running window that
// contains only c1 and c2.
// cnt1, cnt2 : counts of c1 and c2 in the current window
// maxLen     : best balanced length found so far
//
// Base case : start == n  → return maxLen
// Recursive : process S[start] and call for start+1
int checkPairRec(const string& S, char c1, char c2,
                  int start, int cnt1, int cnt2, int maxLen) {
    // ── Base case ────────────────────────────────────────────
    if (start == (int)S.size())
        return maxLen;

    char ch = S[start];

    // ── Character not in our pair → reset window ─────────────
    if (ch != c1 && ch != c2)
        return checkPairRec(S, c1, c2, start + 1, 0, 0, maxLen);

    // ── Update counts ────────────────────────────────────────
    if (ch == c1) cnt1++;
    else          cnt2++;

    // ── Check if current window is balanced ──────────────────
    if (cnt1 == cnt2 && cnt1 > 0)
        maxLen = max(maxLen, cnt1 + cnt2);

    // ── Recurse on the rest ───────────────────────────────────
    return checkPairRec(S, c1, c2, start + 1, cnt1, cnt2, maxLen);
}

// ── Main algorithm: Recursive ─────────────────────────────────
// For every pair of distinct characters (c1, c2) present in S,
// run the recursive scan and keep the global maximum.
int longestBalancedRecursive(const string& S) {
    // Collect distinct characters
    set<char> chars(S.begin(), S.end());
    vector<char> cv(chars.begin(), chars.end());

    int maxLen = 0;

    // Try every pair — O(k^2) pairs where k = |alphabet| ≤ 26
    for (int i = 0; i < (int)cv.size(); i++) {
        for (int j = i + 1; j < (int)cv.size(); j++) {
            int result = checkPairRec(S, cv[i], cv[j],
                                      0, 0, 0, 0);
            maxLen = max(maxLen, result);
        }
    }
    return maxLen;
}

// ── Entry point ───────────────────────────────────────────────
int main() {
    // --- Test cases from the task sheet ---
    string tests[] = {"cabbacc", "abababa", "aaaaaaa"};
    int expected[]  = {4,         6,         0};

    cout << "=== Balanced String — Recursive Algorithm ===" << endl;
    cout << "---------------------------------------------" << endl;

    for (int t = 0; t < 3; t++) {
        int result = longestBalancedRecursive(tests[t]);
        cout << "Input    : \"" << tests[t]   << "\""  << endl;
        cout << "Output   : "  << result               << endl;
        cout << "Expected : "  << expected[t]          << endl;
        cout << "Status   : "  << (result == expected[t] ? "PASS ✓" : "FAIL ✗") << endl;
        cout << "---------------------------------------------" << endl;
    }

    // --- Interactive input ---
    cout << "\nEnter a string to test: ";
    string input;
    cin >> input;
    cout << "Longest balanced substring length = "
         << longestBalancedRecursive(input) << endl;

    return 0;
}
