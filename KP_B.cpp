#include <iostream>
#include <vector>
using namespace std;

int knapsackBacktrack(int i, int W, vector<int>& weights, vector<int>& profit, int currentValue) {
    if (i == weights.size()) return currentValue;

    int withoutItem = knapsackBacktrack(i + 1, W, weights, profit, currentValue);

    int withItem = 0;
    if (weights[i] <= W) {
        withItem = knapsackBacktrack(i + 1, W - weights[i], weights, profit, currentValue + profit[i]);
    }

    return max(withoutItem, withItem);
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

    cout << "Maximum value in knapsack (Backtracking): " << knapsackBacktrack(0, W, weights, profit, 0) << endl;
    return 0;
}

// TC = O(2^n) (worst-case)
// SC = o(n)   n=no. of items