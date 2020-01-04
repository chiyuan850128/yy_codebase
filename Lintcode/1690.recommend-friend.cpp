/*************************************************
Copyright: jokerkeny
Author: jokerkeny
Date:
Description:
**************************************************/
#include <iostream>
#include <limits.h>
#include <vector>

#include <set>
using namespace std;

class Solution {
public:
  /**
   * @param val: the personality value of user
   * @return: Return their recommend friends' value
   */
  vector<int> getAns(vector<int> &val) {
    // Write your code here
    vector<int> ans;
    set<int> S;
    S.insert(val[0]);
    for (int i = 1; i < val.size(); i++) {
      int &v = val[i];
      if (S.find(v)!=S.end()) {
        ans.push_back(v);
        continue;
      }
      auto p = S.insert(v);
      auto it = p.first;
      int diff = INT_MAX, fr;
      if (it != S.begin()) {
        fr = *(prev(it));
        diff = v - fr;
      }
      if ((++it) != S.end()) {
        if (diff > (*it - v)) {
          fr = *it;
        }
      }
      ans.push_back(fr);
    }
    return ans;
  }
};

int main() {
  vector<int> val = {557091, 752985, 188469, 777011,
                     15595,  432051, 796577, 547595};
  vector<int> ans = Solution().getAns(val);
  for (auto a : ans)
    cout << a << endl;
  return 0;
}
