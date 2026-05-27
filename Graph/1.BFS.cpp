/*
    Problem: Breadth First Search (BFS) Traversal of Graph
    return a vector containing the BFS traversal of the graph starting from node 0.

    Approaches:
    ---------------------------------------------------------
    1) Optimal Approach: Queue + Visited Array
       - Use a queue to explore the graph layer by layer (FIFO).
       - Use a visited array to keep track of nodes already added to the queue.
       - CRITICAL: Ensure you mark the NEIGHBOR (num) as visited when pushing it, 
         not the current node (x).

       Time Complexity: O(V + E) 
       Space Complexity: O(V)    
*/

#include <vector>
#include <queue>
using namespace std;

// ======================= OPTIMAL APPROACH =======================

class Solution {
public:
    vector<int> bfs(vector<vector<int>> &adj) {
        int n = adj.size();
        vector<int> vis(n, 0); 
        queue<int> q;
        vector<int> ans;
        
        q.push(0);
        vis[0] = 1; 
        
        while(!q.empty())
        {
            int x = q.front();
            q.pop();
            ans.push_back(x);
            
            for(int num : adj[x])
            {
                if(vis[num] == 0)
                {
                    q.push(num);
                    vis[num] = 1; // 🟢 CORRECT: Marking the pushed neighbor
                }
            }
        }
        return ans;
    }
};

/*
    ===========================================================================
    VISUALIZATION (THE TARGET VARIABLE TYPO)
    ===========================================================================

    Current node: x = 0
    Neighbors of 0: num = 1
    
    Inside the loop:
    If vis[1] is 0:
        q.push(1);
        vis[0] = 1; <-- If you write 'x' here, node 1 stays unvisited (vis[1] = 0).
                        Next time node 1 is encountered from another path, 
                        it will be pushed into the queue again!

    ===========================================================================
    KEY IDEA / COMMON INTERVIEW MISTAKE AVOIDED
    ===========================================================================
    - Always double-check variable names inside nested loops. 
    - The item being updated in the `vis` array must exactly match the item 
      being inserted into the `queue`.
    ===========================================================================
*/


// ===========================================================================
// 🔥 MY INITIAL MISTAKE / BROKEN ATTEMPT (DO NOT REPEAT)
// ===========================================================================
/*
class SolutionBroken {
public:
    vector<int> bfs(vector<vector<int>> &adj) {
        queue<int> q;
        int vis[adj.size()] = {0};
        vector<int> ans;
        q.push(0);
        vis[0] = 1;
        
        while(!q.empty())
        {
            int x = q.front();
            q.pop();
            ans.push_back(x);

            for(int num : adj[x])
            {
                if(vis[num] == 0)
                {
                    q.push(num);
                    
                    // MISTAKE HERE:
                    // Accidentally updated vis[x] instead of vis[num]. 
                    // This leaves the neighbor marked as unvisited, defeating 
                    // the entire purpose of the early visited check.
                    vis[x] = 1; 
                }
            }
        }
        return ans;
    }
};
*/