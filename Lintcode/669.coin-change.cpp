/*************************************************
Copyright: jokerkeny
Author: jokerkeny
Date: 2019-10-06
Description: 
**************************************************/
#include <iostream>
#include <map>
#include <time.h>
#include <vector>

using namespace std;
class Solution {
public:
  /**
   * @param coins: a list of integer
   * @param amount: a total amount of money amount
   * @return: the fewest number of coins that you need to make up
   */
  int coinChange(vector<int> &coins, int amount) {
    // write your code here
    if (coins.empty() && amount)
      return -1;
    map<int, int> dp;
    dp.insert({0, 0});
    int iter = 0;
    for (auto it = dp.begin(); it != dp.end(); it++) {
      int sum = it->first;
      if (sum == amount) {
        cout << "Iterations: " << iter << endl;
        cout << sizeof(dp) + dp.size() * (sizeof(decltype(dp)::key_type) + sizeof(decltype(dp)::mapped_type)) <<" bytes"<< endl;
        cout << sizeof(decltype(dp)::key_type) << endl;
        cout << sizeof(decltype(dp)::mapped_type) << endl;
        return it->second;
      }
      if (sum > amount)
        return -1;
      int nextnum = it->second + 1;
      for (auto coin : coins) {
        iter++;
        int nextsum = sum + coin;
        if (dp.find(nextsum) == dp.end())
          dp.insert({nextsum, nextnum});
        else
          dp[nextsum] = min(dp[nextsum], nextnum);
      }
    }
    return -1;
  }
};

class std_Solution {
public:
  /**
   * @param coins: a list of integer
   * @param amount: a total amount of money amount
   * @return: the fewest number of coins that you need to make up
   */
  int coinChange(vector<int> &coins, int amount) {
    // write your code here
    if (coins.empty() && amount)
      return -1;
    int n = coins.size();
    vector<int> dp(amount + 1, -1);
    dp[0] = 0;
    int iter = 0;
    for (int i = 1; i <= amount; i++)
      for (int j = 0; j < n; j++) {
        iter++;
        int v = i - coins[j];
        if (v >= 0 && dp[v] != -1)
          if (dp[i] == -1 || dp[i] > dp[v] + 1)
            dp[i] = dp[v] + 1;
      }
    cout << "Iterations: " << iter << endl;
    cout << sizeof(dp) + dp.size()*sizeof(decltype(dp)::value_type) <<" bytes" << endl;
    return dp[amount];
  }
};
int main() {
  vector<int> coins{1,  2,  20, 41, 30, 40, 34, 43, 47, 38,
                    26, 39, 25, 42, 37, 23, 28, 49, 27};
  int amount = 410100;
  clock_t c0 = clock();
  int std_ans = std_Solution().coinChange(coins, amount);
  clock_t c1 = clock();
  cout << std_ans << endl;
  cout << (c1 - c0) * 1000 / CLOCKS_PER_SEC << "ms" << endl;

  int ans = Solution().coinChange(coins, amount);
  clock_t c2 = clock();
  cout << ans << endl;
  cout << (c2 - c1) * 1000 / CLOCKS_PER_SEC << "ms" << endl;
  return 0;
}
