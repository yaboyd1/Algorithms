#include <stdio.h>
#include <stdlib.h>

#define k 10

// NOTE: I used STL queue, unordered_map as well as helper functions in maxflow()
#include <queue>         // Provides queue
#include <unordered_map> // Provides hash map 
#include <algorithm>     // Provides min(x, y)
#include <climits>       // Provides INT_MAX
using namespace std;

// PRECONDITON: cap and flow contains non-negative values and are n x n adj matrices
// POSTCONDTION: One iteration of the Ford Fulkerson Algorithm
// ALGORITHM: Ford Fulkerson using BFS
/* Psuedo Code
Construct the residual graph using cap and flow
Find a path in residual graph using BFS
if a valid path exists,
    Find the bottleneck capacity or minimum flow of the path
    Update the flow graph with the bottleneck capacity
return the bottleneck capacity, defaults to 0
*/
int maxflow(int n, int* cap, int* flow, int* residual);

// PRECONDITON: n is the size of the square array of the graph (n x n 2D adj matrix)
// POSTCONDTION: Finds the shortest path from (0, 0) to (n - 1, n - 1) in the form of a hash map
// ALGORITHM: BFS using an additional hash map to find where a node reached from
/* Psuedo Code
Put the starting node in the queue
while (queue is not empty):
	node = next value of the queue
	if (node is the target)
		draw the shortest path in orange from target->start
		return
	if (node has not been visited):
		mark node as visited
		for all valid children of the node:
			if (child is not from any other node)
				mark child as from this node
				draw green line from node->child
*/
bool bfs(const int& n, int*& graph, unordered_map<int, int>& path);

main() {
	int capacities[4 * k + 2][4 * k + 2];
	int flow[4 * k + 2][4 * k + 2];
	int residual[4 * k + 2][4 * k + 2];
	int i, j, improvement, stepcount, totalflow;
	int inflow, outflow;
	for (i = 0; i < 4 * k + 2; i++)
		for (j = 0; j < 4 * k + 2; j++) {
			capacities[i][j] = 0;
			flow[i][j] = 0;
			residual[i][j] = 0;
		}
	/* initialize capacities */
	for (i = 1; i < k + 1; i++) {
		capacities[0][i] = 20;
		capacities[i][k + i] = 4;
		capacities[i][k + (i % k) + 1] = 4;
		capacities[i][2 * k + i] = 5;
		capacities[k + i][3 * k + i] = 5;
		capacities[2 * k + i][3 * k + i] = 3;
		capacities[2 * k + i][3 * k + (i % k) + 1] = 3;
		capacities[2 * k + i][3 * k + ((i + 1) % k) + 1] = 3;
		capacities[3 * k + i][4 * k + 1] = 12;
	}
	printf("created capacity matrix. %d vertices, expected maximum flow %d.\n",
		4 * k + 2, 10 * k);

	improvement = 1;
	stepcount = 0;
	while (improvement > 0) {
		improvement = maxflow(4 * k + 2, &(capacities[0][0]), &(flow[0][0]),
			&(residual[0][0]));
		stepcount++;
		/* check flow matrix: capacity constraint and nonnegativity */
		for (i = 0; i < 4 * k + 2; i++)
			for (j = 0; j < 4 * k + 2; j++) {
				if (flow[i][j] < 0) {
					printf("step %d: negative flow value %d on edge %d -> %d\n",
						stepcount, flow[i][j], i, j);
					fflush(stdout);
					exit(0);
				}
				if (flow[i][j] > capacities[i][j]) {
					printf("step %d: flow %d > capacity %d on edge %d -> %d\n",
						stepcount, flow[i][j], capacities[i][j], i, j);
					fflush(stdout);
					exit(0);
				}
			}
		/* check flow matrix: inflow = outflow */
		for (i = 1; i < 4 * k + 1; i++) {
			inflow = 0;
			outflow = 0;
			for (j = 0; j < 4 * k + 2; j++) {
				inflow += flow[j][i];
				outflow += flow[i][j];
			}
			if (inflow != outflow) {
				printf("step %d: flow conservation violated in vertex %d\n",
					stepcount, i);
				fflush(stdout);
				exit(0);
			}
		}
		printf("step %d completed; improvement %d\n", stepcount, improvement);
	}
	totalflow = 0;
	for (i = 1; i < k + 1; i++)
		totalflow += flow[0][i];
	printf("finished after %d steps; total flow %d\n", stepcount, totalflow);
}

int maxflow(int n, int* cap, int* flow, int* residual) {
	// Create Residual Graph for BFS traversal
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			residual[j * n + i] = flow[i * n + j];

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (residual[i * n + j] == 0)
				residual[i * n + j] = cap[i * n + j] - flow[i * n + j];

	// If a valid path is found
	int bottleneck = 0;
	unordered_map<int, int> path;
	if (bfs(n, residual, path)) {
		// Find bottleneck
		bottleneck = INT_MAX;
		for (int i = n - 1; i != 0; i = path[i])
			bottleneck = min(residual[path[i] * n + i], bottleneck);

		// Update flow with bottleneck
		for (int i = n - 1; i != 0; i = path[i])
			flow[path[i] * n + 1] >= 0 ? flow[path[i] * n + i] += bottleneck : flow[path[i] * n + i] -= bottleneck;
	}
	return bottleneck;
}

bool bfs(const int& n, int*& graph, unordered_map<int, int>& parent) {
	queue<int> q;
	unordered_map<int, bool> visited;

	int chosenNode = 0;
	q.push(chosenNode);

	while (!q.empty()) {
		chosenNode = q.front();
		q.pop();

		// Stop early if target is reached
		if (chosenNode == n - 1)
			return true;

		if (!visited[chosenNode]) {
			visited[chosenNode] = true;
			for (int child = 0; child < n; ++child) {
				// If valid child and not found
				if (graph[chosenNode * n + child] > 0 && parent.find(child) == parent.end()) {
					parent[child] = chosenNode;
					q.push(child);
				}
			}
		}
	}
	return false;
}
