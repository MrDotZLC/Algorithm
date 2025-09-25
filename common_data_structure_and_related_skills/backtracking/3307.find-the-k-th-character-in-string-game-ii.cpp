/*
 * @lc app=leetcode id=3307 lang=cpp
 *
 * [3307] Find the K-th Character in String Game II
 *
 * https://leetcode.com/problems/find-the-k-th-character-in-string-game-ii/description/
 *
 * algorithms
 * Hard (48.70%)
 * Likes:    506
 * Dislikes: 31
 * Total Accepted:    85.8K
 * Total Submissions: 176.3K
 * Testcase Example:  '5\n[0,0,0]'
 *
 * Alice and Bob are playing a game. Initially, Alice has a string word = "a".
 * 
 * You are given a positive integer k. You are also given an integer array
 * operations, where operations[i] represents the type of the i^th operation.
 * 
 * Now Bob will ask Alice to perform all operations in sequence:
 * 
 * 
 * If operations[i] == 0, append a copy of word to itself.
 * If operations[i] == 1, generate a new string by changing each character in
 * word to its next character in the English alphabet, and append it to the
 * original word. For example, performing the operation on "c" generates "cd"
 * and performing the operation on "zb" generates "zbac".
 * 
 * 
 * Return the value of the k^th character in word after performing all the
 * operations.
 * 
 * Note that the character 'z' can be changed to 'a' in the second type of
 * operation.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: k = 5, operations = [0,0,0]
 * 
 * Output: "a"
 * 
 * Explanation:
 * 
 * Initially, word == "a". Alice performs the three operations as
 * follows:
 * 
 * 
 * Appends "a" to "a", word becomes "aa".
 * Appends "aa" to "aa", word becomes "aaaa".
 * Appends "aaaa" to "aaaa", word becomes "aaaaaaaa".
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: k = 10, operations = [0,1,0,1]
 * 
 * Output: "b"
 * 
 * Explanation:
 * 
 * Initially, word == "a". Alice performs the four operations as follows:
 * 
 * 
 * Appends "a" to "a", word becomes "aa".
 * Appends "bb" to "aa", word becomes "aabb".
 * Appends "aabb" to "aabb", word becomes "aabbaabb".
 * Appends "bbccbbcc" to "aabbaabb", word becomes "aabbaabbbbccbbcc".
 * 
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= k <= 10^14
 * 1 <= operations.length <= 100
 * operations[i] is either 0 or 1.
 * The input is generated such that word has at least k characters after all
 * operations.
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
    // 递归
    char kthCharacter1(long long k, vector<int>& operations) {
        if (operations.empty()) {
            return 'a';
        }

        int op = operations.back();
        operations.pop_back();
        int n = operations.size();
        if (n >= 63 || k <= (1LL << n)) { // n过大时，k一定在左边，限制n也可避免类型溢出风险
            return kthCharacter1(k, operations);
        }
        char ans = kthCharacter1(k - (1LL << n), operations);
        return 'a' + (ans - 'a' + op) % 26; // 考虑最后一个op的情况
    }

    // 迭代：实际计算k > (1 << n)的次数：k > 2^i => k-1 >= 2^i
    char kthCharacter2(long long k, vector<int>& operations) {
        // k-1 >= 2^i => i <= log2(k-1)
        int m = bit_width((__UINT64_TYPE__)k - 1);
        int inc = 0;
        for (int i = m - 1; i >= 0; i--) {
            if (k > (1LL << i)) { // k在右半段
                inc += operations[i];
                k -= (1LL << i);
            }
        }
        return 'a' + inc % 26; // 考虑最后一个op的情况
    }

    // 迭代：实际计算k > (1 << n)的次数：k > 2^i => k-1 >= 2^i
    char kthCharacter3(long long k, vector<int>& operations) {
        // k-1 >= 2^i => i <= log2(k-1)
        k = k - 1;
        int m = bit_width((__UINT64_TYPE__)k);
        int inc = 0;
        for (int i = m - 1; i >= 0; i--) {
            if (k >> i & 1) { // k在右半段
                inc += operations[i];
            }
        }
        return 'a' + inc % 26; // 考虑最后一个op的情况
    }

    // 迭代：实际计算k > (1 << n)的次数：k > 2^i => k-1 >= 2^i
    char kthCharacter(long long k, vector<int>& operations) {
        // k-1 >= 2^i => i <= log2(k-1)
        k = k - 1;
        int m = bit_width((__UINT64_TYPE__)k);
        int inc = 0;
        for (int i = m - 1; i >= 0; i--) {
            inc += k >> i & operations[i];
        }
        return 'a' + inc % 26; // 考虑最后一个op的情况
    }
};
// @lc code=end

