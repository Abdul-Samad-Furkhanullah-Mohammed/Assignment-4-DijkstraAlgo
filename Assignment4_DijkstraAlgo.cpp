#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

// Function to implement the algorithm given
void di_jk_st_ra_1510(const vector<vector<pair<int, int>>>& graph, int source) {
    int n_01 = graph.size(); // to input the size of the structure

    // Initialize length and queue data structure
    vector<int> dist(n_01, numeric_limits<int>::max()), prev(n_01, -1);
    dist[source] = 0; // Distance to the source node is 0


    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source}); // Push the source length as 0

    while (!pq.empty()) {
        int u = pq.top().second; // terminal with the smallest length
        int d = pq.top().first;  // its length
        pq.pop();

        // skipping if its length is outdated
        if (d > dist[u]) continue;


        for (const auto& edge : graph[u]) {
            int v = edge.first;  // Neighbor
            int weight = edge.second; // Weight


            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push({dist[v], v}); // Push the update
            }
        }
    }

    // Output of the result
    cout << "Vertex\tCost\tPath\n";
    for (int i = 0; i < n_01; ++i) {
        if (i == source) continue; // Skip the source

        cout << "A -> " << char('A' + i) << "\t" << dist[i] << "\t";

        // Recreate and display the path
        vector<char> path;
        for (int v = i; v != -1; v = prev[v]) {
            path.push_back(char('A' + v));
        }
        reverse(path.begin(), path.end());
        for (size_t j = 0; j < path.size(); ++j) {
            cout << path[j];
            if (j != path.size() - 1) cout << " -> ";
        }
        cout << endl;
    }
}

int main() {
    int n_11; // size
    cout << "Enter the nodes: ";
    cin >> n_11;


    vector<vector<pair<int, int>>> graph(n_11);
    cout << "Enter the adjacency matrix (0 for no edge):\n";
    for (int i = 0; i < n_11; ++i) {
        for (int j = 0; j < n_11; ++j) {
            int weight;
            cin >> weight;
            if (weight != 0) { // Add if a connection
                graph[i].emplace_back(j, weight);
            }
        }
    }

    int source;
    cout << "Enter the starting node (A = 0, B = 1, ...): ";
    cin >> source;


    di_jk_st_ra_1510(graph, source);
    return 0;
}
