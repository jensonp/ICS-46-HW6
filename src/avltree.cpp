#include "avltree.h"
#include "bst.h"

AVLTree::iterator AVLTree::begin() const {
    return BSTIterator(root);
}

AVLTree::iterator AVLTree::end() const {
    BSTIterator it(root);
    it.index = it.keys.size();
    return it;
}


AVLTree::AVLTree() : BST("AVLTree") { }
void AVLTree::insert(const string& key) {
    if (!find(key)) {
        root = insert_node(root, key);
        ++count;
    }
}

bool AVLTree::find(const string & key) const { return find_node(root, key) != nullptr; }

void AVLTree::remove(const string & key) {
    if (find(key)) {
        root = delete_node(root, key);
        --count;
    }
}

bool AVLTree::is_empty() const { return root == nullptr; }

int AVLTree::get_height() const { return get_height(root); }

// AVLTree helper functions

int AVLTree::get_height(Node *node) { return node?node->height:0; }
int AVLTree::get_balance(Node *node) { return node?get_height(node->left)-get_height(node->right):0; }

void AVLTree::set_height(Node *node) {
    if (node){
        int leftHeight = get_height(node->left), rightHeight = get_height(node->right);
        node->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }
}

Node* AVLTree::right_rotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    set_height(y);
    set_height(x);
    return x;
}

Node* AVLTree::left_rotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    set_height(x);
    set_height(y);
    return y;
}

Node* AVLTree::rebalance(Node* t){
    if (!t) return t;
    set_height(t);
    int balance = get_balance(t);
    if (balance > 1){
        if (get_balance(t->left)<0) t->left = left_rotate(t->left);
        return right_rotate(t);
    }
    if (balance < -1){
        if (get_balance(t->right)>0) t->right = right_rotate(t->right);
        return left_rotate(t);
    }
    return t;
}

Node* AVLTree::insert_node(Node* t, string key){
    if (!t) return new Node(key);
    if (key < t->key) t->left = insert_node(t->left, key);
    else if (key > t->key) t->right = insert_node(t->right, key);
    else return t;
    return rebalance(t);
}

Node* AVLTree::find_node(Node* t, string key) {
    if (!t) return nullptr;
    if (key == t->key) return t;
    else if (key < t->key) return find_node(t->left, key);
    else return find_node(t->right, key);
}

Node* AVLTree::delete_node(Node* t, string key) {
    if (!t) return t;
    if (key < t->key) t->left = delete_node(t->left, key);
    else if (key > t->key) t->right = delete_node(t->right, key);
    else {
        if (!t->left || !t->right){
            Node* temp = t->left ? t->left : t->right;
            if (!temp){
                delete t;
                return nullptr;
            } 
            else{
                *t = *temp;
                delete temp;
            }
        } 
        else{
            Node* temp = t->right;
            while (temp->left) temp = temp->left;
            t->key = temp->key;
            t->right = delete_node(t->right, temp->key);
        }
    }
    if (!t) return t;
    return rebalance(t);
}
