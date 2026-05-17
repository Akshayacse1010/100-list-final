/*
    Problem: First Missing Positive (LeetCode 41)
    Given an unsorted integer array nums, return the smallest missing positive integer.

    Constraint:
    - Must run in O(N) time
    - Must use O(1) extra space

    Approaches:
    ---------------------------------------------------------
    1) Brute Force
       - Start checking from 1 onwards.
       - For every number, scan the entire array.

       Time Complexity: O(N^2)
       Space Complexity: O(1)

    ---------------------------------------------------------
    2) Better Approach: Hashing
       - Store all positive numbers in a hash set.
       - Start checking from 1 onwards for missing number.

       Time Complexity: O(N)
       Space Complexity: O(N)

    ---------------------------------------------------------
    3) Optimal Approach: Cyclic Sort / Index Placement
       - Every positive number x should ideally be placed at index (x - 1)
       - Ignore:
            - negative numbers
            - zero
            - numbers > size
       - Rearrange array in-place
       - First index where nums[i] != i+1 is answer

       Time Complexity: O(N)
                        - Every element moved at most once/twice

       Space Complexity: O(1)
*/

#include <vector>
using namespace std;


// ======================= OPTIMAL APPROACH =======================

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {

        int size = nums.size();

        // Place elements at correct indices
        for(int i = 0; i < size; i++)
        {
            long long pos = nums[i] - 1L;

            // ❗ Important Conditions:
            // pos < size      -> valid index
            // pos > -1        -> positive number only
            // pos != i        -> avoid self swap
            // nums[pos] != nums[i] -> avoid infinite duplicate swaps

            if(pos < size && pos > -1 &&
               pos != i &&
               nums[pos] != nums[i])
            {
                swap(nums[pos], nums[i]);

                // ❗ Recheck current index after swap
                i--;
            }
        }

        // Find first missing positive
        for(int i = 0; i < size; i++)
        {
            if(i + 1 != nums[i])
            {
                return i + 1;
            }
        }

        return size + 1;
    }
};


/*
    ===========================================================================
    VISUALIZATION OF CYCLIC SORT LOGIC
    ===========================================================================

    Input:
    [3, 4, -1, 1]

    Goal:
    Place every number x at index (x - 1)

    Correct arrangement should become:
    [1, -1, 3, 4]

    -----------------------------------------------------------------------
    i = 0
    nums[0] = 3
    Correct position for 3 = index 2

    Swap:
    [ -1, 4, 3, 1 ]

    Recheck same index (i--)

    -----------------------------------------------------------------------
    i = 0
    nums[0] = -1

    Ignore:
    - negative number
    - cannot place

    -----------------------------------------------------------------------
    i = 1
    nums[1] = 4
    Correct position = index 3

    Swap:
    [ -1, 1, 3, 4 ]

    Recheck same index

    -----------------------------------------------------------------------
    i = 1
    nums[1] = 1
    Correct position = index 0

    Swap:
    [ 1, -1, 3, 4 ]

    -----------------------------------------------------------------------
    Final Rearranged Array:
    [1, -1, 3, 4]

    Now scan:

    index 0 → should contain 1 ✅
    index 1 → should contain 2 ❌

    Answer = 2

    ===========================================================================
    KEY INTUITION
    ===========================================================================
    - Every number has a "correct index"
    - Put numbers where they belong
    - First mismatch reveals missing positive

    ===========================================================================
    IMPORTANT EDGE CASES
    ===========================================================================
    1. Ignore negatives and zero
    2. Ignore numbers > size
    3. Prevent infinite swaps using:
            nums[pos] != nums[i]

       Example:
       [1,1]

       Without this condition:
            infinite swapping occurs

    ===========================================================================
    WHY O(N)?
    ===========================================================================
    - Each element is moved to correct place at most once
    - Total swaps across algorithm ≈ N
    - Hence linear complexity

    ===========================================================================
    MEMORY STORY (TO REMEMBER CYCLIC SORT)
    ===========================================================================

    A mother has too many children at a party.

    So she names every seat with a child’s number:
        Seat 1 → Child 1
        Seat 2 → Child 2
        Seat 3 → Child 3
        ...

    Now she makes every child sit in their correct seat.

    - If a child is sitting in the wrong seat:
            swap them to their correct seat

    - Ignore:
            negative children,
            zero,
            children with seat number bigger than total seats

    After everyone settles:

        Start checking seats from left to right.

        First seat where:
            seat number != child sitting there

        → that seat number is the missing child.

    Example:
        [3,4,-1,1]

        Seat arrangement process:
            3 sits at seat 3
            4 sits at seat 4
            1 sits at seat 1

        Final:
            [1,-1,3,4]

        Seat 2 is mismatched
        → Missing child = 2

    ===========================================================================
*/


// ======================= ONE LINE HINT =======================

/*
    Place x at index (x-1) → first mismatch gives missing positive
*/