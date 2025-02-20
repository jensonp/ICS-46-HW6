#include "bstree.h"

BSTree::BSTree() :BST("BSTree"){}
void BSTree::insert(const string &key){ if(!find(key)){ root = insert_node(root, key); ++count; } }
bool BSTree::find(const string &key) const{ return find_node(root, key)!=nullptr; }
void BSTree::remove(const string &key){ if(find(key)){ root = delete_node(root, key); --count; } }
bool BSTree::is_empty()const{ return root==nullptr; }
int BSTree::get_height()const{ return compute_height(root); }

// BSTree Helper Functions
Node* BSTree::left_most(Node* t) { while(t && t->left) t = t->left; return t; }
int BSTree::compute_height(Node* t) {
    if (!t) return 0;
    int leftHeight = compute_height(t->left), rightHeight = compute_height(t->right);
    return 1+(leftHeight>rightHeight?
              leftHeight:rightHeight);
}

Node* BSTree::insert_node(Node* t, string key) {
    if(!t) return new Node(key);
    if(key < t->key) t->left = insert_node(t->left, key);
    else if(key > t->key) t->right = insert_node(t->right, key);
    return t;
}

Node* BSTree::find_node(Node* t, string key) {
    if(!t) return nullptr;
    if(key == t->key) return t;
    else if(key < t->key) return find_node(t->left, key);
    else return find_node(t->right, key);
}


Node* BSTree::delete_node(Node* t, string key) {
    if (!t) return t;
    if (key < t->key) t->left = delete_node(t->left, key);
    else if (key > t->key) t->right = delete_node(t->right, key);
    else {
        if (!t->left){
            Node* temp = t->right;
            delete t;
            return temp;
        } 
        else if (!t->right){
            Node* temp = t->left;
            delete t;
            return temp;
        } 
        else{
            Node* temp = left_most(t->right);
            t->key = temp->key;
            t->right = delete_node(t->right, temp->key);
        }
    }
    return t;
}
