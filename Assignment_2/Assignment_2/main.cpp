//
//  main.cpp
//  Assignment_2
//
//  Created by Steven Karl on 6/15/17.
//  Copyright © 2017 Steven Karl. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include <cstddef>
using namespace std;


struct wordItem{
    string word;
    int count;

};

int arrayDoubling(int uniqueWordCount, int arraySize, wordItem *uniqueWords, int arrayDoublingCount){
    wordItem *tempWords;
    if(uniqueWordCount == arraySize){
        tempWords = new wordItem[2*arraySize];
        
        for (int i = 0; i < arraySize; i++) {
            tempWords[i] = uniqueWords[i];
        }
        delete[] uniqueWords;
        uniqueWords = new wordItem[2*arraySize];
        arraySize = 2*arraySize;
        for(int j = 0; j< arraySize; j++){
            uniqueWords[j] = tempWords[j];
        }
        delete[] tempWords;
        
        arrayDoublingCount++;
    }
    
}

int isUniqueWord(string word, wordItem uniqueWordsList[], int uniqueWordCount){
    bool alreadyInTheList = false;
    for(int i = 0; i < uniqueWordCount; i++){
        if(uniqueWordsList[i].word == word){
            alreadyInTheList = true;
            uniqueWordCount++;
        }
    }
    if(!alreadyInTheList){
        uniqueWordsList[uniqueWordCount].word = word;
        uniqueWordsList[uniqueWordCount].count++;
    }

    return <#expression#>
}

bool isCommonWord(string word, vector<string>& _vecIgnoreWords){
    bool commonWord = false;
    for(int i = 0; i < arraySize; i++){
        if(word == ignoredWords[i]){
            commonWord = true;
            break;
        }
        
    }
    return commonWord;
}

void printTopN(wordItem wordItemList[], int topN){
    wordItem printedArray[topN];
    for(int i = 0; i < topN; i++){
        printedArray[i].word = wordItemList[i].word;
        printedArray[i].count = wordItemList[i].count;
    
    }
    for(int k = 0; k < topN; k++){
        cout << printedArray[k].word << " - " << printedArray[k].count << endl;
    }
}

int getTotalNumberNonCommonWords(wordItem wordItemList[], int uniqueWordCount){
    int totalCount = 0;
    for(int i = 0; i < uniqueWordCount; i ++){
        totalCount = totalCount + wordItemList[i].count;
    
    }
    return totalCount;
}


void readInFile(string fName){
    wordItem *uniqueWords = new wordItem[100];//create an array of structs to 100;
    wordItem *tempWords; //create a temporary array
    
    int arraySize = 100;// define the size of the array
    int arrayDoublingCount = 0;// create a counter for the number of times needed to double the array
    int uniqueWordCount = 0;//counter for the unique words
    int totalwordCount = 0;// counter for the total words
    int printSize = 0;
    
    string uniqueLine;
    string uniqueWord;
    ifstream infile;
    infile.open(fName);//open the file that the user passes
    while(!infile.eof()){
        getline(infile, uniqueLine);
        //Get individual line from the file
        stringstream ss(uniqueLine);
        //get individual word from the line
        while(ss >> uniqueWord){
            arrayDoubling(uniqueWordCount, arraySize, uniqueWords, arrayDoublingCount); 
        }
    
    
    }
    printTopN(uniqueWords, printSize);
    cout << "#" << endl;
    cout << "Array doubled :" << arrayDoublingCount << endl;
    cout << "#" << endl;
    cout << "Unique non-common words:" << uniqueWordCount << endl;
    cout << "#" << endl;
    cout << "Total non-common words:" << totalwordCount << endl;
    


}

int main(int argc, const char * argv[]) {
    // insert code here...
    string fName = "";
    int numberOfMostFrequentWords;
    getline(cin, fName); // allows the user to input the filename
    cin >> numberOfMostFrequentWords; // takes input on the number of most frequent words
    readInFile(fName);
    return 0;
}
