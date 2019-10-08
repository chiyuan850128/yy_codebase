/*************************************************
Copyright: jokerkeny
Author: jokerkeny
Date: 2019-09-26
Description: 
**************************************************/
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
class Solution {
public:
  /**
   * @param n: the n
   * @return: the smallest lucky number  that is not less than n
   */
  void add1(string &n, int i) {
    if (i == n.size()) {
      n = string(i / 2 + 1, '5') + string(i / 2 + 1, '3');
      cnt_3 = cnt_5 = i / 2 + 1;
      return;
    }
    if (n[i] >= '5') {
      if(n[i]=='5')
        cnt_5--;
      n[i] = '3';
      cnt_3++;
      add1(n, i + 1);
      return;
    }
    for (int j = i - 1; cnt_5 && j >= 0; j--) {
      if (n[j] == '5') {
        n[j] = '3';
        cnt_3++;
        cnt_5--;
      }
    }
    if (n[i] < '3') {
      n[i] = '3';
      cnt_3++;
    } else if (n[i] < '5') {
      if(n[i]=='3')
        cnt_3--;
      n[i] = '5';
      cnt_5++;
    }
  }
  string luckyNumber(string &n) {
    // Write your code here.
    // O(n2) algorithm
    // after condition cnt_5 at add1{ for ...}, become O(n)
    // add1很容易出错，注意我所有数都变3变5后，add1理应在初始序列上+1。得注意后续影响。
    if (n.size() & 1) {
      return string((n.size() / 2 + 1), '3') + string((n.size() / 2 + 1), '5');
    }
    reverse(n.begin(), n.end());
    for (int i = 0; i < n.size(); i++) {
      char &c = n[i];
      if (c != '3' && c != '5')
        add1(n, i);
    }
    cnt_3 = 0;
    cnt_5 = 0;
    for (auto c : n) {
      if (c == '3')
        cnt_3++;
      else if (c == '5')
        cnt_5++;
    }

    for (int i = 0; i < n.size() && cnt_3 != cnt_5; i++) {
      if (cnt_3 > cnt_5) {
        if (n[i] == '3') {
          n[i] = '5';
          cnt_3--;
          cnt_5++;
        }
      } else {
        if (n[i] == '5') {
          add1(n, i);
          if (cnt_3 > cnt_5)
            i = -1;
        }
      }
    }
    reverse(n.begin(), n.end());
    return n;
  }

private:
  int cnt_3, cnt_5;
};

int main() {
  string num;
  while (cin >> num) {
    string ans = Solution().luckyNumber(num);
    cout << ans << endl;
  }
  return 0;
}
