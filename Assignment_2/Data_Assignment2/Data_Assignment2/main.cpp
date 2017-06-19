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


struct word{
    string w;
    int count;
    
};

void doubleArrayAndAdd(int uniqueWordCount, int arraySize, word *uniqueWords, int arrayDoublingCount){
    word *tempWords;
    if(uniqueWordCount == arraySize){
        tempWords = new word[2*arraySize];
        
        for (int i = 0; i < arraySize; i++) {
            tempWords[i] = uniqueWords[i];
        }
        delete[] uniqueWords;
        uniqueWords = new word[2*arraySize];
        arraySize = 2*arraySize;
        for(int j = 0; j< arraySize; j++){
            uniqueWords[j] = tempWords[j];
        }
        delete[] tempWords;
        
        arrayDoublingCount++;
    }
}

int getArrayDoubling();

void sortData(word wordList[], int uniqueWordCount, word *uniqueWords){
    word swap;
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

void printResult(int timesDoubled, int uniqueWordCount, int wordCount, int printSize, word *uniqueWords){
    printCommonWords(uniqueWords, printSize);
    cout << "#" << endl;
    cout << "Array doubled :" << timesDoubled << endl;
    cout << "#" << endl;
    cout << "Unique non-common words:" << uniqueWordCount << endl;
    cout << "#" << endl;
    cout << "Total non-common words:" << wordCount << endl;
};

void printCommonWords(word wordList[], int topN)
{
    word printedArray[topN];
    for(int i = 0; i<topN; i++){
        printedArray[i].w = wordList[i].w;
        printedArray[i].count = wordList[i].count;
    }
    for(int i = 0; i<topN; i++){
        cout << printedArray[i].w << printedArray[i].count << endl;
    }
    return;
}

int getWordCount(word wordList[], int uniqueWordCount)
{
    int totalCount = 0;
    for(int i = 0; i<uniqueWordCount; i++)
    {
        totalCount += wordList[i].count;
    }
    return totalCount;
}

int getUniqueWordCount(string word, word uniqueWordsList[], int uniqueWordCount)
{
    bool alreadyInList = false;
    
    for(int i = 0; i < uniqueWordCount; i++)			//loop through all seen unique words
    {
        if(uniqueWordsList[i].w == word)					//if hte new unique word is an already seen unique word
        {
            alreadyInList = true;
            uniqueWordsList[i].count++;
            return 0;
        }
    }
    if(!alreadyInList)
    {
        uniqueWordsList[uniqueWordCount].w = word;
        uniqueWordsList[uniqueWordCount].count ++;
        return 1;
    }
    return 0;
}


bool checkIfCommonWord(string word, vector<string>& _vecIgnoreWords)
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

bool readDataFile(string fName){
    
    word *uniqueWords = new word[100];
    word *tmpWords;
    
    int arraySize = 100;
    //int printSize = stoi(argv[1]);
    
    int timesDoubled = 0;   		//counts how many times the array was doubled
    int uniqueWordCount = 0;
    int wordCount = 0;
    
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
    readDataFile(fName);
    return 0;
}
