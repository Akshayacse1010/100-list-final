/*
    Problem: Maximum Subarray
    Given an integer array nums, find the contiguous subarray 
    with the largest sum and return its sum.

    Approaches:
    ---------------------------------------------------------
    1) Brute Force
       1. define i and j as intervals via 2 loops 
       2. iterate thorugh the intervals using another loop k 
       3. sum and add it to the max. if max is more than sum then replace max with sum
       - Compute sum for each subarray.
       - Track maximum.

       Time Complexity: O(N^3)
       Space Complexity: O(1)
       Result: TLE

    ---------------------------------------------------------
    2) Better Approach: 2 Loops
       - Fix starting index i.
       - Expand subarray using j.
       - Keep running sum (avoid inner k loop).

       Time Complexity: O(N^2)
       Space Complexity: O(1)

    ---------------------------------------------------------
    3) Optimal Approach: Kadane’s Algorithm
       - Maintain running sum.
       - If sum becomes negative → discard it (reset to 0).
       - Always track maximum.

       Time Complexity: O(N)
       Space Complexity: O(1)
*/

#include <vector>
#include <climits>
using namespace std;


// ======================= OPTIMAL APPROACH =======================

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int maxi = INT_MIN;
        int sum = 0;

        for(int i = 0; i < nums.size(); i++)
        {
            sum += nums[i];

            // ❗ Important: update maxi BEFORE resetting sum
            // (handles all-negative arrays)
            maxi = max(sum , maxi);

            if(sum < 0)
            {
                sum = 0;
            }
        }
        return maxi;
    }
};


/*
    ===========================================================================
    VISUALIZATION OF KADANE'S ALGORITHM
    ===========================================================================

    Input: [-2, 1, -3, 4, -1, 2, 1, -5, 4]

    -----------------------------------------------------------------------
    i=0 → sum = -2 → maxi = -2 → sum < 0 → reset sum = 0

    i=1 → sum = 1 → maxi = 1

    i=2 → sum = -2 → maxi = 1 → reset sum = 0

    i=3 → sum = 4 → maxi = 4

    i=4 → sum = 3 → maxi = 4

    i=5 → sum = 5 → maxi = 5

    i=6 → sum = 6 → maxi = 6  ✅

    i=7 → sum = 1 → maxi = 6

    i=8 → sum = 5 → maxi = 6

    -----------------------------------------------------------------------
    Final Answer: 6
    Subarray: [4, -1, 2, 1]

    ===========================================================================
    KEY INTUITION
    ===========================================================================
    - Negative prefix always hurts future sums → discard it
    - Only carry forward positive contribution
    - Local best → contributes to global best

    ===========================================================================
    EDGE CASE (IMPORTANT)
    ===========================================================================
    Input: [-3, -2, -5]

    If you reset sum before updating maxi → WRONG (returns 0)
    Correct flow:
        sum = -3 → maxi = -3
        sum reset → 0

    Final Answer: -2

    ===========================================================================
    WHY PREFIX/SUFFIX IDEA FAILS
    ===========================================================================
    - Prefix/suffix works when answer depends on boundaries
    - Here answer depends on "continuous contribution"
    - Kadane dynamically decides:
        "Is previous sum worth keeping or not?"

    ===========================================================================
*/