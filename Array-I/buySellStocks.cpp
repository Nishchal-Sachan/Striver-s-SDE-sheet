#include <iostream>
#include <vector>
#include <climits>
using namespace std;

/*
    ============================================================================
    PROBLEM: Best Time to Buy and Sell Stock
    ============================================================================
    You are given prices[], where prices[i] is the stock price on day i.
    
    You must choose:
        - One day to BUY
        - One later day to SELL
    Return the MAXIMUM profit you can achieve.

    If no profit can be made → return 0.
*/



/*
    ============================================================================
    APPROACH 1 — BRUTE FORCE (O(n²))
    ============================================================================
    IDEA:
        Try every possible pair (i, j) where j > i:
            profit = prices[j] - prices[i]
        Track the maximum profit.

    WHY IT WORKS:
        It checks all possible valid buy/sell pairs.

    WHY IT'S SLOW:
        Two nested loops → O(n²)
        For n = 100000 → 10 billion operations (TLE)

    TIME COMPLEXITY:  O(n²)
    SPACE COMPLEXITY: O(1)
*/
int maxProfitBruteforce(vector<int>& arr) {

    int maxPro = 0;
    int n = arr.size();

    // Choose every possible buy day
    for (int i = 0; i < n; i++) {

        // Choose every possible sell day (must be after buy)
        for (int j = i + 1; j < n; j++) {

            if (arr[j] > arr[i]) {
                maxPro = max(maxPro, arr[j] - arr[i]);
            }
        }
    }

    return maxPro;
}





/*
    ============================================================================
    APPROACH 2 — OPTIMIZED (O(n)) — Kadane-like greedy solution
    ============================================================================
    IDEA:
        As you scan the array:
            Track the MINIMUM price seen so far → best BUY price.
            At each day, calculate profit if selling today:
                    profit = price_today - minPrice

            Keep updating maxProfit.

    WHY THIS WORKS:
        For each day, we simulate:
            "If I had bought at the lowest price so far,
             what is the profit if I sell today?"

        This guarantees we check all valid buy-before-sell pairs
        but without nested loops.

    TIME COMPLEXITY:  O(n)
    SPACE COMPLEXITY: O(1)

    This is the BEST POSSIBLE approach.
*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {

        int minPrice = INT_MAX;   // Store the lowest price seen so far
        int maxProfit = 0;        // Store the best profit so far

        // Iterate through all days
        for (int price : prices) {

            // Update minimum buying price
            minPrice = min(minPrice, price);

            // Calculate possible profit if we sell today
            int profit = price - minPrice;

            // Update max profit
            maxProfit = max(maxProfit, profit);
        }

        return maxProfit;
    }
};




/*
    ============================================================================
    MAIN FUNCTION — Demo for both approaches
    ============================================================================
*/
int main() {

    vector<int> prices = {7, 1, 5, 3, 6, 4};

    cout << "Brute Force Profit: "
         << maxProfitBruteforce(prices) << endl;

    Solution sol;
    cout << "Optimized Profit  : "
         << sol.maxProfit(prices) << endl;

    return 0;
}
