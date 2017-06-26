//
//  main.cpp
//  Data_Structures#3
//
//  Created by Steven Karl on 6/21/17.
//  Copyright © 2017 Steven Karl. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include <cstddef>
#include "CommunicationNetwork.h"
using namespace std;


void CommunicationNetwork::addCity(string newCityName, string previousCityName){
    City *newCity = new City(newCityName, NULL, NULL, "");
    
    
    if(previousCityName == "First"){//Case # 1 if they want to put the new city in front
        City *temp = head;
        newCity -> next = temp;
        head = newCity;
    }
    for(City *i = head; i != NULL; i = i -> next){
        if(i-> cityName == previousCityName){
            if(i->next == NULL){//Case #2 if they want to put the new city at the end;
                City *temp = i;
                i -> next = newCity;
                newCity->next = NULL;
                newCity -> previous = temp;
            }
            else{                           //Case # 3 if they want to put the new city in the middle
                City *temp = i -> next;
                i -> next = newCity;
                newCity ->next = temp;
            }
        
        }
    }
}

void CommunicationNetwork::buildNetwork(){
    string linus [6] = {"Miami" ,"New York", "Chicago", "Seattle", "Denver", "Dallas"};
    head->cityName = linus[0];
    for(int i = 1; i < 5; i++){
        addCity(linus[i+1], linus[i]);
    }
    tail->cityName = linus[5];
    
    printNetwork();
}
void CommunicationNetwork::transmitMsg(string filename){

    cout<<sender->cityName<<" received "<<sender-message<<endl;
    //if network not built yet, head = nullptr
    cout << "Empty list" << endl;



}

void CommunicationNetwork::printNetwork(){
    cout << "===CURRENT PATH===" << endl;
    cout << "NULL <- ";
    for(City *tmp = head; tmp != NULL; tmp = tmp-> next){
        if(tmp -> next == NULL){
            cout << tmp->cityName;
            break;
        }
        cout << tmp->cityName << " <-> ";   //for all nodes in network
    }
    cout << " -> NULL" << endl;
    cout << "==================" << endl;
}

void CommunicationNetwork::deleteCity(string removeCity){
    for(City *i = head; i != NULL; i = i-> next){
        if(removeCity == i->cityName){
            if(head == i){
                City *temp = head;
                head = i -> next;
                delete[] temp;
            }
            else if(i->next == NULL){
                City *temp = i;
                (i -> previous) -> next = NULL;
                delete[] temp;
            }
            else{
                City *temp = i;
                (i->previous) -> next = i -> next;
                (i->next)->previous = i->previous;
                delete[] temp;
            }
        }
        else{
            cout<< cityNameIn << "not found" <<endl;
        }
}
}
void CommunicationNetwork::deleteNetwork(){
    for(City *tmp = head; tmp != NULL; tmp = tmp -> next){
        delete[] tmp;
        cout<<"deleting "<<tmp->cityName<<endl; //for all nodes in network
    }
}
CommunicationNetwork::CommunicationNetwork(){
    head = NULL;
    tail = NULL;

}
CommunicationNetwork::~CommunicationNetwork(){

    delete[] head;
    delete[] tail;

}


int main(int argc, const char * argv[]) {
    // insert code here...
    cout << "======Main Menu======" << endl;
    cout << "1. Build Network" << endl;
    cout << "2. Print Network Path" << endl;
    cout << "3. Transmit Message Coast-To-Coast" << endl;
    cout << "4. Add City" << endl;
    cout << "5. Delete City" << endl;
    cout << "6. Clear Network" << endl;
    cout << "7. Quit" << endl;
    
    string choice = " ";
    int input;
    while(input != 7 ) { // loop until the user decides to quit
        getline(cin, choice);
        input = stoi(choice);
        
        switch(input){
                //if the user chooses #1 then this case runs building and printing the network after
            case 1:
                CommunicationNetwork *charles = new CommunicationNetwork();

                
                //if the user chooses #2 then this case runs printing the network path
            case 2:
                printNetwork();
                break;
                
                //if the user chooses #3 then this case runs transmitting the message from city to city
            case 3:
                string fName = "";
                cout << "Enter name of file: " << endl;
                getline(cin, fName);
                transmitMsg(fName);
                break;
                //if the user chooses #4 then this case runs adding a city to the linked list of cities
            case 4:
                string newCityName = " ";
                string prevCityName = " ";
                cout << "Enter a city name: " << endl;
                getline(cin, newCityName);
                cout << "Enter a previous city name: " << endl;
                getline(cin, prevCityName);
                
                
                addCity(newCityName, previousCityName);
                
                break;
                
                //if the user chooses #5 then this case runs deleting a specified city from the network
            case 5:
                string removeCity = " ";
                cout << "Enter a city name: " << endl;
                getline(cin, removeCity);
                
                deleteCity(removeCity);
                
                break;

                
                //if the user chooses #6 then this case runs and the entire network is cleared
            case 6:
                deleteNetwork();
                
                break;
        }
    }
    if(input == 7){
        cout << "Goodbye!" << endl;
    }
    
    return 0;
}
