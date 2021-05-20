#include <iostream>
#include <queue>
#include <vector>
#include <array>
#include <unordered_map>

using namespace std;
# define INF 0x3f3f3f3f

typedef pair<int, int> iPair;

class Graph
{
    int V, E;
    int RR = 5, CC = 5;
    vector<vector<int> > matrix;

    list< pair<int, int> >* adj;
    vector< pair<int, iPair> > edges;
public:
    Graph(int V, int E);

    void addEdge(int u, int v, int w);

    void shortestPath(int s);

    int kruskalMST();

    int kruskalMST2();

    void printGraph();
};

Graph::Graph(int V, int E)
{
    this->V = V;
    adj = new list<iPair>[V];
    
    this->V = V;
    this->E = E;

    matrix.resize(V);

    
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            matrix[i].push_back(0);
        }
    }
}

void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
    edges.push_back({ w, {u, v} });
    
}

void Graph::shortestPath(int src)
{
    priority_queue< iPair, vector <iPair>, greater<iPair> > pq;

    vector<int> dist(V, INF);

    pq.push(make_pair(0, src));
    dist[src] = 0;

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            int v = (*i).first;
            int weight = (*i).second;

            if (dist[v] > dist[u] + weight)
            {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

struct DisjointSets
{
    int *parent, *rnk;
    int n;
  
    DisjointSets(int n)
    {
        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];
  
        for (int i = 0; i <= n; i++)
        {
            rnk[i] = 0;
            parent[i] = i;
        }
    }

    int find(int u)
    {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }
    void merge(int x, int y)
    {
        x = find(x), y = find(y);

        if (rnk[x] > rnk[y])
            parent[y] = x;
        else parent[x] = y;
  
        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};

int Graph::kruskalMST()
{
    int mst_wt = 0;

    sort(edges.begin(), edges.end());

    DisjointSets ds(V);

    vector< pair<int, iPair> >::iterator it;
    for (it = edges.begin(); it != edges.end(); it++)
    {
        int u = it->second.first;
        int v = it->second.second;

        int set_u = ds.find(u);
        int set_v = ds.find(v);

        if (set_u != set_v)
        {
            cout << u << " - " << v << endl;
            mst_wt += it->first;
            ds.merge(set_u, set_v);
        }
    }

    return mst_wt;
}

int Graph::kruskalMST2()
{
    int mst_wt = 0;

    sort(edges.begin(), edges.end());

    DisjointSets ds(V);

    vector< pair<int, iPair> >::iterator it;
    for (it = edges.begin(); it != edges.end(); it++)
    {
        int u = it->second.first;
        int v = it->second.second;

        int set_u = ds.find(u);
        int set_v = ds.find(v);

        if (set_u != set_v)
        {
            matrix[u][v] = 1;
            matrix[v][u] = 1;
            cout << u << " - " << v << endl;
            mst_wt += it->first;
            ds.merge(set_u, set_v);
        }
    }
    cout << "Matrix" << endl;
    cout << "   ";
    for (int j = 0; j < matrix[0].size(); j++) {
        cout << j << " ";
    }
    cout << endl;
    for (int i = 0; i < matrix.size(); i++) {
        cout << i << ": ";
        for (int j = 0; j < matrix[0].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    return mst_wt;
}

void Graph::printGraph()
{
    for (int v = 0; v < V; ++v)
    {
        cout << "\n Adjacency list of vertex "
            << v << "\n head ";
        for (auto x : adj[v])
            cout << "-> " << x.first << " " <<x.second<<endl;
    }
}

int main()
{
    int V = 9, E = 14;
    Graph g(V, E);

    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);
    g.shortestPath(0);

    cout << "Edges of MST are \n";
    int mst_wt = g.kruskalMST();
    cout << "\nWeight of MST is " << mst_wt<<endl;

    cout<<g.kruskalMST2();
    cout << endl;
    cout << endl;
    cout << endl;

    g.printGraph();
    return 0;
}