#include <iostream>
#include <vector>
#include <utility>
using namespace std;

/*
    ---------------------------------------------------------------
    PROBLEM: Set Matrix Zeroes
    ---------------------------------------------------------------
    If an element of the matrix is 0, you must set its entire row
    and column to 0.

    Example:
    
        Input:
        1 1 1
        1 0 1
        1 1 1

        Output:
        1 0 1
        0 0 0
        1 0 1

    ---------------------------------------------------------------
    YOUR APPROACH (Brute Force With Extra Space)
    ---------------------------------------------------------------
    1. Traverse the matrix.
    2. Whenever you find a 0, store its (row, col) in a vector.
    3. After collecting all 0 positions, iterate over them:
        - Make entire row = 0
        - Make entire column = 0

    TIME COMPLEXITY: 
        O((rows * cols) + K * (rows + cols))
        where K = number of zeroes.

    SPACE COMPLEXITY:
        O(K)  → storing all zero positions.

    This approach is correct but not optimal.
*/

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();

        // Stores all (row, col) positions where matrix[i][j] == 0
        vector<pair<int,int>> zeroes;

        // Step 1: collect all zero positions
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                if(matrix[i][j] == 0) {
                    zeroes.push_back(make_pair(i, j));
                }
            }
        }

        // Step 2: for each zero position, make row and column = 0
        for(int i = 0; i < zeroes.size(); i++) {
            int r = zeroes[i].first;
            int c = zeroes[i].second;

            // Set entire column c = 0
            for(int a = 0; a < rows; a++) {
                matrix[a][c] = 0;
            }

            // Set entire row r = 0
            for(int a = 0; a < cols; a++) {
                matrix[r][a] = 0;
            }
        }
    }
};


/*
    ======================================================================
    OPTIMIZED APPROACH (O(1) Extra Space)
    ======================================================================
    The idea is brilliant and commonly asked in interviews:

    - Instead of using extra space to store zero locations,
      use the FIRST ROW and FIRST COLUMN of the matrix itself
      as markers / indicators.

    STEPS:
    -----------------------------------------------------
    1. Check if first row should be zero.
    2. Check if first column should be zero.
    3. For the rest of the matrix:
        If matrix[i][j] == 0:
            Mark matrix[i][0] = 0   (row marker)
            Mark matrix[0][j] = 0   (column marker)
    4. Based on markers, zero out cells.
    5. Finally, zero out first row/column if needed.

    TIME COMPLEXITY:  O(rows * cols)
    SPACE COMPLEXITY: O(1)
*/


class OptimizedSolution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();

        bool firstRowZero = false;
        bool firstColZero = false;

        // Check if first row has a zero
        for(int j = 0; j < cols; j++) {
            if(matrix[0][j] == 0) {
                firstRowZero = true;
                break;
            }
        }

        // Check if first column has a zero
        for(int i = 0; i < rows; i++) {
            if(matrix[i][0] == 0) {
                firstColZero = true;
                break;
            }
        }

        // Use first row & first column as markers
        for(int i = 1; i < rows; i++) {
            for(int j = 1; j < cols; j++) {
                if(matrix[i][j] == 0) {
                    matrix[i][0] = 0;   // mark row
                    matrix[0][j] = 0;   // mark column
                }
            }
        }

        // Zero out cells based on markers
        for(int i = 1; i < rows; i++) {
            for(int j = 1; j < cols; j++) {
                if(matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }

        // Zero out first row if needed
        if(firstRowZero) {
            for(int j = 0; j < cols; j++) {
                matrix[0][j] = 0;
            }
        }

        // Zero out first column if needed
        if(firstColZero) {
            for(int i = 0; i < rows; i++) {
                matrix[i][0] = 0;
            }
        }
    }
};


int main() {
    // Example usage:

    vector<vector<int>> matrix = {
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1}
    };

    Solution s;
    s.setZeroes(matrix);

    cout << "After applying setZeroes (Brute Force):\n";
    for(const auto &row : matrix) {
        for(int x : row) cout << x << " ";
        cout << endl;
    }

    return 0;
}
