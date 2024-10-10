#include <bits/stdc++.h>
using namespace std;
const int OO = (int) 1e6;
// OO is used as a representation of infinity, indicating unreachable nodes.
// It's set to a large value (1 million), assuming no path would have a cost greater than this in practice.
void print(const vector<vector<int>> &adjMatrix)
{
    int n = adjMatrix.size();
    // 'n' is the size of the adjacency matrix (i.e., number of nodes).
    for (int i = 0; i < n; ++i)  // Iterating over all rows (nodes)
    {
        for (int j = 0; j < n; ++j)  // Iterating over all columns (nodes)
        {
            if (adjMatrix[i][j] >= OO)  // If the value is infinity (OO), it means no path exists.
                cout << "OO" << " ";  // Print "OO" to represent no path between nodes.
            else
                cout << adjMatrix[i][j] << " ";  // Otherwise, print the actual distance between nodes.
        }
        cout << "\n";  // Move to the next row.
    }
    cout << "**************************\n";
}// This function prints the adjacency matrix to visualize the current state of the graph.
// It distinguishes between unreachable nodes and valid paths.
void readGraph(vector<vector<int>> &adjMatrix)
{
    int n, m;  // 'n' is the number of nodes, 'm' is the number of edges.
    cin >> n >> m;
    // Initialize the adjacency matrix with infinity (OO).
    adjMatrix = vector<vector<int>>(n, vector<int>(n, OO));
    for (int i = 0; i < n; ++i)
        adjMatrix[i][i] = 0;  // Distance from a node to itself is 0.
    for (int i = 0; i < m; ++i)
    {
        int from, to, weight;
        cin >> from >> to >> weight;  // Input the edge details (from node, to node, and the weight).
        if (from == to)
            continue;  // Ignore self-loops, even if negative.
        adjMatrix[from][to] = min(adjMatrix[from][to], weight);
        // If there's already an edge between 'from' and 'to', take the smaller weight.
    }
}
// The 'read_graph' function reads the number of nodes and edges from the user,
// initializes the adjacency matrix with infinite values (OO), and sets up the matrix
// based on the input edges, ignoring self-loops.
void floyd(vector<vector<int>> &adjMatrix) //Time : O(n³) // Space : O(n²)
{
    int n =adjMatrix.size();
    cout << "Input matrix\n";
    print(adjMatrix); // Print the initial state of the adjacency matrix.
    // Floyd-Warshall Algorithm: Dynamic Programming approach to find all-pairs shortest paths.
    for (int k = 0; k < n; ++k) // 'k' is the intermediate node being considered for relaxation.
    {
        for (int i = 0; i < n; ++i) // Iterating over all pairs (i, j) to update their shortest path.
            for (int j = 0; j < n; ++j)
            {
                // Calculate if the path from i to j through k is shorter.
                int relax= adjMatrix[i][k] + adjMatrix[k][j];
                adjMatrix[i][j]= min(relax,adjMatrix[i][j]);
                // If going through node 'k' provides a shorter path, update the distance.
            }
        cout<<"After relaxing with "<<k<<"\n";
        print(adjMatrix);  // Print the matrix after considering node 'k' as an intermediate.
    }
}
// The 'floyd' function implements the Floyd-Warshall algorithm to compute the shortest
// paths between all pairs of nodes. It relaxes each node (k) to check if using it as an intermediate
// results in a shorter path between any two nodes (i, j)
int main()
{
    vector<vector<int>> adjMatrix;
    readGraph(adjMatrix);
    floyd(adjMatrix);
    return 0;
}