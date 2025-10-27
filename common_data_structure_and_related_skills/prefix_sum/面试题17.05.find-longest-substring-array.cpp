/* 
    面试题 17.05. 字母与数字
    同步题目状态

    中等
    相关标签
    premium lock icon
    相关企业
    提示
    给定一个放有字母和数字的数组，找到最长的子数组，且包含的字母和数字的个数相同。

    返回该子数组，若存在多个最长子数组，返回左端点下标值最小的子数组。若不存在这样的数组，返回一个空数组。

    示例 1：

    输入：["A","1","B","C","D","2","3","4","E","5","F","G","6","7","H","I","J","K","L","M"]

    输出：["A","1","B","C","D","2","3","4","E","5","F","G","6","7"]
    示例 2：

    输入：["A","A"]

    输出：[]
    提示：

    array.length <= 100000
*/
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;
class Solution {
public:
    vector<string> findLongestSubarray(vector<string>& array) {
        int sum = 0, mx = 0, start = INT_MAX;
        unordered_map<int, int> idx = {{0, -1}};
        for (int i = 0; i < array.size(); i++) {
            isdigit(array[i][0]) ? --sum : ++sum;
            if (idx.contains(sum)) {
                if (i - idx[sum] > mx) {
                    mx = i - idx[sum];
                    start = idx[sum] + 1;
                } else if (i - idx[sum] == mx) {
                    if (start == INT_MAX || start > idx[sum] + 1) {
                        start = idx[sum] + 1;
                    }
                }
            } else {
                idx[sum] = i;
            }
        }

        return start == INT_MAX
                   ? vector<string>{}
                   : vector<string>(array.begin() + start,
                                    array.begin() + start + mx);
    }
};