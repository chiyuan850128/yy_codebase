/*************************************************
Copyright: jokerkeny
Author: jokerkeny
Date: 
Description: 
**************************************************/
#include <vector>
using namespace std;
class Solution {
private:
vector<vector<int>> ans;
vector<int> curv;
public:
    /*
     * @param A: an integer array
     * @param k: a postive integer <= length(A)
     * @param target: an integer
     * @return: A list of lists of integer
     */
    void helper(vector<int> &A, int i, int k, int target) {
        if (target < k) return; //剪枝,sort 后k*A[i]
        //target > k * A.back();
        if (!k && !target) {
            ans.push_back(curv);
            return;
        }
        for(; i< A.size(); i++) {
            curv.push_back(A[i]);
            helper(A, i + 1, k - 1, target - A[i]);
            curv.pop_back();
        }
    }
    vector<vector<int>> kSumII(vector<int> &A, int k, int target) {
        // write your code here
        helper(A, 0, k, target);
        return ans;
    }
};