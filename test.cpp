#define DEBUG
#include "intbst.cpp"

int main(){
    int arr[10]={5,3,-4,7,-12,13,18,9,0,-7};
    IntBST bst1;
    for(int n:arr) bst1.insert(n);
    bst1.printInOrder();
    print();

    bst1.printPreOrder();
    print();
    bst1.printPostOrder();
    print();
    for(int n:arr){
        print(n, bst1.getPredecessor(n), bst1.getSuccessor(n));
    }
    print();
    print();
    bst1.remove(-12);
    bst1.printInOrder();
    print();
    bst1.printPreOrder();
    print();
    bst1.printPostOrder();
    print();
    print("end");
}
/*
            64
     8            128
  4    32             512
      16           256


*/