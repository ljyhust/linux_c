#include <stdio.h>

void swap(int* nums, int i, int j);
int find_middle_num(int* nums, int i, int j);
int findKthLargest(int* nums, int numsSize, int k);
int find_kth_larger_num(int* nums, int lo, int hi, int k);

int main(int argc, char *argv[]) {
    int nums[4] = {1, 99,99, 99};
    //int size = sizeof(nums) / sizeof(nums[0]);
    int kth = findKthLargest(nums, 4, 1);
    printf("result is %d", kth);
    return 0;
}

/**
 * find Kth largest element in an array
 * quick sort
 * k is from 1 to numSize
 */
int findKthLargest(int* nums, int numsSize, int k) {
    if (k < 1 || k > numsSize) {
        return -1;
    }
    // set middle num to i
    // compare large to small
    // swap
    // iterate
    return find_kth_larger_num(nums, 0, numsSize - 1, k - 1);
}

int find_kth_larger_num(int* nums, int lo, int hi, int k) {
    if (lo > hi) {
        return -1;
    }
    int middle_num = find_middle_num(nums, lo, hi);
    int left = lo, right = hi;
    while(left < hi && right > lo) {
        // 不须判断 = 的情况，到后面取中值或返回时判断
        while(nums[++left] > middle_num){}
        while(nums[--right] < middle_num){}
        if (left < right) {
            swap(nums, left, right);
        } else {
            break;
        }
        
    }
    swap(nums, lo, right);
    // check kth value
    if (right == k) {
        return nums[right];
    }
    if(right > k) {
        return find_kth_larger_num(nums, lo, right - 1, k);
    }
    if (right < k) {
        return find_kth_larger_num(nums, right + 1, hi, k);
    }
}

void swap(int* nums, int i, int j) {
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}

int find_middle_num(int* nums, int i, int j) {
    if (i == j) {
        return nums[i];
    }
    int middle = (i + j) / 2;
    // min num put in array.last
    if (nums[j] > nums[middle]) {
        swap(nums, j, middle);
    }
    if (nums[j] > nums[i]) {
        swap(nums, i, j);
    }
    if (nums[middle] > nums[i]) {
        swap(nums, i, middle);
    }
    return nums[i];
}


