//
//  main.cpp
//  DataStructures_Assignment6
//
//  Created by Steven Karl on 7/14/17.
//  Copyright © 2017 Steven Karl. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <sstream>

using namespace std;

struct MovieNode
{
    int ranking;
    string title;
    int year;
    int quantity;
    bool isRed;
    MovieNode *right;
    MovieNode *left;
    MovieNode *parent;
    
    MovieNode(){};
    
    MovieNode(int in_ranking, string in_title, int in_year, int in_quantity)
    {
        ranking = in_ranking;
        title = in_title;
        year = in_year;
        quantity = in_quantity;
        isRed = true;
    }
};

class MovieTree
{
    
public:
    MovieTree();
    virtual ~MovieTree();
    void printMovieInventory();
    int countMovieNodes();
    void deleteMovieNode(string title);
    void addMovieNode(int ranking, string title, int releaseYear, int quantity);
    void findMovie(string title);
    void rentMovie(string title);
    bool isValid();
    int countLongestPath();
    MovieNode* findMinimum(MovieNode *node);
    MovieTree * handleUserInput(MovieTree * movieTree);
    void displayMenu();
    MovieNode* getRoot()
    {
        return root;
    }
    void rightRotate(MovieNode * x); //rotate the tree right with x as the root of the rotation
    
protected:
    
private:
    void DeleteAll(MovieNode * node); //use this for the post-order traversal deletion of the tree
    void printMovieInventory(MovieNode * node);
    void rbAddFixup(MovieNode * node); // called after insert to fix tree
    void leftRotate(MovieNode * x); //rotate the tree left with x as the root of the rotation
    void rbDelete(MovieNode * z); //delete a node. Call this from deleteMovieNode, the actual delete functionality happens here.
    
    void rbDeleteFixup(MovieNode * node); //called after delete to fix the tree
    void rbTransplant(MovieNode * u, MovieNode * v); //replace node u in tree with node v. Your solution doesn't necessarily need to use this method
    int rbValid(MovieNode * node); //check if the tree is valid, with node as the root of the tree
    int countMovieNodes(MovieNode *node); //number of unique titles in the tree
    int countLongestPath(MovieNode *node); //longest path from node to a leaf node in the tree
    MovieNode* searchMovieTree(MovieNode * node, string title);
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
    MovieNode *x = getRoot();
    
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
    
}

//////////////////////////////////////////////////////////////

void MovieTree::rbDelete(MovieNode * z) //delete a node. Call this from deleteMovieNode, the actual delete functionality happens here.
{
    
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
            if(node -> left -> isRed || node -> right -> isRed)
            {
                cout << "This tree contains a red violation" << endl;
                return 0;
            }
        }
        
        // Check for valid binary search tree.
        if ((node->left != nil && node -> left -> title.compare(node->title) > 0) || (node->right != nil && node->right->title.compare(node->title) < 0))
        {
            cout << "This tree contains a binary tree violation" << endl;
            return 0;
        }
        
        // Deteremine the height of let and right children.
        lh = rbValid(node->left);
        rh = rbValid(node->right);
        
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
    MovieNode *rentedMovie = searchMovieTree(title);
    if(rentedMovie == nullptr)
    {
        cout << "Movie not found." << endl;
    }
    if(rentedMovie != nullptr)
    {
        if(rentedMovie -> quantity > 0)
        {
            rentedMovie -> quantity--;
            cout << "Movie has been rented." << endl;
            cout << "Movie Info:" << endl;
            cout << "===========" << endl;
            cout << "Ranking:" << foundMovie->ranking << endl;
            cout << "Title:" << foundMovie->title << endl;
            cout << "Year:" << foundMovie->year << endl;
            cout << "Quantity:" << foundMovie->quantity << endl;
        }
        if(rentedMovie -> quantity == 0)
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
                movieTree -> deleteAll(movieTree -> getRoot());
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
}

MovieTree::~MovieTree()
{
    deleteAll(this->root);
}

int main(int argc, const char * argv[]) {

    MovieTree * movieTree = new MovieTree();
    int itemCount = 1;
    string fName = "";
    ifstream inFile;
    string uniqueLine = "";
    string uniqueWord = "";
    getline(cin, fName);
    inFile.open(fName);
    if(!inFile.is_open())
    {
        cout << "File not open" << endl;
        return 0;
    }
    if(inFile.is_open())
    {
        //Get the individual line from the file
        while(getline(inFile, uniqueLine))
        {
            stringstream ss(uniqueLine);
            itemCount = 1;
            int ranking = 0;
            string title = "";
            int year = 0;
            int quantity = 0;
            
            //Get the individual item from the line
            while(getline(ss, uniqueWord, ','))
            {
                switch(itemCount){
                    case 1:
                        ranking = stoi(uniqueWord);
                        break;
                        
                    case 2:
                        title = uniqueWord;
                        break;
                        
                    case 3:
                        year = stoi(uniqueWord);
                        break;
                        
                    case 4:
                        quantity = stoi(uniqueWord);
                        break;
                        
                    default:
                        break;
                }
                itemCount++;
            }
            movieTree->addMovieNode(ranking, title, year, quantity);
        }
    }
    inFile.close();
    movieTree = handleUserInput(movieTree);
    delete(movieTree);
    return 0;

}
