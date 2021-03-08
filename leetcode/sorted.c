// 排序算法 2021-03-04
#include <stdio.h>

// 插入排序
void insert_sorted(int num[], int len);

// 冒泡排序
void boom_sorted(int a[], int len);

// 归并排序，分解 - 解决 - 合并
void merge_sort(int a[], int left, int right);
// 归并排序中的 解决 + 合并  方法
void merge(int a[], int left, int right, int mid);

// 快速排序 先分解 - 解决 - 合并，合并由于原地已经有序，不需要再归并了
void quick_sort(int a[], int left, int right);

int quick_pivot(int a[], int left, int right);

/**
 * implement
 */
void insert_sorted(int num[], int len) {
    // 后面是未排序好的，遍历后面的元素，与前面的比较
    for(int i = 1; i < len; i++) {
        // 前面是已排序好的，a[i]与 a[i-1 ...]比较
        int j = i - 1;
        int temp = num[i]; // 缓存起来，找个位置存放
        for(; j >= 0; j--) {
            if (temp < num[j]) {
                num[j+1] = num[j]; 
            } else {
                break;
            }
        }
        //插入a[i]
        num[j + 1] = temp;
    }
}

void boom_sorted(int a[], int len) {
    // 相邻两个判断
    for(int i = 0; i < len; i++) {
        // 每次排序都会至少将一个元素放在正确的位置，这个位置便是 len - i - 1
        for (int j = 0; j < len - i - 1; j++) {
            if (a[j+1] < a[j]) {
                //交换
                int temp = a[j + 1];
                a[j + 1] = a[j];
                a[j] = temp;
            }
        }
    }
}

void merge_sort(int a[], int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = (left + right) / 2;
    merge_sort(a, left, mid);
    merge_sort(a, mid + 1, right);
    merge(a, left, right, mid);
}

// 归并排序中的 解决 + 合并  方法
void merge(int a[], int left, int right, int mid) {
    if (left == right) {
        return;
    }
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int left_arr[n1 + 1];
    int right_arr[n2 + 1];
    for(int i = 0; i < n1; i++) {
        left_arr[i] = a[left + i];
    }
    for (int j = 0; j < n2; j++) {
        right_arr[j] = a[mid + 1 + j];
    }
    // 哨兵
    left_arr[n1] = 0x7fffffff;
    right_arr[n2] = 0x7fffffff;
    // 解决
    int i = 0, j = 0;
    for(int k = left; k <= right; k++) {
        if (left_arr[i] <= right_arr[j]) {
            a[k] = left_arr[i++];
        } else {
            a[k] = right_arr[j++];
        }
    }
}

void quick_sort(int a[], int left, int right) {
    if (left >= right) {
        return;
    }
    int pivot = quick_pivot(a, left, right);
    quick_sort(a, left, pivot);
    quick_sort(a, pivot + 1, right);
}

int quick_pivot(int a[], int left, int right) {
    if (right == left) {
        return left;
    }
    // 计算找出pivot，左边 a[pivot] 右边 > a[pivot]
    // 比较left right 及 (left + right) /2
    // 三值中间值为pivot 放在最右边
}

int main(int argc, char* argv[]) {
    int num[] = {4, 6, 5, 9, 3, 1, 2};
    int len = sizeof(num) / sizeof(num[0]);
    //boom_sorted(num, len);
    merge_sort(num, 0, len - 1);
    for(int i = 0; i < len; i++) {
        printf("%d\t", num[i]);
    }
}