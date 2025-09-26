/* 
    面试题 16.24. 数对和

    提示
    设计一个算法，找出数组中两数之和为指定值的所有整数对。一个数只能属于一个数对。

    示例 1：

    输入：nums = [5,6,5], target = 11
    输出：[[5,6]]
    示例 2：

    输入：nums = [5,6,5,6], target = 11
    输出：[[5,6],[5,6]]
    提示：

    nums.length <= 100000
    -105 <= nums[i], target <= 105
*/
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
class Solution {
public:
    vector<vector<int>> pairSums1(vector<int>& nums, int target) {
        vector<vector<int>> ans;
        unordered_map<int, int> cnt;
        for (int j = 0; j < nums.size(); j++) {
            int x = nums[j];
            auto it = cnt.find(target - x);
            if (it != cnt.end() && it->second) {
                ans.emplace_back(x, target - x);
                it->second--;
            } else {
                cnt[x]++;
            }
        }
        return ans;
    }

    vector<vector<int>> pairSums(vector<int>& nums, int target) {
        ranges::sort(nums);
        vector<vector<int>> ans;
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            if (nums[l] + nums[r] < target) {
                l++;
            } else if (nums[l] + nums[r] > target) {
                r--;
            } else {
                ans.push_back({nums[l], nums[r]});
                l++;
                r--;
            }
        }
        return ans;
    }
};