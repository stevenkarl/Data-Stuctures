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
        void printInOrder(MovieNode *node);
        MovieTree *buildBst(string filename);
        void printEach(MovieNode *node);
        void addMovieNode(int ranking, string title, int releaseYear, int quantity);
        void findMovie(string title);
        MovieNode *search(string title);
        void rentMovie(string title);
        void deleteMovie(string title);
        int getMovieCount(MovieNode *node);
        void deleteAll(MovieNode *node)
        {
            if(node != nullptr)
            {
                deleteAll(node->left);
                deleteAll(node->right);
                cout << "Deleting: "<< node->title << endl;
                delete node;
            }
        }
        MovieNode* findMinimum(MovieNode *node);
        MovieNode* getRoot()
        {
            return root;
        }
    
    private:
        MovieNode *root;
   
};

MovieTree * handleUserInput(MovieTree * movieTree);
void displayMenu();

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

MovieNode *MovieTree::search(string title)
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
            else if(foundMovie -> title.compare(title) > 0)
            {
                foundMovie = foundMovie -> left;
            }
            else if(foundMovie -> title.compare(title) < 0)
            {
                foundMovie = foundMovie -> right;
            }
        }
    }
    return foundMovie;
}
void MovieTree::rentMovie(string title)
{
    MovieNode *rentedMovie = root;
    if(rentedMovie == nullptr)
    {
        cout << "Movie not found." << endl;
    }
    else
    {
        while(rentedMovie != nullptr)
        {
            if(rentedMovie -> title.compare(title) == 0)
            {
                //Movie is then still in stock
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
                    //Movie is not in stock
                    cout << "Movie out of stock." << endl;
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
void MovieTree::deleteMovie(string title)
{
    MovieNode  *movie = search(title);
    if(movie != nullptr)
    {
        if((movie -> left == nullptr)&&(movie -> right == nullptr))
        {
            if(movie -> parent -> left == movie)
            {
                movie -> parent -> left = nullptr;
            }
            else if(movie -> parent -> right == movie)
            {
                movie -> parent -> right = nullptr;
            }
            delete movie;
        }
        else if((movie->left != nullptr)&&(movie -> right == nullptr))
        {
            if(movie -> parent -> left == movie)
            {
                movie -> parent -> left = movie -> left;
                movie -> left -> parent = movie -> parent;
            }
            else if(movie -> parent -> right == movie)
            {
                movie -> parent -> right = movie -> right;
                movie -> right -> parent = movie -> parent;
            }
            delete movie;
        }
        else if((movie -> left == nullptr)&&(movie -> right != nullptr))
        {
            if(movie -> parent -> left == movie)
            {
                movie -> parent -> left = movie -> right;
                movie -> right -> parent = movie -> parent;
            }
            else if(movie -> parent -> right == movie)
            {
                movie -> parent -> right = movie -> right;
                movie -> right -> parent = movie -> parent;
            }
            delete movie;
        }
        else if((movie -> left != nullptr)&&(movie -> right != nullptr))
        {
            MovieNode *replace = findMinimum(movie->right);
            MovieNode *temp = new MovieNode(replace -> ranking, replace -> title, replace-> year, replace -> quantity);
            
            deleteMovie(replace -> title);
            
            movie -> title = temp -> title;
            movie -> ranking = temp -> ranking;;
            movie -> year = temp -> year;
            movie -> quantity = temp -> quantity;
            
            delete temp;
        }
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




MovieTree::MovieTree(){
    root = NULL;
}

MovieTree::~MovieTree(){}

int main(int argc, const char * argv[]) {
    //if(argc == 1)
    //{
     //   cout << "Need to input text file" << endl;
    //    return -1;
    //}
    MovieTree * movieTree = new MovieTree();
    int itemCount = 1;
    string fName = "";
    ifstream inFile;
    string uniqueLine = "";
    string uniqueWord = "";
    getline(cin, fName);
    //inFile.open(argv[1]);
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
                movieTree -> printInOrder(movieTree->getRoot());
                break;
            }
                
            case 4:{ // This is the case in which the user chooses 4 and wants to delete a movie from the tree
                string deleteMovieTitle = "";
                bool found = true;
                cout << "Enter title:" << endl;
                getline(cin, deleteMovieTitle);
                movieTree -> deleteMovie(deleteMovieTitle);
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
