/*
    Problem: Contains Duplicate
    Given an integer array nums, return true if any value appears 
    at least twice, otherwise return false.

    Approaches:
    ---------------------------------------------------------
    1) Brute Force
       - Compare every pair (i, j)

       Time Complexity: O(N^2)
       Space Complexity: O(1)

    ---------------------------------------------------------
    2) Better Approach: Sorting
       - Sort the array
       - Check adjacent elements

       Time Complexity: O(N log N)
       Space Complexity: O(1)

    ---------------------------------------------------------
    3) Optimal Approach: Hash Set
       - Use unordered_set to track seen elements
       - If element already exists → duplicate found

       Time Complexity: O(N) average
                        - Insert + lookup = O(1) avg
       Space Complexity: O(N)

       ⚠️ Worst Case:
       - O(N^2) if heavy collisions (rare in practice)
*/

#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;


// ======================= OPTIMAL APPROACH =======================

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> st;

        for(int x : nums)
        {
            if(st.find(x) != st.end())
                return true;

            st.insert(x);
        }
        return false;
    }
};


/*
    ===========================================================================
    VISUALIZATION (HASH SET)
    ===========================================================================

    Input: [1, 2, 3, 1]

    Step 1:
    st = {}
    see 1 → not present → insert
    st = {1}

    Step 2:
    see 2 → not present → insert
    st = {1, 2}

    Step 3:
    see 3 → not present → insert
    st = {1, 2, 3}

    Step 4:
    see 1 → already present ✅
    → return true

    ===========================================================================
    KEY INTUITION
    ===========================================================================
    - Use hash structure for O(1) lookup
    - Detect duplicate at first repetition

    ===========================================================================
    WHY SET > MAP HERE
    ===========================================================================
    - We only care about existence, not frequency
    - Set avoids unnecessary value storage

    ===========================================================================
    PATTERN
    ===========================================================================
    - Hashing for existence check
    - Used in:
        • Duplicate detection
        • Two Sum
        • Frequency problems (extended)

    ===========================================================================
*/