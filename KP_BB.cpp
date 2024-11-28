#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Node {
    int level, profit, bound, weight;
};

int bound(Node u, int n, int W, vector<int>& weights, vector<int>& values) {
    if (u.weight >= W) return 0;

    int profitBound = u.profit, j = u.level + 1, totWeight = u.weight;

    while (j < n && totWeight + weights[j] <= W) {
        totWeight += weights[j];
        profitBound += values[j];
        j++;
    }

    if (j < n) profitBound += (W - totWeight) * values[j] / weights[j];
    return profitBound;
}

int knapsackBranchBound(int W, vector<int>& weights, vector<int>& values, int n) {
    auto cmp = [](Node a, Node b) { return a.bound < b.bound; };
    priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);

    Node u, v;
    u.level = -1; u.profit = 0; u.weight = 0;
    u.bound = bound(u, n, W, weights, values);
    pq.push(u);

    int maxProfit = 0;
    while (!pq.empty()) {
        u = pq.top();
        pq.pop();

        if (u.level == n - 1) continue;

        v.level = u.level + 1;

        v.weight = u.weight + weights[v.level];
        v.profit = u.profit + values[v.level];

        if (v.weight <= W && v.profit > maxProfit) maxProfit = v.profit;

        v.bound = bound(v, n, W, weights, values);
        if (v.bound > maxProfit) pq.push(v);

        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = bound(v, n, W, weights, values);
        if (v.bound > maxProfit) pq.push(v);
    }

    return maxProfit;
}

int main() {
    int n, W;
    cout << "Enter the number of items: ";
    cin >> n;
    vector<int> weights(n), values(n);

    cout << "Enter the weights of items: ";
    for (int i = 0; i < n; i++) cin >> weights[i];

    cout << "Enter the values of items: ";
    for (int i = 0; i < n; i++) cin >> values[i];

    cout << "Enter the capacity of the knapsack: ";
    cin >> W;

    cout << "Maximum value in knapsack (Branch and Bound): " << knapsackBranchBound(W, weights, values, n) << endl;
    return 0;
}

// TC = O(2^n) (worst-case)
// SC = o(n)   n=no. of items