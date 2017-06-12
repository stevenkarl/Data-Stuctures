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


int removeAndShift(item (&itemList)[], int rem, int z){
    for(int i = rem + 1; i < z; i++){
        itemList[i-1] = itemList[i];
    }
    item empty;
    itemList[z-1] = empty;
    
    return rem;

}

void isMatch(item itemList[], int& ops, int& z){
    for(int n = 0; n < z; n++){//loops through the next line in the list to compare
        ops++;
        for(int m = 0; m < z; m++){
            if(itemList[n].sale == true){
                if(itemList[m].type == itemList[n].type && itemList[m].sale != itemList[n].sale && itemList[m].price >= itemList[n].price){
                    cout << itemList[n].type << " " << itemList[n].price << endl;
                    removeAndShift(itemList, n, z);
                    z--;
                }
            }
            else{
                if(itemList[m].type == itemList[n].type && itemList[m].sale != itemList[n].sale && itemList[m].price <= itemList[n].price){
                    cout << itemList[m].type << " " << itemList[m].price << endl;
                    removeAndShift(itemList, m, z);
                    z--;
                }
            }
            
            //I think that I have to do something like this for the case where no match is found. It says to add the item to the first unused position but I don't really understand how something is unused??
        }
        item temp = itemList[removeAndShift(itemList, n, z)];
        itemList[n+1] = itemList[n];
        itemList[n] = itemList[z];
    }

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
    int i = 0;
    string strline = "";
    while(!infile.eof()){
        getline(infile, strline);
        cin.ignore();
        type = strline.substr(0, strline.find_first_of(','));//this locates the string in the line that is the type
        want = strline.substr(strline.find_first_of(',') + 2);//this locates the string in the line for the sale or want
        if(want[0] == 'f'){// this is to assign a boolean variable to the string/char that was found in the line
            sale = false;
        }
        else{
            sale = true;
        }
        price = atoi(strline.substr(strline.find_last_of(',')+2).c_str());//this locates the instance of the price and makes it an int
        
            itemList[i].price = price;
            itemList[i].type = type;
            itemList[i].sale = sale;
            ops++; // this is adding up the operations that were used
            i++;
        cout << "item read " << itemList[i].type << " cost " << endl;
    }
    int n = 0;
    while(itemList[n].type != ""){
        n++;
    }
    isMatch(itemList, ops, n);
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    string fName = "";
    cout << "Welcome to Craigslist, but not Craiglist. Please enter your filename."<< endl;//opening statement
    getline(cin,fName);// Allows the user to input the filename
    readFile(fName);
    
    
    
    
    return 0;
}
