/*
    Problem: Topological Sort (Kahn's Algorithm - BFS)
    Given a Directed Acyclic Graph (DAG) with V vertices and E edges, 
    find a Topological Order of the vertices.

    Approaches:
    ---------------------------------------------------------
    1) Optimal Approach: Kahn's Algorithm (BFS)
       - Compute the in-degree (number of incoming edges) for each vertex.
       - Push all vertices with an in-degree of 0 into a queue.
       - Pop a vertex, add it to the linear ordering, and reduce the in-degree 
         of all its neighboring vertices by 1.
       - If a neighbor's in-degree drops to 0, push it into the queue.

       Time Complexity: O(V + E)
       Space Complexity: O(V) -> For the adjacency list, indegree array, and queue.
*/

#include <vector>
#include <queue>
#include <iostream>
using namespace std;

// ======================= OPTIMAL APPROACH =======================

class Solution {
public:
    vector<int> topoSort(int V, vector<vector<int>>& edges) {
        vector<vector<int>> adj(V);
        vector<int> indegree(V, 0); // Standard-compliant vector allocation
        vector<int> ans;
        
        // Build adjacency list and calculate in-degrees
        for(const vector<int>& curr : edges)
        {
            adj[curr[0]].push_back(curr[1]);
            indegree[curr[1]]++; 
        }
        
        queue<int> q;
        // Push all nodes with 0 incoming dependencies
        for(int i = 0; i < V; i++)
        {
            if(indegree[i] == 0)
            {
                q.push(i);
            }
        }
        
        while(!q.empty())
        {
            int x = q.front();
            q.pop();
            ans.push_back(x);
            
            for(int temp : adj[x])
            {
                indegree[temp]--;
                if(indegree[temp] == 0)
                {
                    q.push(temp);
                }
            }
        }
        
        return ans;
    }
};

/*
    ===========================================================================
    POINTER ROLES & TOOLS
    ===========================================================================
    queue      -> Keeps track of all nodes currently ready to be processed (0 dependencies).
    indegree[] -> Counts incoming dependencies remaining for each node.

    ===========================================================================
    KEY IDEA / COMMON INTERVIEW MISTAKE AVOIDED
    ===========================================================================
    - Placing code after a `return` statement makes it completely dead/unreachable.
    - Renamed the tracking array from `vis` to `indegree` to clearly communicate 
      intent to the interviewer (Kahn's doesn't track "visited" states explicitly).
    ===========================================================================
*/

/*
    Topic: Graph Time Complexity Intuition - O(V + E)
    Understanding why Adjacency List traversals (BFS, DFS, Kahn's) take O(V + E) time.

    Core Concepts:
    ---------------------------------------------------------
    V = Total Vertices (Nodes) in the graph.
    E = Total Edges (Connections) in the graph.
    
    The '+' sign means these two operations happen independently across the lifecycle 
    of the algorithm; they do not multiply.
*/

/*
    ===========================================================================
    VISUALIZING O(V + E) VIA ADJACENCY LIST
    ===========================================================================

    Graph:  0 ----> 1 ----> 2
            \               ^
             -------------->|

    Adjacency List Structure in Memory:
    
    Vertex Array [O(V) Work]         Edge Vectors [O(E) Work]
    +-----------+                    +-------+-------+
    |  Node 0   |  ----------=====>  |   1   |   2   |  (Out-edges of 0)
    +-----------+                    +-------+-------+
    |  Node 1   |  ----------=====>  |   2   |          (Out-edges of 1)
    +-----------+                    +-------+-------+
    |  Node 2   |  ----------=====>  | Empty |          (Out-edges of 2)
    +-----------+                    +-------+
    
    Total Vertices processed (Rows) = V
    Total Edge nodes scanned (Cells) = E
    Total Time = O(V + E)
*/

/*
    ===========================================================================
    THE TWO-PART BREAKDOWN
    ===========================================================================
    
    1) Why O(V)? [The Vertices]
       - Every node enters the queue/recursion stack exactly ONCE.
       - The visited array/indegree check protects nodes from being processed 
         multiple times.
       - Processing V individual nodes = O(V) work.

    2) Why O(E)? [The Edges]
       - Inside the algorithm, when standing on a vertex 'x', we loop through 
         its neighbors: `for(int neighbor : adj[x])`
       - Over the entire run of the algorithm, we visit every vertex's row exactly once.
       - Therefore, we end up scanning every single cell in the entire edge list.
       - Scanning all elements across all neighbor vectors combined = O(E) work.

    ===========================================================================
    KEY IDEA / COMMON INTERVIEW TRAPS AVOIDED
    ===========================================================================
    - It is NOT O(V * E): We do not scan ALL edges for EVERY vertex. We only scan 
      a vertex's specific outgoing edges when standing on that vertex.
      
    - The Matrix Trap: If the graph is represented as an Adjacency Matrix (V x V grid) 
      instead of an Adjacency List, the time complexity becomes O(V^2). This is 
      because you are forced to scan an entire row of size V for every single node 
      just to see if an edge exists, even if the graph has 0 edges.
    ===========================================================================
*/