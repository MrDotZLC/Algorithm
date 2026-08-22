#include <iostream>

using namespace std;
// 快速幂 res=pow(base, exp)
// exp 为 0  ，res=0
// exp 为偶数，res=(base^(exp/2))^2
// exp 为奇数，res=base(base^((exp-1)/2))^2

// 整数快速幂
long long fast_pow_integer(long long base, long long exp, long long modulus) {
    long long res = 1;
    base %= modulus; // 先对底数取模，防止溢出

    while (exp > 0) {
        if (exp & 1) { // exp 为奇数
            res = res * base % modulus;
        }
        base = base * base % modulus;
        exp >>= 1;
    }
    return res;
}

// 浮点快速幂
double fast_pow_double(double base, int exp) {
    long long new_exp = exp;
    if (new_exp < 0) {
        base = 1.0 / base;
        new_exp = -new_exp;
    }

    double res = 1.0;
    while (new_exp > 0) {
        if (new_exp & 1) {
            res *= base;
        }
        base *= base;
        new_exp >>= 1;
    }
    return res;
}

int main() {
    long long base = 2;
    long long exp = 10;
    long long modulus = 1e9+7;

    cout << "integer fast pow, base=" << base 
         << ", exp=" << exp << ", res=" << fast_pow_integer(base, exp, modulus) << endl;


    double base2 = 0.5;
    int exp2 = -10;
    // int exp2 = INT_MIN;

    cout << "double fast pow, base2=" << base2 
         << ", exp2=" << exp2 << ", res=" << fast_pow_double(base2, exp2) << endl;

}