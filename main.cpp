#include <iostream>
#include <cstdlib>
#include "BST.cpp"
using namespace std;

int main(){
    int input;
    int treekeys[16] = {50,76, 21, 4, 32, 64, 15,52, 14, 100, 83, 2, 3, 70, 87, 80};

    BST myTree;

    for(int i = 0; i < 16; i++){
        myTree.Addleaf(treekeys[i]);
    }

    cout << "Priniting in order" << endl;

    myTree.PrintInOrder();
    cout << endl;

    myTree.PrintChildren(myTree.ReturnRootKey()); 

    cout << "The smallest value is " <<  myTree.FindSmallest() << endl;

    cout << "Enter a key value to delete. Enter -1 to stop process" << endl;

    while(input != -1){
        cout << "\nDelete Node: ";
        cin >> input;
        if(input != -1){
            myTree.RemoveNode(input);
            myTree.PrintInOrder();
            cout << endl;
        }
    }
    return 0;
}