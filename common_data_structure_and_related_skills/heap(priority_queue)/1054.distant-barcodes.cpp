/*
 * @lc app=leetcode id=1054 lang=cpp
 *
 * [1054] Distant Barcodes
 *
 * https://leetcode.com/problems/distant-barcodes/description/
 *
 * algorithms
 * Medium (47.70%)
 * Likes:    1338
 * Dislikes: 52
 * Total Accepted:    53.6K
 * Total Submissions: 111.4K
 * Testcase Example:  '[1,1,1,2,2,2]'
 *
 * In a warehouse, there is a row of barcodes, where the i^th barcode is
 * barcodes[i].
 * 
 * Rearrange the barcodes so that no two adjacent barcodes are equal. You may
 * return any answer, and it is guaranteed an answer exists.
 * 
 * 
 * Example 1:
 * Input: barcodes = [1,1,1,2,2,2]
 * Output: [2,1,2,1,2,1]
 * Example 2:
 * Input: barcodes = [1,1,1,1,2,2,3,3]
 * Output: [1,3,1,3,1,2,1,2]
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= barcodes.length <= 10000
 * 1 <= barcodes[i] <= 10000
 * 
 * 
 */
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    // heap
    vector<int> rearrangeBarcodes1(vector<int>& barcodes) {
        int n = barcodes.size();
        unordered_map<int, int> cnt;
        for (int x : barcodes) {
            cnt[x]++;
        }
        priority_queue<pair<int, int>> pq;
        for (auto &[x, v] : cnt) {
            pq.emplace(v, x);
        }

        int i = 0;
        while (!pq.empty()) {
            auto t = pq.top();
            pq.pop();
            if (i > 0 && barcodes[i - 1] == t.second) {
                if (pq.empty()) {
                    break;
                }
                auto t1 = pq.top();
                pq.pop();
                barcodes[i++] = t1.second;
                if (--t1.first > 0) {
                    pq.push(t1);
                }
                pq.push(t);
            } else {
                barcodes[i++] = t.second;
                if (--t.first > 0) {
                    pq.push(t);
                }
            }
        }
        return barcodes;
    }

    // greedy
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {
        int n = barcodes.size(), mcnt = 0, mx = barcodes[0];
        unordered_map<int, int> cnt;
        for (int x : barcodes) {
            if (++cnt[x] > mcnt) {
                mcnt = cnt[x];
                mx = x;
            }
        }

        int i = 0;
        for (; mcnt--; i += 2) {
            barcodes[i] = mx;
        }
        cnt[mx] = 0;

        for (auto &[c, v] : cnt) {
            while (v--) {
                if (i >= n) {
                    i = 1;
                }
                barcodes[i] = c;
                i += 2;
            }
        }
        return barcodes;
    }
};
// @lc code=end

