#include <vector>
using namespace std;
#define DEBUG
#include "intbst.cpp"
#ifndef PRINT
#define PRINT
#ifdef DEBUG
void print(){std::cout<<"\n";}
template<typename T1, typename ...T>
inline void print(const T1&first, const T&... t){
    std::cout<<first<<" ";
    print(t...);
}
#else
void print(){}
template<typename T1, typename ...T>
inline void print(const T1&first, const T&... t){
}
#endif
#endif
void printpredes(IntBST& t,vector<int>&arr){
    for(int n:arr) print(n, t.getPredecessor(n), t.getSuccessor(n));
}
int main(){
    vector<int>arr={5,3,-4,7,-12,13,18,9,0,-7};
    //           5 3 -4 7 -12 13 18 9 0 -7
    //                   -7 3 5 7 9 13 18
    IntBST bst1;
    for(int n:arr) bst1.insert(n);
    bst1.printInOrder();
    print();

    bst1.remove(-7);
    bst1.printInOrder();
    print();
    printpredes(bst1,arr);


    print("end");
    return 0;
}
/*

*/