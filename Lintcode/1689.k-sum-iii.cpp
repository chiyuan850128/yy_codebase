/*************************************************
Copyright: jokerkeny
Author: jokerkeny
Date: 2019-10-06
Description: 
**************************************************/
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
public:
  /**
   * @param a: the array a
   * @param k: the integer k
   * @param target: the integer target
   * @return: return the number of legal schemes
   */
  int getAns(vector<int> &a, int k, int target) {
    // write your code here
    if (target & 1) {
      for (auto it = a.begin(); it < a.end(); it++) {
        if (!(*it & 1))
          a.erase(it);
      }
    } else if (k & 1) {
      for (auto it = a.begin(); it < a.end(); it++) {
        if ((*it & 1))
          a.erase(it);
      }
    }

    vector<map<int, int>> odd /* (k+1,map<int,int>({})) */,
        even /* (k+1,map<int,int>({})) */;
    odd.push_back({});
    even.push_back({});
    odd[0].insert({0, 1});
    even[0].insert({0, 1});
    for (int i = 0; i < a.size(); i++) {
      int num = a[i];
      if (num & 1) {
        odd.push_back({});
        for (int j = min((int)odd.size() - 2, k - 1); j >= 0; j--) {
          auto &next_map = odd[j + 1];
          for (auto pair : odd[j]) {
            int sum = num + pair.first;
            if (sum > target)
              break;
            if (next_map.find(sum) == next_map.end())
              next_map.insert({sum, pair.second});
            else
              next_map[sum] += pair.second;
          }
        }
      } else {
        even.push_back({});
        for (int j = min((int)even.size() - 2, k - 1); j >= 0; j--) {
          auto &next_map = even[j + 1];
          for (auto pair : even[j]) {
            int sum = num + pair.first;
            if (sum > target)
              break;
            if (next_map.find(sum) == next_map.end())
              next_map.insert({sum, pair.second});
            else
              next_map[sum] += pair.second;
          }
        }
      }
    }
    // return 0;
    return (odd.size() > k && odd[k].find(target) != odd[k].end()
                ? odd[k][target]
                : 0) +
           (even.size() > k && even[k].find(target) != even[k].end()
                ? even[k][target]
                : 0);
  }
};

int main() {
  int k = 4, target = 8;
  vector<int> a = {8, 1, 5, 5, 4, 7, 2, 1, 5, 8, 1, 4, 1, 3, 7, 3, 5, 3, 6, 8};
  int ans = Solution().getAns(a, k, target);
  cout << ans << endl;
  return 0;
}
