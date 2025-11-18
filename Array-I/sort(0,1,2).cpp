#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
    =========================================================================
    SORT COLORS (0s, 1s, 2s)
    =========================================================================
    You are given an array containing ONLY:
        0 → represents color Red
        1 → represents color White
        2 → represents color Blue

    Goal:
        Sort the array IN-PLACE so that:
            all 0s come first,
            then all 1s,
            then all 2s.

    We implement TWO approaches inside this file:

        1️⃣ Counting Sort (Simple & Easy)
        2️⃣ Dutch National Flag Algorithm (Optimal → O(1) extra space)

    Let's understand both approaches in detail.
*/



/*  
    =========================================================================
    1️⃣ APPROACH 1 — COUNTING SORT
    =========================================================================
    IDEA:
        Since the array has only 3 possible values (0, 1, 2),
        we can simply count how many of each appear.

    STEPS:
        Step 1 → Count zeroCount, oneCount, twoCount  
        Step 2 → Rewrite the array:
                    zeroCount times put 0
                    oneCount  times put 1
                    twoCount  times put 2

    WHY IT WORKS:
        We are not comparing elements — just reconstructing the sorted array
        based on frequencies.

    TIME COMPLEXITY: O(n)
    SPACE COMPLEXITY: O(1)
*/
class CountSortSolution {
public:
    void sortColors(vector<int>& nums) {

        int zeroCount = 0, oneCount = 0, twoCount = 0;

        // Count frequencies of 0, 1, 2
        for (int val : nums) {
            if (val == 0) zeroCount++;
            else if (val == 1) oneCount++;
            else twoCount++;
        }

        // Fill array in sorted order using the counts
        int index = 0;

        // Fill 0s
        while (zeroCount--) {
            nums[index++] = 0;
        }

        // Fill 1s
        while (oneCount--) {
            nums[index++] = 1;
        }

        // Fill 2s
        while (twoCount--) {
            nums[index++] = 2;
        }
    }
};





/*
    =========================================================================
    2️⃣ APPROACH 2 — DUTCH NATIONAL FLAG ALGORITHM (Optimal)
    =========================================================================
    This is the MOST IMPORTANT + MOST ASKED INTERVIEW solution.

    IDEA:
        Partition the array into 3 regions using 3 pointers:

            [0 … low-1] → all 0s    (sorted)
            [low … mid-1] → all 1s  (sorted)
            [mid … high]  → unknown (unprocessed)
            [high+1 … end] → all 2s (sorted)

        mid scans the array, and based on nums[mid]:
            → If 0: swap with low, expand 0-region, move both pointers
            → If 1: leave it, just move mid forward
            → If 2: swap with high, move high backward
                    (DO NOT move mid, because swapped element must be checked)

    WHY THIS WORKS:
        - 0s are always pushed to the beginning
        - 2s are always pushed to the end
        - 1s naturally stay in the middle
        - Each element is processed EXACTLY once → O(n)

    TIME COMPLEXITY: O(n)
    SPACE COMPLEXITY: O(1)
*/
class DutchFlagSolution {
public:
    void sortColors(vector<int>& nums) {

        int low = 0;                 // next position for a 0
        int mid = 0;                 // current pointer
        int high = nums.size() - 1;  // next position for a 2

        // Process until mid crosses high
        while (mid <= high) {

            // CASE 1: nums[mid] == 0 → belongs to the beginning
            if (nums[mid] == 0) {
                swap(nums[low], nums[mid]);
                low++;   // 0-region expands
                mid++;   // move mid forward
            }

            // CASE 2: nums[mid] == 1 → already in correct region
            else if (nums[mid] == 1) {
                mid++;   // just skip it
            }

            // CASE 3: nums[mid] == 2 → belongs to the end
            else {
                swap(nums[mid], nums[high]);
                high--;  // 2-region expands backward
                // DO NOT increment mid
                // because nums[mid] now contains a new unprocessed value
            }
        }
    }
};




/*
    =========================================================================
    MAIN FUNCTION — Simple demo for both approaches
    =========================================================================
*/
int main() {

    vector<int> nums1 = {2, 0, 2, 1, 1, 0};
    vector<int> nums2 = nums1;

    CountSortSolution countSol;
    DutchFlagSolution dutchSol;

    cout << "Original Array: ";
    for (int x : nums1) cout << x << " ";
    cout << "\n";

    // Counting Sort
    countSol.sortColors(nums1);
    cout << "After Counting Sort: ";
    for (int x : nums1) cout << x << " ";
    cout << "\n";

    // Dutch National Flag (Optimal)
    dutchSol.sortColors(nums2);
    cout << "After Dutch National Flag Sort: ";
    for (int x : nums2) cout << x << " ";
    cout << "\n";

    return 0;
}
