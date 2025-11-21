#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
using namespace std;

/*
    ============================================================================
                             MAJORITY ELEMENT
    ============================================================================
    Given an array nums of size n, find the element that appears MORE THAN
    n/2 times. This majority element always exists.
*/



/*
    ============================================================================
    1️⃣ APPROACH 1 — HASH MAP (Frequency Count)
    ============================================================================
    IDEA:
        - Count occurrences of each element using an unordered_map.
        - The element with frequency > n/2 is the answer.

    TIME COMPLEXITY:  O(n)
    SPACE COMPLEXITY: O(n)

    This is simple, intuitive, but uses extra memory.
*/
class HashMapSolution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> freq;

        // Count frequencies
        for (int val : nums) {
            freq[val]++;
        }

        // Find element with max frequency
        int maxFreq = INT_MIN;
        int majority = -1;

        for (auto &p : freq) {
            if (p.second > maxFreq) {
                maxFreq = p.second;
                majority = p.first;
            }
        }

        return majority;
    }
};




/*
    ============================================================================
    2️⃣ APPROACH 2 — MOORE'S VOTING ALGORITHM (Optimal)
    ============================================================================
    KEY OBSERVATION:
        Since the majority element appears > n/2 times,
        it will "cancel out" all other elements.

    Steps:
        - Maintain a count and candidate.
        - If count becomes 0, choose current number as the new candidate.
        - If number == candidate → increment count
          Else → decrement count

    WHY THIS WORKS:
        - Majority element has more votes than all others combined.
        - So after all cancellations, majority element remains.

    TIME COMPLEXITY:  O(n)
    SPACE COMPLEXITY: O(1)   (Optimal)
*/
class MooresVotingSolution {
public:
    int majorityElement(vector<int>& nums) {
        int count = 0;
        int candidate = 0;

        for (int num : nums) {

            // If count becomes zero → choose new candidate
            if (count == 0) {
                candidate = num;
                count = 1;
            }
            else if (num == candidate) {
                // same as candidate → vote increases
                count++;
            }
            else {
                // different element → vote decreases
                count--;
            }
        }

        return candidate;
    }
};




/*
    ============================================================================
    MAIN — Test both approaches
    ============================================================================
*/
int main() {

    vector<int> nums = {2, 2, 1, 1, 1, 2, 2};

    HashMapSolution s1;
    MooresVotingSolution s2;

    cout << "Majority Element (HashMap): " << s1.majorityElement(nums) << endl;
    cout << "Majority Element (Moore's Voting): " << s2.majorityElement(nums) << endl;

    return 0;
}
