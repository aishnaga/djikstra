#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>
#include <map>
#include <bitset>

using namespace std;

typedef map<int, map<int,int> > Graph;

class Comparator
{
public:
    int operator() ( const pair<int,int>& p1, const pair<int,int> &p2)
    {
     return p1.second > p2.second;
    }
};

bool dijkstra(Graph  &G, int source, int destination, vector<int> &path) {
    vector<int> d(destination+1);
    vector<int> parent(destination+1);
    bitset<100000> bits;

    for(int i = 0 ;i < (destination+1); i++){
        d[i] = std::numeric_limits<int>::max();
        parent[i] = -1;
    }

    priority_queue<pair<int,int>, vector<pair<int,int> >, Comparator> Q;

    d[source] = 0;
    Q.push(make_pair(source,d[source]));

    bool found = false;
    while(!Q.empty()){
        int u = Q.top().first;
        if(u==destination) {
            found = true;
            break;
        }
        bits.set(u);    
        Q.pop();

        for(auto it = G[u].begin(); it != G[u].end(); it ++) {
            int v = it->first;
            if (!bits[v]) {
                int w = it->second;
                if(d[v] > d[u]+w) {
                   d[v] = d[u]+w;
                   parent[v] = u;
                   Q.push(make_pair(v,d[v]));
                }
            }
        }
    }

    if (found) {
        path.clear();
        int p = destination;
        path.push_back(destination);
        
        while(p!=source){
            p = parent[p];
            path.push_back(p);
        }
    }

    return found;
}

int main()
{
    Graph g;
    unsigned n, m;
    cin >> n >> m;
    for (unsigned i = 0; i < m; i ++) {
        unsigned x, y, z;
        cin >> x >> y >> z;
        g[x][y] = g[y][x] = z;
    }

    vector<int> path;
    if (dijkstra(g,1,n,path)) {
        for(int i=path.size()-1;i>=0;i--) {
            cout<<path[i]<< " ";
        }
        cout << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;
}
