/*************************************************
Copyright: jokerkeny
Author: jokerkeny
Date:
Description:
**************************************************/
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include <queue>
#include <unordered_set>
using namespace std;

class Solution {
public:
  /*
   * @param start: a string
   * @param end: a string
   * @param dict: a set of string
   * @return: a list of lists of string
   */
  vector<vector<string>> findLadders(string &start, string &end,
                                     unordered_set<string> &dict) {
    // write your code here
    dict.insert(end);
    vector<vector<string>> ans;
    queue<vector<string>> paths;
    paths.push({start});
    unordered_set<string> visited;
    int minlevel = INT_MAX;
    int level = 1;
    while (!paths.empty()) {
      vector<string> &path =
          paths.front(); // Wrong! Reference & = queue.front() and then
                         // queue.pop(). The reference become ilegal
      paths.pop();
      if (level < path.size()) {
        level = path.size();
        if (level > minlevel)
          break;
        for (auto &str : visited)
          dict.erase(str);
        visited.clear();
      }
      string &last = path.back();
      for (int i = 0; i < last.length(); i++) {
        string nxt = last;
        for (char c = 'a'; c <= 'z'; c++) {
          nxt[i] = c;
          if (dict.find(nxt) != dict.end()) {
            visited.insert(nxt);
            vector<string> newpath = path;
            newpath.push_back(nxt);
            if (nxt == end) {
              ans.push_back(newpath);
              minlevel = level;
            } else
              paths.push(newpath);
          }
        }
      }
    }
    return ans;
  }
};

int main() {
  string start = "a", end = "c";

  unordered_set<string> dict{"a", "b", "c"};
  vector<vector<string>> ans = Solution().findLadders(start, end, dict);
  for (auto &vs : ans) {
    for (auto &str : vs)
      cout << str << " ";
    cout << endl;
  }
  return 0;
}
