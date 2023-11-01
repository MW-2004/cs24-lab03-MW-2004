// intbst.cpp
// Implements class IntBST
// Marcus Wu, 10 31 2023
#include "intbst.h"
#include <iostream>
using std::cout;
#ifdef DEBUG
template<typename T>
inline void print(const T&first){
    std::cout<<first<<"\n";
}
template<typename T1, typename ...T>
inline void print(const T1&first, const T&... t){
    std::cout<<first<<" ";
    print(t...);
}
void print(){std::cout<<"\n";}
#else
template<typename T>
inline void print(const T&first){
}
template<typename T1, typename ...T>
inline void print(const T1&first, const T&... t){
}
void print(){}
#endif

// constructor sets up empty tree
IntBST::IntBST() { 
    root=0;
}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
    root=0;//defensive
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if(!n) return;
    clear(n->left);
    clear(n->right);
    delete n;
}
// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if(!root){
        root=new Node(value);
        return 1;
    }
    return insert(value,root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    int v=n->info;
    if(value==n->info) return 0;
    if(value<v){
        if(!n->left){
            n->left=new Node(value);
            n->left->parent=n;
            return 1;
        }
        return insert(value, n->left);
    }
    if(!n->right){
        n->right=new Node(value);
        n->right->parent=n;
        return 1;
    }
    return insert(value, n->right);
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
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
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
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node *n=getNodeFor(value, root);
    if(!n) return 0;
    if(n->left){
        Node *tmp=n->left;
        while(tmp->right) tmp=tmp->right;
        return tmp;
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
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node *n=getNodeFor(value, root);
    if(!n) return 0;
    if(n->right){
        Node *tmp=n->right;
        while(tmp->left) tmp=tmp->left;
        return tmp;
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
    if(count()==1){
        delete root;
        root=0;
        return true;
    }
    
    Node *n=getNodeFor(value, root);
    print(n);
    if(!n) return 0;
    Node *pre=getPredecessorNode(n->info);
    while(pre){
        //print("in",pre->info,pre->parent->info);
        Node *tmp=getPredecessorNode(pre->info);
        n->info=pre->info;
        n=pre;
        pre=tmp;
        if(!(n->left||n->right)) break;
    }
    if(root==n){
        root=root->right;//root doesn't have pred
        delete n;
        return 1;
    }
    if(isleftchild(n)) n->parent->left=0;
    else n->parent->right=0;
    delete n;
    return 1;
    printPreOrder();
    cout<<"   ";
    printPostOrder();
    cout<<"\n";
}
#undef isleftchild
#undef isrightchild