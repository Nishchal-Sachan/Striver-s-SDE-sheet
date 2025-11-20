#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
    ============================================================================
                       FIND DUPLICATE NUMBER — 3 APPROACHES
    ============================================================================

    You are given an array "nums" of size n+1 containing numbers from 1 to n.
    Exactly ONE number is duplicated (may appear multiple times).

    We solve using:
        1️⃣ Sorting (Easy but modifies array)
        2️⃣ Frequency Array (O(n) space)
        3️⃣ Floyd’s Cycle Detection (Optimal → O(1) space)
*/



/*
    ============================================================================
    1️⃣ APPROACH 1 — SORTING
    ============================================================================
    IDEA:
        After sorting, duplicate numbers become adjacent.
        Check if arr[i] == arr[i+1].

    TIME COMPLEXITY:  O(n log n)
    SPACE COMPLEXITY: O(1)  (extra space)

    NOTE:
        This modifies the array → not allowed in strict interview version.
*/
int findDuplicate_sort(vector<int>& arr) {
    sort(arr.begin(), arr.end());

    for (int i = 0; i < arr.size() - 1; i++) {
        if (arr[i] == arr[i + 1]) {
            return arr[i];
        }
    }
    return -1; // should never occur
}



/*
    ============================================================================
    2️⃣ APPROACH 2 — FREQUENCY ARRAY (Hashing)
    ============================================================================
    IDEA:
        Create a frequency array of size n+1.
        First time seeing a number → mark count.
        If seen again → that’s the duplicate.

    TIME COMPLEXITY:  O(n)
    SPACE COMPLEXITY: O(n)

    NOTE:
        Uses extra memory → not optimal.
*/
int findDuplicate_freq(vector<int>& arr) {
    int n = arr.size();
    vector<int> freq(n + 1, 0);

    for (int x : arr) {
        if (freq[x] == 1)
            return x;
        freq[x]++;
    }
    return -1;
}



/*
    ============================================================================
    3️⃣ APPROACH 3 — FLOYD'S TORTOISE–HARE (BEST APPROACH)
    ============================================================================
    IDEA:
        Treat array like a linked list:
            index → value → next index

        Duplicate value creates a cycle.
        Use cycle detection to find the duplicate.

    PHASE 1:
        Use slow and fast pointers to meet inside the cycle.

    PHASE 2:
        Move one pointer to start, move both 1 step each.
        Meeting point = duplicate.

    TIME COMPLEXITY:  O(n)
    SPACE COMPLEXITY: O(1)

    This is the **BEST and required interview solution**.
*/
int findDuplicate_floyd(vector<int>& nums) {

    int slow = nums[0];
    int fast = nums[0];

    // Phase 1 — detect cycle
    do {
        slow = nums[slow];
        fast = nums[nums[fast]];
    } while (slow != fast);

    // Phase 2 — find entry of cycle = duplicate
    fast = nums[0];

    while (slow != fast) {
        slow = nums[slow];
        fast = nums[fast];
    }

    return slow;
}



/*
    ============================================================================
    MAIN — DEMO of All Approaches
    ============================================================================
*/
int main() {

    vector<int> nums = {1, 3, 4, 2, 2};

    vector<int> a = nums;
    vector<int> b = nums;
    vector<int> c = nums;

    cout << "Sorting Approach      : " << findDuplicate_sort(a) << endl;
    cout << "Frequency Approach    : " << findDuplicate_freq(b) << endl;
    cout << "Floyd Cycle Detection : " << findDuplicate_floyd(c) << endl;

    return 0;
}
