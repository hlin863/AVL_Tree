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
            root = leftBalance(root);
        }
        root->height = maxValue(height(root->left), height(root->right)) + 1;
    } else if (element > root->element){
        root->right = AVLInsert(root->right, element);
        if (height(root->right) > height(root->left)){
            // if the right subtree is taller
            root = rightBalance(root);
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

AVLTreeNode *leftBalance(AVLTreeNode *node){
    
    if (height(node->left) > height(node->right)){
        node = rotateRight(node);
    } else {
        node->left = rotateLeft(node->left);
        node = rotateRight(node);
    }

    return node;
}

AVLTreeNode *rightBalance(AVLTreeNode *node){

    if (height(node->right) > height(node->left)){
        node = rotateLeft(node);
    } else {
        node->right = rotateRight(node->right);
        node = rotateLeft(node);
    }

    return node;
}

AVLTreeNode *rotateLeft(AVLTreeNode *node){
    // swap the left subtree with the right subtree of the left subtree
    
    AVLTreeNode *temp = node->right;

    node->right = temp->left;

    temp->left = node;

    return temp;

}

AVLTreeNode *rotateRight(AVLTreeNode *node){

    AVLTreeNode *temp = node->left;

    node->left = temp->right;

    temp->right = node;

    return temp;
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

char *getDirection(AVLTreeNode *node){
    char *direction = (char *)malloc(sizeof(char) * 2);

    strcpy(direction, "");

    if (height(node->left) > height(node->right)){
        strcpy(direction, "LH");
    } else if (height(node->left) < height(node->right)){
        strcpy(direction, "RH");
    } else {
        strcpy(direction, "EH");
    }

    return direction;
}

void displaySideWaysTree(AVLTreeNode *node, int level){
    
    if (node == NULL){
        return;
    }

    displaySideWaysTree(node->right, level + 1);
    char *direction = getDirection(node);
    for (int i = 0; i < level; i++){
        printf("\t");
    }
    printf("(%d) %d %s\n", level + 1, node->element, direction);
    displaySideWaysTree(node->left, level + 1);
    
}

AVLTreeNode *AVLDelete(AVLTreeNode *root, int element, bool *success){
    if (root == NULL){
        // if the subtree is empty. 
        *success = false;
        return root;
    }

    if (element < root->element){
        root->left = AVLDelete(root->left, element, success);
        if ((height(root->left) - height(root->right)) > 1){
            // if the left subtree is taller
            leftBalance(root);
        }
        return root;
    } else if (element > root-> element){
        root->right = AVLDelete(root->right, element, success);
        if ((height(root->right) - height(root->left)) > 1){
            // if the right subtree is taller
            rightBalance(root);
        }
        return root;
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

int getPredecessor(AVLTreeNode *node, int element){

    if (node == NULL){
        // base case when the node is a NULL value
        return -1;
    }

    if (node->left == NULL && node->right==NULL){
        // base case when reached a dead end.
        return -1;
    } else {
        if (node->left == NULL && node->right != NULL){
            if (node->right->element == element){
                return node->element;
            } else {
                if (node->element < element){
                    return getPredecessor(node->right, element);
                } else {
                    return -1;
                }
            }
        } else if (node->left != NULL && node->right == NULL){
            if (node->left->element == element){
                return node->element;
            } else {
                if (node->element > element){
                    return getPredecessor(node->left, element);
                } else {
                    return -1;
                }
            }
        } else {
            
            if (element < node->left->element){
                return getPredecessor(node->left, element);
            } else {

                if (node->right->element == element){
                    return node->element;
                } else if (node->left->element == element) {
                    return node->element;
                } else {
                    if (element < node->element){
                        return getPredecessor(node->left, element);
                    } else {
                        return getPredecessor(node->right, element);
                    }
                }
            
            }

        }
    }

}

int main(){
    
    AVLTreeNode *root = NULL;

    root = AVLInsert(root, 70);

    root = AVLInsert(root, 80);

    root = AVLInsert(root, 60);

    root = AVLInsert(root, 75);

    root = AVLInsert(root, 65);

    root = AVLInsert(root, 50);

    root = AVLInsert(root, 45);

    // displayTree(root, 0);
    // printf("\n");

    bool success;

    displaySideWaysTree(root, 0);

    printf("\n");

    /* TESTING finding predecessor */

    int predecessor = getPredecessor(root, 60);

    printf("Predecessor of 60 is %d\n", predecessor);

    predecessor = getPredecessor(root, 45);

    printf("Predecessor of 45 is %d\n", predecessor);

    predecessor = getPredecessor(root, 70);

    printf("Predecessor of 70 is %d\n", predecessor);

    /* 
    Test function to delete a node from the tree.
    */
    // root = AVLDelete(root, 17, &success);

    // printf("%d\n", root->element);

    // displayTree(root, 0);
    // printf("\n");

}