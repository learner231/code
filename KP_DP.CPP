#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int knapsackDP(int W, vector<int>& weights, vector<int>& profit, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(profit[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    return dp[n][W];
}

int main() {
    int n, W;
    cout << "Enter the number of items: ";
    cin >> n;
    vector<int> weights(n), profit(n);

    cout << "Enter the weights of items: ";
    for (int i = 0; i < n; i++) cin >> weights[i];

    cout << "Enter the profit of items: ";
    for (int i = 0; i < n; i++) cin >> profit[i];

    cout << "Enter the capacity of the knapsack: ";
    cin >> W;

    cout << "Maximum profit in knapsack (DP): " << knapsackDP(W, weights, profit, n) << endl;
    return 0;
}

// Time complexity: o(n*Capacity)
// space complexity:o(n*capacity)