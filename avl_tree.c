#include "avl_tree.h"

AVLTreeNode *AVLInsert(AVLTreeNode *root, int element){

    if (root == NULL){
        // insert at root
        root = newAVLTreeNode(element);
        return root;
    }

    if (element < root->element){
        root->left = AVLInsert(root->left, element);
        if (height(root->left) > height(root->right)){
            // if the left subtree is taller
            leftBalance(root);
        }
        root->height = maxValue(height(root->left), height(root->right)) + 1;
    } else if (element > root->element){
        root->right = AVLInsert(root->right, element);
        if (height(root->right) > height(root->left)){
            // if the right subtree is taller
            rightBalance(root);
        }
        root->height = maxValue(height(root->left), height(root->right)) + 1;
    } else {
        // element already exists
        return root;
    }

    return root;

}

AVLTreeNode *newAVLTreeNode(int element){

    AVLTreeNode *node = (AVLTreeNode *)malloc(sizeof(AVLTreeNode ));

    node->element = element;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;

}

int height(AVLTreeNode *node){

    if (node == NULL){
        return 0;
    } else {
        return node->height;
    }

}

void leftBalance(AVLTreeNode *node){
    
    if (height(node->left) > height(node->right)){
        rotateRight(node);
    } else {
        rotateLeft(node->left);
        rotateRight(node);
    }
}

void rightBalance(AVLTreeNode *node){

    if (height(node->right) > height(node->left)){
        rotateLeft(node);
    } else {
        rotateRight(node->right);
        rotateLeft(node);
    }

}

void rotateLeft(AVLTreeNode *node){
    // swap the left subtree with the right subtree of the left subtree
    
    AVLTreeNode *temp = node->right;

    node->right = node->left;

    node->left = temp;

}

void rotateRight(AVLTreeNode *node){

    AVLTreeNode *temp = node->left;

    node->left = node->right;

    node->right = temp;

}

int maxValue(int a, int b){

    if (a > b){
        return a;
    } else {
        return b;
    }

}

void displayTree(AVLTreeNode *node, int level){

    if (node == NULL){
        return;
    }

    displayTree(node->left, level + 1);
    printf("Level: %d Value: %d\n", level, node->element);
    displayTree(node->right, level + 1);

}

AVLTreeNode *AVLDelete(AVLTreeNode *root, int element, bool *success){
    if (root == NULL){
        // if the subtree is empty. 
        *success = false;
        return root;
    }

    if (element < root->element){
        root->left = AVLDelete(root->left, element, success);
        if (height(root->left) > height(root->right)){
            // if the left subtree is taller
            leftBalance(root);
        }
    } else if (element > root-> element){
        root->right = AVLDelete(root->right, element, success);
        if (height(root->right) > height(root->left)){
            // if the right subtree is taller
            rightBalance(root);
        }
    } else {
        AVLTreeNode *temp = root;

        // if no right subtree.
        if (temp->right == NULL){
            root = temp->left;
            *success = true;
            free(temp);
            return root;
        } else if (temp->left == NULL){
            // if no left subtree.
            root = temp->right;
            *success = true;
            free(temp);
            return root;
        } else {
            // if both subtrees exist.
            temp = root->left;

            while (temp->right != NULL){
                temp = temp->right;
            }

            int hold = root->element;

            root->element = temp->element;

            temp->element = hold;

            root->left = AVLDelete(root->left, temp->element, success);

            return root;
        }
    }
}

int main(){
    
    AVLTreeNode *root = NULL;

    root = AVLInsert(root, 18);

    root = AVLInsert(root, 20);

    root = AVLInsert(root, 12);

    root = AVLInsert(root, 19);

    displayTree(root, 0);
    printf("\n");

}