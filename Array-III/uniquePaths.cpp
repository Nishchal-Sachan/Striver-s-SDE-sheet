#include <iostream>
#include <vector>
using namespace std;

/*
    ============================================================================
                           ✅ UNIQUE PATHS — 4 APPROACHES
    ============================================================================

    A robot is placed at the top-left (0,0) of an m x n grid.
    It may only move:
            → Right  (j + 1)
            → Down   (i + 1)

    Goal:
            Count total distinct paths to reach bottom-right (m-1, n-1)

    We implement:
        1️⃣ Pure Recursion (Exponential)
        2️⃣ Recursion + Memoization (Top-Down DP)
        3️⃣ Bottom-Up DP Tabulation
        4️⃣ Combinatorics (O(1) space, Most optimal mathematically)
*/



// ============================================================================
// 1️⃣ APPROACH 1 — PURE RECURSION (EXPONENTIAL)
// ============================================================================
//
// Intuition:
//
// From any cell (i,j), we have TWO choices:
//      → move DOWN  to (i+1, j)
//      → move RIGHT to (i, j+1)
//
// The total paths from (i,j) = sum of paths from these two moves.
//
// Base cases:
//      ✅ If we reach destination → return 1 path
//      ✅ If we go outside grid → return 0 paths
//
// Very slow because:
//      - overlapping subproblems
//      - recomputation
//
// Complexity:
//      ⏱ Time:  O(2^(m+n))   (worst case branching recursion)
//      💾 Space: O(m+n) recursion depth
// ============================================================================

class RecursionSolution {
public:
    int countPaths(int i, int j, int m, int n) {

        // If we reached bottom-right cell → valid path found
        if (i == m - 1 && j == n - 1)
            return 1;

        // If we step outside grid → invalid path
        if (i >= m || j >= n)
            return 0;

        // Recursive exploration:
        //   Option 1: Go Down
        //   Option 2: Go Right
        return countPaths(i + 1, j, m, n) +
               countPaths(i, j + 1, m, n);
    }

    int uniquePaths(int m, int n) {
        return countPaths(0, 0, m, n);
    }
};



// ============================================================================
// 2️⃣ APPROACH 2 — MEMOIZATION (TOP-DOWN DP)
// ============================================================================
//
// Fixing recursion inefficiency using DP.
//
// dp[i][j] definition:
//      Number of ways to reach destination from cell (i,j)
//
// Transition:
//      dp[i][j] = dp[i+1][j] + dp[i][j+1]
//
// WHY pass dp BY REFERENCE?
//      If passed by value → copy created → memoization breaks
//
// Complexity:
//      ⏱ Time:  O(m*n)
//      💾 Space: O(m*n) + recursion stack
// ============================================================================

class MemoSolution {
public:
    int countPaths(int i, int j, int m, int n, vector<vector<int>>& dp) {

        if (i == m - 1 && j == n - 1)
            return 1;

        if (i >= m || j >= n)
            return 0;

        // If already computed, return stored value
        if (dp[i][j] != -1)
            return dp[i][j];

        // Compute and store result
        return dp[i][j] =
            countPaths(i + 1, j, m, n, dp) +
            countPaths(i, j + 1, m, n, dp);
    }

    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, -1));
        return countPaths(0, 0, m, n, dp);
    }
};



// ============================================================================
// 3️⃣ APPROACH 3 — TABULATION (BOTTOM-UP DP)
// ============================================================================
//
// Build solution iteratively.
//
// dp[i][j] meaning:
//      Number of ways to reach (i,j) from start (0,0)
//
// Initialization:
//      First row → all 1's (only right moves possible)
//      First column → all 1's (only down moves possible)
//
// Transition formula:
//      dp[i][j] = dp[i-1][j] + dp[i][j-1]
//
// Complexity:
//      ⏱ Time:  O(m*n)
//      💾 Space: O(m*n)
// ============================================================================

class TabulationSolution {
public:
    int uniquePaths(int m, int n) {

        vector<vector<int>> dp(m, vector<int>(n, 1));

        // Fill grid from (1,1) since edges already 1
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {

                // Ways to reach cell = from top + from left
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }

        return dp[m - 1][n - 1];
    }
};



// ============================================================================
// 4️⃣ APPROACH 4 — COMBINATORICS (O(1) SPACE, FASTEST)
// ============================================================================
//
// KEY OBSERVATION:
// To reach destination, robot must make:
//
//      ✅ (m-1) downward moves
//      ✅ (n-1) rightward moves
//
// Total moves = (m+n-2)
// Choose positions of DOWN moves:
//
//      Answer = C(m+n-2, m-1)
//             = (m+n-2)! / ( (m-1)! * (n-1)! )
//
// Instead of factorials (overflow risk), compute iteratively:
//
//      res *= (total - R + i) / i
//
// Complexity:
//      ⏱ Time:  O(min(m,n))
//      💾 Space: O(1)
// ============================================================================

class CombinatoricsSolution {
public:
    int uniquePaths(int m, int n) {

        long double res = 1;
        int R = m - 1;                // choose down moves
        int total = m + n - 2;        // total moves

        // Compute nCr iteratively
        for (int i = 1; i <= R; i++) {
            res = res * (total - R + i) / i;
        }

        return (int)res;  // result always integer
    }
};



// ============================================================================
// ✅ MAIN — RUN ALL FOUR APPROACHES
// ============================================================================

int main() {

    int m = 3, n = 7;

    RecursionSolution s1;
    MemoSolution s2;
    TabulationSolution s3;
    CombinatoricsSolution s4;

    cout << "Recursion               : " << s1.uniquePaths(m, n) << endl;
    cout << "Memoization (DP)        : " << s2.uniquePaths(m, n) << endl;
    cout << "Tabulation (DP)         : " << s3.uniquePaths(m, n) << endl;
    cout << "Combinatorics (O(1))    : " << s4.uniquePaths(m, n) << endl;

    return 0;
}
