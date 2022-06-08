#include "avl_tree_arr.h"

TREE *new_tree(){

    TREE *tree = (TREE *)malloc(sizeof(TREE));
    // initialize the tree with a maximum capacity of 10 elements.
    tree->data = (int*) malloc(sizeof(int) * 10);
    // initalize the tree with default values of 0s.
    tree = initialiseTree(tree, 10);
    tree->index = 0;
    tree->size = 0;
    return tree;

}

TREE *insert(TREE *tree, int data, int index){
    
    if (tree->size == 0){
        /* 
            BASE CASE
            If the tree is empty, insert the data at the root.
        */
        
        tree->data[tree->index] = data;
        tree->size += 1;

    } else {

        /* 
            RECURSIVE CASE
            If the tree is not empty, insert the data in the tree.
        */
        if (index < 0){
            // invalid index
            displayInvalidIndex(index);
            return tree;
        } else {

            if (data < tree->data[index]){

                /* 
                    LEFT SUBTREE
                    If the data is less than the data at the index, insert the data in the left subtree.
                */

                if (2 * index + 1 > tree->size){
                    // if the left subtree is full, double the capacity of the tree.

                    tree->data = (int*) realloc(tree->data, sizeof(int) * (tree->size * 2));

                    tree = initialiseTree(tree, tree->size * 2);

                    tree->data[2 * index + 1] = data;
                    tree->size += 1;

                    return tree;
                
                } else {

                    if (tree->data[2 * index + 1] == 0){

                        // if the left subtree is empty, insert the data at the index.

                        tree->data[2 * index + 1] = data;
                        tree->size += 1;

                    } else {

                        // if the left subtree is not empty, insert the data in the left subtree.

                        tree = insert(tree, data, 2 * index + 1);

                    }

                }

            } else if (data > tree->data[index]){

                /* 
                    RIGHT SUBTREE
                    If the data is greater than the data at the index, insert the data in the right subtree.
                */

               if (2 * index + 2 > tree->size){
                    // if the right subtree is full, double the capacity of the tree.

                    tree->data = (int*) realloc(tree->data, sizeof(int) * (tree->size * 2));

                    tree = initialiseTree(tree, tree->size * 2);

                    tree->data[2 * index + 2] = data;
                    tree->size += 1;

                    return tree;
                
                } else {

                    if (tree->data[2 * index + 2] == 0){

                        // if the right subtree is empty, insert the data at the index.

                        tree->data[2 * index + 2] = data;
                        tree->size += 1;

                    } else {

                        // if the right subtree is not empty, insert the data in the right subtree.

                        tree = insert(tree, data, 2 * index + 2);

                    }

                }
            
            }

        }

    }

    return tree;

}

void displayInvalidIndex(int index){
    printf("Invalid index: %d\n", index);
}

TREE *initialiseTree(TREE *tree, int size){
    for (int i = 0; i < size; i++){
        tree->data[i] = 0;
    }
    return tree;
}

void displayTree(TREE *tree, int index){

    if (index > tree->size){
        return;
    } else {
            
        if (tree->data[index] == 0){
            return;
        } else {
            displayTree(tree, 2 * index + 1);
            printf("%d ", tree->data[index]);
            displayTree(tree, 2 * index + 2);
        }
    }

}

TREE *deleteElement(TREE *tree, int element, int index){
    if (index > tree->size){
        // invalid index
        return tree;
    } else {

        if (tree->data[index] == 0){
            // element not found
            return tree;
        } else {

            if (tree->data[index] == element){
                // element found
                if (2 * index + 1 < tree->size){
                    // left subtree exists
                    if (2 * index + 2 > tree->size){
                        // right subtree does not exist
                    }
                }

                tree->data[index] = 0;
                tree->size -= 1;
                return tree;
            } else {

                if (element < tree->data[index]){
                    // element not found in the left subtree
                    tree = deleteElement(tree, element, 2 * index + 1);
                } else {
                    // element not found in the right subtree
                    tree = deleteElement(tree, element, 2 * index + 2);

                }

                return tree;

            }

        }

    }
}

int main(){
    
    TREE *tree = new_tree();

    tree = insert(tree, 70, 0);
    tree = insert(tree, 60, 0);
    tree = insert(tree, 80, 0);
    tree = insert(tree, 50, 0);
    // tree = insert(tree, 90, 0);
    // tree = insert(tree, 40, 0);

    displayTree(tree, 0);

    printf("\n");

    tree = deleteElement(tree, 60, 0);

    displayTree(tree, 0);

    printf("\n");

    return 0;

}