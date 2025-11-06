/*     
    LCR 165. 解密数字
    同步题目状态

    中等
    相关标签
    premium lock icon
    相关企业
    现有一串神秘的密文 ciphertext，经调查，密文的特点和规则如下：

    密文由非负整数组成
    数字 0-25 分别对应字母 a-z
    请根据上述规则将密文 ciphertext 解密为字母，并返回共有多少种解密结果。

    

    

    示例 1：

    输入：ciphertext = 216612
    输出：6
    解释：216612 解密后有 6 种不同的形式，分别是 "cbggbc"，"vggbc"，"vggm"，"cbggm"，"cqgbc" 和 "cqgm" 
    

    提示：

    0 <= ciphertext < 231
*/
#include <vector>
#include <string>
using namespace std;
class Solution {
public:
    int crackNumber(int ciphertext) {
        string s = to_string(ciphertext);
        int n = s.length(), f0 = 1, f1 = f0;
        for (int i = 1; i < n; i++) {
            int cnt = f1;
            if (s[i - 1] == '1' || (s[i - 1] == '2' && s[i] <= '5')) {
                cnt += f0;
            }
            f0 = f1;
            f1 = cnt;
        }
        return f1;
    }
};