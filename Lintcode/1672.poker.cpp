/*************************************************
Copyright: jokerkeny
Author: jokerkeny
Date: 
Description: 
**************************************************/
#include <cstring>
#include <vector>
#include <iostream>

using namespace std;
class Solution {
public:
  /**
   * @param cards:
   * @return: the minimal times to discard all cards
   */
  int getAns(vector<int> &cards) {
    res = cards.size();
    memset(count, 0, sizeof(count));
    for (auto card : cards)
      count[card]++;
    dfs(0);
    return res;
  }

private:
  int res;
  int count[10];
  void dfs(int sum) {
    int continious = 0;
    for (int i = 1; i <= 9; i++) {
      if (count[i])
        continious++;
      else
        continious = 0;
      if (continious >= 5) {
        for (int j = i - continious + 1; j <= i - 5 + 1; j++) {
          for (int k = j; k <= i; k++)
            count[k]--;
          dfs(sum + 1);
          for (int k = j; k <= i; k++)
            count[k]++;
        }
      }
    }
    for (auto cnt : count)
      if (cnt)
        sum++;
    res = min(res, sum);
  }
};

int main() {
  vector<int> cards{1, 1, 1, 2, 3, 4, 5};
  int ans = Solution().getAns(cards);
  cout << ans << endl;
  return 0;
}
