#ifndef BST_H
#define BST_H

#include <iostream>
using namespace std;

//constexpr int NWORDS = 45;
constexpr int NWORDS = 45392;


struct Node
{
    string key;
    int value;
    Node * left, * right;
    int height;
    Node(const string & new_key, Node * new_left=nullptr, Node * new_right=nullptr)
        : key(new_key),
          value(0), // for map, BST needs both key and value, but ignore for our measurement
          left(new_left), right(new_right),
          height(1)
    { }

};

void destroy(Node* node);

// iterator
struct BSTIterator {
    std::vector<string> keys;
    size_t index;
    static void in_order(Node *node, std::vector<string> &keys){
        if (!node) return;
        in_order(node->left, keys);
        keys.push_back(node->key);
        in_order(node->right, keys);
    }
    BSTIterator(Node* root) : index(0){in_order(root, keys);}
    BSTIterator(const std::vector<string>& keys, size_t index)
        : keys(keys), index(index){}
    
    const string & operator*()const{ return keys[index]; }
    string & operator*(){ return keys[index]; }
    BSTIterator& operator++(){ ++index; return *this; }
    BSTIterator operator++(int){ BSTIterator tmp = *this; ++index; return tmp; }
    BSTIterator& operator--(){ --index; return *this; }
    BSTIterator operator--(int){ BSTIterator tmp = *this; --index; return tmp; }
    bool operator==(const BSTIterator &other) const { return index==other.index && keys==other.keys; }
    bool operator!=(const BSTIterator &other) const { return !(*this == other); }
    BSTIterator operator+(int n) const{ BSTIterator tmp = *this; tmp.index += n; return tmp; }
    BSTIterator operator-(int n) const{ BSTIterator tmp = *this; tmp.index -= n; return tmp; }
    int operator-(const BSTIterator &other) const { return index-other.index; }
    BSTIterator& operator+=(int n){ index += n; return *this; }
    BSTIterator& operator-=(int n){ index -= n; return *this; }
    const string &operator[](int n)const{ return keys[index+n]; }
};

struct BST
{
    Node * root;
    const string name;
    int count;
    using iterator = BSTIterator;
    BST(const string & new_name)
        : root(nullptr), name(new_name), count(0) { }

    virtual void insert( const string & word) = 0;
    virtual bool find( const string & word ) const = 0;
    virtual void remove( const string & word ) = 0;

    virtual bool is_empty() const = 0;
    virtual int size() const { return count; }
    virtual int get_height() const = 0;

    static void pre_order_print(ostream & out, Node * t);
    static void in_order_print(ostream & out, Node * t);
    static void post_order_print(ostream & out, Node * t);

    void print(ostream & out) const
    {
        // pre_order_print(out, root);
        in_order_print(out, root);
        // post_order_print(out, root);
    }

    virtual ~BST(); // must delete any Nodes in the tree pointed to by root
    BST(const BST & L) = delete;
    BST& operator =(const BST & L) = delete;
};

ostream & operator << (ostream & out, BST & L);

void error(string word, string msg);
void insert_all_words(int k, string file_name, BST & L);
void find_all_words(int k, string file_name, BST & L);
void remove_all_words(int k, string file_name, BST & L);
void measure_BST(string file_name, BST & L);
void measure_BSTs(string input_file);
void print_times();
#endif
