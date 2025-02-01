#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

class Graph {
public:
    unordered_map<int, vector<pii>> adjList;
    
    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight}); // Assuming an undirected graph
    }
    
    vector<int> dijkstra(int start, int end) {
        unordered_map<int, int> dist;
        unordered_map<int, int> prev;
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        
        for (auto& node : adjList) {
            dist[node.first] = numeric_limits<int>::max();
        }
        
        dist[start] = 0;
        pq.push({0, start});
        
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            
            for (auto& neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;
                int newDist = dist[u] + weight;
                
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    prev[v] = u;
                    pq.push({newDist, v});
                }
            }
        }
        
        vector<int> path;
        for (int at = end; at != start; at = prev[at]) {
            path.push_back(at);
            if (prev.find(at) == prev.end()) {
                cout << "No path found!" << endl;
                return {};
            }
        }
        path.push_back(start);
        reverse(path);
        
        cout << "Shortest Path Cost: " << dist[end] << endl;
        return path;
    }
    
    void reverse(vector<int>& path) {
        int left = 0, right = path.size() - 1;
        while (left < right) {
            swap(path[left], path[right]);
            left++;
            right--;
        }
    }
};

int main() {
    Graph g;
    g.addEdge(1, 2, 4);
    g.addEdge(1, 3, 1);
    g.addEdge(3, 2, 2);
    g.addEdge(2, 4, 1);
    g.addEdge(3, 4, 5);
    
    int start, end;
    cout << "Enter start node: ";
    cin >> start;
    cout << "Enter end node: ";
    cin >> end;
    
    vector<int> path = g.dijkstra(start, end);
    
    if (!path.empty()) {
        cout << "Shortest Path: ";
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    }
    
    return 0;
}
