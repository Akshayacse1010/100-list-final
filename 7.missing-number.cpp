/*
    Problem: Missing Number (LeetCode 268)
    Given an array nums containing n distinct numbers in the range [0, n],
    return the only number missing from the array.

    Approaches:
    ---------------------------------------------------------
    1) Brute Force
       - For every number from 0 to n:
            scan the array and check if present

       Time Complexity: O(N^2)
       Space Complexity: O(1)

    ---------------------------------------------------------
    2) Better Approach: Hashing
       - Store all elements in hash set / frequency array
       - Traverse from 0 to n and find missing number

       Time Complexity: O(N)
       Space Complexity: O(N)

    ---------------------------------------------------------
    3) Optimal Approach: Sum Formula
       - Sum of first n natural numbers:
            n * (n + 1) / 2

       - Compute actual array sum
       - Difference = missing number

       Time Complexity: O(N)
       Space Complexity: O(1)
*/

#include <vector>
using namespace std;


// ======================= OPTIMAL APPROACH =======================

class Solution {
public:
    int missingNumber(vector<int>& nums) {

        int size = nums.size();

        // Expected sum from 0 → n
        int sum = size * (size + 1) / 2;

        // Actual array sum
        int numsum = 0;

        for(int x : nums)
        {
            numsum += x;
        }

        // Missing number
        return sum - numsum;
    }
};


/*
    ===========================================================================
    VISUALIZATION OF SUM FORMULA LOGIC
    ===========================================================================

    Input:
    [3, 0, 1]

    size = 3

    -----------------------------------------------------------------------
    Step 1: Calculate expected sum

        Numbers should be:
            [0,1,2,3]

        Formula:
            n * (n + 1) / 2

        = 3 * 4 / 2
        = 6

    -----------------------------------------------------------------------
    Step 2: Calculate actual array sum

        3 + 0 + 1 = 4

    -----------------------------------------------------------------------
    Step 3: Difference

        expected sum - actual sum
        = 6 - 4
        = 2

    Missing Number = 2

    ===========================================================================
    KEY INTUITION
    ===========================================================================
    - Array should contain all numbers from 0 → n
    - One number is missing
    - Missing value creates difference in total sum

    ===========================================================================
    WHY IT WORKS
    ===========================================================================
    Expected:
        0 + 1 + 2 + 3 + 4 + ... + n

    Actual:
        Same sum but one number absent

    Difference:
        Missing Number

    ===========================================================================
    IMPORTANT EDGE CASES
    ===========================================================================
    1. Missing number = 0

        Input:
            [1,2,3]

        Expected Sum = 6
        Actual Sum   = 6

        Missing = 0

    -----------------------------------------------------------------------

    2. Missing number = n

        Input:
            [0,1,2]

        Expected Sum = 6
        Actual Sum   = 3

        Missing = 3

    ===========================================================================
    ALTERNATIVE OPTIMAL APPROACH (XOR)
    ===========================================================================
    XOR all indices and array values.

    Why it works:
        same numbers cancel out

        a ^ a = 0

    Remaining number = missing number

    ===========================================================================
    MEMORY STORY
    ===========================================================================

    A teacher wrote attendance numbers from 0 to n on the board.

    She knows:
        total expected attendance sum

    Then she checks:
        actual students present sum

    The difference tells:
        which student is absent.

    Example:
        Expected class strength sum = 6
        Present students sum = 4

        Missing student = 2

    ===========================================================================
*/


// ======================= ONE LINE HINT =======================

/*
    Expected sum - actual sum = missing number
*/