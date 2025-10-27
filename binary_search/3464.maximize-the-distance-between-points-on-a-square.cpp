/*
 * @lc app=leetcode id=3464 lang=cpp
 *
 * [3464] Maximize the Distance Between Points on a Square
 *
 * https://leetcode.com/problems/maximize-the-distance-between-points-on-a-square/description/
 *
 * algorithms
 * Hard (19.45%)
 * Likes:    35
 * Dislikes: 7
 * Total Accepted:    3K
 * Total Submissions: 15.4K
 * Testcase Example:  '2\n[[0,2],[2,0],[2,2],[0,0]]\n4'
 *
 * You are given an integer side, representing the edge length of a square with
 * corners at (0, 0), (0, side), (side, 0), and (side, side) on a Cartesian
 * plane.
 * 
 * You are also given a positive integer k and a 2D integer array points, where
 * points[i] = [xi, yi] represents the coordinate of a point lying on the
 * boundary of the square.
 * 
 * You need to select k elements among points such that the minimum Manhattan
 * distance between any two points is maximized.
 * 
 * Return the maximum possible minimum Manhattan distance between the selected
 * k points.
 * 
 * The Manhattan Distance between two cells (xi, yi) and (xj, yj) is |xi - xj|
 * + |yi - yj|.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: side = 2, points = [[0,2],[2,0],[2,2],[0,0]], k = 4
 * 
 * Output: 2
 * 
 * Explanation:
 * 
 * 
 * 
 * Select all four points.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: side = 2, points = [[0,0],[1,2],[2,0],[2,2],[2,1]], k = 4
 * 
 * Output: 1
 * 
 * Explanation:
 * 
 * 
 * 
 * Select the points (0, 0), (2, 0), (2, 2), and (2, 1).
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: side = 2, points = [[0,0],[0,1],[0,2],[1,2],[2,0],[2,2],[2,1]], k =
 * 5
 * 
 * Output: 1
 * 
 * Explanation:
 * 
 * 
 * 
 * Select the points (0, 0), (0, 1), (0, 2), (1, 2), and (2, 2).
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= side <= 10^9
 * 4 <= points.length <= min(4 * side, 15 * 10^3)
 * points[i] == [xi, yi]
 * The input is generated such that:
 * 
 * points[i] lies on the boundary of the square.
 * All points[i] are unique.
 * 
 * 
 * 4 <= k <= min(25, points.length)
 * 
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int maxDistance(int side, vector<vector<int>>& points, int k) {
        vector<long long> a;
        for (auto& p : points) {
            int x = p[0], y = p[1];
            if (x == 0) {
                a.push_back(y);
            } else if (y == side) {
                a.push_back(side + x);
            } else if (x == side) {
                a.push_back(side * 3LL - y);
            } else {
                a.push_back(side * 4LL - x);
            }
        }

        ranges::sort(a);

        // auto check = [&](int target) -> bool {
        //     for (long long s : a) {
        //         long long cur = s;
        //         for (int i = 0; i < k - 1; i++) {
        //             auto it = ranges::lower_bound(a, cur + target);
        //             if (it == a.end() || *it > s + 4LL * side - target) {
        //                 cur = -1;
        //                 break;
        //             }
        //             cur = *it;
        //         } 
        //         if (cur >= 0) {
        //             return true;
        //         }
        //     }
        //     return false;
        // };

        int L = 0;
        int R = side * 4LL / k + 1; // Evenly split the perimeter
        while (L + 1 < R) {
            int mid = L + (R - L) / 2;
            (check(a, side, k, mid) ? L : R) = mid; 
        }
        return L;
    }

    // binary answer + binary search
    bool check1(vector<long long> a, int side, int k, int target) {
        for (long long s : a) {
            long long cur = s;
            for (int i = 0; i < k - 1; i++) {
                auto it = ranges::lower_bound(a, cur + target);
                if (it == a.end() || *it > s + 4LL * side - target) {
                    cur = -1;
                    break;
                }
                cur = *it;
            } 
            if (cur >= 0) {
                return true;
            }
        }
        return false;
    }

    // binary answer + k-pointers
    bool check(vector<long long> a, int side, int k, int target) {
        vector<int> idx(k);
        while (true) {
            for (int i = 1; i < k; i++) {
                while (a[idx[i]] < a[idx[i - 1]] + target) {
                    idx[i]++;
                    if (idx[i] == a.size()) {
                        return false;
                    }
                }
            } 
            if (a[idx[k - 1]] <= a[idx[0]] + 4LL * side - target) {
                return true;
            }
            idx[0]++;
        }
    }
};
// @lc code=end

