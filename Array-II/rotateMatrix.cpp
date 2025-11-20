#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
    ============================================================================
    PROBLEM: Rotate Image (90° Clockwise)
    ============================================================================
    Given an n x n matrix, rotate it 90 degrees clockwise IN-PLACE.

    Two approaches are provided:

        1️⃣ Brute Force (uses extra matrix) — O(n²) time, O(n²) space
        2️⃣ Optimal (Transpose + Reverse) — O(n²) time, O(1) space

    Both versions are very important for interviews.
*/



/*
    ============================================================================
    1️⃣ BRUTE FORCE APPROACH — Using a second matrix
    ============================================================================
    IDEA:
        Create a new matrix "ans".
        The mapping for 90° clockwise rotation is:

            ans[col][n - row - 1] = matrix[row][col]

        After filling ans, copy ans → matrix.

    WHY IT WORKS:
        For every element, its new rotated position follows this formula.
        This approach is simple but NOT in-place.

    TIME COMPLEXITY: O(n²)
    SPACE COMPLEXITY: O(n²)
*/
class BruteForceSolution {
public:
    void rotate(vector<vector<int>>& matrix) {

        int n = matrix.size();
        vector<vector<int>> ans(n, vector<int>(n));

        int colToFill = n - 1;  // tracks the last column of ans to fill

        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                // Move matrix[row][col] → ans[col][new_col]
                ans[col][colToFill] = matrix[row][col];
            }
            colToFill--;
        }

        matrix = ans; // copy rotated matrix back
    }
};




/*
    ============================================================================
    2️⃣ OPTIMAL APPROACH — TRANSPOSE + REVERSE EACH ROW
    ============================================================================
    This is the MOST ASKED interview solution.

    OBSERVATION:
        A 90° clockwise rotation can be achieved via:
            Step 1: Transpose the matrix
                    (swap matrix[i][j] with matrix[j][i])

            Step 2: Reverse each row

    WHY THIS WORKS:
        - Transpose converts rows → columns
        - Reversing each row aligns it to match 90° rotation

    EXAMPLE:
        Before transpose:       After transpose:
        1 2 3                   1 4 7
        4 5 6       →           2 5 8
        7 8 9                   3 6 9

        After reversing rows:
        7 4 1
        8 5 2
        9 6 3   ← Final rotated matrix

    TIME COMPLEXITY: O(n²)
    SPACE COMPLEXITY: O(1)
*/
class OptimalSolution {
public:
    void rotate(vector<vector<int>>& matrix) {

        int n = matrix.size();

        // Step 1: Transpose the matrix
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }

        // Step 2: Reverse each row
        for (int i = 0; i < n; i++) {
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};




/*
    ============================================================================
    MAIN FUNCTION — DEMO FOR BOTH SOLUTIONS
    ============================================================================
*/
int main() {

    vector<vector<int>> mat1 = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };

    vector<vector<int>> mat2 = mat1;

    BruteForceSolution brute;
    OptimalSolution optimal;

    brute.rotate(mat1);
    optimal.rotate(mat2);

    cout << "Brute Force Rotated Matrix:\n";
    for (auto &row : mat1) {
        for (int x : row) cout << x << " ";
        cout << "\n";
    }

    cout << "\nOptimal Rotated Matrix:\n";
    for (auto &row : mat2) {
        for (int x : row) cout << x << " ";
        cout << "\n";
    }

    return 0;
}
