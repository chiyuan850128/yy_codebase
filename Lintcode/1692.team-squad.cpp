/*************************************************
Copyright: jokerkeny
Author: jokerkeny
Date:
Description:
**************************************************/
#include <iostream>
#include <vector>

#include <algorithm>
using namespace std;

class Solution {
public:
    /**
     * @param atk1: the power of heros
     * @param atk2: the power of monsters
     * @return: how many monsters can you kill at most?
     */
    int getAns(vector<int> &atk1, vector<int> &atk2) {
        // Write your code here
        sort(atk1.begin(), atk1.end());
        sort(atk2.begin(), atk2.end());
        int ans = 0;
        auto it1 = atk1.begin(), it2 = atk2.begin();
        for (; it1 != atk1.end() && it2 != atk2.end(); it1++) {
          if(*it1 > *it2) {
            it2++;
          }
        }
        return it2 - atk2.begin();
    }
};

int main() {
  vector<int> atk1 = {43,25,33,17,21,4,37,49,7,17};
  vector<int> atk2 = {41,41,17,11,20,31,17,17,11,29};
  int  ans = Solution().getAns(atk1, atk2);
  cout << ans << endl;
  return 0;
}
