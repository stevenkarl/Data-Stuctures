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
    if(node -> left != nullptr)
    {
        printInOrder(node -> left);
    }
    cout << node -> key << endl;
    if(node -> right != nullptr)
    {
        printInOrder(node -> right);
    }
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
            if(value < index-> key)
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

}
//////////////////////////////////
//
void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity){
    MovieNode * tmp = new MovieNode(ranking, title, releaseYear, quantity);
    tmp->leftChild = NULL;
    tmp->rightChild = NULL;
    MovieNode * child = root;
    MovieNode * parent = NULL;
    
    if(ranking == 1)
    {
        root = tmp;
        root->parent = NULL;
        root->leftChild = NULL;
        root->rightChild = NULL;
        return;
    }
    else
    {
        while(child != NULL){
            parent = child;
            if(tmp->title.compare(child->title)<0){
                child = child->leftChild;
            }
            else{
                child = child->rightChild;
            }
        }
        tmp->parent = parent;
        if(tmp->title.compare(parent->title)<0)
        {
            tmp->parent->leftChild = tmp;
        }
        else
        {
            tmp->parent->rightChild = tmp;
        }
        return;
    }
}

