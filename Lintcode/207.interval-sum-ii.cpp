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
private:
  inline int lowbit(int x) { return x & -x; }
  int n;
  long long *tree;
  int *v;
  inline long long sum(int i) {
    long long sum = 0;
    while(i>0) {
      sum += tree[i];
      i -= lowbit(i);
    }
    return sum;
  }
public:
  /* you may need to use some attributes here */

  /*
   * @param A: An integer array
   */
  Solution(vector<int> A) {
    n = A.size();
    tree = new long long[n + 1]();
    v = new int[n + 1]();
    for (int i = 0; i < n; i++) {
      modify(i, A[i]);
      v[i+1] = A[i];
    }
    // do intialization if necessary
  }
  ~Solution() {
    delete[] tree;
    delete[] v;
  }

  /*
   * @param start: An integer
   * @param end: An integer
   * @return: The sum from start to end
   */
  long long query(int start, int end) {
    // write your code here
    return sum(end + 1) - sum(start);
  }

  /*
   * @param index: An integer
   * @param value: An integer
   * @return: nothing
   */
  void modify(int index, int value) {
    // write your code here
    index++;
    int add = value - v[index];
    v[index] = value;
    while(index <= n) {
      tree[index] += add;
      index += lowbit(index);
    }
  }
};

int main() {
  // Solution sol;
  // int ans = sol.getMinimumNumOfBoots(10, 4, {0, 2, 8, 3, 6, 7, 5, 1, 4, 0},
  //                                    {2, 4, 3, 7}, {3, 2, 4, 1});
  // cout << ans << endl;
  return 0;
}
