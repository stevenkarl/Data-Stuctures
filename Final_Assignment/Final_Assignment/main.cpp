//
//  main.cpp
//  Final_Assignment
//
//  Created by Steven Karl on 7/16/17.
//  Copyright © 2017 Steven Karl. All rights reserved.
//

#include <iostream>
#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct MovieNode{
    int ranking;
    string title;
    int year;
    int quantity;
    bool isRed;
    MovieNode *parent;
    MovieNode *left;
    MovieNode *right;
    
    MovieNode(){};
    
    MovieNode(int in_ranking, string in_title, int in_year, int in_quantity)
    {
        ranking = in_ranking;
        title = in_title;
        year = in_year;
        quantity = in_quantity;
        // Now that we are using nil these NULL's should be overwritten in addMovieNode.
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        isRed = true;
    }
    
};

class MovieTree
{
    
public:
    MovieTree();
    virtual ~MovieTree();
    void displayMenu();
    int countMovieNodes();
    void deleteMovieNode(string title);
    void addMovieNode(int ranking, string title, int releaseYear, int quantity);
    void findMovie(string title);
    void rentMovie(string title);
    MovieNode * findMinimum(MovieNode *node);
    bool isValid();
    void DeleteAll(MovieNode * node); //use this for the post-order traversal deletion of the tree
    void printMovieInventory(MovieNode * node);
    void rbAddFixup(MovieNode * node); // called after insert to fix tree
    void leftRotate(MovieNode * x); //rotate the tree left with x as the root of the rotation
    void rbDelete(MovieNode * z); //delete a node. Call this from deleteMovieNode, the actual delete functionality happens here.
    void rightRotate(MovieNode * x); //rotate the tree right with x as the root of the rotation
    void rbDeleteFixup(MovieNode * node); //called after delete to fix the tree
    int rbValid(MovieNode * node); //check if the tree is valid, with node as the root of the tree
    int countMovieNodes(MovieNode *node); //number of unique titles in the tree
    int countLongestPath(MovieNode *node); //longest path from node to a leaf node in the tree
    MovieNode* searchMovieTree(string title);
    
protected:
    
private:

    MovieNode *root;
    MovieNode *nil;
    
    
};

//////////////////////////////////////////////

void MovieTree::leftRotate(MovieNode * x) //rotate the tree left with x as the root of the rotation
{
    MovieNode *y = x -> right; // setting y location
    x -> right = y -> left; // making y's left subtree into x's right subtree
    if(y -> left != nil)
    {
        y -> left -> parent = x;
    }
    y -> parent = x -> parent;// link x's parent to y;
    if(x -> parent == nil)
    {
        root = y;
    }
    else if( x == x -> parent -> left)
    {
        x -> parent -> left = y;
    }
    else
    {
        x-> parent -> right = y;
    }
    y -> left = x; // putting x on y's left
    x -> parent = y;
}

////////////////////////////////////////////
void MovieTree::rightRotate(MovieNode * x)
{
    MovieNode *y = x -> left; //setting y location
    x -> left = y -> right; //making y's right subtree into x's left subtree
    if(y -> right != nil)
    {
        y -> right -> parent = x;
    }
    x -> parent = y -> parent;
    if(x -> parent == nil)
    {
        root = y;
    }
    else if( x == x -> parent -> left)
    {
        x -> parent -> left = y;
    }
    else
    {
        x -> parent -> right = y;
    }
    y -> right = x;
    x -> parent = y;
}

//////////////////////////////////////////////

void MovieTree::addMovieNode(int ranking, string title, int releaseYear, int quantity)
{
    MovieNode *newNode = new MovieNode(ranking, title, releaseYear, quantity); //Creating the node that will be inserted
    newNode -> left = nil;
    newNode -> right = nil;
    MovieNode *y = nil;
    MovieNode *x = root;
    
    while(x != nil) //Reach the end of the tree where we need to insert
    {
        y = x;
        if(newNode -> title.compare(x -> title) < 0) // compare the titles
        {
            newNode = newNode -> left;//smaller go left
        }
        else
        {
            newNode = newNode -> right;//else go right
        }
        
    }
    //set the parent of the node that was inserted
    newNode -> parent = y;
    //Figure out if we are now a left or a right child or the root
    if(y == nil)
    {
        root = newNode;
    }
    else if(newNode -> title.compare(y -> title) < 0)
    {
        y -> left  = newNode;
    }
    else
    {
        y -> right = newNode;
    }
    rbAddFixup(newNode); // called after insert to fix tree
    return;
}

/////////////////////////////////////////////////////

void rbAddFixup(MovieNode *x) // called after insert to fix tree
{
    x -> left = nil;
    x -> right = nil;
    MovieNode *y = NULL;
    x -> isRed = true;
    while(x != root && x -> parent -> isRed == true)
    {
        if(x -> parent == x -> parent -> parent -> left)
        {
            y = x -> parent -> parent -> right;
            if(y -> isRed == true)                      /////////Case 1
            {
                x -> parent -> isRed  = false;          /////////Case 1
                y -> isRed = false;                     /////////Case 1
                x -> parent -> parent -> isRed = true;  /////////Case 1
                x = x -> parent -> parent;              /////////Case 1
            }
            else
            {
                if(x == x -> parent -> right)
                {
                    x = x -> parent;                    /////////Case 2
                    leftRotate(x);                      /////////Case 2
                }
                x -> parent  -> isRed = false;          /////////Case 3
                x -> parent -> parent -> isRed = true;  /////////Case 3
                rightRotate(x);                         /////////Case 3
            }
        }
        else
        {
            y  = x -> parent -> parent -> left;
            if( y -> isRed == true)
            {
                x -> parent -> isRed = false;
                y -> isRed = false;
                x -> parent -> parent -> isRed = true;
                x = x -> parent -> parent;
            }
            else
            {
                if(x == x -> parent -> left)
                {
                    x = x -> parent;
                    rightRotate(x);
                }
                x -> parent -> isRed = false;
                x -> parent -> parent -> isRed = true;
                leftRotate(x);
            }
        }
    }
    root -> isRed = false;
}

//////////////////////////////////////////////////////////////

void MovieTree::deleteMovieNode(string title)
{
    MovieNode *toDelete = searchMovieTree(title);
    rbDelete(toDelete);
    return;
}

//////////////////////////////////////////////////////////////

void MovieTree::rbDelete(string title) //delete a node. Call this from deleteMovieNode, the actual delete functionality happens here.
{
    MovieNode *movie = searchMovieTree(title);
    MovieNode *x = nil;
    bool nodeColor = movie -> isRed;
    if(movie != root)
    {
        if(movie -> left == nil && movie -> right == nil)//no children
        {
            movie -> parent -> left = nil;
            x = movie -> parent -> left;
        }
        else if(movie -> left != nil && movie -> right != nil)//two children
        {
            MovieNode *min = findMinimum(movie -> right);
            nodeColor = min -> isRed; // replace the color
            x = min -> right;
            
            if(min == movie -> right)
            {
                movie -> parent -> left = min;
                min -> parent = movie -> parent;
                min -> left = movie -> left;
                min -> left -> parent = min;
            }
            else
            {
                min -> parent -> left = min -> right;
                min -> right  -> parent = min -> parent;
                min -> parent = movie -> parent;
                movie -> parent -> left = min;
                min -> left = movie -> left;
                min -> right = movie -> right;
                movie -> right -> parent = min;
                movie -> left -> parent = min;
                min -> isRed = movie -> isRed;//replacement gets nodes color
            }
        }
        else //one child
        {
            x = movie -> left;
            movie -> parent -> left = x;
            x -> parent = movie -> parent;
        }
    }
    else
    {
        
    }
    if(nodeColor -> isRed == false)
    {
        rbDeleteFixup(x)
    }
    delete movie;
}

//////////////////////////////////////////////////////////////

void MovieTree::rbDeleteFixup(MovieNode *x) //called after delete to fix the tree
{
    MovieNode *sibling = NULL;
    while(x != root && x -> isRed == false)
    {
        if(x == x -> parent -> left)
        {
            sibling = x ->  parent -> right; //Set the sibling location for reference later
            if(sibling  -> isRed == true)
            {
                sibling -> isRed = false;
                x -> parent -> isRed = true;
                leftRotate(x -> parent);
                sibling = x -> parent -> right;
                
                if(sibling -> left -> isRed == false && sibling -> right -> isRed == false)
                {
                    sibling -> isRed = true;
                    x = x -> parent;
                }
                else if(sibling -> left -> isRed == true && sibling -> right -> isRed == false)
                {
                    sibling -> left -> isRed = false;
                    sibling -> isRed = true;
                    rightRotate(sibling);
                    sibling = x -> parent -> right;
                }
            }
            else
            {
                sibling -> isRed = x -> parent -> isRed;
                x -> parent -> isRed = false;
                sibling -> right -> isRed = false;
                leftRotate(x->parent);
                x = root;
            }
        }
        else
        {
            sibling = x -> parent -> left; //Set the sibling location for reference later
            if(sibling -> isRed == true)
            {
                sibling -> isRed = false;
                x -> parent -> isRed = true;
                rightRotate(x -> parent);
                sibling = x -> parent -> right;
                
                if(sibling -> left -> isRed == false && sibling -> right -> isRed == false)
                {
                    sibling -> isRed = true;
                    x = x -> parent;
                }
                else if(sibling -> left -> isRed == true && sibling -> right -> isRed == false)
                {
                    sibling -> left -> isRed = false;
                    sibling -> isRed = true;
                    leftRotate(sibling);
                    sibling = x -> parent -> left;
                }
            }
            else
            {
                sibling -> isRed = x -> parent -> isRed;
                x -> parent -> isRed = false;
                sibling -> left -> isRed = false;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x -> isRed = false;
    rbValid(root);
}

//////////////////////////////////////////////////////////////

void MovieTree::DeleteAll(MovieNode * node) //use this for the post-order traversal deletion of the tree
{
    if(node != nullptr)
    {
        DeleteAll(node -> left);
        DeleteAll(node-> right);
        cout << "Deleting: "<< node->title << endl;
        delete node;
    }
}

//////////////////////////////////////////////////////////////

void MovieTree::printMovieInventory(MovieNode * node)
{
    if(node == nullptr)
    {
        return;
    }
    if(node -> left != nullptr)
    {
        printMovieInventory(node -> left);
    }
    cout<<"Movie: "<<node->title<<" "<<node->quantity<<endl;
    if(node -> right != nullptr)
    {
        printMovieInventory(node -> right);
    }
    return;
}

//////////////////////////////////////////////////////////////

int MovieTree::rbValid(MovieNode * node) //check if the tree is valid, with node as the root of the tree
{
    int lh = 0;
    int rh = 0;
    
    // If we are at a nil node just return 1
    if (node == nil)
        return 1;
    
    else
    {
        // First check for consecutive red links.
        if (node->isRed)
        {
            if(node->leftChild->isRed || node->rightChild->isRed)
            {
                cout << "This tree contains a red violation" << endl;
                return 0;
            }
        }
        
        // Check for valid binary search tree.
        if ((node->leftChild != nil && node->leftChild->title.compare(node->title) > 0) || (node->rightChild != nil && node->rightChild->title.compare(node->title) < 0))
        {
            cout << "This tree contains a binary tree violation" << endl;
            return 0;
        }
        
        // Deteremine the height of let and right children.
        lh = rbValid(node->leftChild);
        rh = rbValid(node->rightChild);
        
        // black height mismatch
        if (lh != 0 && rh != 0 && lh != rh)
        {
            cout << "This tree contains a black height violation" << endl;
            return 0;
        }
        
        // If neither height is zero, incrament if it if black.
        if (lh != 0 && rh != 0)
        {
            if (node->isRed)
                return lh;
            else
                return lh+1;
        }
        
        else
            return 0;
        
    }
    
}

//////////////////////////////////////////////////////////////

int countMovieNodes(MovieNode *node) //number of unique titles in the tree
{
    int c = 1;
    if(node -> left != nullptr)
    {
        c+=countMovieNodes(node -> left);
    }
    if(node -> right != nullptr)
    {
        c+=countMovieNodes(node -> right);
    }
    return c;
}

//////////////////////////////////////////////////////////////

int MovieTree::MovieCount(MovieNode *node)
{
    int c = 0;
    if(node != nullptr)
    {
        c = countMovieNodes(node);
    }
    return c;
}

//////////////////////////////////////////////////////////////

int countLongestPath(MovieNode *node) //longest path from node to a leaf node in the tree
{
    n = MovieCount(node) + 1;
    return log2(n);
    
}

//////////////////////////////////////////////////////////////

MovieNode* MovieTree::searchMovieTree(string title)
{
    MovieNode *foundMovie = root;
    if(foundMovie == nullptr)
    {
        return nullptr;
    }
    else
    {
        while(foundMovie != nullptr)
        {
            if(foundMovie -> title.compare(title) == 0)
            {
                return foundMovie;
                break;
            }
            else if(foundMovie -> title.compare(title) < 0)
            {
                foundMovie = foundMovie -> left;
            }
            else if(foundMovie -> title.compare(title) > 0)
            {
                foundMovie = foundMovie -> right;
            }
        }
    }
    return nullptr;
}

//////////////////////////////////////////////////////////////

MovieNode* MovieTree::findMinimum(MovieNode *node)
{
    while(node != nullptr)
    {
        node = node -> left;
    }
    return node;
}

//////////////////////////////////////////////////////////////

void MovieTree::findMovie(string title)
{
    MovieNode *foundMovie = root;
    if(foundMovie == nullptr)
    {
        cout << "Movie not found." << endl;
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
            else if(foundMovie -> title.compare(title) < 0)
            {
                foundMovie = foundMovie -> left;
            }
            else if(foundMovie -> title.compare(title) > 0)
            {
                foundMovie = foundMovie -> right;
            }
        }
        if(foundMovie == nullptr)
        {
            cout << "Movie not found." <<endl;
        }
    }
}

//////////////////////////////////////////////////////////////

void MovieTree::rentMovie(string title)
{
    MovieNode *foundMovie = searchMovieTree(title);
    if(foundMovie == nullptr)
    {
        cout << "Movie not found." << endl;
    }
    if(foundMovie != nullptr)
    {
        if(foundMovie -> quantity > 0)
        {
            foundMovie -> quantity--;
            cout << "Movie has been rented." << endl;
            cout << "Movie Info:" << endl;
            cout << "===========" << endl;
            cout << "Ranking:" << foundMovie->ranking << endl;
            cout << "Title:" << foundMovie->title << endl;
            cout << "Year:" << foundMovie->year << endl;
            cout << "Quantity:" << foundMovie->quantity << endl;
        }
        if(foundMovie -> quantity == 0)
        {
            deleteMovieNode(title);
        }
    }
}

MovieTree * MovieTree::handleUserInput(MovieTree * movieTree)
{
    string choice = " ";
    int input;
    bool quit = false;
    while(quit == false){
        displayMenu();
        getline(cin, choice);
        input = stoi(choice);
        switch(input){
                
            case 1:{ // This is the case in which the user chooses 1 and wants to find a movie in the tree
                string foundMovieTitle = "";
                cout << "Enter title:" << endl;
                getline(cin, foundMovieTitle);
                movieTree -> findMovie(foundMovieTitle);
                break;
            }
                
            case 2:{ // This is the case in which the user chooses 2 and wants to rent a movie in the tree
                string rentMovieTitle = "";
                bool rentMovieFind = true;
                cout << "Enter title:" << endl;
                getline(cin, rentMovieTitle);
                movieTree -> rentMovie(rentMovieTitle);
                if(rentMovieFind == false)
                {
                    cout << "Movie not found." << endl;
                }
                break;
            }
                
            case 3:{ //This is the case in which the user chooses 3 and wants to print out the inventory
                movieTree -> printMovieInventory(movieTree -> getRoot());
                break;
            }
                
            case 4:{ // This is the case in which the user chooses 4 and wants to delete a movie from the tree
                string deleteMovieTitle = "";
                bool found = true;
                cout << "Enter title:" << endl;
                getline(cin, deleteMovieTitle);
                movieTree -> deleteMovieNode(deleteMovieTitle);
                if(found == false){
                    cout << "Movie not found." << endl;
                }
                break;
            }
                
            case 5:{ // This is the case in which the user chooses 5 and wants to know how many movie nodes there are in the tree
                int count = movieTree -> MovieCount(movieTree->getRoot());
                cout << "Tree contains: " << count << " movies." << endl;
                count = 0;
                break;
            }
                
            case 6:{ // This is the case in which the user chooses 6 and wishes to Count the longest path from root to leaf
                movieTree -> countLongestPath(movieTree -> getRoot());
                break;
            }
                
            case 7:{ // This is the case in which the user chooses 6 and wishes to quit the program
                quit = true;
                cout << "Goodbye!" << endl;
                movieTree -> DeleteAll(movieTree -> getRoot());
                break;
            }
                
        }
        
    }
    return movieTree;
}

////////////////////////////////////////////////////

void MovieTree::displayMenu()
{
    cout << "======Main Menu======" << endl;
    cout << "1. Find a movie" << endl;
    cout << "2. Rent a movie" << endl;
    cout << "3. Print the inventory" << endl;
    cout << "4. Delete a movie" << endl;
    cout << "5. Count the movies" << endl;
    cout << "6. Count the longest path" << endl;
    cout << "7. Quit" << endl;
}

/////////////////////////////////////////////////////
//Constructor and destructor
MovieTree::MovieTree()
{
    root = NULL;
    nil = new MovieNode(0, "", 0, 0);
    root = nil;
    nil->isRed = false;
    nil->left = nil->right = nil;
}

MovieTree::~MovieTree()
{
    DeleteAll(this->root);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}