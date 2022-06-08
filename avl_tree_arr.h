#include <stdio.h>
#include <stdlib.h>

typedef struct AVLTree{

    int *data;
    int index;
    int size;

} TREE;

TREE *new_tree();

/*
    * Inserts a new element in the tree.
    * @param tree: the tree to insert the element in.
    * @param data: the element to insert.
    * @param index: tracking the position of where to insert the element.
    * @return: the tree with the new element inserted.
*/
TREE *insert(TREE *tree, int data, int index);

/*
    * Displays error messages when the index is invalid.
    * @param index: the index to check.
*/
void displayInvalidIndex(int index);

/*
    * Initialises the tree data variable with zeros.
    * @param tree: the tree to initialise.
    * @param size: the size of the tree.
    * @return: the tree with the data variable initialised.
*/
TREE *initialiseTree(TREE *tree, int size);

/* 
    * Displays the tree.
    * @param tree: the tree to display.
    * @param index: the index to display.
*/
void displayTree(TREE *tree, int index);

/* 
    * Deletes an element from the tree. 
    * @param tree: the tree to delete the element from.
    * @param data: the element to delete.
    * @param index: tracking the position of where to delete the element.
    * @return: the tree with the element deleted.
*/
TREE *deleteElement(TREE *tree, int element, int index);