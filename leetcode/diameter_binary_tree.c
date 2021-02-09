/**
 * diameter of binary tree
 * 求二叉树的直径，从左到右最高
 * 求根节点左 右子树最高
 * 注意一个边界条件：树为左树或右树，即另一边为null的这种
 */
#include <stdio.h>
#include <string.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
int max_tree_height(struct TreeNode* root);
int ans = 1;

int diameterOfBinaryTree(struct TreeNode* root){
    if (NULL == root) {
        return 0;
    }
    max_tree_height(root);
    return ans - 1;
}

/**
 * 求树高，递归
 * 判断子树最长的路径 + 本节点
 * 基准：本节点无子树，返回本节点 char*
 */
int max_tree_height(struct TreeNode* root) {
    if (NULL == root) {
        return 0;
    }
    int left_height = max_tree_height(root->left);
    int right_height = max_tree_height(root->right);
    ans = ans > left_height + right_height + 1 ? ans : left_height + right_height + 1;
    return left_height > right_height ? left_height + 1 : right_height + 1;

}

int main(int argc, char* argv[]) {
    struct TreeNode test;
    test.left = NULL;
    test.right = NULL;
    test.val = 1;
    int height = diameterOfBinaryTree(&test);
    printf("%d", height);
}