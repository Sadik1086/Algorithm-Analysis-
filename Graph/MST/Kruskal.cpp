#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool compare(vector<int> a, vector<int> b)
{
    return a[2] < b[2];
}

int findParent(int parent[], int x)
{
    if (parent[x] == x)
        return x;

    return findParent(parent, parent[x]);
}

void unionSet(int parent[], int a, int b)
{
    a = findParent(parent, a);
    b = findParent(parent, b);

    parent[b] = a;
}

int main()
{
    int n, e;
    cin >> n >> e;

    vector<vector<int>> edges;

    // Input edges
    for (int i = 0; i < e; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        edges.push_back({u, v, w});
    }

    // Sort edges according to weight
    sort(edges.begin(), edges.end(), compare);

    int parent[100];

    for (int i = 0; i < n; i++)
        parent[i] = i;

    int totalCost = 0;
    int count = 0;

    cout << "Edges in MST:\n";

    for (int i = 0; i < e; i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];

        int parentU = findParent(parent, u);
        int parentV = findParent(parent, v);

        // Take edge if it does not create a cycle
        if (parentU != parentV)
        {
            cout << u << " - " << v << " : " << w << endl;

            totalCost += w;
            count++;

            unionSet(parent, u, v);

            if (count == n - 1)
                break;
        }
    }

    cout << "Total MST Cost = " << totalCost << endl;

    return 0;
}
