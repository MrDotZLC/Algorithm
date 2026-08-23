#include <vector>
#include <iostream>
using namespace std;

void merge(vector<int>& arr, int lo, int mid, int hi, vector<int>& tmp) {
    for (int k = lo; k <= hi; ++k) {
        tmp[k] = arr[k];
    }

    int i = lo, j = mid + 1;

    for (int k = lo; k <= hi; ++k) {
        if (i > mid) {
            arr[k] = tmp[j++];
        } else if (j > hi) {
            arr[k] = tmp[i++];
        } else if (tmp[i] <= tmp[j]) {
            arr[k] = tmp[i++];
        } else {
            arr[k] = tmp[j++];
        }
    }
}
void merge_sort(vector<int>& arr, int lo, int hi, vector<int>& tmp) {
    if (lo >= hi) return;

    int mid = lo + (hi - lo) / 2;
    merge_sort(arr, lo, mid, tmp);
    merge_sort(arr, mid + 1, hi, tmp);
    merge(arr, lo, mid, hi, tmp);
}

void merge_sort(vector<int>& arr) {
    vector<int> tmp(arr.size());
    merge_sort(arr, 0, arr.size() - 1, tmp);
}

int main() {
    vector<int> arr = {4, 6, 3, 2, 10, 999, -999};
    merge_sort(arr);
    for (int i : arr) {
        cout << i << ' ';
    }
}