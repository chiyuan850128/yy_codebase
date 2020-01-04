/*************************************************
Copyright: jokerkeny
Author: jokerkeny
Date:
Description:
**************************************************/
#include <cstring>
#include <iostream>
#include <limits.h>
#include <vector>

#include <cmath>
using namespace std;

#define NMAX 11
#define BLOCKMAX 4
int st[BLOCKMAX], ed[BLOCKMAX];
int belong[NMAX];
int min_count[BLOCKMAX];
int delta[BLOCKMAX];
class Solution {

  

public:
  /**
   * @param r: the number of classrooms available for rent
   * @param d: the number of classrooms you need to borrow
   * @param s: the start day you borrow the classroom
   * @param t: the end day you borrow the classroom
   * @return: which applicant to modify the order
   */
  int getApplicant(vector<int> &r, vector<int> &d, vector<int> &s,
                   vector<int> &t) {
    // Write your code here.
    int n = r.size();
    int m = d.size();
    int n_block = sqrt(n);
    for (int i = 0; i <= n; i++) // <=很重要，我的t[i]是+了1的，半开半闭区间，需要用到belong[开区间端点]
      belong[i] = i / n_block;
    for (int i = 0; i < n_block; i++) {
      st[i] = i * n_block;
      ed[i] = st[i] + n_block;
    }
    st[n_block] = n_block * n_block;
    ed[n_block] = n;

    for (int i = 0; i < n_block; i++) {
      min_count[i] = INT_MAX;
      for (int j = 0; j < n_block; j++)
        min_count[i] = min(min_count[i], r[st[i] + j]);
    }
    memset(delta, 0, sizeof(delta));
    for (int i = 0; i < m; i++) {
      // t[i]++;
      s[i]--;//有些错位，妈的！
      int left = belong[s[i]], right = belong[t[i]];
      int curblock;
      if (left == right) {
        curblock = left;
        for (int j = s[i]; j < t[i]; j++) {
          r[j] -= d[i];
          min_count[curblock] = min(min_count[curblock], r[j]);
        }
        if (min_count[curblock] + delta[curblock] < 0)
          return i + 1;
      }
      if (left == right - 1) {
        curblock = left;
        for (int j = s[i]; j < ed[curblock]; j++) {
          r[j] -= d[i];
          min_count[curblock] = min(min_count[curblock], r[j]);
        }
        if (min_count[curblock] + delta[curblock] < 0)
          return i + 1;
        curblock = right;
        for (int j = st[curblock]; j < t[i]; j++) {
          r[j] -= d[i];
          min_count[curblock] = min(min_count[curblock], r[j]);
        }
        if (min_count[curblock] + delta[curblock] < 0)
          return i + 1;
      }
      if (left < right - 1) {
        curblock = left;
        for (int j = s[i]; j < ed[curblock]; j++) {
          r[j] -= d[i];
          min_count[curblock] = min(min_count[curblock], r[j]);
        }
        if (min_count[curblock] + delta[curblock] < 0)
          return i + 1;

        for (curblock = left + 1; curblock < right; curblock++) {
          delta[curblock] -= d[i];
          if (min_count[curblock] + delta[curblock] < 0)
            return i + 1;
        }

        curblock = right;
        for (int j = st[curblock]; j < t[i]; j++) {
          r[j] -= d[i];
          min_count[curblock] = min(min_count[curblock], r[j]);
        }
        if (min_count[curblock] + delta[curblock] < 0)
          return i + 1;
      }
    }

    return 0;
  }
};

int main() {
  vector<int> r = {42323424,  633675939, 990396626, 965164370, 965164370,
                   965164370, 972489810, 619351082, 619351082, 0};
  vector<int> d{586780256, 316471206, 42323424, 8081621, 36667522,
                110729,    4572259,   7436169,  3834281, 8646496};
  vector<int> s{2, 3, 1, 3, 3, 3, 2, 7, 3, 4};
  vector<int> t{9, 7, 3, 9, 7, 6, 9, 9, 9, 9};
  int ans = Solution().getApplicant(r, d, s, t);
  cout << ans << endl;
  return 0;
}
