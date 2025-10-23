/*
 * @lc app=leetcode id=480 lang=cpp
 *
 * [480] Sliding Window Median
 *
 * https://leetcode.com/problems/sliding-window-median/description/
 *
 * algorithms
 * Hard (38.67%)
 * Likes:    3482
 * Dislikes: 230
 * Total Accepted:    203K
 * Total Submissions: 523.4K
 * Testcase Example:  '[1,3,-1,-3,5,3,6,7]\n3'
 *
 * The median is the middle value in an ordered integer list. If the size of
 * the list is even, there is no middle value. So the median is the mean of the
 * two middle values.
 * 
 * 
 * For examples, if arr = [2,3,4], the median is 3.
 * For examples, if arr = [1,2,3,4], the median is (2 + 3) / 2 = 2.5.
 * 
 * 
 * You are given an integer array nums and an integer k. There is a sliding
 * window of size k which is moving from the very left of the array to the very
 * right. You can only see the k numbers in the window. Each time the sliding
 * window moves right by one position.
 * 
 * Return the median array for each window in the original array. Answers
 * within 10^-5 of the actual value will be accepted.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
 * Output: [1.00000,-1.00000,-1.00000,3.00000,5.00000,6.00000]
 * Explanation: 
 * Window position                Median
 * ---------------                -----
 * [1  3  -1] -3  5  3  6  7        1
 * ⁠1 [3  -1  -3] 5  3  6  7       -1
 * ⁠1  3 [-1  -3  5] 3  6  7       -1
 * ⁠1  3  -1 [-3  5  3] 6  7        3
 * ⁠1  3  -1  -3 [5  3  6] 7        5
 * ⁠1  3  -1  -3  5 [3  6  7]       6
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,2,3,4,2,3,1,4,2], k = 3
 * Output: [2.00000,3.00000,3.00000,3.00000,2.00000,3.00000,2.00000]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= k <= nums.length <= 10^5
 * -2^31 <= nums[i] <= 2^31 - 1
 * 
 * 
 */
#include <queue>
#include <unordered_map>
using namespace std;
// @lc code=start
template<typename T, typename Compare = less<T>>
class LazyHeap {
private:
    priority_queue<T, vector<T>, Compare> pq;
    unordered_map<int, int> remove_cnt;
    size_t sz = 0;

    // 真正执行删除
    void apply_remove() {
        while (!pq.empty() && remove_cnt[pq.top()] > 0) {
            remove_cnt[pq.top()]--;
            pq.pop();
        }
    }
public:
    size_t size() {
        return sz;
    }

    // 删除
    void remove(T x) {
        remove_cnt[x]++;
        sz--;
    }

    // 查看堆顶
    T top() {
        apply_remove();
        return pq.top();
    }

    // 出堆
    T pop() {
        apply_remove();
        sz--;
        T x = pq.top();
        pq.pop();
        return x;
    }

    // 入堆
    void push(T x) {
        pq.push(x);
        sz++;
    }

    // 先push(x)再pop()
    T push_pop(T x) {
        if (sz > 0 && Compare()(x, top())) {
            pq.push(x);
            x = pq.top();
            pq.pop();
        }
        return x;
    }
};

class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<double> ans(n - k + 1);
        LazyHeap<int> left;
        LazyHeap<int, greater<int>> right;

        for (int i = 0; i < n; i++) {
            // 进入窗口
            int in = nums[i];
            if (left.size() == right.size()) {
                left.push(right.push_pop(in));
            } else if (left.size() > right.size()) {
                right.push(left.push_pop(in));
            }

            int l = i - k + 1;
            if (l < 0) {
                continue;
            }

            // 计算答案
            if (k % 2) {
                ans[l] = left.top();
            } else {
                ans[l] = ((long long) left.top() + right.top()) / 2.0;
            }

            // 离开窗口
            int out = nums[l];
            if (out <= left.top()) {
                left.remove(out);
                if (left.size() < right.size()) {
                    left.push(right.pop());
                }
            } else {
                right.remove(out);
                if (left.size() > right.size() + 1) {
                    right.push(left.pop());
                }
            }
        }
        return ans;
    }
};
// @lc code=end

