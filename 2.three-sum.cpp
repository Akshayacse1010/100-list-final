/*
    Problem: 3Sum
    Given an integer array nums, return all unique triplets [nums[i], nums[j], nums[k]]
    such that nums[i] + nums[j] + nums[k] == 0.

    Approaches:
    ---------------------------------------------------------
    1) Better Approach: Set + 2 Loops
       - Fix one element (i).
       - Use a hash set to find the third element.
       - Store triplets in a set to avoid duplicates.

       Time Complexity: O(N^2 log N)
                        - Outer loop: O(N)
                        - Inner loop: O(N)
                        - Set insertion: O(log N)

       Space Complexity: O(N)
                        - Hash set + result set

    ---------------------------------------------------------
    2) Optimal Approach: Sorting + Two Pointers
       - Sort the array.
       - Fix one element (i).
       - Use two pointers (j, k).
       - Skip duplicates.

       Time Complexity: O(N^2)
       Space Complexity: O(1)
*/

#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>

using namespace std;


// ======================= BETTER APPROACH =======================

class SolutionBetter {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        set<vector<int>> st;
        int n = nums.size();

        for(int i = 0; i < n; i++) {
            unordered_set<int> hash;

            for(int j = i + 1; j < n; j++) {
                int third = -(nums[i] + nums[j]);

                if(hash.find(third) != hash.end()) {
                    vector<int> temp = {nums[i], nums[j], third};
                    sort(temp.begin(), temp.end());
                    st.insert(temp);
                }
                hash.insert(nums[j]);
            }
        }
        return vector<vector<int>>(st.begin(), st.end());
    }
};


/*
    ===========================================================================
    VISUALIZATION OF BETTER APPROACH (SET + HASHING)
    ===========================================================================

    Input: [-1, 0, 1, 2, -1, -4]

    -----------------------------------------------------------------------
    i = 0 → nums[i] = -1
    hash = {}

    j = 1 → nums[j] = 0
        third = -(-1 + 0) = 1
        hash = {0}

    j = 2 → nums[j] = 1
        third = -(-1 + 1) = 0
        0 exists in hash ✅
        Triplet = [-1, 1, 0] → sorted → [-1, 0, 1]
        hash = {0, 1}

    j = 3 → nums[j] = 2
        third = -(-1 + 2) = -1
        -1 not in hash
        hash = {0, 1, 2}

    j = 4 → nums[j] = -1
        third = -(-1 + -1) = 2
        2 exists in hash ✅
        Triplet = [-1, -1, 2]
        hash = {0, 1, 2, -1}

    -----------------------------------------------------------------------
    i = 1 → nums[i] = 0
    hash = {}

    j = 2 → nums[j] = 1
        third = -(0 + 1) = -1
        hash = {1}

    j = 3 → nums[j] = 2
        third = -(0 + 2) = -2
        hash = {1, 2}

    j = 4 → nums[j] = -1
        third = -(0 + -1) = 1
        1 exists in hash ✅
        Triplet = [0, -1, 1] → sorted → [-1, 0, 1]

    -----------------------------------------------------------------------
    Final Set (duplicates auto-removed):
    [
      [-1, -1, 2],
      [-1, 0, 1]
    ]

    ===========================================================================
    KEY INTUITION
    ===========================================================================
    - Reduce 3Sum → 2Sum using hashing
    - For each pair (i, j), compute required third
    - Hash set checks existence in O(1)
    - Sorting triplet + set removes duplicates

    ===========================================================================
*/


// ======================= OPTIMAL APPROACH =======================

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());
        int n = nums.size();

        for(int i = 0; i < n - 2; i++) {

            // ❌ Wrong duplicate skipping for i (earlier used while and modified i)
            if (i > 0 && nums[i] == nums[i-1]) continue;  // ✅ correct

            int j = i + 1, k = n - 1;

            while(j < k) {
                int sum = nums[i] + nums[j] + nums[k];

                if(sum == 0) {
                    ans.push_back({nums[i], nums[j], nums[k]});

                    // ❌ Wrong duplicate skipping for j (earlier used nums[j] == nums[j-1])
                    while(j < k && nums[j] == nums[j+1]) j++;  // ✅ correct

                    while(j < k && nums[k] == nums[k-1]) k--;

                    j++;
                    k--;
                }
                else if(sum > 0) {
                    k--;
                }
                else {
                    j++;
                }
            }
        }
        return ans;
    }
};


/*
    ===========================================================================
    VISUALIZATION OF TWO POINTER LOGIC (OPTIMAL)
    ===========================================================================

    Input: [-1, 0, 1, 2, -1, -4]

    Step 1: Sort
    [-4, -1, -1, 0, 1, 2]

    i = 1 → nums[i] = -1
    j = 2 (-1), k = 5 (2)

        sum = 0 → [-1, -1, 2]
        move both pointers

    j = 3 (0), k = 4 (1)
        sum = 0 → [-1, 0, 1]

    ===========================================================================
    WHY IT WORKS
    ===========================================================================
    - Sorted array → controlled movement
    - Move j → increase sum
    - Move k → decrease sum
    - Skip duplicates → unique answers

    ===========================================================================
*/