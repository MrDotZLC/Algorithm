#include <vector>
#include <iostream>
using namespace std;

// sift_down：将下标 i 的元素下沉到正确位置 ─────────────────────────────
// heap_size：当前堆的有效大小（堆尾已交换到数组末尾，不参与堆操作）
void sift_down(vector<int>& arr, int i, int heap_size) {
    while (true) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        // 找出 i 和两个孩子的最大值
        if (left < heap_size && arr[left] > arr[largest]) {
            largest = left;
        }
        if (right < heap_size && arr[right] > arr[largest]) {
            largest = right;
        }

        if (largest == i) { // 满足最大堆性质，退出
            break;
        }

        swap(arr[i], arr[largest]); // 将当前节点置下沉
        i = largest; 
    }
}

void heap_sort(vector<int>& arr) {
    int n = arr.size();

    // 从最后一个非叶子节点（n/2-1）倒序下沉，构建最大堆
    // 最后一个节点是最后一个非叶子节点的孩子，有 2i+1=n-1 或 2i+2=n-1
    // 向下取整，则推出最后一个非叶子节点 i=n/2-1  
    for (int i = n / 2 - 1; i >= 0; --i) {
        sift_down(arr, i, n);
    }

    // 逐步将堆顶交换到数组末尾
    for (int end = n - 1; end > 0; end--) {
        swap(arr[0], arr[end]);
        sift_down(arr, 0, end);
    }
}

int main() {
    vector<int> arr = {4, 6, 3, 2, 10, 999, -999};
    heap_sort(arr);
    for (int i : arr) {
        cout << i << ' ';
    }
}