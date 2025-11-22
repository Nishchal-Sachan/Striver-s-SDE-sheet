#include <iostream>
#include <vector>
using namespace std;

/*
    =====================================================================================
                                 REVERSE PAIRS (LeetCode 493)
    =====================================================================================
    Count pairs (i, j) such that:
            i < j   AND   nums[i] > 2 * nums[j]

    APPROACHES INCLUDED:
        1️⃣ Brute Force (O(n²)) — simple but slow
        2️⃣ Optimal Merge Sort Based (O(n log n)) — required for large inputs

    The optimal approach uses modified merge sort to count pairs WHILE merging.
*/



/*
    =====================================================================================
    1️⃣ BRUTE FORCE APPROACH — O(n²)
    =====================================================================================
    Directly compare each pair.

    NOTE:
        Must cast to long long to avoid integer overflow when computing nums[j] * 2
*/
class BruteForceSolution {
public:
    int reversePairs(vector<int>& nums) {
        int count = 0;
        int n = nums.size();

        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){

                // Cast to long long to avoid overflow
                if ((long long)nums[i] > (long long)nums[j] * 2) {
                    count++;
                }
            }
        }
        return count;
    }
};




/*
    =====================================================================================
    2️⃣ OPTIMAL APPROACH — MODIFIED MERGE SORT (O(n log n))
    =====================================================================================

    WHY THIS WORKS:
    ---------------
    - During merge sort, the LEFT half and RIGHT half are already sorted.
    - This allows counting valid pairs efficiently using two pointers.

    KEY INSIGHT:
    ------------
        For each nums[i] in left half,
        we find how many nums[j] in right half satisfy:

                nums[i] > 2 * nums[j]

        Since right half is sorted, j only moves FORWARD,
        never backward → O(n) per merge.

    OVERALL COMPLEXITY:
        Time:  O(n log n)
        Space: O(n) for merging
*/
class OptimalSolution {
public:

    // Count cross reverse pairs across midpoint
    int countCrossPairs(vector<int>& nums, int left, int mid, int right) {

        int count = 0;
        int j = mid + 1;

        /*
            For each element in left half:
                move j while nums[i] > 2 * nums[j]

            Because right half is sorted:
                once nums[i] <= 2*nums[j], no further j will satisfy
        */
        for (int i = left; i <= mid; i++) {
            while (j <= right && (long long)nums[i] > 2LL * nums[j]) {
                j++;
            }

            // j moved to first invalid index, so all previous (j - (mid+1)) are valid pairs
            count += (j - (mid + 1));
        }

        return count;
    }


    // Recursive merge sort + counting function
    int mergeSort(vector<int>& nums, int left, int right) {

        if (left >= right) return 0; // Single element has no pairs

        int mid = (left + right) / 2;
        int count = 0;

        // Count pairs in left half
        count += mergeSort(nums, left, mid);

        // Count pairs in right half
        count += mergeSort(nums, mid + 1, right);

        // Count cross pairs
        count += countCrossPairs(nums, left, mid, right);

        // Standard merge step to keep array sorted
        vector<int> temp;
        int i = left, j = mid + 1;

        while (i <= mid && j <= right) {
            if (nums[i] <= nums[j]) temp.push_back(nums[i++]);
            else temp.push_back(nums[j++]);
        }

        while (i <= mid) temp.push_back(nums[i++]);
        while (j <= right) temp.push_back(nums[j++]);

        // Copy back to original array
        for (int k = left; k <= right; k++) {
            nums[k] = temp[k - left];
        }

        return count;
    }


    int reversePairs(vector<int>& nums) {
        return mergeSort(nums, 0, nums.size() - 1);
    }
};




/*
    =====================================================================================
    MAIN — DEMO
    =====================================================================================
*/
int main() {

    vector<int> nums = {1, 3, 2, 3, 1};

    BruteForceSolution b;
    OptimalSolution o;

    cout << "Brute Force Result : " << b.reversePairs(nums) << endl;

    cout << "Optimal Result     : " << o.reversePairs(nums) << endl;

    return 0;
}
