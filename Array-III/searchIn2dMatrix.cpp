#include <iostream>
#include <vector>
using namespace std;

/*
    ============================================================================
                        SEARCH IN A 2D MATRIX (3 APPROACHES)
    ============================================================================
    The matrix follows:
        - Rows are sorted.
        - First element of each row > last element of previous row.
    This means matrix is equivalent to a sorted 1D array.
*/



/*
    ============================================================================
    1️⃣ APPROACH 1 — BRUTE FORCE SEARCH
    ============================================================================
    Simply scan every cell of the matrix.

    TIME COMPLEXITY:  O(n * m)
    SPACE COMPLEXITY: O(1)
*/
bool searchMatrix_bruteforce(vector<vector<int>>& matrix, int target) {

    int n = matrix.size();
    int m = matrix[0].size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {

            if (matrix[i][j] == target) 
                return true;
        }
    }
    return false;
}



/*
    ============================================================================
    2️⃣ APPROACH 2 — BINARY SEARCH IN EACH ROW
    ============================================================================
    For each row:
        - Check if target can lie in that row:
                matrix[i][0] <= target <= matrix[i][m-1]
        - If yes → apply binary search on that row.

    TIME COMPLEXITY:  O(n + log m)
    SPACE COMPLEXITY: O(1)
*/
bool binarySearchRow(vector<int>& row, int target) {
    int low = 0, high = row.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (row[mid] == target) return true;
        else if (row[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return false;
}

bool searchMatrix_rowBinary(vector<vector<int>>& matrix, int target) {

    int n = matrix.size();
    int m = matrix[0].size();

    for (int i = 0; i < n; i++) {

        // Check if target could lie in this row
        if (matrix[i][0] <= target && target <= matrix[i][m - 1]) {
            return binarySearchRow(matrix[i], target);
        }
    }
    return false;
}



/*
    ============================================================================
    3️⃣ APPROACH 3 — OPTIMAL (Binary Search on Flattened Matrix)
    ============================================================================
    Treat matrix as a sorted 1D array of size (n * m):

        index → (index / cols, index % cols)

    Apply normal binary search on 0 to (n*m - 1).

    TIME COMPLEXITY:  O(log(n * m))
    SPACE COMPLEXITY: O(1)

    This is the BEST and most optimal solution.
*/
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {

        int rows = matrix.size();
        int cols = matrix[0].size();

        int left = 0, right = rows * cols - 1;

        while (left <= right) {

            int mid = left + (right - left) / 2;

            int value = matrix[mid / cols][mid % cols];

            if (value == target) 
                return true;

            else if (value < target) 
                left = mid + 1;

            else 
                right = mid - 1;
        }

        return false;
    }
};



/*
    ============================================================================
    MAIN — DEMONSTRATION OF ALL METHODS
    ============================================================================
*/
int main() {

    vector<vector<int>> matrix = {
        {1,  3,  5, 7},
        {10,11,16,20},
        {23,30,34,60}
    };

    int target = 16;

    cout << "Brute Force           : " 
         << (searchMatrix_bruteforce(matrix, target) ? "Found" : "Not Found") << endl;

    cout << "Row-wise Binary Search: "
         << (searchMatrix_rowBinary(matrix, target) ? "Found" : "Not Found") << endl;

    Solution sol;
    cout << "Flattened Binary Search: "
         << (sol.searchMatrix(matrix, target) ? "Found" : "Not Found") << endl;

    return 0;
}
