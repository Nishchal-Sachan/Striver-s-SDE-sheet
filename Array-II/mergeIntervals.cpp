#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
    ============================================================================
                             MERGE INTERVALS  
    ============================================================================
    You are given an array of intervals where each interval = [start, end].
    Your task is to merge all overlapping intervals.

    Example:
        Input:  [[1,3],[2,6],[8,10],[15,18]]
        Output: [[1,6],[8,10],[15,18]]

    Key Idea:
        After sorting by start time, overlapping intervals will always
        appear next to each other. So we can simply scan and merge.
*/



/*
    ============================================================================
    APPROACH 1 — Using currStart & currEnd (Your Style)
    ============================================================================
    STEPS:
        1️⃣ Sort intervals by starting point.  
        2️⃣ Start with the first interval as current block.  
        3️⃣ For each next interval:
                - If it overlaps → merge (extend currEnd)
                - Else → push current interval & reset currStart/currEnd  
        4️⃣ Push the last interval.

    Overlap condition:
            intervals[i][0] <= currEnd

    TIME COMPLEXITY:  O(n log n)  (sorting)
    SPACE COMPLEXITY: O(n)
*/
class SolutionApproach1 {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {

        sort(intervals.begin(), intervals.end());

        vector<vector<int>> ans;
        int currStart = intervals[0][0];
        int currEnd   = intervals[0][1];

        for (int i = 1; i < intervals.size(); i++) {

            // If intervals overlap → merge by extending end
            if (intervals[i][0] <= currEnd) {
                currEnd = max(currEnd, intervals[i][1]);
            }
            else {
                // No overlap → push current interval and update
                ans.push_back({currStart, currEnd});
                currStart = intervals[i][0];
                currEnd   = intervals[i][1];
            }
        }

        // Push last block
        ans.push_back({currStart, currEnd});
        return ans;
    }
};




/*
    ============================================================================
    APPROACH 2 — Using merged.back() (Standard Clean Approach)
    ============================================================================
    IDEA:
        Keep pushing intervals into 'merged'.
        For each interval:
            - If merged is empty → directly push
            - Else compare with merged.back()
                • If overlapping → extend merged.back()[1]
                • Else → push as a new interval

    TIME COMPLEXITY:  O(n log n)
    SPACE COMPLEXITY: O(n)
*/
class SolutionApproach2 {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {

        sort(intervals.begin(), intervals.end());
        vector<vector<int>> merged;

        for (auto &interval : intervals) {

            // First interval OR non-overlapping interval → push new
            if (merged.empty() || merged.back()[1] < interval[0]) {
                merged.push_back(interval);
            }

            // Overlapping → extend the end time
            else {
                merged.back()[1] = max(merged.back()[1], interval[1]);
            }
        }

        return merged;
    }
};




/*
    ============================================================================
    MAIN — Demonstration for both solutions
    ============================================================================
*/
int main() {

    vector<vector<int>> intervals = {
        {1,3}, {2,6}, {8,10}, {15,18}
    };

    SolutionApproach1 s1;
    SolutionApproach2 s2;

    auto res1 = s1.merge(intervals);
    auto res2 = s2.merge(intervals);

    cout << "Approach 1 Output:\n";
    for (auto &v : res1)
        cout << "[" << v[0] << "," << v[1] << "] ";
    cout << "\n\n";

    cout << "Approach 2 Output:\n";
    for (auto &v : res2)
        cout << "[" << v[0] << "," << v[1] << "] ";
    cout << "\n";

    return 0;
}
