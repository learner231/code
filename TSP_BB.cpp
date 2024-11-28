#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;

struct Node {
    vector<bool> visited;
    int cost, level, currentCity;
};

int tspBranchBound(int n, vector<vector<int>>& dist) {
    auto compare = [](Node& a, Node& b) { return a.cost > b.cost; };
    priority_queue<Node, vector<Node>, decltype(compare)> pq(compare);

    Node root;
    root.visited = vector<bool>(n, false);
    root.visited[0] = true;
    root.cost = 0;
    root.level = 0;
    root.currentCity = 0;

    pq.push(root);
    int minCost = INT_MAX;

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.level == n - 1) {
            int totalCost = current.cost + dist[current.currentCity][0];
            minCost = min(minCost, totalCost);
            continue;
        }

        for (int nextCity = 0; nextCity < n; nextCity++) {
            if (!current.visited[nextCity]) {
                Node next = current;
                next.visited[nextCity] = true;
                next.level++;
                next.cost += dist[current.currentCity][nextCity];
                next.currentCity = nextCity;

                if (next.cost < minCost) {
                    pq.push(next);
                }
            }
        }
    }

    return minCost;
}

int main() {
    int n;
    cout << "Enter the number of cities: ";
    cin >> n;

    vector<vector<int>> dist(n, vector<int>(n));
    cout << "Enter the distance matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> dist[i][j];
        }
    }

    cout << "Minimum cost (Branch and Bound): " << tspBranchBound(n, dist) << endl;
    return 0;
}

// time complexity:o(n!)(worst case)
// space=o(n2)