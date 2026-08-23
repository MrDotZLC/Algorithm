#include <iostream>
using namespace std;

// 二分法（<=target 的最大值）
int sqrt_binary(int n) {
    if (n < 2) return n;
    int lo = 1, hi = n / 2;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        long long sq = 1LL * mid * mid; 

        if (sq <= n) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return hi; // 最大为 hi
}

// 牛顿迭代法
// 求 f(x)=x^2-a
// x_{n+1}=x_n-((f(x_n)/f'(x_n))
//        =x_n-((x_n)^2-a/2(x_n))=x_n+(x_n)/2+a/2(x_n)
//        =(x_n)/2+a/2(x_n)=(x_n+a/(x_n))/2
double sqrt_newton(double n, double eps = 1e-9) {
    if (n < 0.0) return -1.0;
    if (n == 0.0) return 0.0;

    double x = n / 2;
    while (true) {
        double next = 0.5 * (x + n / x);
        if (abs(next - x) < eps) {
            break;
        }
        x = next;
    }
    return x;
}

int main() {
    int n = INT_MAX - 10000000;
    // int n = -11.0;
    cout << "input=" << n << ", binary_output=" << sqrt_binary(n) << endl;
    cout << "input=" << n << ", newton_output=" << sqrt_newton(n) << endl;
}