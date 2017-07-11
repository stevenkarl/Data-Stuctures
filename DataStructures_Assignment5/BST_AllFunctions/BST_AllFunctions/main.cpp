//
//  main.cpp
//  BST_AllFunctions
//
//  Created by Steven Karl on 7/10/17.
//  Copyright © 2017 Steven Karl. All rights reserved.
//

#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

////////////////////////////////////
// Finding the minimum inorder to use for the delete
Node* MovieTree::findMinimum(MovieNode *node)
{
    while(node-> left !=nullptr)
    {
        node = node -> left;
    }
    return node;
}
Node* MovieTree::findMinimum()
{
    return findMinimum(root);
}
///////////////////////////////////
//Printing the movies using inOrder printing
void MovieTree::printInOrder(MovieNode *node)
{
    if(node == nullptr)
    {
        return;
    }
    if(node -> left != nullptr)
    {
        printInOrder(node -> left);
    }
    cout << node -> key << endl;
    if(node -> right != nullptr)
    {
        printInOrder(node -> right);
    }
    return;
}
///////////////////////////////////
//This is the function for adding the nodes to the bst....So building the BST
void MovieTree::addMovieNode(int ranking, string title, int releaseYear, int quantity)
{
    MovieNode *newNode = new MovieNode(ranking, title, releaseYear, quantity);
    //first the case in which the BST is empty
    if(root == nullptr)
    {
        root = newNode;
    }
    else
    {
        MovieNode *index = root;
        MovieNode *index_parent = root;
        while(index != nullptr)
        {
            index_parent = index; // So when the nullptr is reached, cannot access parent
            if(newNode -> title.compare(title) > 0)
            {
                index = index -> left;
            }
            else
            {
                index = index -> right;
            }
        }
        if(value < index_parent -> key)
        {
            index -> parent -> left = newNode;
            newNode -> parent = index_parent;
        }
        else
        {
            index -> parent -> right = newNode;
            newNode -> parent = index_parent;
        }
    }

}
//////////////////////////////////
//This is the funciton to find a movie node
void MovieTree::findMovie(string title)
{
    Movienode *foundMovie = root;
    if(foundMovie == nullptr)
    {
        cout << "Movie not found" << endl;
    }
    else
    {
        while(foundMovie != nullptr)
        {
            if(foundMovie -> title.compare(title) == 0)
            {
                cout << "Movie Info:" << endl;
                cout << "===========" << endl;
                cout << "Ranking:" << foundMovie->ranking << endl;
                cout << "Title:" << foundMovie->title << endl;
                cout << "Year:" << foundMovie->year << endl;
                cout << "Quantity:" << foundMovie->quantity << endl;
                break;
            }
            else if(foundMovie -> title.compare(title) > 0)
            {
                foundMovie = foundMovie -> left;
            }
            else if(foundMovie -> title.compare(title) < 0)
            {
                foundMovie = foundMovie -> right;
            }
        }
        if(foundMovie == nullptr)
        {
            cout << "Movie not found" << endl;
        }
    }
}
///////////////////////////////////
//This is the function to find the movie but a different way recursively
MovieNode* MovieTree::findMovie(MovieNode *node, int searchKey)
{
    if(node == nullptr)
    {
        return nullptr;
    }
    if(node -> key = searchKey)
    {
        return node;
    }
    else if(node -> key > searchKey)
    {
        return findMovie(node -> left, searchKey);
    }
    else
    {
        return findMovie(node -> right, searchKey);
    }
}
MovieNode* MovieTree::find(int searchKey)
{
    return findMovie(root, searchKey);
}
///////////////////////////////////
//This is the function to rent a movie from the inventory
void MovieTree::rentMovie(string title)
{
    MovieNode *rentedMovie = root;
    if(rentedMovie == nullptr)
    {
        cout << "Movie not Found" << endl;
    }
    else
    {
        while(rentedMovie != nullptr)
        {
            if(rentedMovie -> title.compare(title) == 0)
            {
                //Movie is still in stock
                if(rentedMovie -> quantity > 0)
                {
                    rentedMovie -> quantity--;
                    cout << "Movie has been rented." << endl;
                    cout << "Movie Info:" << endl;
                    cout << "===========" << endl;
                    cout << "Ranking:" << rentedMovie->ranking << endl;
                    cout << "Title:" << rentedMovie->title << endl;
                    cout << "Year:" << rentedMovie->year << endl;
                    cout << "Quantity:" << rentedMovie->quantity << endl; 
                    break;
                }
                else if(rentedMovie -> quantity == 0)
                {
                    //Movie is out of stock
                    cout << "Movie out of Stock." << endl;
                    break;
                }
            }
            else if(rentedMovie -> title.compare(title) > 0)
            {
                rentedMovie = rentedMovie -> left;
            }
            else if(rentedMovie -> title.compare(title) < 0)
            {
                rentedMovie = rentedMovie -> right;
            }
        }
        if(rentedMovie == nullptr)
        {
            cout << "Movie not found." << endl;
        }
    }
    return;
}
//////////////////////////////////
//
void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity){
    MovieNode * newNode = new MovieNode(ranking, title, releaseYear, quantity);
    newNode->left = NULL;
    newNode->right = NULL;
    MovieNode * index = root;
    MovieNode * index_parent = NULL;
    
    if(ranking == 1)
    {
        root = newNode;
        root->parent = NULL;
        root->left = NULL;
        root->right = NULL;
        return;
    }
    else
    {
        while(index != NULL){
            index_parent = index;
            if(newNode->title.compare(index->title)<0){
                index = index->left;
            }
            else{
                index = index->right;
            }
        }
        newNode->parent = index_parent;
        if(newNode->title.compare(index_parent->title)<0)
        {
            newNode->parent->left = newNode;
        }
        else
        {
            newNode->parent->right = newNode;
        }
        return;
    }
}
/////////////////////////////////////////////

//This is the function to delete

void deleteMovie(MovieNode *root, string title)
{
    MovieNode *movie = search(title);
    if(movie != NULL)
    {
        if((moive->left == nullptr)&&(movie->right == nullptr))
        {
            if(movie -> parent -> left == movie)
            {
                movie -> parent -> left = nullptr;
            }
            else if(movie -> parent -> right == movie)
            {
                movie -> parent -> right
            }
        }
    }
}
/////////////////////////////////////////

void BSTree::deleteNode(int value){
    Node *node = search(value);
    if (node != root){
        if(node->left == nullptr && node->right == nullptr){//no children
            if (node->parent->left == node){//node is a left child
                node->parent->left = nullptr;
            }else{ //node is a right child
                node->parent->right = nullptr;}
        }else if (node->left != nullptr && node->right != nullptr){//two children
            Node *min = treeMinimum(node->right);//replacement min right subtree
            if (min == node->right){//replacement node rightChild
                if (node->parent->left == node){//node is a leftChild
                    node->parent->left = min;
                    min->parent = node->parent;
                    min->left = node->left;
                    min->left->parent = min;
                }else{//node is a rightChild
                    node->parent->right = min;//connecting 45 to 90
                    min->parent = node->parent;//connecting 90 to 45
                    min->left = node->left; //shifting 54
                    min->left->parent = min;//shilfting 54
                }
            }else {//replacement is not the rightChild of node e.g. 12
                if (node->parent->left == node){//node is leftChild
                    min->parent->left = min->right;//detaching min
                    //linking min rightChild, next should have a conditional
                    if (min->right!=nullptr) min->right->parent = min->parent;
                    min->parent = node->parent;//linking min to parent
                    node->parent->left = min;//linking parent to min
                    min->left = node->left;//linking min to left child
                    node->left->parent = min;////linking left child to min
                    min->right = node->right;//linking min to right child
                    node->right->parent = min;//linking right child to min
                }else{//node is rightChild e.g. 56 with 60 (not in the example)
                    min->parent->left = min->right;//detaching min from parent
                    //linking min rightChild, next should have a conditional
                    if (min->right != nullptr) min->right->parent = min->parent;
                    min->parent = node->parent;//linking min to parent
                    node->parent->right = min;//linking parent to min
                    min->left = node->left;//linking min to left child 54
                    node->left->parent = min;////linking left child 54 to min
                    min->right = node->right;//linking min to right child
                    node->right->parent = min;//linking right child to min
                }
            }
        }else {//one child
            if (node->parent->left == node){//node is leftChild
                if (node->left != nullptr){//node has a leftChild
                    node->left->parent = node->parent;
                    node->parent->left = node->left;
                }else{//node has a rightChild
                    node->right->parent = node->parent;
                    node->parent->left = node->left;
                }
            }else{//node is rightChild
                if (node->left!=nullptr){//node has a left child
                    node->left->parent = node->parent;//linking leftChild
                    node->parent->right = node->left;//detaching node
                }else{//node has a rightChild
                    node->right->parent = node->parent;//linking rightChild
                    node->parent->right = node->right;//detaching node
                }
            }
        }
    }else{
        //repeat cases of 0, 1, or 2 children
        //replacement node is the new root
        //parent of replacement is nullptr
        
    }
    delete node;
}


