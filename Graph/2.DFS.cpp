/*
    Problem: Depth First Search (DFS) Traversal of Graph
    Given a connected undirected/directed graph represented as an adjacency list, 
    return a vector containing the DFS traversal of the graph starting from node 0.

    Approaches:
    ---------------------------------------------------------
    1) Optimal Approach: Recursion + Visited Array
       - Use a recursion stack to dive deep into a path until a dead end (LIFO).
       - Use a visited array to track processed nodes and prevent infinite cycles.

       Time Complexity: O(V + E)
       Space Complexity: O(V) -> For the visited array and recursion stack frame.
*/

#include <vector>
using namespace std;

// ======================= OPTIMAL APPROACH =======================

class Solution {
private:
    void dfsHelper(int x, vector<int>& vis, vector<vector<int>>& adj, vector<int>& ans) {
        ans.push_back(x);
        vis[x] = 1; 
        
        for(int num : adj[x]) {
            if(vis[num] == 0) {
                dfsHelper(num, vis, adj, ans);
            }
        }
    }

public:
    vector<int> dfs(vector<vector<int>>& adj) {
        int n = adj.size();
        vector<int> vis(n, 0); // Standard standard-compliant allocation
        vector<int> ans;
        
        dfsHelper(0, vis, adj, ans);
        return ans;
    }
};

/*
    ===========================================================================
    POINTER ROLES & TOOLS
    ===========================================================================
    Recursion Stack -> Implicitly tracks backtracking, prioritizing depth first.
    vis[]           -> Halts cycle loops instantly.

    ===========================================================================
    KEY IDEA / COMMON INTERVIEW MISTAKE AVOIDED
    ===========================================================================
    - VLAs (`int vis[size]`) are non-standard C++. Pass a `vector<int>&` by 
      reference instead to prevent stack overflows and compiler compatibility errors.
    ===========================================================================
*/


// ===========================================================================
// 🔥 MY INITIAL MISTAKE / BROKEN ATTEMPT (DO NOT REPEAT)
// ===========================================================================
/*
class SolutionBroken {
public:
    void find(int x, int* vis, vector<vector<int>>& adj, vector<int>& ans)
    {
        if(vis[x] == 1) // Redundant base case check
        {
            return;
        }
        ans.push_back(x);
        vis[x] = 1;
    
        for(int num : adj[x])
        {
            if(vis[num] == 0)
            {
                find(num, vis, adj, ans);
            }
        }
    }
    
    vector<int> dfs(vector<vector<int>>& adj) {
       vector<int> ans;
       
       // MISTAKE: Variable length array syntax 'int vis[adj.size()]'
       // is a GCC extension and can fail on standard-compliant compilers.
       int vis[adj.size()] = {0}; 
       
       find(0 , vis, adj, ans);
       return ans;
    }
};
*/