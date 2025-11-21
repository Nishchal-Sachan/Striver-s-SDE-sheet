#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/*
    =============================================================================
                              MAJORITY ELEMENT II
    =============================================================================
    Find all elements that appear MORE THAN n/3 times.
    At most, there can be **only 2 majority elements**.
        → Pigeonhole principle:
          You cannot have 3 different elements each occurring more than n/3.

    We implement 2 approaches:
        1️⃣ HashMap (easy)
        2️⃣ Extended Moore’s Voting Algorithm (O(1) extra space)
*/



/*
    =============================================================================
    1️⃣ APPROACH 1 — HASH MAP (Easy, but uses extra memory)
    =============================================================================
    - Count frequencies using unordered_map.
    - Push all elements whose count > n/3.

    TIME COMPLEXITY:  O(n)
    SPACE COMPLEXITY: O(n)
*/
class HashMapSolution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        unordered_map<int, int> freq;
        vector<int> ans;

        for (int val : nums) {
            freq[val]++;
        }

        for (auto &p : freq) {
            if (p.second > nums.size() / 3) {
                ans.push_back(p.first);
            }
        }
        return ans;
    }
};




/*
    =============================================================================
    2️⃣ APPROACH 2 — EXTENDED MOORE’S VOTING ALGORITHM (Optimal)
    =============================================================================
    KEY IDEA:
        For majority > n/3:
            There can be at most TWO such elements.

        So we keep TWO candidates:
            candidate1, count1
            candidate2, count2

    STEPS:
        1. Find potential candidates using voting:
                - If num == candidate → increase its count
                - Else if second slot empty → assign
                - Else decrement both counts
        2. Verify the counts (because candidates may be false positives)

    WHY THIS WORKS:
        Similar to normal Moore’s Voting,
        all non-majority elements get cancelled out.
        At the end, only potential majority elements survive.

    TIME COMPLEXITY:  O(n)
    SPACE COMPLEXITY: O(1)
*/
class MooresVotingSolution {
public:
    vector<int> majorityElement(vector<int>& nums) {

        /*
            ====================================================================
            PHASE 1: FIND POTENTIAL CANDIDATES
            ====================================================================

            We will maintain:

                candidate1, count1
                candidate2, count2

            RULES:

            1. If current number matches candidate1 → count1++
            2. Else if matches candidate2 → count2++
            3. Else if count1 == 0 → make this number candidate1
            4. Else if count2 == 0 → make this number candidate2
            5. Else → num matches none → cancel both:
                    count1--, count2--

            WHY THIS WORKS:
            ----------------
            - We eliminate 3 distinct numbers in each cancellation step.
            - A number that appears > n/3 times cannot be fully cancelled.
            - After complete scan, candidate1 and candidate2 are the ONLY
              possible majority elements.
        */

        int candidate1 = 0, candidate2 = 0;
        int count1 = 0, count2 = 0;

        for (int num : nums) {

            if (num == candidate1) {
                // Same as candidate1 → strengthen count
                count1++;
            }
            else if (num == candidate2) {
                // Same as candidate2 → strengthen count
                count2++;
            }
            else if (count1 == 0) {
                // Slot 1 empty → take this as the new candidate1
                candidate1 = num;
                count1 = 1;
            }
            else if (count2 == 0) {
                // Slot 2 empty → take this as the new candidate2
                candidate2 = num;
                count2 = 1;
            }
            else {
                // num matches neither candidate → perform cancellation
                count1--;
                count2--;
            }
        }



        /*
            ====================================================================
            PHASE 2: VERIFY COUNTS
            ====================================================================

            IMPORTANT:
                The above step only gives *potential* candidates.
                They MUST be verified because candidates can be false positives.

            So we:
                - Reset counts
                - Count actual occurrences of candidate1 and candidate2
        */

        count1 = 0;
        count2 = 0;

        for (int num : nums) {
            if (num == candidate1) count1++;
            else if (num == candidate2) count2++;
        }



        /*
            ====================================================================
            PHASE 3: COLLECT VALID ANSWERS
            ====================================================================

            Only include candidates whose count > n/3
        */
        vector<int> ans;
        int n = nums.size();

        if (count1 > n / 3) ans.push_back(candidate1);
        if (count2 > n / 3) ans.push_back(candidate2);

        return ans;
    }
};



/*
    =============================================================================
    MAIN — TEST BOTH SOLUTIONS
    =============================================================================
*/
int main() {

    vector<int> nums = {1,1,1,3,3,2,2,2};

    HashMapSolution s1;
    MooresVotingSolution s2;

    auto a1 = s1.majorityElement(nums);
    auto a2 = s2.majorityElement(nums);

    cout << "HashMap Solution: ";
    for (int x : a1) cout << x << " ";
    cout << endl;

    cout << "Moore's Voting (Optimal): ";
    for (int x : a2) cout << x << " ";
    cout << endl;

    return 0;
}
