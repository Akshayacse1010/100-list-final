/*
    Problem: Two Sum (find indices of two numbers such that they add up to target)

    Approaches (short):
    ---------------------------------------------------------
    1) Brute force
       Check every pair (i,j) -> O(n^2) time, O(1) space.
       Too slow for large inputs.

    2) Optimal: Hash Map (used here)
       - Traverse array once
       - For each element x, check if (target - x) already exists
       - If yes → return indices
       - Else → store x in map

    Key Idea:
       Instead of checking all pairs,
       store previously seen elements and look up complement instantly.

    Example:
        nums = [2, 7, 11, 15], target = 9

        i = 0 → x = 2 → need 7 → not found → store {2:0}
        i = 1 → x = 7 → need 2 → found → return [0,1]

    Pitfalls / notes:
    - Store element AFTER checking (to avoid using same index twice)
    - Use unordered_map for O(1) average lookup
    - If duplicates exist (e.g., [3,3], target=6), this approach still works
    - Problem guarantees exactly one solution (in LC version)

    Time Complexity: O(n)
    Space Complexity: O(n)

    This file uses hashmap approach for optimal performance.
*/

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> mp; // value -> index

        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];

            // check if complement already seen
            if (mp.find(complement) != mp.end()) {
                return {mp[complement], i};
            }

            // store current element
            mp[nums[i]] = i;
        }

        return {}; // should never reach here if one solution exists
    }
};


/*
    Visual Flow:

    nums = [2, 7, 11, 15], target = 9

    Step 1:
        i = 0 → num = 2
        need = 7 → not in map
        map = {2:0}

    Step 2:
        i = 1 → num = 7
        need = 2 → found in map
        return [0,1]

---------------------------------------------------------

    Pattern:
        Hashing / Complement lookup

    When to use:
        - Need pair with target sum
        - Frequent lookups required
        - Optimize brute force O(n^2) → O(n)

    Variations:
        - Two Sum II (sorted array → use two pointers)
        - 3Sum → fix one element + two pointers
*/