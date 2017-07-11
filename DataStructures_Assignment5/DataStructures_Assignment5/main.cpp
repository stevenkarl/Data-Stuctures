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
    MovieNode *rightChild;
    MovieNode *leftChild;
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
        void getMovieCount();
        MovieNode* findMinimum(MovieNode *node);
    
    private:
        MovieNode *root;
        void printMovieInventory(MovieNode * node);
        void postDelete(MovieNode * node );
};

MovieTree * handleUserInput(MovieTree * movieTree);
void displayMenu();
void MovieTree::printMovieInventory(){};
void MovieTree::printMovieInventory(MovieNode * node){};
void MovieTree::addMovieNode(int ranking, string title, int releaseYear, int quantity){};
void MovieTree::findMovie(string title){};
void MovieTree::rentMovie(string title){};
void MovieTree::deleteMovie(MovieNode *root, string title){};
void MovieTree::getMovieCount(){};
MovieNode* MovieTree::findMinimum(MovieNode *node);
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

MovieTree* handleUserInput(MovieNode *movieTree)
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
                movieTree -> deleteMovie(deleteMovieTitle);
                if(found == false){
                    cout << "Movie not found." << endl;
                }
                break;
            }
                
            case 5:{ // This is the case in which the user chooses 5 and wants to know how many movie nodes there are in the tree
                movieTree -> countMovieNodes();
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
