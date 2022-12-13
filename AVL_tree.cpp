//
// Created by da on 06.11.2022.
//

#include "AVL_tree.h"


AVL_tree::Node *AVL_tree::insert(AVL_tree::Node *node, Key key, int pos) {
    if (node == nullptr) {
        return new Node(key, pos);
    }
    if (key > node->key)
        node->right = insert(node->right, key, pos);
    else {
        node->left = insert(node->left, key, pos);
    }
    return balance(node);
}

void AVL_tree::insert(Key key, int pos) {
    size++;
    root = insert(root, key, pos);
}

int AVL_tree::get(Node *node, Key key) {
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

int AVL_tree::get(Key key) {
    return get(root, key);
}

AVL_tree::Node *AVL_tree::remove(AVL_tree::Node *node, Key key) {
    if (node == nullptr || node->key == key && !node->right && !node->left)return nullptr;
    if (node->key == key) {
        if (node->left == nullptr) {
            return balance(node->right);
        } else if (node->right == nullptr) {
            return balance(node->left);
        }
        Node *minNodeInRightSubtree = findMinRightElem(node->right);
        node->key = minNodeInRightSubtree->key;
        node->pos = minNodeInRightSubtree->pos;
        remove(node->left, minNodeInRightSubtree->key);
        return balance(node);
    }
    if (key < node->key) {
        if (node->left == nullptr) {
            return balance(node);
        }
        node->left = remove(node->left, key);
    }
    if (key > node->key) {
        if (node->right == nullptr) {
            return balance(node);
        }
        node->right = remove(node->right, key);
    }
    return balance(node);
}

void AVL_tree::remove(Key key) {
    root = remove(root, key);
}

void AVL_tree::print() {
    print(root, "", false);
}

void AVL_tree::print(Node *node, string pref, bool isRight) {
    if (node == nullptr)return;
    cout << pref << ((isRight) ? "├── " : "└── ");
    node->key.print();
    cout << " " << node->height << endl;
    string nextPref = pref + (isRight ? "│   " : "    ");
    print(node->right, nextPref, true);
    print(node->left, nextPref, false);
}


AVL_tree::Node *AVL_tree::findMinRightElem(AVL_tree::Node *node) {
    if (node->left == nullptr)return node;
    return findMinRightElem(node->left);
}

int AVL_tree::getHeight(AVL_tree::Node *node) {
    return node ? node->height : 0;
}

int AVL_tree::getBalance(Node *node) {
    return getHeight(node->right) - getHeight(node->left);
}

AVL_tree::Node *AVL_tree::rightRotate(Node *y) {
    countOfRotates++;
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    fixHeight(y);
    fixHeight(x);
    return x;
}

AVL_tree::Node *AVL_tree::leftRotate(Node *x) {
    countOfRotates++;
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    fixHeight(x);
    fixHeight(y);
    return y;
}


void AVL_tree::fixHeight(Node *node) {
    node->height = max(getHeight(node->right), getHeight(node->left)) + 1;
}

AVL_tree::Node *AVL_tree::balance(AVL_tree::Node *p) {
   fixHeight(p);
    if (getBalance(p) == 2) {
        if (getBalance(p->right) < 0)
            p->right = rightRotate(p->right);
        return leftRotate(p);
    }
    if (getBalance(p) == -2) {
        if (getBalance(p->left) > 0)
            p->left = leftRotate(p->left);
        return rightRotate(p);
    }
    return p;
}




