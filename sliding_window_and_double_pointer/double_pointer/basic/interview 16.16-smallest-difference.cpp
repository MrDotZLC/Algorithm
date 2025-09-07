/**
 * 给定两个整数数组a和b，计算具有最小差绝对值的一对数值（每个数组中取一个值），并返回该对数值的差
 * 示例：
 * 输入：{1, 3, 15, 11, 2}, {23, 127, 235, 19, 8}
 * 输出：3，即数值对(11, 8)
 * 提示：
 * 1 <= a.length, b.length <= 100000
 * -2147483648 <= a[i], b[i] <= 2147483647
 * 正确结果在区间 [0, 2147483647] 内
 */

 #include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int smallestDifference(vector<int>& a, vector<int>& b) {
        long ans = 2147483647L;
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        int m = a.size(), n = b.size();
        int i = 0, j = 0;
        while (i < m && j < n) {
            if (a[i] != b[j]) {
                ans = min(ans, abs((long)a[i] - (long)b[j]));
                if (a[i] < b[j]) {
                    i++;
                } else {
                    j++;
                }
            } else {
                return 0;
            }
        }
        return ans;
    }
};