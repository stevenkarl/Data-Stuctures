//
//  main.cpp
//  Data_Assignment2
//
//  Created by Steven Karl on 6/19/17.
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

void arrayDoubling(int uniqueWordCount, int arraySize, wordItem *uniqueWords, int arrayDoublingCount){
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

void sortData(wordItem wordItemList[], int uniqueWordCount, wordItem *uniqueWords){
    wordItem swap;
    for(int i = 0; i < uniqueWordCount; i++)
    {
        for(int j = 0; j < (uniqueWordCount - i); j++)
        {
            if(uniqueWords[j].count < uniqueWords[j+1].count)
            {
                swap = uniqueWords[j];
                uniqueWords[j] = uniqueWords[j+1];
                uniqueWords[j+1] = swap;
            }
        }
    }

}

void printResult(int arrayDoubleCount, int uniqueWordCount, int totalWords, int printSize, wordItem *uniqueWords){
    printCommonWords(uniqueWords, printSize);
    cout << "#" << endl;
    cout << "Array doubled :" << arrayDoubleCount << endl;
    cout << "#" << endl;
    cout << "Unique non-common words:" << uniqueWordCount << endl;
    cout << "#" << endl;
    cout << "Total non-common words:" << totalWords << endl;
};

void printCommonWords(wordItem wordItemList[], int topN)
{
    wordItem printedArray[topN];
    for(int i = 0; i<topN; i++){
        printedArray[i].word = wordItemList[i].word;
        printedArray[i].count = wordItemList[i].count;
    }
    for(int i = 0; i<topN; i++){
        cout << printedArray[i].word << printedArray[i].count << endl;
    }
    return;
}

int getTotalNumberNonCommonWords(wordItem wordItemList[], int uniqueWordCount)
{
    int totalCount = 0;
    for(int i = 0; i<uniqueWordCount; i++)
    {
        totalCount += wordItemList[i].count;
    }
    return totalCount;
}

int isUniqueWord(string word, wordItem uniqueWordsList[], int uniqueWordCount)
{
    bool alreadyInList = false;
    
    for(int i = 0; i < uniqueWordCount; i++)			//loop through all seen unique words
    {
        if(uniqueWordsList[i].word == word)					//if hte new unique word is an already seen unique word
        {
            alreadyInList = true;
            uniqueWordsList[i].count++;
            return 0;
        }
    }
    if(!alreadyInList)
    {
        uniqueWordsList[uniqueWordCount].word = word;
        uniqueWordsList[uniqueWordCount].count ++;
        return 1;
    }
    return 0;
}


bool isCommonWord(string word, vector<string>& _vecIgnoreWords)
{
    bool commonWord = false;
    string excludedWords[50] = {"the","be","to","of","and","a","in","that","have","i","it",
        "for","not","on","with","he","as","you","do","at","this","but","his","by","from","they",
        "we","say","her","she","or","an","will","my","one","all","would","there","their","what",
        "so","up","out","if","about","who","get","which","go","me"};
    for(int i = 0; i < 50; i++)
    {
        if(excludedWords[i] == word)
        {
            commonWord = true;
            break;
        }
    }
    return commonWord;
}

void readInFile(string fName){
    
    wordItem *uniqueWords = new wordItem[100];
    wordItem *tmpWords;
    
    int arraySize = 100;
    //int printSize = stoi(argv[1]);
    
    int arrayDoubleCount = 0;   		//counts how many times the array was doubled
    int uniqueWordCount = 0;
    int totalWords = 0;
    
    string uniqueLine;
    string uniqueWord;
    ifstream infile;
    infile.open(fName);//open the file that the user passes
    
    if(infile.is_open()){
        //get the individual line from the file
        while(getline(infile, uniqueLine))
        {
            stringstream ss(uniqueLine);
            
            //get the individual word from the line
            while(ss >> uniqueWord){
                //arraydoubling goes here
            }
    }

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
