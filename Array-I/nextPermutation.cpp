#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
    ===============================================================
    PROBLEM: Next Permutation
    ===============================================================
    Rearrange numbers to form the lexicographically next greater
    permutation. If no greater permutation exists, return the
    smallest permutation (sorted in ascending order).

    Example:
        Input:  [1,2,3]
        Output: [1,3,2]

        Input:  [3,2,1]
        Output: [1,2,3]   (no next permutation → return smallest)

    ===============================================================
    INTUITION:
    We want the *smallest possible number that is bigger* than the
    current permutation.

    To achieve that we must:
    
    1. Find the rightmost position where nums[i] < nums[i+1].
       This position is called the "pivot".
       (If none exists, array is descending → reverse it.)

    2. Find the smallest element GREATER than nums[pivot], but on
       the RIGHT side. Swap them.

    3. Reverse the right side to get the smallest suffix.
       Why? Because the right side was in descending order, and we
       want the next minimal value → sort it → reverse is fastest.

    ===============================================================
    WHY SEARCH FROM THE RIGHT?
    ---------------------------------------------------------------
    Because we want the RIGHTMOST pivot to ensure:
        - Minimum change in number
        - Maximum closeness to the next permutation
        - Avoid skipping permutations

    If we took a pivot from the left, we would jump too far.

    ===============================================================
    ALGORITHM STEPS:
    ---------------------------------------------------------------
    1. Scan from right to left to find first index 'idx' where:
            nums[idx] < nums[idx + 1]

    2. If no such idx exists:
            Reverse entire array → smallest permutation.

    3. Otherwise:
            Scan from right to left again to find the first number
            greater than nums[idx]. Swap them.

    4. Reverse the suffix after idx to make it ascending.

    ===============================================================
    TIME COMPLEXITY:  O(n)
    SPACE COMPLEXITY: O(1)
*/

class Solution {
public:
    void nextPermutation(vector<int>& nums) {

        int n = nums.size();
        int idx = -1;   // pivot index

        // STEP 1: Find pivot from right (first decreasing element)
        for (int i = n - 2; i >= 0; i--) {
            if (nums[i] < nums[i + 1]) {
                idx = i;
                break;  // found pivot
            }
        }

        // STEP 2: If no pivot → array is descending → smallest perm
        if (idx == -1) {
            reverse(nums.begin(), nums.end());
            return;
        }

        // STEP 3: Find the next greater element from the right
        for (int i = n - 1; i > idx; i--) {
            if (nums[i] > nums[idx]) {
                swap(nums[i], nums[idx]);
                break;
            }
        }

        // STEP 4: Reverse the suffix (right side of pivot)
        reverse(nums.begin() + idx + 1, nums.end());
    }
};

/*
===============================================================
    BruteForce Approach (Generating All Permutations)
===============================================================
    1. Generate all permutations of the array.
    2. Store them in a list and sort them.
    3. Find the current permutation in the list.
    4. Return the next permutation or the first if at the end.

    TIME COMPLEXITY:
        O(n * n!)  → generating all permutations takes n! time,
                     and each permutation takes O(n) to store/compare.

    SPACE COMPLEXITY:
        O(n!)      → storing all permutations.
*/

int main() {
    // Example usage:
    vector<int> nums = {1, 2, 3};

    Solution s;
    s.nextPermutation(nums);

    cout << "Next Permutation: ";
    for (int x : nums) cout << x << " ";
    cout << endl;

    return 0;
}