//
//  main.cpp
//  DataStructures_Assignment5
//
//  Created by Steven Karl on 7/10/17.
//  Copyright © 2017 Steven Karl. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cstddef>
using namespace std;

struct MovieNode
{
    int ranking;
    string title;
    int year;
    int quantity;
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
    }
};

class MovieTree
{
    public:
        MovieTree();
        ~MovieTree();
        void printMovieInventory();
        void printEach(MovieNode *node);
        void addMovieNode(int ranking, string title, int releaseYear, int quantity);
        void findMovie(string title);
        void rentMovie(string title);
        void deleteMovie(MovieNode *root, string title);
        int getMovieCount(MovieNode *node);
        MovieNode* findMinimum(MovieNode *node);
        MovieNode* getRoot()
        {
            return root;
        }
    
    private:
        MovieNode *root;
        void printInOrder(MovieNode *node);
        void postDelete(MovieNode *node);
        void deleteAll(MovieNode *node);
   
};

MovieTree * handleUserInput(MovieTree * movieTree);
void displayMenu();
void MovieTree::printMovieInventory(){};

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
    cout<<"Movie: "<<node->title<<" "<<node->quantity<<endl;
    if(node -> right != nullptr)
    {
        printInOrder(node -> right);
    }
    return;
}

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
            cout << "Movie not found." << endl;
        }
    }

}
void MovieTree::rentMovie(string title){};
void MovieTree::deleteMovie(MovieNode *root, string title){};
void MovieTree::deleteAll(<#MovieNode *node#>)
{
    if(node != nullptr)
    {
        deleteAll(node->left);
        deleteAll(node->right);
        cout << "Deleting: "<< node->title << endl;
        delete node;
    }
}

int MovieTree::getMovieCount(MovieNode *node)
{
    static int c = 1;
    if(node == nullptr)
    {
        return 0;
    }
    if(node -> left != nullptr)
    {
        getMovieCount(node -> left);
        c++;
    }
    if(node -> right != nullptr)
    {
        getMovieCount(node -> right);
        c++;

    }
    return c;
}
MovieNode* MovieTree::findMinimum(MovieNode *node)
{
    while(node-> left !=nullptr)
    {
        node = node -> left;
    }
    return node;
}
void MovieTree::postDelete(MovieNode * node){};




MovieTree::MovieTree(){
    root = NULL;
}

MovieTree::~MovieTree(){}

int main(int argc, const char * argv[]) {
    if(argc == 1)
    {
        cout << "Need to input text file" << endl;
        return -1;
    }
    MovieTree * movieTree = new MovieTree();
    int itemCount = 1;
    ifstream inFile;
    string uniqueLine = "";
    string uniqueWord = "";
    inFile.open(argv[1]);
    if(inFile.is_open())
    {
        //Get the individual line from the file
        while(getline(inFile, uniqueLine))
        {
            stringstream ss(uniqueLine);
            itemCount = 1;
            int ranking;
            string title;
            int year;
            int quantity;
            
            //Get the individual item from the line
            while(getline(ss, uniqueWord))
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


void displayMenu()
{
    cout << "======Main Menu======" << endl;
    cout << "1. Find a movie" << endl;
    cout << "2. Rent a movie" << endl;
    cout << "3. Print the inventory" << endl;
    cout << "4. Delete a movie" << endl;
    cout << "5. Count the movies" << endl;
    cout << "6. Quit" << endl;
}

MovieTree* handleUserInput(MovieTree *movieTree)
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
                cout << "Enter title:" << endl;
                getline(cin, rentMovieTitle);
                movieTree -> rentMovie(rentMovieTitle);
                break;
            }
                
            case 3:{ //This is the case in which the user chooses 3 and wants to print out the inventory
                movieTree -> printMovieInventory();
                break;
            }
                
            case 4:{ // This is the case in which the user chooses 4 and wants to delete a movie from the tree
                string deleteMovieTitle = "";
                bool found = true;
                cout << "Enter title:" << endl;
                getline(cin, deleteMovieTitle);
                movieTree -> deleteMovie(movieTree->getRoot(), deleteMovieTitle);
                if(found == false){
                    cout << "Movie not found." << endl;
                }
                break;
            }
                
            case 5:{ // This is the case in which the user chooses 5 and wants to know how many movie nodes there are in the tree
                movieTree -> getMovieCount(movieTree->getRoot());
                break;
            }
                
            case 6:{ // This is the case in which the user chooses 6 and wishes to quit the program
                quit = true;
                cout << "Goodbye!" << endl;
                break;
            }
                
        }
        
    }
    return movieTree;
}
