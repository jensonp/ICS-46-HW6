#include "bst.h"
#include "bstree.h"
#include "avltree.h"
#include "timer.h"

#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

ostream &operator<<(ostream & out, BST & L) {
    L.print(out);
    return out;
}

// destructor
void destroy(Node* node) {
    if (node == nullptr) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}
BST::~BST(){destroy(root);}

// print
void BST::pre_order_print(ostream &out, Node *t) {
    if (!t) return;
    out << t->key << " ";
    pre_order_print(out, t->left);
    pre_order_print(out, t->right);
}

void BST::in_order_print(ostream & out, Node * t) {
    if (!t) return;
    in_order_print(out, t->left);
    out << t->key << " ";
    in_order_print(out, t->right);
}

void BST::post_order_print(ostream & out, Node * t) {
    if (!t) return;
    post_order_print(out, t->left);
    post_order_print(out, t->right);
    out << t->key << " ";
}


BSTIterator begin(const BST &tree){ return BSTIterator(tree.root); }
BSTIterator end(const BST &tree){
    BSTIterator it(tree.root);
    it.index = it.keys.size();
    return it;
}

// Measurements

void error(string word, string msg) {
    cerr << "Error: " << msg << " (" << word << ")" << endl;
}
void insert_all_words(int K, string file_name, BST & L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = K * NWORDS / 10;
    t.start();
    for (string word; (in >> word) && (limit > 0); --limit) {L.insert(word); }
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\tI = " << eTime << endl;
}
void find_all_words(int K, string file_name, BST & L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = K * NWORDS / 10;
    t.start();
    for (string word; (in >> word) && (limit > 0); --limit) { L.find(word); }
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\tF = " << eTime << endl;
}

void remove_all_words(int K, string file_name, BST & L) {
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = K * NWORDS / 10;
    t.start();
    for (string word; (in >> word) && (limit > 0); --limit) { L.remove(word); }
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\tR = " << eTime << endl;
}

void measure_BST(string file_name, BST & L) {
    cout << L.name << endl;
    for (int K = 1; K <= 10; ++K) {
        cout << "\n\tK = " << K << endl;
        insert_all_words(K, file_name, L);
        find_all_words(K, file_name, L);
        remove_all_words(K, file_name, L);
    }
}

void measure_BSTs(string input_file) {
    cout << input_file << endl;
    BSTree bst;
    measure_BST(input_file, bst);
    //print_times();
    AVLTree avl;
    measure_BST(input_file, avl);
    //print_times();


}