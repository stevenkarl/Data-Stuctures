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

void WordAnalysis::doubleArrayAndAdd(string nWord){//doi
    if(index == wordCount){
        
        word *tempWords = new word[2*wordCount];
        
        for (int i = 0; i < wordCount; i++) {
            tempWords[i] = words[i];
        }
        delete[] words;
        words = new word[2*wordCount];
        wordCount = 2*wordCount;
        for(int j = 0; j< wordCount; j++){
            words[j] = tempWords[j];
        }
        delete[] tempWords;
        
        timesDoubled++;
        word temp;
        temp.w = nWord;
        temp.count = 1;
        words[index] = temp;
        return;
        
    }
    word temp;
    temp.w = nWord;
    temp.count = 1;
    words[index] = temp;
}

int WordAnalysis::getArrayDoubling(){
   
    return timesDoubled;
}

void WordAnalysis::sortData(){
    word swap;
    for(int i = 0; i < index; i++)
    {
        for(int j = 0; j < (index - i); j++)
        {
            if(words[j].count < words[j+1].count)
            {
                swap = words[j];
                words[j] = words[j+1];
                words[j+1] = swap;
            }
        }
    }

}

void WordAnalysis::printResult(int num){
    printCommonWords(num);
    cout << "#" << endl;
    cout << "Array doubled :" << timesDoubled << endl;
    cout << "#" << endl;
    cout << "Unique non-common words:" << index << endl;
    cout << "#" << endl;
    cout << "Total non-common words:" << getWordCount() << endl;
}

void WordAnalysis::printCommonWords(int topN){
    word *printedArray = new word[topN];
    for(int i = 0; i<topN; i++){
        printedArray[i].w = words[i].w;
        printedArray[i].count = words[i].count;
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
        totalCount = totalCount + words[i].count;
    }
    return totalCount;
}

int WordAnalysis::getUniqueWordCount()
{

    return index;
}


bool WordAnalysis::checkIfCommonWord(string word){//call this function to make sure not to add these words to the list of common words

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

bool WordAnalysis::readDataFile(char *fName){//use this function to read the fie
    string uniqueLine = "";
    string uniqueWord = "";
    ifstream infile;
    infile.open(fName);//open the file that the user passes
    if(infile.is_open()){
        //get the individual line from the file
        while(getline(infile, uniqueLine))
        {
            stringstream ss(uniqueLine);
            
            //get the individual word from the line
            while(ss >> uniqueWord){
                if(checkIfCommonWord(uniqueWord) == true){
                    //I DON'T WANT IT IN THE ARRAY
                }
                
                else{
                //now check if already in the array
                bool alreadyInList = false;
                for(int i = 0; i < index; i++)
                {
                    if(words[i].w == uniqueWord)
                    {
                        alreadyInList = true;
                        words[i].count++;
                    }
                }
                if(!alreadyInList)
                {
                    doubleArrayAndAdd(uniqueWord);
                    index++;
                }
                }
            }
        }
        sortData();
        return true;

    }
    
    else{
        cout << "file didn't open"<< endl;
        return false;
    }
}

WordAnalysis::WordAnalysis(int zane){
    words = new word[100];
    wordCount = 0;
    index = 0;
    timesDoubled = 0;
};

WordAnalysis::~WordAnalysis(){
    delete[] words;
};
int main(int argc, const char * argv[]) {
    string fName = "";
    int numberOfMostFrequentWords;
    cout << "Please enter your filename."<< endl;//opening statement
    getline(cin, fName); // allows the user to input the filename
    cin >> numberOfMostFrequentWords; // takes input on the number of most frequent words
    int defaultsize = 100;
    WordAnalysis wa(defaultsize);
    char* fileN = (char*)fName.c_str();
    wa.readDataFile(fileN);
    wa.printCommonWords(numberOfMostFrequentWords);
    wa.printResult(numberOfMostFrequentWords);
    return 0;
}
