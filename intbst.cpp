// intbst.cpp
// Implements class IntBST
// Marcus Wu, 11 02 2023
#include "intbst.h"
#include <iostream>
using std::cout;
#ifndef PRINT
#define PRINT
#ifdef DEBUG
void print(){std::cout<<"\n";}
template<typename T1, typename ...T>
inline void print(const T1&first, const T&... t){
    std::cout<<first<<" ";
    print(t...);
}
#define _printnode(n, x) do{if(n->x) print(#x, n->x->info);else print("no",#x);}while(0)
#define printnode(n) do{if(!n)print("no ",n);else{\
    print(n, ": ",n->info);\
    _printnode(n,parent);\
    _printnode(n,left);\
    _printnode(n,right);}}while(0)
#else// #ifdef DEBUG
void print(){}
template<typename T1, typename ...T>
inline void print(const T1&first, const T&... t){
}
#define printnode(n) do{}while(0)
#endif// #ifdef DEBUG
#endif// #ifndef PRINT

// constructor sets up empty tree
IntBST::IntBST() { 
    root=0;
}

// destructor deletes all nodes
IntBST::~IntBST() {
    print("!!!removing");
    clear(root);
    root=0;//defensive
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if(!n) return;
    printnode(n);
    clear(n->left);
    clear(n->right);
    delete n;
}
// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if(root) return insert(value,root);
    root=new Node(value);
    return 1;
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    int v=n->info;
    if(value==n->info) return 0;
    if(value<v){
        if(n->left) return insert(value, n->left);
        n->left=new Node(value);
        n->left->parent=n;
        return 1;
    }
    if(n->right) return insert(value, n->right);
    n->right=new Node(value);
    n->right->parent=n;
    return 1;
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if(!n) return;
    cout<<n->info<<" ";
    printPreOrder(n->left);
    printPreOrder(n->right);
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
    if(!n) return;
    printInOrder(n->left);
    cout<<n->info<<" ";
    printInOrder(n->right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if(!n) return;
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout<<n->info<<" ";
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if(!n) return 0;
    return sum(n->left)+sum(n->right)+n->info;
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if(!n) return 0;
    return count(n->left)+count(n->right)+1;
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node *IntBST::getNodeFor(int value, Node* n) const{
    if(!n) return 0;
    if(value==n->info) return n;
    if(value<n->info) return getNodeFor(value, n->left);
    return getNodeFor(value, n->right);
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    return getNodeFor(value, root);
}

#define isleftchild(node) node->parent&&node->parent->left==node
#define isrightchild(node) node->parent&&node->parent->right==node
// returns the Node containing the predecessor of the given value
IntBST::Node *IntBST::getPredecessorNode(int value) const{
    Node *n=getNodeFor(value, root);
    if(!n) return 0;
    if(n->left){
        n=n->left;
        while(n->right) n=n->right;
        return n;
    }
    while(isleftchild(n)) n=n->parent;
    if(n==root) return 0;
    return n->parent;
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    Node *n=getPredecessorNode(value);
    if(n) return n->info;
    return 0;
}

// returns the Node containing the successor of the given value
IntBST::Node *IntBST::getSuccessorNode(int value) const{
    Node *n=getNodeFor(value, root);
    if(!n) return 0;
    if(n->right){
        n=n->right;
        while(n->left) n=n->left;
        return n;
    }
    while(isrightchild(n)) n=n->parent;
    if(n==root) return 0;
    return n->parent;

}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    Node *n=getSuccessorNode(value);
    if(n) return n->info;
    return 0;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    Node *n=getNodeFor(value, root);
    if(!n) return 0;
    if(count()==1){
        delete root;
        root=0;
        return 1;
    }

    Node *pre=getPredecessorNode(n->info);
    while(pre){
        Node *tmp=getPredecessorNode(pre->info);
        n->info=pre->info;
        n=pre;
        pre=tmp;
        if(!(n->left||n->right)) break;//optimization: no child
    }
    if(root==n){
        root=root->right;//root doesn't have pred
        delete n;
        return 1;
    }
    printnode(n);
    if(isleftchild(n)){
        n->parent->left=n->right;
        if(n->right) n->right->parent=n->parent;
    }else n->parent->right=0;//necessary after optimization
    delete n;
    return 1;
}