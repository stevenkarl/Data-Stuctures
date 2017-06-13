//
//  main.cpp
//  Assignment1_StevenKarl
//
//  Created by Steven Karl on 6/9/17.
//  Copyright © 2017 Steven Karl. All rights reserved.
//

#include <iostream>
#include <fstream> 
#include <string> 
#include <cstring> 
#include <istream>
using namespace std;


struct item{
    string type;
    int price;
    bool sale;
};

void removeAndShift(item itemList[], int rem, int z){
    for(int j = rem + 1; j < z; j++){
        itemList[j-1] = itemList[j];
    }
    itemList[z-1].price = 0;
    itemList[z-1].sale = false;
    itemList[z-1].type = "";

}

bool isMatch(item itemList[], item temp, int i, int& ops){
    for(int n = 0; n < i; n++){//loops through the next line in the list to compare
        ops++;
            if(itemList[n].sale == true){
                if(temp.type == itemList[n].type && temp.sale != itemList[n].sale &&  itemList[n].price>= temp.price){
                    cout << itemList[n].type << " " << itemList[n].price << endl;
                    removeAndShift(itemList, n, i);
                    i--;
                    return true;
                }
            }
            else{
                if(temp.type == itemList[n].type && temp.sale != itemList[n].sale && temp.price >= itemList[n].price){
                    cout << temp.type << " " << temp.price << endl;
                    removeAndShift(itemList, n, i);
                    i--;
                    return true;
                }
            }
    }
    return false;
}

void readFile(string fName){
    ifstream infile;
    infile.open(fName);//opens the file
    item itemList[100];//creates an array of structs of 100
    int ops = 0;// for counting the number of operations
    bool sale = 0;
    string type = "";
    string want = "";
    int price = 0;
    int i = 0;// counts number of elements in the array
    item temp;
    string strline = "";
    while(!infile.eof()){
        getline(infile, strline);
        //cin.ignore();
        type = strline.substr(0, strline.find_first_of(','));//this locates the string in the line that is the type
        want = strline.substr(strline.find_first_of(',') + 2);//this locates the string in the line for the sale or want
        if(want[0] == 'f'){// this is to assign a boolean variable to the string/char that was found in the line
            sale = false;
        }
        else{
            sale = true;
        }
        price = atoi(strline.substr(strline.find_last_of(',')+2).c_str());//this locates the instance of the price and makes it an int
        
        temp.price = price;
        temp.type = type;
        temp.sale = sale;
        isMatch(itemList, temp, i, ops);// this is calling the match function
        if(!isMatch(itemList, temp, i, ops)){
            itemList[i] = temp;
            
        }
        
        cout << "item read " << itemList[i].type << " cost " << itemList[i].price << endl; // this is printing out the array
        i++;
    }

    
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    string fName = "";
    cout << "Welcome to Craigslist, but not Craiglist. Please enter your filename."<< endl;//opening statement
    getline(cin,fName);// Allows the user to input the filename
    readFile(fName);
    
    
    
    
    return 0;
}
