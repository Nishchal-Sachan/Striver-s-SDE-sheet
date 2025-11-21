#include <iostream>
using namespace std;

/*
    ============================================================================
                                 POW(x, n)
    ============================================================================
    We compute x raised to the power n (x^n).

    IMPORTANT:
    - n can be negative
    - n can be INT_MIN (−2^31) → must handle carefully
*/


/*
    ============================================================================
    1️⃣ APPROACH 1 — SIMPLE MULTIPLICATION (O(n))
    ============================================================================
    For n > 0:
         multiply x n times.

    For n < 0:
         compute positive power and return 1/ans.

    This is straightforward but too slow for large n (like 1e9).
*/
class SimplePower {
public:
    double myPow(double x, int n) {
        long long m = n;        // convert to long long to avoid overflow
        if (m < 0) m = -m;

        double ans = 1.0;

        for (long long i = 0; i < m; i++) {
            ans *= x;
        }

        return (n < 0) ? (1.0 / ans) : ans;
    }
};



/*
    ============================================================================
    2️⃣ APPROACH 2 — FAST EXPONENTIATION (Binary Exponentiation)
    ============================================================================
    KEY IDEA:
        x^n =
            if n even → (x*x)^(n/2)
            if n odd  → x * (x*x)^(n-1)

    ADVANTAGES:
        - Reduces power from n → log2(n)
        - Mandatory for large values (n up to 10^9)

    Handles negative powers by:
        - converting n to long long
        - computing power for positive exponent
        - taking reciprocal at the end
*/
class FastPower {
public:
    double myPow(double x, int n) {

        /*
            ---------------------------------------------------------------
            WHY WE USE long long FOR n
            ---------------------------------------------------------------
            - n can be INT_MIN = -2,147,483,648
            - But abs(INT_MIN) cannot be represented in an int (overflow)
            - So we convert to long long to safely take its absolute value
        */
        long long power = n;

        // Check if the exponent is negative
        bool isNegative = (power < 0);

        // Convert negative exponent to positive for calculation
        if (isNegative) {
            power = -power;
        }

        /*
            ---------------------------------------------------------------
            FAST EXPONENTIATION (Binary Exponentiation)
            ---------------------------------------------------------------
            Core idea:
                x^power can be broken down using properties:
                
                If power is EVEN:
                    x^power = (x * x)^(power / 2)

                If power is ODD:
                    x^power = x * (x^(power - 1))

            We repeatedly:
                - Square x
                - Halve the exponent

            This reduces the time from O(n) → O(log n)
        */

        double ans = 1.0;     // final result

        while (power > 0) {

            /*
                -----------------------------------------------------------
                CASE 1: power is ODD
                -----------------------------------------------------------
                Example:
                    3^5 = 3 * 3^4

                - If power is odd, we take one "x" out
                - Multiply it into answer
                - Make power even by subtracting 1
            */
            if (power % 2 == 1) {
                ans = ans * x;   // include this x into result
                power--;         // decrease power to make it even
            }
            else {
                /*
                    -------------------------------------------------------
                    CASE 2: power is EVEN
                    -------------------------------------------------------
                    Example:
                        3^8 = (3^2)^4
                            = (9)^4
                            = (81)^2
                            = (6561)^1

                    So instead of multiplying 3 * 3 * 3 * 3 * 3 * 3 * 3 * 3
                    we repeatedly square x and halve the exponent.
                */
                x = x * x;       // square the base → x = x^2
                power /= 2;      // reduce exponent by half
            }
        }

        /*
            ---------------------------------------------------------------
            HANDLE NEGATIVE EXPONENT
            ---------------------------------------------------------------
            If n was originally negative:
                x^-n = 1 / (x^n)

            Example:
                2^-3 = 1 / 2^3 = 1 / 8
        */
        if (n < 0) {
            ans = 1.0 / ans;
        }

        return ans;
    }
};



/*
    ============================================================================
    MAIN — Demonstration
    ============================================================================
*/
int main() {

    SimplePower s1;
    FastPower s2;

    double x = 2.0;
    int n = -3;

    cout << "Simple Approach      : " << s1.myPow(x, n) << endl;
    cout << "Fast Exponentiation  : " << s2.myPow(x, n) << endl;

    return 0;
}
