/*
 * @lc app=leetcode id=677 lang=cpp
 *
 * [677] Map Sum Pairs
 *
 * https://leetcode.com/problems/map-sum-pairs/description/
 *
 * algorithms
 * Medium (56.79%)
 * Likes:    1718
 * Dislikes: 164
 * Total Accepted:    135.5K
 * Total Submissions: 237.9K
 * Testcase Example:  '["MapSum","insert","sum","insert","sum"]\n' +
  '[[],["apple",3],["ap"],["app",2],["ap"]]'
 *
 * Design a map that allows you to do the following:
 * 
 * 
 * Maps a string key to a given value.
 * Returns the sum of the values that have a key with a prefix equal to a given
 * string.
 * 
 * 
 * Implement the MapSum class:
 * 
 * 
 * MapSum() Initializes the MapSum object.
 * void insert(String key, int val) Inserts the key-val pair into the map. If
 * the key already existed, the original key-value pair will be overridden to
 * the new one.
 * int sum(string prefix) Returns the sum of all the pairs' value whose key
 * starts with the prefix.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input
 * ["MapSum", "insert", "sum", "insert", "sum"]
 * [[], ["apple", 3], ["ap"], ["app", 2], ["ap"]]
 * Output
 * [null, null, 3, null, 5]
 * 
 * Explanation
 * MapSum mapSum = new MapSum();
 * mapSum.insert("apple", 3);  
 * mapSum.sum("ap");           // return 3 (apple = 3)
 * mapSum.insert("app", 2);    
 * mapSum.sum("ap");           // return 5 (apple + app = 3 + 2 = 5)
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= key.length, prefix.length <= 50
 * key and prefix consist of only lowercase English letters.
 * 1 <= val <= 1000
 * At most 50 calls will be made to insert and sum.
 * 
 * 
 */
#include <vector>
#include <string>
using namespace std;
// @lc code=start
struct Node {
    Node* son[26]{};
    int score = 0;
};
class MapSum {
public:
    MapSum() {
        this->root = new Node();
    }
    
    void insert(string key, int val) {
        Node* cur = root;
        for (char c : key) {
            if (cur->son[c - 'a'] == nullptr) {
                cur->son[c - 'a'] = new Node();
            }
            cur = cur->son[c - 'a'];
        }
        cur->score = val;
    }
    
    int sum(string prefix) {
        Node* cur = root;
        for (char c : prefix) {
            c -= 'a';
            if (!cur->son[c]) {
                return 0;
            } else {
                cur = cur->son[c];
            }
        }
        return count_prefix(cur);
    }

    int count_prefix(Node* node) {
        if (!node) {
            return 0;
        }
        int ans = node->score;
        for (Node* s : node->son) {
            if (s) {
                ans += count_prefix(s);
            }
        }
        return ans;
    }

private:
    Node* root;
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */
// @lc code=end

