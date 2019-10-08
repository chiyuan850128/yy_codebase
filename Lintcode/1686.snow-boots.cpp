/*************************************************
Copyright: jokerkeny
Author: jokerkeny
Date: 2019-10-07
Description:
**************************************************/
#include <algorithm>
#include <iostream>
#include <vector>

#include <cstring>

using namespace std;
class Solution {
public:
  /**
   * @param n: The number of bricks.
   * @param b: The number of boots.
   * @param f: The thickness of snow on bricks.
   * @param s: The boots maximum depth of walking.
   * @param d: The boots maximum length of walking.
   * @return: Return the minimum number of boots you should discard.
   */
  int getMinimumNumOfBoots(int n, int b, const vector<int> &f,
                           const vector<int> &s, const vector<int> &d) {
    // Write your code here.
    int pos, shoe, nxt;
    int dp[n + 1];
    memset(dp, -1, sizeof(dp));
    dp[0] = 0;
    for (pos = 0; pos < n; pos++) {
      if (dp[pos] == -1)
        continue; //很容易遗漏，遗漏估计也会出问题！
      for (shoe = dp[pos]; shoe < b; shoe++) {
        if (s[shoe] < f[pos])
          continue;
        for (nxt = min(n - 1, pos + d[shoe]); nxt > pos; nxt--)
          if (s[shoe] >= f[nxt])
            dp[nxt] = dp[nxt] == -1 ? shoe : min(dp[nxt], shoe);
      }
    }
    return dp[n - 1];
  }
};

int main() {
  string num;
  Solution sol;
  int ans = sol.getMinimumNumOfBoots(10, 4, {0, 2, 8, 3, 6, 7, 5, 1, 4, 0},
                                     {2, 4, 3, 7}, {3, 2, 4, 1});
  cout << ans << endl;
  return 0;
}
