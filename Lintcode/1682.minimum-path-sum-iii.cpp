/*************************************************
Copyright: jokerkeny
Author: jokerkeny
Date: 2019-10-07
Description:
**************************************************/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
  /**
   * @param grid:
   * @return: nothing
   */
  int minimumPathSumIII_std(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();
    int dp[n][m];
    dp[0][0] = grid[0][0];
    for (int i = 1; i < n; i++)
      dp[i][0] = dp[i - 1][0] + grid[i][0];
    for (int j = 1; j < m; j++)
      dp[0][j] = dp[0][j - 1] + grid[0][j];
    for (int i = 1; i < n; i++) {
      for (int j = 1; j < m; j++) {
        dp[i][j] =
            min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + grid[i][j];
      }
    }
    return dp[n - 1][m - 1];
  }
  int minimumPathSumIII_wrong(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<int> dp(m + 1, INT_MAX);
    dp[1] = 0;
    int temp, prev;
    for (int i = 1; i <= n; i++) {
      prev = INT_MAX;
      for (int j = 1; j <= m; j++) {
        temp = dp[j];
        dp[j] = min({prev, dp[j], dp[j - 1]}) + grid[i - 1][j - 1];
        prev = temp;
      }
    }
    return dp[m];
  }
  int minimumPathSumIII(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<int> dp(m + 1, INT_MAX);
    dp[1] = grid[0][0];
    int temp, prev;
    for (int j = 2; j <= m; j++)
      dp[j] = dp[j - 1] + grid[0][j - 1];
    for (int i = 2; i <= n; i++) {
      prev = INT_MAX;
      for (int j = 1; j <= m; j++) {
        temp = dp[j];
        dp[j] = min({prev, dp[j], dp[j - 1]}) + grid[i - 1][j - 1];
        prev = temp;
      }
    }
    return dp[m];
  }
};

int main() {
  string num;
  vector<vector<int>> grid = {
      {4, -5, -4}, {-3, -3, -4}, {0, 2, 3},   {1, -2, 4},  {-4, -5, -1},
      {1, 1, -5},  {4, -4, -3},  {4, -2, -1}, {-2, 0, 3},  {-3, 4, -5},
      {-4, -2, 2}, {3, -1, 1},   {-2, 2, 2},  {-5, 4, -2}, {-4, 3, 1}};
  Solution sol;
  int ans_std = sol.minimumPathSumIII_std(grid);
  cout << ans_std << endl;
  int answrong = sol.minimumPathSumIII_wrong(grid);
  cout << answrong << endl;
  int ans = sol.minimumPathSumIII(grid);
  cout << ans << endl;
  return 0;
}
