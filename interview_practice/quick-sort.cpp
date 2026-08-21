#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

void quick_sort_2_way(vector<int>& arr, int l, int r) {
    if (r - l < 1) {
        return;
    }

    // partition
    int mid = l + (r - l) / 2;
    if (arr[l] > arr[mid]) {
        swap(arr[l], arr[mid]);
    }
    if (arr[l] > arr[r]) {
        swap(arr[l], arr[r]);
    }
    if (arr[mid] > arr[r]) {
        swap(arr[mid], arr[r]);
    }
    // 将 mid 换到 r-1 的位置
    swap(arr[mid], arr[r - 1]);

    // 界标
    int pivot = arr[r - 1];

    // 遍历，将小于 arr[r-1] 的放 r-1 左边，将大于 arr[r-1] 的放 r-1 右边
    int i = l, j = r - 1;
    while (true) {
        while(arr[++i] < pivot) {}
        while(arr[--j] > pivot) {}
        if (i >= j) {
            break;
        }
        swap(arr[i], arr[j]);
    }
    swap(arr[i], arr[r - 1]);

    // recursion left and right part
    quick_sort_2_way(arr, l, i - 1);
    quick_sort_2_way(arr, i + 1, r);
}


void quick_sort_3_way(vector<int>& arr, int l, int r) {
    if (r - l < 1) {
        return;
    }

    int pivot = arr[l + (r - l) / 2];
    int lt = l; // arr[l..lt]  <  pivot
    int gt = r; // arr[gt..r]  >  pivot
    int i = l;  // arr[lt..gt] == pivot

    // 将 arr 分为小于、等于、大于 pivot 三段
    while (i <= gt) {
        if (arr[i] < pivot) {
            swap(arr[lt++], arr[i++]);
        } else if (arr[i] > pivot) {
            swap(arr[i], arr[gt--]);
        } else {
            i++;
        }
    }

    quick_sort_3_way(arr, l, lt - 1);       // 递归 < pivot 段
    quick_sort_3_way(arr, gt + 1, r);         // 递归 > pivot 段
}

int main() {
    vector<int> arr = {4, 6, 3, 2, 10, 999, -999};
    quick_sort_3_way(arr, 0, int(arr.size()) - 1);
    for (int i : arr) {
        cout << i << ' ';
    }
}