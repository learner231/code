#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int tsp(int n, const vector<vector<int>>& dist) {
    int VISITED_ALL = (1 << n) - 1; 
    vector<vector<int>> dp(n, vector<int>(1 << n, INT_MAX)); 

    for (int i = 0; i < n; i++) {
        dp[i][1 << i] = dist[0][i];
    }

    for (int mask = 1; mask < (1 << n); mask++) {
        for (int current = 0; current < n; current++) {
            if (!(mask & (1 << current))) continue; 
            for (int next = 0; next < n; next++) {
                if (mask & (1 << next)) continue; 
                int newMask = mask | (1 << next);
                dp[next][newMask] = min(dp[next][newMask], dp[current][mask] + dist[current][next]);
            }
        }
    }

    int minCost = INT_MAX;
    for (int i = 1; i < n; i++) {
        minCost = min(minCost, dp[i][VISITED_ALL] + dist[i][0]);
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

    int result = tsp(n, dist);
    cout << "Minimum cost (Dynamic Programming): " << result << endl;
    return 0;
}

// TC= o(n^2 * 2^n)
// SC= o(n * 2^n)