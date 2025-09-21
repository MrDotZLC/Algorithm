/*
 * @lc app=leetcode id=1286 lang=cpp
 *
 * [1286] Iterator for Combination
 *
 * https://leetcode.com/problems/iterator-for-combination/description/
 *
 * algorithms
 * Medium (72.52%)
 * Likes:    1381
 * Dislikes: 108
 * Total Accepted:    80K
 * Total Submissions: 110.2K
 * Testcase Example:  '["CombinationIterator","next","hasNext","next","hasNext","next","hasNext"]\n' +
  '[["abc",2],[],[],[],[],[],[]]'
 *
 * Design the CombinationIterator class:
 * 
 * 
 * CombinationIterator(string characters, int combinationLength) Initializes
 * the object with a string characters of sorted distinct lowercase English
 * letters and a number combinationLength as arguments.
 * next() Returns the next combination of length combinationLength in
 * lexicographical order.
 * hasNext() Returns true if and only if there exists a next combination.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input
 * ["CombinationIterator", "next", "hasNext", "next", "hasNext", "next",
 * "hasNext"]
 * [["abc", 2], [], [], [], [], [], []]
 * Output
 * [null, "ab", true, "ac", true, "bc", false]
 * 
 * Explanation
 * CombinationIterator itr = new CombinationIterator("abc", 2);
 * itr.next();    // return "ab"
 * itr.hasNext(); // return True
 * itr.next();    // return "ac"
 * itr.hasNext(); // return True
 * itr.next();    // return "bc"
 * itr.hasNext(); // return False
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= combinationLength <= characters.length <= 15
 * All the characters of characters are unique.
 * At most 10^4 calls will be made to next and hasNext.
 * It is guaranteed that all calls of the function next are valid.
 * 
 * 
 */
#include <string>
#include <vector>
using namespace std;
// @lc code=start
class CombinationIterator {
public:
    vector<string> _ans;
    int _idx = 0;
    CombinationIterator(string characters, int combinationLength) {
        int n = characters.size();
        string combi = "";
        auto dfs = [&](auto &dfs, int pos) -> void {
            if (combi.size() == combinationLength) {
                _ans.push_back(combi);
                return;
            }

            for (int i = pos; i < n; i++) {
                combi.push_back(characters[i]);
                dfs(dfs, i + 1);
                combi.pop_back();
            }
        };
        dfs(dfs, 0);
    }
    
    string next() {
        return hasNext() ? _ans[_idx++] : "";
    }
    
    bool hasNext() {
        return _idx < _ans.size();
    }
};

/**
 * Your CombinationIterator object will be instantiated and called as such:
 * CombinationIterator* obj = new CombinationIterator(characters, combinationLength);
 * string param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
// @lc code=end

