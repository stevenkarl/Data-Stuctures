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

// struct to store word + count combinations
struct wordItem {
    string word;
    int count;
};

/*
 * Function name: isUniqueWord
 * Purpose: place word in uniqueWordsList
 * @param word - unique word
 * @param uniqueWordsList - Array for unique words
 * @uniqueWordCount - number of unique words already in array
 */
int isUniqueWord(string word, wordItem uniqueWordsList[], int uniqueWordCount);

/*
 * Function name: getStopWords
 * Purpose: read stop word list from file and store into vector
 * @param ignoreWordFile - filename (the file storing ignore words)
 * @param _vecIgnoreWords - store ignore words from the file (pass by reference) * @return - none
 * Note: The number of words is fixed to 50
 */
void getStopWords(char *ignoreWordFileName, vector<string>& _vecIgnoreWords);

/*
 * Function name: isCommonWord
 * Purpose: to see if a word is a common word
 * @param word - a word (which you want to check if it is a common word)
 * @param _vecIgnoreWords - the vector type of string storing ignore/common words * @return - true (if word is a common word), or false (otherwise)
 */
bool isCommonWord(string word, vector<string>& _vecIgnoreWords);

/*
 * Function name: printTopN
 * Purpose: to print the top N high frequency words
 * @param wordItemList - a pointer that points to an array of wordItems * @param topN - the number of top frequency words to print
 * @return none
 */
void printTopN(wordItem wordItemList[], int topN);

/*
 * Function name: getTotalNonCommonWords
 * Purpose: to return the total number of non-common words
 * @param wordItemList - a pointer that points to an array of wordItems
 * @param uniqueWordCount - the number of unique words in wordItemList
 */
int getTotalNumberNonCommonWords(wordItem wordItemList[], int uniqueWordCount);

const int STOPWORD_LIST_SIZE = 50;

// ./a.out 10 HW1-HungerGames_edit.txt HW1-ignoreWords.txt

int main(int argc, char* argv[])
{
    vector<string> vecIgnoreWords(STOPWORD_LIST_SIZE);
    wordItem *uniqueWords = new wordItem[100];
    wordItem *tmpWords;
    
    int arraySize = 100;
    int printSize = stoi(argv[1]);
    
    int arrayDoubleCount = 0;   		//counts how many times the array was doubled
    int uniqueWordCount = 0;
    int totalWords = 0;
    
    
    // verify we have the correct # of parameters, else throw error msg & return
    if (argc != 4)
    {
        cout << "Usage: ";
        cout << argv[0] << " <number of words> <filename.txt> <ignorefilename.txt>"; cout << endl;
        return 0;
    }
    
    /* **********************************
     1. Implement your code here.
     Read words from HW1-HungerGames_edit.txt, store and count the words.
     2. Implement the three functions after the main() function seperately.
     *********************************** */
    
    getStopWords(argv[3], vecIgnoreWords);
    
    ifstream inFile;
    string uniqueLine;
    string uniqueWord;
    inFile.open(argv[2]);
    if(inFile.is_open())
    {
        
        //get the individual line from the file
        while(getline(inFile, uniqueLine))
        {
            stringstream ss(uniqueLine);
            
            //get the individual word from the line
            while(ss >> uniqueWord){
                
                //Array Doubling function
                if(uniqueWordCount == arraySize){
                    tmpWords = new wordItem[2*arraySize];
                    
                    for(int i = 0; i<arraySize; i++)
                    {
                        tmpWords[i] = uniqueWords[i];
                    }
                    delete[] uniqueWords;
                    uniqueWords = new wordItem[2*arraySize];
                    arraySize = arraySize*2;
                    for(int i = 0; i<arraySize; i++)
                    {
                        uniqueWords[i] = tmpWords[i];
                    }
                    delete[] tmpWords;
                    
                    arrayDoubleCount++;
                }
                //if uinqueWord is not a common word, update array and corresponding variables
                if(!isCommonWord(uniqueWord, vecIgnoreWords))
                {
                    uniqueWordCount += isUniqueWord(uniqueWord, uniqueWords, uniqueWordCount);
                    
                    totalWords++;
                }
            }
        }
        
    }
    inFile.close();
    
    //reverse bubble sort function
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
    
    totalWords = getTotalNumberNonCommonWords(uniqueWords, uniqueWordCount);
    
    printTopN(uniqueWords, printSize);
    cout << "#" << endl;
    cout << "Array doubled :" << arrayDoubleCount << endl;
    cout << "#" << endl;
    cout << "Unique non-common words:" << uniqueWordCount << endl;
    cout << "#" << endl;
    cout << "Total non-common words:" << totalWords << endl;
    
    delete[] uniqueWords;
    
    
    return 0;
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



void getStopWords(char *ignoreWordFileName, vector<string>& _vecIgnoreWords)
{
    ifstream ignoreFile;
    string stopWord;
    ignoreFile.open(ignoreWordFileName);
    if(ignoreFile.is_open())
    {
        
        
        while(getline(ignoreFile, stopWord))
        {
            stringstream ss(stopWord);
            string tmp;
            ss >> tmp;
            
            _vecIgnoreWords.push_back(tmp);
            
            _vecIgnoreWords.erase(_vecIgnoreWords.begin(), _vecIgnoreWords.begin()+1);
            
            
        }
        ignoreFile.close();
    }
    else
    {
        cout << "StopWord file failed to open" << endl;
    }
    
    return; 
}

bool isCommonWord(string word, vector<string>& _vecIgnoreWords) 
{
    bool commonWord = false;
    for(int i = 0; i < STOPWORD_LIST_SIZE; i++)
    {
        if(word == _vecIgnoreWords[i])
        {
            commonWord = true;
            break;
        }
    }
    return commonWord; 
}

void printTopN(wordItem wordItemList[], int topN) 
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
