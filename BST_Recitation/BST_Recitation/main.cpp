//
//  main.cpp
//  BST_Recitation
//
//  Created by Steven Karl on 7/9/17.
//  Copyright © 2017 Steven Karl. All rights reserved.
//

#include <iostream>
using namespace std;

bool sameValueTree(TreeNode *node1, TreeNode *node2, int *& array1, int *& array2 )
{
    int countTree1 = 0;
    int countTree2 = 0;
    for(int i = 0; i < 10; i++){
        if(node1 -> left != nullptr)
        {
            sameValueTree(node1->left, node2, array1, array2);
        }
        array1[i] = node1 -> key; //add to the array1
        countTree1++;
        if(node1 -> right != nullptr)
        {
            sameValueTree(node1->right, node2, array1, array2);
        }
    }
    for(int j = 0; j < 10; j++){
        if(node2 -> left != nullptr)
        {
            sameValueTree(node1, node2->left, array1, array2);
        }
        array2[j] = node2 -> key; //add to the array2
        countTree2++;
        if(node2 -> right != nullptr)
        {
            sameValueTree(node1, node2->right, array1, array2);
        }
    }
    //compare the two arrays
    for(int p = 0; p < countTree1; p++){
        for(int q = 0; q < countTree2; q++){
            if(array1[p] == array2[q])
            {
                return true;
                cout << array1[p] << endl;
                cout << array2[q] << endl;
            }
            else{
                return false;
            }
        }
    }
}



int main(int argc, const char * argv[]) {
    
    return 0;
}
