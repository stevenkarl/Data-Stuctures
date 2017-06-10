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


void isMatch(){
    for(int n = 0; n < i; n++){//loops through the next line in the list to compare
        ops++;
        if(sale == true){
            if(type == itemList[n].type && sale != itemList[n].sale && price<= itemList[n].price){
                cout << itemList[n].type << " " << itemList[n].price << endl;
                c++;
                
                for(int p = n; p < i - 1; p--){
                    itemlist[p] = itemList[p + 1];
                }
            }
        }
    }

}

void readFile(string fName){
    ifstream infile;
    infile.open(fName);//opens the file
    item itemList[100];//creates an array of structs of 100
    int ops = 0;// for counting the number of operations
    bool sale;
    int i = 0;
    int c = 0;
    string strline;
    while(!infile.eof()){
        item temp;
        getline(infile, strline);
        string type = strline.substr(0, strline.find_first_of(','));//this locates the string in the line that is the type
        string want = strline.substr(strline.find_first_of(',') + 2 );//this locates the string in the line for the sale or want
        if(want[0] == 'f'){// this is to assign a boolean variable to the string/char that was found in the line
            sale = false;
        }
        else
            sale = true;
        
        int price = atoi(strline.substr(strline.find_last_of(',')+2).c_str());//this locates the instance of the price and makes it an int
        
        if(i == 0){ // This is assigning values to the struct for the first line of the file
            itemList[i].price = price;
            itemList[i].type = type;
            itemList[i].sale = sale;
            ops++; // this is adding up the operations that were used
        }
        else{
            for(int n = 0; n < i; n++){
                ops++;
                if(sale == true){
                    if(type == itemList[n].type && sale != itemList[n].sale && price >= itemList[n].price){
                        cout<< itemList[n].type<<" "<< itemList[n].price<<endl;
                        c++;
                    }
                }
            }
        }
        
        
        
        
        
    }
    
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    string fName = "";
    cout << "Welcome to Craigslist, but not Craiglist. Please enter your filename."<< endl;//opening statement
    getline(cin,fName);// Allows the user to input the filename
    return 0;
}
