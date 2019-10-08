/*************************************************
Copyright: jokerkeny
Author: jokerkeny
Date: 2019-10-07
Description:
**************************************************/
#include <algorithm>
#include <iostream>
#include <vector>

#include <queue>
using namespace std;
class Solution {
public:
  /**
   * @param image: a binary matrix with '0' and '1'
   * @param x: the location of one of the black pixels
   * @param y: the location of one of the black pixels
   * @return: an integer
   */
  int minArea(vector<vector<char>> &image, int x, int y) {
    // write your code here
    int n = image.size();
    int m = image[0].size();
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};
    queue<pair<int, int>> Q;
    Q.push({x, y});
    int minx = x, maxx = x, miny = y, maxy = y;
    image[x][y] = 0;
    while(!Q.empty()) {
      pair<int, int> cur = Q.front();
      Q.pop();
      for (int i = 0; i < 4;i++) {
        int nx = cur.first + dx[i];
        int ny = cur.second + dy[i];
        if(nx >= 0 && ny >= 0 && nx < n && ny< m && image[nx][ny] == '1') {
          Q.push({nx, ny});
          image[nx][ny] = 0;
          minx = min(minx, nx);
          miny = min(miny, ny);
          maxx = max(maxx, nx);
          maxy = max(maxy, ny);
        }
      }
    }
    return (maxx - minx + 1) * (maxy - miny + 1);
  }
};
vector<char> str_vecchar(string &str) {
  return vector<char>(str.begin(), str.end());
}
int main() {
  Solution sol;
  vector<string> image_str = {"0010", "0110", "0100"};
  vector<vector<char>> image;
  image.resize(image_str.size());
  transform(image_str.begin(), image_str.end(), image.begin(), str_vecchar);
  int ans = sol.minArea(image, 0, 2);
  cout << ans << endl;
  return 0;
}
