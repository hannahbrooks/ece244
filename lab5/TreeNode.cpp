#include "TreeNode.h"

// constructor
TreeNode:: TreeNode(DBentry* _entryPtr) {
    this->entryPtr = _entryPtr;
    this->left = NULL;
    this->right = NULL;
}

// destructor
TreeNode:: ~TreeNode() {
    delete entryPtr;
}

// set left
void TreeNode:: setLeft(TreeNode* newLeft) {
    this->left = newLeft;
}

// set right
void TreeNode:: setRight(TreeNode* newRight) {
    this->right = newRight;
}

// get left
TreeNode* TreeNode:: getLeft() const {
    return left;
}

// get right
TreeNode* TreeNode:: getRight() const {
    return right;
}

// get pointer to the DBentry the TreeNode contains
DBentry* TreeNode:: getEntry() const {
    return entryPtr;
}

