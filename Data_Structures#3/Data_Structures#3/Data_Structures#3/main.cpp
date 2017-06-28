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

/**This is the addCity function that takes in user input and adds a city to the current network
 @param string newCityName: which is the name of the new city that we want to add to the list
 @param string previousCityName: which is the name of the city that comes before the place that you wish to add the new city
 */
void CommunicationNetwork::addCity (string newCityName, string previousCityName) {
    City *newCity = new City(newCityName, NULL, NULL, "");
    
    if (head->cityName == "") {
        head =  newCity;
        return;
    }
    if (previousCityName == "First") {//Case # 1 if they want to put the new city in front
        City *temp = head;
        head = newCity;
        
        newCity -> next = temp;
        head -> next = newCity -> next;
    }
    for (City *i = head; i != NULL; i = i -> next) {
        if (i-> cityName == previousCityName) {
            if (i->next == NULL) {//Case #2 if they want to put the new city at the end;
                i -> next = newCity;
                newCity -> previous = i;
            } else {                           //Case # 3 if they want to put the new city in the middle
                City *temp = i -> next;
                i -> next = newCity;
                newCity ->next = temp;
                newCity -> previous = i;
                temp -> previous = newCity;
            }
        }
    }
}

/**
 This function is buildNetwork and it is used to setup the initial network that we will preform other functions on
 */
void CommunicationNetwork::buildNetwork () {
    City linus [7] = {City(""), City("Miami") , City("New York"), City("Chicago"), City("Seattle"), City("Denver"), City("Dallas")};
    for (int i = 0; i < 6; i++) {
        addCity(linus[i+1].cityName, linus[i].cityName);
    }
    for (City* i = head; i != NULL; i = i->next) {
        if (i->next == NULL) {
            tail = i;
        }
    }
    printNetwork();
}

/**This is the transmitMsg function that reads in a txt file and passes its contents from one city to the next until the end.
 @param string filename: This is the name of the file that we are reading from and passing from city to city.
 */
void CommunicationNetwork::transmitMsg (string filename) {
    if (head == NULL) {
        cout << "Empty list" << endl;
        return;
    }
    ifstream fs(filename);
    string str = "";
    while (!fs.eof()) {
        fs >> str;
        for (City *i = head; i!= NULL; i = i-> next) {
            if (i == head) {
                i -> message += str;
            } else {
                i -> message += " " + str;
            }
            cout<< i-> cityName << " received " << str <<endl;
        }
    }
    fs.close();
    for (City *i = head; i!= NULL; i = i-> next) {
        if (i -> next == NULL) {
            break;
        }
        i -> message = " ";
    }
}

/**This is the printNetwork function in which we print out the network as it currently is depending on the operations that we preformed
 */
void CommunicationNetwork::printNetwork () {
    cout << "===CURRENT PATH===" << endl;
    cout << "NULL <- ";
    for (City *tmp = head; tmp != NULL; tmp = tmp-> next) {
        if (tmp -> next == NULL) {
            cout << tmp->cityName;
            break;
        }
        cout << tmp->cityName << " <-> ";   //for all nodes in network
    }
    cout << " -> NULL" << endl;
    cout << "==================" << endl;
}

/**This is the deleteCity function that takes the user input city and removes it from the current network
 @param string removeCity is the city being passed by the user that we wish to remove;
 */
void CommunicationNetwork::deleteCity (string removeCity) {
    // first we check if we're removing the head
    if (head->cityName == removeCity) {
        City* temp = head;
        head = head->next;
        head->previous = temp->previous;
        delete temp;
    }
    // second we check if we are removing the tail
    else if (tail->cityName == removeCity) {
        City* temp = tail;
        tail = tail->previous;
        tail->next = temp->next;
        delete temp;
    } else { // Now we check if we are removing from the middle
            for (City* i = head; i != NULL; i = i->next) {
                if (removeCity == i->cityName) {
                    // We do the same as for remvoing the head
                    City* temp = i;
                    i = i->next;
                    i->previous = temp->previous;
                    // We do the same as for removing the tail
                    City* temp2 = temp;
                    temp = temp->previous;
                    temp->next = temp2->next;
                    // In order to prevent memory leak
                    delete temp;
                    delete temp2;
                }
                if(i->next == NULL){
                    cout<< removeCity << " not found" <<endl;
                }
        }
    }
}

/**
 This is the deleteNetwork function that loops through the network and clears all of the cities so that we can start from scratch.
 */
void CommunicationNetwork::deleteNetwork () {
    for (City *tmp = head; tmp != NULL; tmp = tmp -> next) {
        cout<< "deleting "<< tmp->cityName << endl; //for all nodes in network
        delete tmp;
        }
}

/**
 This is the constructor where we intilize the head and the tail of the network.
 */
CommunicationNetwork::CommunicationNetwork () {
    head = new City("",NULL,NULL,"");
    tail = new City("",NULL,NULL,"");
}

/**
 This is the destructor where we loop through and delete the list.
 */
CommunicationNetwork::~CommunicationNetwork () {
    for (City* i = head; i != NULL; i = i->next) {
        delete i;
    }
}

int main() {
    cout << "======Main Menu======" << endl;
    cout << "1. Build Network" << endl;
    cout << "2. Print Network Path" << endl;
    cout << "3. Transmit Message Coast-To-Coast" << endl;
    cout << "4. Add City" << endl;
    cout << "5. Delete City" << endl;
    cout << "6. Clear Network" << endl;
    cout << "7. Quit" << endl;
    
    string choice = "";
    bool quit = true;
    int input;
    CommunicationNetwork *charles = new CommunicationNetwork();
    while(quit == true) { // loop until the user decides to quit
        getline(cin, choice);
        input = stoi(choice);
        switch(input){
                
                //if the user chooses #1 then this case runs building and printing the network after
            case 1:{
                charles = new CommunicationNetwork();
                charles->buildNetwork();
                break;
            }
                
                //if the user chooses #2 then this case runs printing the network path
            case 2:{
                charles->printNetwork();
                break;
            }
                
                //if the user chooses #3 then this case runs transmitting the message from city to city
            case 3:{
                string fName = "";
                cout << "Enter name of file: " << endl;
                getline(cin, fName);
                charles->transmitMsg(fName);
                break;
            }
                
                //if the user chooses #4 then this case runs adding a city to the linked list of cities
            case 4:{
                string newCityName = " ";
                string prevCityName = " ";
                cout << "Enter a city name: " << endl;
                getline(cin, newCityName);
                cout << "Enter a previous city name: " << endl;
                getline(cin, prevCityName);
                charles->addCity(newCityName, prevCityName);
                break;
            }
                
                //if the user chooses #5 then this case runs deleting a specified city from the network
            case 5:{
                string removeCity = " ";
                cout << "Enter a city name: " << endl;
                getline(cin, removeCity);
                
                charles->deleteCity(removeCity);
                break;
            }
                
                //if the user chooses #6 then this case runs and the entire network is cleared
            case 6:{
                charles->deleteNetwork();
                break;
            }
                
                //if the user chooses #7 then they have quit
            case 7:{
                quit = false;
                cout << "Goodbye!" << endl;
            }
        }
    }
    return 0;
}
