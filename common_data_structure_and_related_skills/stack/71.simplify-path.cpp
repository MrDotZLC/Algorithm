/*
 * @lc app=leetcode id=71 lang=cpp
 *
 * [71] Simplify Path
 *
 * https://leetcode.com/problems/simplify-path/description/
 *
 * algorithms
 * Medium (48.20%)
 * Likes:    6321
 * Dislikes: 1382
 * Total Accepted:    1.2M
 * Total Submissions: 2.4M
 * Testcase Example:  '"/home/"'
 *
 * You are given an absolute path for a Unix-style file system, which always
 * begins with a slash '/'. Your task is to transform this absolute path into
 * its simplified canonical path.
 * 
 * The rules of a Unix-style file system are as follows:
 * 
 * 
 * A single period '.' represents the current directory.
 * A double period '..' represents the previous/parent directory.
 * Multiple consecutive slashes such as '//' and '///' are treated as a single
 * slash '/'.
 * Any sequence of periods that does not match the rules above should be
 * treated as a valid directory or file name. For example, '...' and '....' are
 * valid directory or file names.
 * 
 * 
 * The simplified canonical path should follow these rules:
 * 
 * 
 * The path must start with a single slash '/'.
 * Directories within the path must be separated by exactly one slash '/'.
 * The path must not end with a slash '/', unless it is the root directory.
 * The path must not have any single or double periods ('.' and '..') used to
 * denote current or parent directories.
 * 
 * 
 * Return the simplified canonical path.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: path = "/home/"
 * 
 * Output: "/home"
 * 
 * Explanation:
 * 
 * The trailing slash should be removed.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: path = "/home//foo/"
 * 
 * Output: "/home/foo"
 * 
 * Explanation:
 * 
 * Multiple consecutive slashes are replaced by a single one.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: path = "/home/user/Documents/../Pictures"
 * 
 * Output: "/home/user/Pictures"
 * 
 * Explanation:
 * 
 * A double period ".." refers to the directory up a level (the parent
 * directory).
 * 
 * 
 * Example 4:
 * 
 * 
 * Input: path = "/../"
 * 
 * Output: "/"
 * 
 * Explanation:
 * 
 * Going one level up from the root directory is not possible.
 * 
 * 
 * Example 5:
 * 
 * 
 * Input: path = "/.../a/../b/c/../d/./"
 * 
 * Output: "/.../b/d"
 * 
 * Explanation:
 * 
 * "..." is a valid name for a directory in this problem.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= path.length <= 3000
 * path consists of English letters, digits, period '.', slash '/' or '_'.
 * path is a valid absolute Unix path.
 * 
 * 
 */
#include <vector>
#include <string>
#include <sstream>
#include <ranges>
#include <algorithm>
using namespace std;
// @lc code=start
#include <ranges>
class Solution {
public:
    string simplifyPath1(string path) {
        string cur;
        vector<string> st;
        for (int i = 0; i <= path.size(); i++) {
            if (i == path.size() || path[i] == '/') {
                if (cur == "..") {
                    if (!st.empty()) {
                        st.pop_back();
                    }
                } else if (!cur.empty() && cur != ".") {
                    st.push_back(cur);
                }
                cur.clear();
            } else {
                cur += path[i];
            }
        }

        string ans = "/";
        for (int i = 0; i < st.size(); i++) {
            ans += st[i];
            if (i + 1 < st.size()) {
                ans += "/";
            }
        }
        
        return ans;
    }

    string simplifyPath(string path) {
        vector<string> st;
        // stringstream ss(path);
        // string s;

        // while (getline(ss, s, '/')) {
        //     if (s.empty() || s == ".") {
        //         continue;
        //     } 
        //     if (s != "..") {
        //         st.push_back(s);
        //     } else if (!st.empty()) {
        //         st.pop_back();
        //     }
        // }

        for (auto &&part : path | ranges::views::split('/')) {
            string s(part.begin(), part.end());
            if (s.empty() || s == ".") {
                continue;
            } 
            if (s != "..") {
                st.push_back(s);
            } else if (!st.empty()) {
                st.pop_back();
            }
        }

        string ans;
        for (int i = 0; i < st.size(); i++) {
            ans += "/";
            ans += st[i];
        }
        
        return ans.empty() ? "/" : ans;
    }
};
// @lc code=end

