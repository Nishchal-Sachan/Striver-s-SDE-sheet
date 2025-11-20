#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
    ============================================================================
    PROBLEM: Merge Sorted Array (LeetCode #88)
    ============================================================================
    nums1 has size (m + n):
        - first m elements are valid
        - last n positions are empty (0s)
    nums2 has n elements.

    Merge nums2 INTO nums1 such that nums1 becomes fully sorted.
*/


/*
    ============================================================================
    APPROACH 1 — Append nums2 into nums1 → Sort Entire Array
    ============================================================================
    IDEA:
        nums1 has empty space at the end.
        Simply copy nums2’s elements into nums1’s empty positions,
        then sort the entire nums1.

    TIME COMPLEXITY:  O((m+n) log (m+n))
    SPACE COMPLEXITY: O(1)
    
    PROS:
        - Very easy to implement
        - Works for all cases

    CONS:
        - Not optimal
        - Sorting takes extra log factor

    Useful when you want something quick and clean.
*/
class AppendAndSortSolution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {

        // Copy nums2 elements into the empty space of nums1
        for (int i = 0; i < n; i++) {
            nums1[m + i] = nums2[i];
        }

        // Sort final array
        sort(nums1.begin(), nums1.end());
    }
};




/*
    ============================================================================
    APPROACH 2 — Two-Pointer Backward Merge (Optimal)
    ============================================================================
    IDEA:
        Since nums1 has space at the end, we merge from the BACK.

        We use 3 pointers:
            i = m-1  → last valid element in nums1
            j = n-1  → last element in nums2
            k = m+n-1 → last position of nums1 (final position)

        Compare nums1[i] and nums2[j]:
            - Place the larger one at nums1[k]
            - Move pointer accordingly

        Why from back?
            Because placing from front would overwrite nums1 elements.

    TIME COMPLEXITY:  O(m + n)
    SPACE COMPLEXITY: O(1)
    
    This is the official optimal method.
*/
class TwoPointerSolution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {

        int i = m - 1;          // pointer for nums1
        int j = n - 1;          // pointer for nums2
        int k = m + n - 1;      // fill position

        // Merge while both arrays have elements left
        while (i >= 0 && j >= 0) {

            if (nums1[i] > nums2[j]) {
                nums1[k--] = nums1[i--];
            } else {
                nums1[k--] = nums2[j--];
            }
        }

        // If nums2 still has leftover elements, insert them
        while (j >= 0) {
            nums1[k--] = nums2[j--];
        }

        // No need to copy leftover nums1 elements since they are already in place.
    }
};




/*
    ============================================================================
    MAIN FUNCTION — Demonstration
    ============================================================================
*/
int main() {

    vector<int> nums1 = {1, 2, 3, 0, 0, 0};
    vector<int> nums2 = {2, 5, 6};

    AppendAndSortSolution sol1;
    TwoPointerSolution sol2;

    // Approach 1
    vector<int> arr1 = nums1;
    sol1.merge(arr1, 3, nums2, 3);

    cout << "After Append + Sort Approach:\n";
    for (int x : arr1) cout << x << " ";
    cout << "\n\n";

    // Approach 2
    vector<int> arr2 = nums1;
    sol2.merge(arr2, 3, nums2, 3);

    cout << "After Optimal Two-Pointer Approach:\n";
    for (int x : arr2) cout << x << " ";
    cout << "\n";

    return 0;
}
