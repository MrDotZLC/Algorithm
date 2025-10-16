/* 
    天池×LC Q3. 整理书架
    中等
    5 分
    书架上有若干本书，从左至右的书籍编号记于整型数组 order 中。为保证书籍多样性，管理员想取走一些重复编号的书籍，要求满足以下条件：

    剩余书本中相同编号的书本数量均不大于 limit
    取走的书籍数量尽可能少
    由于存在多种整理方案，请返回剩余书本编号的排列为「最小排列」的方案。

    注意：

    「最小排列」：若干数组中第一位数字最小的数组；若第一位数字相同，则为第二位数字最小的数组，以此类推。
    示例 1：

    输入：order = [5,5,6,5], limit = 2
    输出：[5,5,6]
    解释：order 中出现了 3 次 5 号书：
    方案 1：去掉 order[0] 或 order[1]，所得排列为 [5,6,5]；
    方案 2：去掉 order[3]，所得排列为 [5,5,6]；
    经比较，最终返回排列最小的方案 2：[5,5,6]。
    示例 2：

    输入：order = [5,5,6,5], limit = 3
    输出：[5,5,6,5]
    解释：order 中所有相同编号的书本数目均未超过 limit，不需要去除，返回 [5,5,6,5]
    示例 3：

    输入：order = [3,3,9,8,9,2,8], limit = 1
    输出：[3,8,9,2]
    解释：列表中 3、8、9 号数字都出现了 2 次，去掉编号相同的书后的排列结果中 [3,8,9,2] 为排列最小的结果。
    示例 4：

    输入：order = [2,1,2,2,1,3,3,1,3,3], limit = 2
    输出：[1,2,2,1,3,3]
    提示：

    1 <= order.length <= 10^5
    1 <= limit <= 10
    1 <= order[i] <= 10^6
*/
#include <vector>
#include <unordered_map>
using namespace std;
class Solution {
public:
    vector<int> arrangeBookshelf(vector<int>& order, int limit) {
        unordered_map<int, int> left, used;
        for (int x : order) {
            left[x]++;
        }

        vector<int> ans;
        for (int x : order) {
            left[x]--;
            if (used[x] == limit) {
                continue;
            }
            while (ans.size() && ans.back() > x &&
                   left[ans.back()] >= limit - used[ans.back()] + 1 &&
                   used[x] < limit) {
                used[ans.back()]--;
                ans.pop_back();
            }
            used[x]++;
            ans.push_back(x);
        }

        return ans;
    }
};