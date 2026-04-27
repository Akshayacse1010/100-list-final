/*
    Problem: Move Zeroes
    Given an integer array nums, move all 0's to the end while maintaining 
    the relative order of non-zero elements.

    Approaches:
    ---------------------------------------------------------
    1) Brute Force
       - Create a temporary array.
       - First store all non-zero elements.
       - Then append zeros.

       Time Complexity: O(N)
       Space Complexity: O(N)

    ---------------------------------------------------------
    2) Better Approach: Two Pass (Your Solution)
       - Use pointer j to track position for non-zero elements.
       - First pass: copy all non-zero elements to front.
       - Second pass: fill remaining positions with zero.

       Time Complexity: O(N)
       Space Complexity: O(1)

    ---------------------------------------------------------
    3) Optimal Approach: One Pass Swap
       - Use two pointers:
         i → iterate
         j → position for next non-zero
       - Swap whenever non-zero found.

       Time Complexity: O(N)
       Space Complexity: O(1)
*/

#include <vector>
using namespace std;


// ======================= BETTER APPROACH =======================

class SolutionBetter {
public:
    void moveZeroes(vector<int>& nums) {
        int j = 0;

        // Move non-zero elements forward
        for(int i = 0; i < nums.size(); i++)
        {
            if(nums[i] != 0)
            {
                nums[j++] = nums[i];
            }
        }

        // Fill remaining with zero
        while(j < nums.size())
        {
            nums[j++] = 0;
        }
    }
};


// ======================= OPTIMAL APPROACH =======================

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int j = 0;

        for(int i = 0; i < nums.size(); i++)
        {
            if(nums[i] != 0)
            {
                swap(nums[i], nums[j]);
                j++;
            }
        }
    }
};

/*
    ===========================================================================
    VISUALIZATION (TWO POINTERS: i = scan, j = place)
    ===========================================================================

    Input: [0, 1, 0, 3, 12]

    Initial:
    i = 0, j = 0
    [0, 1, 0, 3, 12]
     ↑
     i,j

    -----------------------------------------------------------------------
    Step 1:
    nums[i] = 0 → skip

    i = 1, j = 0
    [0, 1, 0, 3, 12]
        ↑
        i
     ↑
     j

    -----------------------------------------------------------------------
    Step 2:
    nums[i] = 1 → swap(nums[i], nums[j])

    [1, 0, 0, 3, 12]
     ↑   ↑
     j   i

    j++, i++

    i = 2, j = 1

    -----------------------------------------------------------------------
    Step 3:
    nums[i] = 0 → skip

    i = 3, j = 1
    [1, 0, 0, 3, 12]
           ↑
           i
        ↑
        j

    -----------------------------------------------------------------------
    Step 4:
    nums[i] = 3 → swap(nums[i], nums[j])

    [1, 3, 0, 0, 12]
        ↑   ↑
        j   i

    j++, i++

    i = 4, j = 2

    -----------------------------------------------------------------------
    Step 5:
    nums[i] = 12 → swap(nums[i], nums[j])

    [1, 3, 12, 0, 0]
            ↑    ↑
            j    i

    -----------------------------------------------------------------------
    Final Output:
    [1, 3, 12, 0, 0]

    ===========================================================================
    POINTER ROLES
    ===========================================================================
    i → scans every element
    j → marks position to place next non-zero

    ===========================================================================
    KEY IDEA
    ===========================================================================
    - Everything before j → non-zero region
    - Everything after i → unexplored
    - Zeros naturally pushed to the right

    ===========================================================================
*/