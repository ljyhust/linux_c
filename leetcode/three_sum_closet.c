/**
 * 三数之和 close to target
 * 数组有序
 */
#include<stdio.h>

int* three_sum_close(int* nums, int target);

int main(int argc, char* argv) {

}

/**
 * 双指针法
 *  i lo hi 计算，lo++  或  hi--  移动
 */
int* three_sum_close(int* nums, int target) {
    int len = sizeof(nums) / sizeof(int);
    int diff = 66666;
    int res[3] = {0};
    for (int i = 0; i < len; i++) {
        int lo = i + 1;
        int hi = len - 1;
        while(lo < hi) {
            int sum = nums[i] + nums[lo] + nums[hi];
            if (sum - target < diff) {
                diff = sum - target;
            }
            if (sum < target) {
                lo++;
            } else {
                hi--;
            }
        }
        res[0] = i; res[1] = lo; res[2] = hi;
    }

    return res;
}