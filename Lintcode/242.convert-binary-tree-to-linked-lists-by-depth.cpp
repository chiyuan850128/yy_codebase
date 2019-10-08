/*************************************************
Copyright: jokerkeny
Author: jokerkeny
Date:
Description:
**************************************************/
#include <queue>
#include <vector>

using namespace std;

class TreeNode {
public:
  int val;
  TreeNode *left, *right;
  TreeNode(int val) {
    this->val = val;
    this->left = this->right = nullptr;
  }
};
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
  /**
   * @param root the root of binary tree
   * @return a lists of linked list
   */
  vector<ListNode *> binaryTreeToLists(TreeNode *root) {
    // Write your code here
    vector<ListNode *> ans;
    if (!root)
      return ans;
    queue<TreeNode *> Q[2];
    int qi = 0;
    Q[0].push(root);
    while (!Q[qi].empty()) {
      ListNode dummy(0);
      ListNode *head = &dummy;
      while (!Q[qi].empty()) {
        TreeNode *cur = Q[qi].front();
        Q[qi].pop();
        if (cur->left)
          Q[qi ^ 1].push(cur->left);
        if (cur->right)
          Q[qi ^ 1].push(cur->right);
        head->next = new ListNode(cur->val);
        head = head->next;
      }
      ans.push_back(dummy.next);
      qi ^= 1;
    }
    return ans;
  }
};