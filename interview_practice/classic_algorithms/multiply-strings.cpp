#include <string>
#include <vector>
#include <iostream>
using namespace std;

// 大数相乘
// 数字转成string，高位在前，低位在后
// 56*57=
// 0 1 2 3
// -------
//     4 2
//   3 5
//   3 0
// 2 5
// -------
// 3 1 9 2

string multiply_string(const string& num1, const string num2) {
    int m = num1.size(), n = num2.size();

    vector<int> pos(m + n, 0);

    // 从低位到高位逐位相乘
    for (int i = m - 1; i >= 0; --i) {
        for (int j = n - 1; j >= 0; --j) {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int p1 = i + j;
            int p2 = i + j + 1;
            int sum = mul + pos[p2];

            pos[p2] = sum % 10;
            pos[p1] += sum / 10;
        }
    }

    // 将数组转成 string，忽略前导零
    string res;
    for (int i : pos) {
        if (i == 0 && res.empty()) continue;
        res += static_cast<char>('0' + i);
    }

    return res.empty() ? "0" : res;
}

int main() {
    string num1 = "56";
    string num2 = "57";
    cout << "input=" << num1 << ", " << num2 
         << ", output=" << multiply_string(num1, num2) << endl;
}
