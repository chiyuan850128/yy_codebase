#include <cstdio>

int l, n, m;
int d[50002];
bool check(int allow) {
  int mov = 0, dist = 0;
  for (int i = 1; i <= n; i++) {
    dist += d[i] - d[i - 1];
    if (dist < allow)
      mov++;
    else
      dist = 0;
  }
  if (dist + l - d[n] < allow)
    mov++;
  return mov <= m;
}
int main() {
  scanf("%d%d%d", &l, &n, &m);
  for (int i = 1; i <= n; i++)
    scanf("%d", &d[i]);
  int lt = 1, rt = l, ans;
  for (int mid = (lt + rt) / 2; lt <= rt; mid = (lt + rt) / 2) {
    if (check(mid)) {
      lt = mid + 1;
      ans = mid;
    } else
      rt = mid - 1;
  }
  printf("%d\n", ans);
  return 0;
}