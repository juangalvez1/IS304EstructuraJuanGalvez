#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

class UnionFind {
private:
    vector<int> parent, rank;

public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool union_sets(int x, int y) {
        int xr = find(x);
        int yr = find(y);
        if (xr == yr)
            return false;
        if (rank[xr] < rank[yr])
            parent[xr] = yr;
        else if (rank[xr] > rank[yr])
            parent[yr] = xr;
        else {
            parent[yr] = xr;
            rank[xr]++;
        }
        return true;
    }
};

class Graph {
private:
    vector<vector<int>> adj_matrix;
    vector<int> edges_u;
    vector<int> edges_v;
    vector<int> edges_weight;

public:
    Graph(int n) {
        adj_matrix = vector<vector<int>>(n, vector<int>(n, -1));
    }

    void add_edge(int u, int v, int weight) {
        adj_matrix[u][v] = weight;
        adj_matrix[v][u] = weight;
    }

    void print() {
        cout << "Matriz de adyacencia ponderada:\n";
        for (const auto& row : adj_matrix) {
            for (int val : row) {
                if (val == -1) cout << ". ";
                else cout << val << " ";
            }
            cout << endl;
        }
    }

    void extract_edges() {
        int n = adj_matrix.size();
        edges_u.clear();
        edges_v.clear();
        edges_weight.clear();

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (adj_matrix[i][j] != -1) {
                    edges_u.push_back(i);
                    edges_v.push_back(j);
                    edges_weight.push_back(adj_matrix[i][j]);
                }
            }
        }
    }

    void kruskal() {
        extract_edges();
        int n = adj_matrix.size();
        int m = edges_u.size();

        
        vector<int> indices(m);
        for (int i = 0; i < m; ++i) indices[i] = i;

        sort(indices.begin(), indices.end(), [&](int a, int b) {
            return edges_weight[a] < edges_weight[b];
        });

        UnionFind uf(n);
        int mst_weight = 0;

        cout << "\nAristas del Árbol de Expansión Mínima (Kruskal):\n";
        for (int i : indices) {
            int u = edges_u[i];
            int v = edges_v[i];
            int w = edges_weight[i];

            if (uf.union_sets(u, v)) {
                cout << u << " - " << v << " (peso " << w << ")\n";
                mst_weight += w;
            }
        }
        cout << "Peso total del MST: " << mst_weight << endl;
    }
};

int main() {
    int n = 11;
    Graph g(n);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, n - 1);
    uniform_int_distribution<> weight_dist(1, 100);

    for (int i = 0; i < 10; i++) {
        int u = distrib(gen);
        int v = distrib(gen);
        while (v == u) v = distrib(gen);
        g.add_edge(u, v, weight_dist(gen));
    }

    // g.print();
    g.kruskal();

    return 0;
}
