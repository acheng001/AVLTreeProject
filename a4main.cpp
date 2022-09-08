// Basic test program for AVL Tree
// Author: Angus Cheng
// Date: July 13, 2022
// This is a very bad and basic test so dont trust it
#include <vector>
#include <iostream>
#include "AVLTree.h"
using std::cout;
using std::endl;
using std::vector;


void a4marking();
/*
template <class K, class V>
bool checkAVLTree(const AVLTree<K, V>& tree);
*/
int main()
{
    a4marking();
    cout << endl;
}

void a4marking()
{
    //AVLTree<int, int> aspen;
    AVLTree <float,int> a1;
    /*checkAVLTree<int, int>(aspen);*/

    // Method return values
   // bool success = aspen.insert(1, 2);
   /*
    cout<<aspen.insert(13, 10)<<endl; // WORKS PERFECTLY FOR JUST INSERTING ONE NODE
    //cout<<aspen.search(5)<<endl;
    cout<<aspen.insert(10, 2)<<endl;
    cout<<aspen.insert(15, 69)<<endl;
    cout<<aspen.insert(5, 9)<<endl;
    cout<<aspen.insert(11, 8)<<endl;
    cout<<aspen.insert(16, 7)<<endl;
    cout<<aspen.insert(4, 6)<<endl;
    cout<<aspen.insert(8, 5)<<endl;
    cout<<aspen.insert(3, 0)<<endl;
    
    cout<<aspen.insert(30, 2)<<endl;
    cout<<aspen.insert(5, 3)<<endl;
    cout<<aspen.insert(35, 4)<<endl;
    cout<<aspen.insert(32, 6)<<endl;
    cout<<aspen.insert(40, 7)<<endl;
    cout<<aspen.insert(45, 8)<<endl;
    */
   /*
    cout<<a1.insert(20, 8)<<endl;
    cout<<a1.insert(10, 7)<<endl;
    cout<<a1.insert(15, 9)<<endl;
    */
    /*
    a1.insert(20, 1);
    a1.insert(10, 2);
    a1.insert(40, 3);
    a1.insert(5, 4);
    a1.insert(15, 5);
    a1.insert(50, 6); // Remove this node
    cout<<a1.insert(12, 7)<<endl;
    cout<<a1.insert(18, 8)<<endl;
    cout<<a1.remove(50)<<endl;
    */
    
    a1.insert(20.1, 1);
    a1.insert(10.1, 2);
    a1.insert(40.1, 3);
    a1.insert(5.1, 4);
    a1.insert(15.1, 5);
    a1.insert(50.1, 6); // Remove this node
    cout<<a1.insert(12.1, 7)<<endl;
    cout<<a1.insert(18.1, 8)<<endl;
    cout<<a1.remove(50.1)<<endl;
    
    //AVLTree tempTree = aspen;
    //vector<int> k1 = aspen.keys();
    //for(int i = 0; i < aspen.size(); i++){
       // cout<<"Vector: "<<k1[i]<<endl;
    //}
    //cout<<aspen.remove(11)<<endl;
    //cout<<"Root: "<<aspen.groot()<<endl;
    //cout<<aspen.insert(20,80)<<endl;
    
    
    AVLTree <float, int>a2(a1);
    AVLTree <float,int> a3 = a1;
    vector<float> v1 = a1.keys();
    vector<float> v2 = a2.keys();
    vector<float> v3 = a3.keys();
    
    
    for(int i = 0; i < a3.size(); i++){
        cout<<"V3: "<<v3[i]<<endl;
    }

    for(int i = 0; i < a2.size(); i++){
        cout<<"V2: "<<v2[i]<<endl;
    }

    for(int i = 0; i < a1.size(); i++){
        cout<<"V1: "<<v1[i]<<endl;
    }
    
    //cout<<aspen.search(3)<<endl;
    
    cout<<"Finished"<<endl;
}
    /*
    success = aspen.remove(1);
    int result = aspen.search(1);
    vector<int> v2 = aspen.values();
    vector<int> k1 = aspen.keys();
    AVLTree<int, int> larch(aspen);
    aspen = larch;

    cout << endl << "end a4 test" << endl;

}

template <class K, class V>
bool checkAVLTree(const AVLTree<K, V>& tree)
{
    AVLTreeNode<int, int>* nd = (AVLTreeNode<int, int>*)tree.getRoot();
    cout << "height = " << nd->height << endl;

    return false;
}
*/