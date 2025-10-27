/*
 * @lc app=leetcode id=3306 lang=cpp
 *
 * [3306] Count of Substrings Containing Every Vowel and K Consonants II
 *
 * https://leetcode.com/problems/count-of-substrings-containing-every-vowel-and-k-consonants-ii/description/
 *
 * algorithms
 * Medium (40.70%)
 * Likes:    962
 * Dislikes: 146
 * Total Accepted:    110.9K
 * Total Submissions: 272.4K
 * Testcase Example:  '"aeioqq"\n1'
 *
 * You are given a string word and a non-negative integer k.
 * 
 * Return the total number of substrings of word that contain every vowel ('a',
 * 'e', 'i', 'o', and 'u') at least once and exactly k consonants.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: word = "aeioqq", k = 1
 * 
 * Output: 0
 * 
 * Explanation:
 * 
 * There is no substring with every vowel.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: word = "aeiou", k = 0
 * 
 * Output: 1
 * 
 * Explanation:
 * 
 * The only substring with every vowel and zero consonants is word[0..4], which
 * is "aeiou".
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: word = "ieaouqqieaouqq", k = 1
 * 
 * Output: 3
 * 
 * Explanation:
 * 
 * The substrings with every vowel and one consonant are:
 * 
 * 
 * word[0..5], which is "ieaouq".
 * word[6..11], which is "qieaou".
 * word[7..12], which is "ieaouq".
 * 
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 5 <= word.length <= 2 * 10^5
 * word consists only of lowercase English letters.
 * 0 <= k <= word.length - 5
 * 
 * 
 */
#include <vector>
#include <iostream>
#include <string>
using namespace std;
// @lc code=start
class Solution {
public:
    long long countOfSubstrings2(string word, int k) {
        long long ans = 0LL;
        int l1 = 0, l2 = 0, count1 = 0, count2 = 0, empty1 = 5, empty2 = 5;
        int freq1[28] = {}, freq2[28] = {};
        auto is_vowel = [] (char c) -> bool {
            return (c == 'a' || c == 'e' || 
                c == 'i' || c == 'o' || c == 'u');
        };
        for (int r = 0; r < word.length(); r++) {
            if (is_vowel(word[r])) {
                if (++freq1[word[r] - 97] == 1) empty1--;
                if (++freq2[word[r] - 97] == 1) empty2--;
            } else {
                count1++;
                count2++;
            }
            
            while (l1 <= r && empty1 == 0 && count1 >= k) {
                if (is_vowel(word[l1])) {
                    if (--freq1[word[l1] - 97] == 0) empty1++;
                } else {
                    count1--;
                }
                l1++;
            }

            while (l2 <= r && empty2 == 0 && count2 >= k + 1) {
                if (is_vowel(word[l2])) {
                    if (--freq2[word[l2] - 97] == 0) empty2++;
                } else {
                    count2--;
                }
                l2++;
            }

            ans += (l1 - l2);
        }
        return ans;
    }

    long long countOfSubstrings(string word, int k) {
        return f(word, k) - f(word, k + 1);
    }

    long long f(string word, int k) {
        long long ans = 0LL;
        int freq[26] = {};
        int l = 0, empty = 5, count = 0;
        auto is_vowel = [] (char c) -> bool {
            return (c == 'a' || c == 'e' || 
                c == 'i' || c == 'o' || c == 'u');
        };
        for (int r = 0; r < word.size(); r++) {
            char cur = word[r];
            if (is_vowel(cur)) {
                if (++freq[cur - 97] == 1) {
                    empty--;
                }
            } else {
                count++;
            }

            while (l <= r && empty == 0 && count >= k) {
                char out = word[l];
                if (is_vowel(out)) {
                    if (--freq[out - 97] == 0) {
                        empty++;
                    }
                } else {
                    count--;
                }
                l++;
            }

            ans += l;
        }
        return ans;
    }
};
// @lc code=end

