/*
 * @lc app=leetcode id=1456 lang=cpp
 *
 * [1456] Maximum Number of Vowels in a Substring of Given Length
 */
#include <string>
#include <iostream>
using namespace std;

// @lc code=start
class Solution {
public:
    int maxVowels(string s, int k) {
        int l = 0;
        int tmp = 0;
        int res = 0;
        if (s.empty() || k > s.length() || l + k > s.length()) {
            return 0;
        }
        while(l < s.length()) {
            if (isVowels(s.at(l))) { // calculate the entered letters.
                tmp += 1;
            }
            if (l >= k && isVowels(s.at(l - k))) { // calculate the removed letters.
                tmp -= 1;
            }
            l++;
            res = max(res, tmp);
            if (res == s.length()) {
                break;
            }
        }
        return res;
    }

    bool isVowels(const char& c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c== 'u';
    }
};
// @lc code=end

int main() {
    Solution sol;
    string s = "abciiidef";
    int k = 3;
    auto res = sol.maxVowels(s, k);

    cout << "max vowel is " << res << endl;

    return 0;
}