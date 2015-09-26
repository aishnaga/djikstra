#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>
#include <map>
#include <bitset>

using namespace std;

// Graph is a multilevel map 
// First level map is indexed by vertex1
// Second level map is the pair of neighbor vertex2, min distance 
typedef map<int, map<int, int> > Graph;

// Comparison operator for the priority queue
// Sorts by distance given the pair of vertex, distance  
class Comparator
{
public:
    int operator() ( const pair<int, int>& p1, const pair<int, int> &p2)
    {
        return p1.second > p2.second;
    }
};

bool dijkstra(Graph &G, int source, int destination, vector<int> &path) {
    vector<int> d(destination+1); // keeps track of min distance 
    vector<int> parent(destination+1); // used to populate the path vector 
    bitset<100000> bits; // used to track if this vertex has been seen before 
    
    // Populate all distances as infinity (aka max int)
    for(int i = 0 ;i < (destination+1); i++){
        d[i] = numeric_limits<int>::max();
    }

    // Instantiate priority queue which sorts by distance (higher to lower)
    priority_queue<pair<int, int>, vector<pair<int, int> >, Comparator> Q;
    
    // Distance for the source is 0, push it into the PQ
    d[source] = 0;
    Q.push(make_pair(source,d[source]));

    // Update min distances for neighbors 
    while(!Q.empty()){
        int u = Q.top().first; // grab the closest neighbor 
        // If we're at the destination, update path and exit 
        if(u==destination) {
            path.clear();
            int p = destination;
            path.push_back(destination);
            
            while(p!=source){
                p = parent[p];
                path.push_back(p);
            }
            return true;
        }
        // Mark u as a visited vertex in the bitset 
        bits.set(u);    
        // Remove u from the PQ since it's been visited
        Q.pop();
        
        // Go through all neighbors of u
        for(auto &it: G[u]) {
            int v = it.first; // v == vertex
            // If vertex v isn't in the visited set 
            // and we have found a shorter distance 
            // update v's distance and put in the PQ
            if (!bits[v]) { 
                int w = it.second;
                if(d[v] > d[u]+w) {
                   d[v] = d[u]+w;
                   parent[v] = u;
                   Q.push(make_pair(v,d[v]));
                }
            }
        }
    }
    // Went through all neighbors but no path found 
    return false;
}

int main()
{
    // Instantiate the graph
    Graph g;
    // Accept vertices and edges
    unsigned n, m;
    cin >> n >> m;
    // Populate the graph with edge distances 
    for (unsigned i = 0; i < m; i ++) {
        unsigned x, y, z;
        cin >> x >> y >> z;
        g[x][y] = g[y][x] = z;
    }
    // path is the vector of elements from
    // destination to source, so printed 
    // out in reverse 
    vector<int> path;
    if (dijkstra(g,1,n,path)) { // path found 
        for(int i=path.size()-1;i>=0;i--) {
            cout<<path[i]<< " ";
        }
        cout << endl;
    } else { // no path found
        cout << -1 << endl;
    }

    return 0;
}
