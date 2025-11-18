#include <iostream>
#include <vector>
using namespace std;

/*
    -------------------------------------------------------------
    PROBLEM: Generate Pascal's Triangle
    -------------------------------------------------------------
    Given numRows, generate the first numRows of Pascal's Triangle.

    Each row begins and ends with 1.
    Each middle element = sum of the two elements above it.

    Example:
        numRows = 5

        Output:
        1
        1 1
        1 2 1
        1 3 3 1
        1 4 6 4 1

    -------------------------------------------------------------
    APPROACH (Dynamic Programming on Triangle)
    -------------------------------------------------------------
    1. Create an empty vector "triangle".
    2. For each row i (0 to numRows-1):
        - Create a vector 'row' of size (i+1).
        - Set row[0] = row[i] = 1 (first and last element always 1)
        - Fill middle elements by using:
              row[j] = triangle[i-1][j-1] + triangle[i-1][j]

    WHY THIS WORKS:
    -------------------------------------------------------------
    Pascal’s triangle property:
        C(n, k) = C(n-1, k-1) + C(n-1, k)

    So each value depends on the two directly above it.

    -------------------------------------------------------------
    TIME COMPLEXITY:
        O(numRows^2)
    SPACE COMPLEXITY:
        O(numRows^2)

    This is optimal because we must return all numbers anyway.
*/

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> triangle;

        for (int i = 0; i < numRows; i++) {
            // Create a row of size (i + 1)
            vector<int> row(i + 1);

            // First and last elements always 1
            row[0] = 1;
            row[i] = 1;

            // Fill middle elements if row has more than 2 elements
            for (int j = 1; j < i; j++) {
                /*
                    Current row jth value = sum of:
                        - Left parent triangle[i-1][j-1]
                        - Right parent triangle[i-1][j]
                */
                row[j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
            }

            // Push completed row into triangle
            triangle.push_back(row);
        }

        return triangle;
    }
};


/*
    -------------------------------------------------------------
    OPTIMIZED APPROACH? (SPACE)
    -------------------------------------------------------------
    If asked to print ONLY the last row:
        We can store only 1 row at a time → O(numRows)

    But since this problem REQUIRES returning ALL rows,
    full O(n^2) space is mandatory.

    No asymptotic optimization possible.
*/


int main() {
    // Example usage:
    int numRows = 5;

    Solution s;
    vector<vector<int>> result = s.generate(numRows);

    cout << "Pascal's Triangle (" << numRows << " rows):\n";
    for (const auto &row : result) {
        for (int x : row)
            cout << x << " ";
        cout << endl;
    }

    return 0;
}
