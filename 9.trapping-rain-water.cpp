/*
    Problem: Trapping Rain Water
    Given n non-negative integers representing an elevation map where the width 
    of each bar is 1, compute how much water it can trap after raining.

    Approaches:
    ---------------------------------------------------------
    1) Better Approach: Prefix & Suffix Arrays (Your Solution 1)
       - Precompute the maximum height seen so far from the left (prefix).
       - Precompute the maximum height seen so far from the right (suffix).
       - The water trapped at any index is min(prefix[i], suffix[i]) - height[i].

       Time Complexity: O(N)
       Space Complexity: O(N)  --> Due to prefix/suffix arrays

    ---------------------------------------------------------
    2) Optimal Approach: Two Pointers (Your Solution 2)
       - Use two pointers, left and right, and maintain maxleft and maxright.
       - Move the pointer pointing to the smaller height, ensuring that the 
         opposite side always acts as a sufficient boundary.
       - If current height is smaller than its respective side's max, trap water.
       - Otherwise, update that side's max.

       Time Complexity: O(N)
       Space Complexity: O(1) --> Constant space
*/

#include <vector>
#include <algorithm>
using namespace std;


// ======================= BETTER APPROACH =======================

class SolutionBetter {
public:
    int trap(vector<int>& height) {
        int size = height.size();
        if (size == 0) return 0;

        int prefix[size];
        int suffix[size];
        prefix[0] = height[0];
        suffix[size-1] = height[size-1];

        for(int i = 1; i < size; i++)
        {
            prefix[i] = max(height[i], prefix[i-1]);
            suffix[size-i-1] = max(height[size-i-1], suffix[size-i]);
        }

        int sum = 0;
        for(int i = 0; i < size; i++)
        {
            int dum = (min(prefix[i], suffix[i]) - height[i]);
            sum += dum;
        }
        return sum;
    }
};


// ======================= OPTIMAL APPROACH =======================

class SolutionOptimal {
public:
    int trap(vector<int>& height) {
        int maxleft = 0, maxright = 0, water = 0;
        int left = 0, right = height.size() - 1;

        while(left < right)
        {
            if(height[left] < height[right]) {
                if(height[left] < maxleft) {
                    water += maxleft - height[left];
                }
                else {
                    maxleft = height[left];
                }
                left++;
            }
            else {
                if(height[right] < maxright) {
                    water += maxright - height[right];
                }
                else {
                    maxright = height[right];
                }
                right--;
            }
        }
        return water;
    }
};

/*
    ===========================================================================
    VISUALIZATION (TWO POINTERS: left = boundary, right = boundary)
    ===========================================================================

    Input: [3, 0, 2, 0, 4]

    Initial:
    left = 0, right = 4
    maxleft = 0, maxright = 0, water = 0
    [3, 0, 2, 0, 4]
     ↑           ↑
     L           R

    -----------------------------------------------------------------------
    Step 1:
    height[L] = 3, height[R] = 4 → height[L] < height[R] → Process Left side
    height[L] (3) is not less than maxleft (0) → Update maxleft = 3
    L++

    left = 1, right = 4
    maxleft = 3, maxright = 0, water = 0
    [3, 0, 2, 0, 4]
        ↑        ↑
        L        R

    -----------------------------------------------------------------------
    Step 2:
    height[L] = 0, height[R] = 4 → height[L] < height[R] → Process Left side
    height[L] (0) < maxleft (3) → water += 3 - 0 = 3
    L++

    left = 2, right = 4
    maxleft = 3, maxright = 0, water = 3
    [3, 0, 2, 0, 4]
           ↑     ↑
           L     R

    -----------------------------------------------------------------------
    Step 3:
    height[L] = 2, height[R] = 4 → height[L] < height[R] → Process Left side
    height[L] (2) < maxleft (3) → water += 3 - 2 = 4 (total 3 + 1)
    L++

    left = 3, right = 4
    maxleft = 3, maxright = 0, water = 4
    [3, 0, 2, 0, 4]
              ↑  ↑
              L  R

    -----------------------------------------------------------------------
    Step 4:
    height[L] = 0, height[R] = 4 → height[L] < height[R] → Process Left side
    height[L] (0) < maxleft (3) → water += 3 - 0 = 7 (total 4 + 3)
    L++

    left = 4, right = 4 (Loop breaks since left is no longer < right)

    -----------------------------------------------------------------------
    Final Output:
    7

    ===========================================================================
    POINTER ROLES
    ===========================================================================
    left  → Scan forward from left side
    right → Scan backward from right side

    ===========================================================================
    KEY IDEA / COMMON INTERVIEW MISTAKE AVOIDED
    ===========================================================================
    - If height[left] < height[right], it guarantees that there is a wall on 
      the right side at least as tall as height[right].
    - Therefore, the water trapped at 'left' is strictly bounded only by 
      'maxleft'. You DO NOT need to check 'min(maxleft, maxright)'.
    - Move the smaller pointer, trust the opposite side's dam, and calculate 
      water using your own side's max.
    ===========================================================================
*/


// ===========================================================================
// 🔥 MY INITIAL MISTAKE / BROKEN ATTEMPT (DO NOT REPEAT)
// ===========================================================================
/*
class SolutionBroken {
public:
    int trap(vector<int>& height) {
        int size = height.size();
        int left = 0, right = size-1, leftmax = height[0], rightmax = height[size-1], water = 0;
        while(left < right)
        {
            if(height[left] <= height[right])
            {
                leftmax = max(height[left], leftmax);
                
                // MISTAKE HERE:
                // Do not use min(leftmax, rightmax). Because height[left] <= height[right],
                // we already know a massive wall exists on the right side. Taking the min() 
                // with the current 'rightmax' will undercount water if rightmax hasn't been 
                // updated to its ultimate height yet.
                water = water + min(leftmax, rightmax) - height[left]; 
                
                left++;
            }
            else
            {
                rightmax = max(height[right] , rightmax);
                
                // MISTAKE HERE: Same issue on the right side.
                water = water + min(rightmax, leftmax) - height[right];
                
                right--;
            }
        }
        return water;
    }
};
*/