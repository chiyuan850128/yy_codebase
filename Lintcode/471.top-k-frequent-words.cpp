/*************************************************
Copyright: jokerkeny
Author: jokerkeny
Date: 2019-10-06
Description: 
**************************************************/
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
class Solution {
public:
  /**
   * @param words: an array of string
   * @param k: An integer
   * @return: an array of string
   */
  
  static bool myfunc(pair<int,string> p1,pair<int,string> p2){
    return p1.first > p2.first ? true : (p1.first == p2.first?(p1.second < p2.second):false);
  }
  vector<string> topKFrequentWords(vector<string> &words, int k) {
    // write your code here
    unordered_map<string, int> count;
    for (auto &w : words)
      count[w]++;
    vector<pair<int, string>> count_word;
    for (auto p : count)
      count_word.push_back({-p.second, p.first});
    partial_sort(count_word.begin(), count_word.begin() + k,
                 count_word.end(), std::less<pair<int,string>>());
    vector<string> ans;
    for (int i = 0; i < k; i++)
      ans.push_back(count_word[i].second);
    return ans;
  }
};
int main() {
  string num;
  vector<string> words = {"yes",  "lint", "code", "yes",    "code",
                          "baby", "you",  "baby", "chrome", "safari",
                          "lint", "code", "body", "lint",   "code"};
  vector<string> ans = Solution().topKFrequentWords(words, 4);
  for (auto w : ans)
    cout << w << endl;
  return 0;
}
