#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    int n, e;
    cin >> n >> e;

    vector<vector<pair<int, int>>> graph(n);

    // Input graph
    for (int i = 0; i < e; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    vector<bool> visited(n, false);

    // {weight, {parent, vertex}}
    priority_queue<
        pair<int, pair<int, int>>,
        vector<pair<int, pair<int, int>>>,
        greater<pair<int, pair<int, int>>>
    > pq;

    // Start from vertex 0
    pq.push({0, {-1, 0}});

    int totalCost = 0;

    cout << "Edges in MST:\n";

    while (!pq.empty())
    {
        int weight = pq.top().first;
        int parent = pq.top().second.first;
        int u = pq.top().second.second;

        pq.pop();

        if (visited[u])
            continue;

        visited[u] = true;

        // Print selected edge
        if (parent != -1)
        {
            cout << parent << " - " << u << " : " << weight << endl;
            totalCost += weight;
        }

        // Add adjacent edges
        for (int i = 0; i < graph[u].size(); i++)
        {
            int v = graph[u][i].first;
            int w = graph[u][i].second;

            if (!visited[v])
            {
                pq.push({w, {u, v}});
            }
        }
    }

    cout << "Total MST Cost = " << totalCost << endl;

    return 0;
}
