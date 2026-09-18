#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

int main() {
    int n, e;

    cout << "Enter number of vertices and edges: ";
    cin >> n >> e;

    vector<vector<pair<int, int>>> adj(n + 1);

    cout << "Enter edges (u v weight):\n";

    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // Print Adjacency List
    cout << "\nAdjacency List:\n";

    for (int i = 1; i <= n; i++) {
        cout << i << " -> ";

        for (auto edge : adj[i]) {
            cout << "(" << edge.first << "," << edge.second << ") ";
        }

        cout << endl;
    }

    int source;
    cout << "\nEnter source vertex: ";
    cin >> source;

    vector<int> dist(n + 1, INT_MAX);

    // Parent array
    vector<int> parent(n + 1, -1);

    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {

        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u])
            continue;

        for (auto edge : adj[u]) {

            int v = edge.first;
            int w = edge.second;

            if (dist[u] + w < dist[v]) {

                dist[v] = dist[u] + w;

                // Store previous vertex
                parent[v] = u;

                pq.push({dist[v], v});
            }
        }
    }

    // Distance + Path
    cout << "\nShortest Distance and Path from " << source << ":\n";

    for (int i = 1; i <= n; i++) {

        if (dist[i] == INT_MAX) {
            cout << i << " -> INF\n";
            continue;
        }

        // Construct path
        vector<int> path;

        int current = i;

        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }

        reverse(path.begin(), path.end());

        cout << i << " : Distance = " << dist[i];
        cout << ", Path = ";

        for (int j = 0; j < path.size(); j++) {
            cout << path[j];

            if (j != path.size() - 1)
                cout << " -> ";
        }

        cout << endl;
    }

    return 0;
}
