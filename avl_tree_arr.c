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

    if (index >= tree->size){
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

TREE *deleteElement(TREE *tree, int element, int index, bool *success){
    if (tree->size == 0){
        // if the tree is empty, return the tree.
        *success = false;
        return tree;
    } else {
        if (element < tree->data[index]){
            // check the left subtree if the deleted element is less than the node at the index.
            tree = deleteElement(tree, element, 2 * index + 1, success);
        } else if (element > tree->data[index]){
            tree = deleteElement(tree, element, 2 * index + 2, success);
        } else {
            
            if (2 * index + 1 > tree->size){
                // deleting an element with no children nodes.
                *success = true;
                tree->data[index] = 0;
                return tree;
            } else {

                if (2 * index + 2 > tree->size){
                    // if only the left branch was present
                    *success = true;
                    tree->data[index] = tree->data[2 * index + 1];
                    tree->data[2 * index + 1] = 0;
                    return tree;
                } else {

                    displayTree(tree, 0);

                    printf("\n");

                    *success = true;
                        
                    int temp = index;

                    int children_size = 10;

                    int children_index = 0;

                    // use an array to track the children of the node to be deleted.
                    int *children = (int*) malloc(sizeof(int) * children_size);

                    trackChildren(tree, 2 * index + 1, &children_index, children);

                    trackChildren(tree, 2 * index + 2, &children_index, children);

                    /******************************************************************************************/

                    printf("TEST CHILDREN 1\n");
                    /* test function to display the children nodes. */
                    displayArray(children, children_index);

                    /******************************************************************************************/

                    // restructure the children of the node to be deleted.
                    tree = restructureChildren(tree, children, children_index, temp);

                    /*******************************************************************************************/

                    // test the display of the elements before the index.

                    tree->size -= 1;

                    printf("Total nodes: ");

                    for (int i = 0; i < tree->size; i++){
                        printf("%d ", tree->data[i]);
                    }

                    printf("\n");

                    /*******************************************************************************************/



                    return tree;

                }

            }

        }
    }
}

void displayArray(int *array, int size){
    /******************************************************************************************/

    /* test function to display the children nodes. */
    printf("Children nodes: ");

    for (int i = 0; i < size; i++){
        printf("%d ", array[i]);
    }

    printf("\n");

    /******************************************************************************************/
}

TREE *restructureChildren(TREE *tree, int *children, int children_index, int temp){

    printf("TEST CHILDREN 2\n");
    /* test function to display the children nodes. */
    displayArray(children, children_index);

    printf("Tree index: %d\n", temp);

    /******************************************************************************************/
    // test to check the size of children array.

    printf("Children size: %d\n", children_index);

    /******************************************************************************************/

    children = sortArray(children, children_index);

    /******************************************************************************************/

    tree = insertChildren(tree, children, 0, temp);

    return tree;

}

TREE *insertChildren(TREE *tree, int *filtered_children, int filtered_index, int index){
    if (index > tree->size){
        return tree;
    } else {
        
        if (filtered_index >= sizeof(filtered_children) / sizeof(int)){
            return tree;
        }
        
        tree->data[index] = filtered_children[filtered_index];

        tree = insertChildren(tree, filtered_children, filtered_index + 1, 2 * index + 1);
        tree = insertChildren(tree, filtered_children, filtered_index + 2, 2 * index + 2);

        return tree;
    }
}

int *filterChildren(int *children, int children_index){

    int *result = (int*) malloc(sizeof(int) * children_index);

    for (int i = 1; i < children_index; i++){
        result[i - 1] = children[i - 1];
    }

    return result;

}

int *sortArray(int *filtered_children, int children_index){

    for (int i = 1; i < children_index; i++){
        for (int j = 1; j < children_index; j++){
            if (filtered_children[j - 1] > filtered_children[j]){
                int temp = filtered_children[j - 1];
                filtered_children[j - 1] = filtered_children[j];
                filtered_children[j] = temp;
            }
        }
    }

    return filtered_children;

}

void trackChildren(TREE *tree, int index, int *children_index, int *children){

    if (index > tree->size){
        return;
    } else {

        // printf("Children array size: %d\n", sizeof(children));

        if (*children_index == sizeof(children)){
            // if the array is full, double the capacity of the array.
            children = (int*) realloc(children, sizeof(int) * (*children_index * 2));
        }

        if (tree->data[index] != 0){

            /******************************************************************************************/

            // if the children node was a valid value.
            printf("Children: %d\n", tree->data[index]);

            children[*children_index] = tree->data[index];

            *children_index += 1;

            trackChildren(tree, 2 * index + 1, children_index, children);
            trackChildren(tree, 2 * index + 2, children_index, children);

            /******************************************************************************************/

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

    bool success;

    printf("\n");

    tree = deleteElement(tree, 60, 0, &success);

    displayTree(tree, 0);

    printf("\n");

    return 0;

}