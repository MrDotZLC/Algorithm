/*
 * @lc app=leetcode id=735 lang=cpp
 *
 * [735] Asteroid Collision
 *
 * https://leetcode.com/problems/asteroid-collision/description/
 *
 * algorithms
 * Medium (45.71%)
 * Likes:    8989
 * Dislikes: 1280
 * Total Accepted:    890.5K
 * Total Submissions: 1.9M
 * Testcase Example:  '[5,10,-5]'
 *
 * We are given an array asteroids of integers representing asteroids in a row.
 * The indices of the asteriod in the array represent their relative position
 * in space.
 * 
 * For each asteroid, the absolute value represents its size, and the sign
 * represents its direction (positive meaning right, negative meaning left).
 * Each asteroid moves at the same speed.
 * 
 * Find out the state of the asteroids after all collisions. If two asteroids
 * meet, the smaller one will explode. If both are the same size, both will
 * explode. Two asteroids moving in the same direction will never meet.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: asteroids = [5,10,-5]
 * Output: [5,10]
 * Explanation: The 10 and -5 collide resulting in 10. The 5 and 10 never
 * collide.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: asteroids = [8,-8]
 * Output: []
 * Explanation: The 8 and -8 collide exploding each other.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: asteroids = [10,2,-5]
 * Output: [10]
 * Explanation: The 2 and -5 collide resulting in -5. The 10 and -5 collide
 * resulting in 10.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= asteroids.length <= 10^4
 * -1000 <= asteroids[i] <= 1000
 * asteroids[i] != 0
 * 
 * 
 */
#include <vector>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> st;
        for (int a : asteroids) {
            // if (st.empty() || ((st.back() > 0) ^ (a < 0))) {
            //     st.push_back(a);
            // } else {
            //     while (!st.empty() && st.back() > 0 && a < 0 &&
            //            st.back() < abs(a)) {
            //         st.pop_back();
            //     }
                
            //     if (!st.empty() && st.back() > 0 && a < 0) {
            //         if (st.back() == abs(a)) {
            //             st.pop_back();
            //         }
            //     } else {
            //         st.push_back(a);
            //     }
            // }

            bool is_alive = true;
            while (is_alive && a < 0 && !st.empty() && st.back() > 0) {
                is_alive = st.back() < -a;
                if (st.back() <= -a) {
                    st.pop_back();
                } 
            }
            if (is_alive) {
                st.push_back(a);
            }
        }
        return st;
    }
};
// @lc code=end

