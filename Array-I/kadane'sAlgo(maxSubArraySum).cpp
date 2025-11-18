#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
    =====================================================================
    PROBLEM: Maximum Subarray (Kadane's Algorithm)
    =====================================================================
    You are given an integer array nums.
    Your task is to find the subarray (contiguous) with the maximum sum.

    Example:
        Input:  [-2,1,-3,4,-1,2,1,-5,4]
        Output: 6
        Explanation: [4,-1,2,1] has sum = 6

    =====================================================================
    INTUITION (Kadane's Algorithm):
    =====================================================================
    Maintain a running sum (current subarray sum).
    If running sum becomes negative → RESET to 0.

    Why reset?
        Because adding a negative prefix will only make future sums worse.

    We also track the global maximum while moving forward.

    =====================================================================
    ALGORITHM STEPS:
    =====================================================================
    1. Create:
            sum  → stores current running sum
            maxi → stores maximum subarray sum found so far

    2. For each number in the array:
            - Add it to running sum.
            - Update maxi = max(maxi, sum)
            - If sum < 0 → reset sum = 0

    3. Return maxi

    =====================================================================
    DRY RUN:
    nums = [-2,1,-3,4,-1,2,1,-5,4]

    sum   maxi
    -------------------
    -2     -2
    0      -2   (reset sum)
    1       1
    -2      1   (reset)
    4       4
    3       4
    5       5
    6       6   (best)
    1       6
    5       6

    Answer = 6

    =====================================================================
    TIME COMPLEXITY:  O(n)
    SPACE COMPLEXITY: O(1)

    =====================================================================
*/

class Solution {
public:
    int maxSubArray(vector<int>& nums) {

        int sum = 0;               // running sum
        int maxi = nums[0];        // global max (must start from nums[0])

        for (int i = 0; i < nums.size(); i++) {

            sum += nums[i];        // add current element

            maxi = max(maxi, sum); // update global max

            if (sum < 0) {
                sum = 0;           // reset if running sum goes negative
            }
        }

        return maxi;
    }
};


int main() {
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};

    Solution s;
    int result = s.maxSubArray(nums);

    cout << "Maximum Subarray Sum: " << result << endl;

    return 0;
}
