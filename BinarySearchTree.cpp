//
// Created by da on 06.11.2022.
//

#include "BinarySearchTree.h"

Node *BinarySearchTree::insert(Node *node, Key key, int pos) {
    if (node == nullptr)return new Node(key, pos);
    if (node->key < key) {
        node->right = insert(node->right, key, pos);
    } else {
        node->left = insert(node->left, key, pos);
    }
    return node;
}

void BinarySearchTree::insert(Key key, int pos) {
    root = insert(root, key, pos);
}

void BinarySearchTree::remove(Key key) {
    root = remove(root, key);
}

Node *BinarySearchTree::remove(Node *node, Key key) {
    if (node == nullptr || node->key == key && !node->right && !node->left)return nullptr;
    if (node->key == key) {
        if (node->left == nullptr) {
            return node->right;
        } else if (node->right == nullptr) {
            return node->left;
        }
        Node *minNodeInRightSubtree = findMinRightElem(node->right);
        node->key = minNodeInRightSubtree->key;
        node->pos = minNodeInRightSubtree->pos;
        remove(node->left, minNodeInRightSubtree->key);
        return node;
    }
    if (key < node->key) {
        if (node->left == nullptr) {
            return node;
        }
        node->left = remove(node->left, key);
    }
    if (key > node->key) {
        if (node->right == nullptr) {
            return node;
        }
        node->right = remove(node->right, key);
    }
    return node;
}

Node *BinarySearchTree::findMinRightElem(Node *node) {
    if (node->left == nullptr)return node;
    return findMinRightElem(node->left);
}

int BinarySearchTree::get(Node *node, Key key) {
    if (node == nullptr)return -1;
    if (key == node->key) {
        return node->pos;
    }
    if (key < node->key) {
        return get(node->left, key);
    }
    if (key > node->key) {
        return get(node->right, key);
    }
    return -1;
}

int BinarySearchTree::get(Key key) {
    return get(root, key);
}

void BinarySearchTree::print() {
    print(root, "", false);
}

void BinarySearchTree::print(Node *node, string pref, bool isRight) {
    if (node == nullptr)return;
    cout << pref << ((isRight) ? "├── " : "└── ");
    node->key.print();
    cout << endl;
    string nextPref = pref + (isRight ? "│   " : "    ");
    print(node->right, nextPref, true);
    print(node->left, nextPref, false);
}
