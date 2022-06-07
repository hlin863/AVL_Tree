#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct AVLTreeNode {

    int element;
    struct AVLTreeNode *left;
    struct AVLTreeNode *right;
    int height;

} AVLTreeNode;

AVLTreeNode *AVLInsert(AVLTreeNode *root, int element);

AVLTreeNode *newAVLTreeNode(int element);

int height(AVLTreeNode *node);

void leftBalance(AVLTreeNode *node);

void rightBalance(AVLTreeNode *node);

void rotateLeft(AVLTreeNode *node);

void rotateRight(AVLTreeNode *node);

int maxValue(int a, int b);

void displayTree(AVLTreeNode *node, int level);

AVLTreeNode *AVLDelete(AVLTreeNode *root, int element, bool *success);