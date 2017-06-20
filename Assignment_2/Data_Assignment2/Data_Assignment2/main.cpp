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
#include "WordAnalysis.h"

using namespace std;

void WordAnalysis::doubleArrayAndAdd(word *uniqueWords){
    word *tempWords;
    int timesDoubled = 0;
    int arraySize = 100;
    int index = 0;
    int wordCount = 0;
    if(index == arraySize){
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
        
        timesDoubled++;
    }
}

int WordAnalysis::getArrayDoubling(){
    int timesDoubled = 0;
    if(WordAnalysis::doubleArrayAndAdd(<#word *uniqueWords#>)){
        timesDoubled++;
    }

    return timesDoubled;
};

void WordAnalysis::sortData(){
    word swap;
    for(int i = 0; i < index; i++)
    {
        for(int j = 0; j < (index - i); j++)
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

void WordAnalysis::printResult(int ){
    printCommonWords(uniqueWords, printSize);
    cout << "#" << endl;
    cout << "Array doubled :" << timesDoubled << endl;
    cout << "#" << endl;
    cout << "Unique non-common words:" << index << endl;
    cout << "#" << endl;
    cout << "Total non-common words:" << getWordCount(); << endl;
}

void WordAnalysis::printCommonWords(int topN)
{
    word printedArray[topN];
    for(int i = 0; i<topN; i++){
        printedArray[i].w = wordList[i].w;
        printedArray[i].count = wordList[i].count;
    }
    for(int i = 0; i<topN; i++){
        cout << printedArray[i].w << " - " << printedArray[i].count << endl;
    }
    return;
}

int WordAnalysis::getWordCount()
{
    int totalCount = 0;
    for(int i = 0; i<index; i++)
    {
        totalCount += wordList[i].count;
    }
    return totalCount;
}

int WordAnalysis::getUniqueWordCount()
{
    bool alreadyInList = false;
    int index = 0;
    
    for(int i = 0; i < index; i++)			//loop through all seen unique words
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
        uniqueWordsList[index].w = word;
        uniqueWordsList[index].count ++;
        return 1;
    }
    return index;
}


bool WordAnalysis::checkIfCommonWord(string word)//call this function to make sure not to add these words to the list of common words
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

bool WordAnalysis::readDataFile(string fName){//use this function to read the fie
    bool fileRead = true;
    word *uniqueWords = new word[100];
    word *tmpWords;
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
                WordAnalysis::doubleArrayAndAdd(<#word *uniqueWords#>);
                if(WordAnalysis::checkIfCommonWord(uniqueWord) == true){
                    //I DON'T WANT IT IN THE ARRAY
                }
                
                else{
                    // I WANT IT IN THE ARRAY
                    WordAnalysis::getUniqueWordCount(uniqueWord);
                    wordCount++;
                }
                //arraydoubling goes here
            }
        }

    }
    
    else{
        cout << "file didn't open"<< endl;
        fileRead = false;
    }
    WordAnalysis::sortData(<#word *uniqueWords#>)
    return fileRead;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    string fName = "";
    char* fileN = fName; 
    int numberOfMostFrequentWords;
    getline(cin, fName); // allows the user to input the filename
    cin >> numberOfMostFrequentWords; // takes input on the number of most frequent words
    readDataFile(fName);
    return 0;
}
