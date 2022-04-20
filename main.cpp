#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

#include "asdaCheckout.h"

using namespace std;

map<string, float> itemDatabase;

int initialiseDB(){

    itemDatabase["milk"] = 2.99;
    itemDatabase["bread"] = 1.00;
    itemDatabase["eggs"] = 1.20;
    itemDatabase["cheese"] = 1.00;
    itemDatabase["apple"] = 0.60;
    itemDatabase["chocolate"] = 1.99;


   /* for(auto it = itemDatabase.cbegin(); it != itemDatabase.cend(); ++it) {   
    cout << it->first << " " << it->second << "\n";
    } */

    if (itemDatabase.size() == 0 ) {
        cout << "Failed to Connect to Database - please contact the nearest member of staff" << endl;
        return -1;
    }

    return 1;

}


int main() {

    initialiseDB();

    string list;

    cout << "Hello welcome, to the shopping system! " << endl;
    cout << "Please enter the items you have wish to purchase as a comma seperated list (i.e. bread, eggs, chocolate)" << endl;
    getline(cin, list);

    

    if (list.length() == 0){
        cout << "No Items Entered - please try again";
        return 0;
    }

    //set all to lower case - this will avoid case sensitive issues with regards to looking up in the map
    transform(list.begin(), list.end(), list.begin(), ::tolower);

    //why assign to heap - number of items
    //want to show my avility to use smart pointers and regualr memory allocation
    vector<string> *returnVector = new vector<string>;
    stringstream ss(list);
    string parsed;
    //seperate string my commas and also remove spaces (once again to avoid any look up errors)
    while (getline(ss, parsed, ',')){
        parsed.erase(remove(parsed.begin(), parsed.end(), ' '), parsed.end());
        returnVector->push_back(parsed);
    }

    //sort alphabetically - this assists when finding duplicates and removing items from vectors and corresponding arrays
    sort(returnVector->begin(), returnVector->end());


    //unique pointer - will delete memory allocation on its own
    unique_ptr<asdaCheckoutSystem> asda1(new asdaCheckoutSystem(20, "Nottingham", "Asda"));
    int returnCode = asda1->setList(itemDatabase, returnVector);
    
    
    if (returnCode == -1){
        cout << "Till System Error - Please contact the nearest Member of Staff";
        return 0;
    }

    //get prices and print the reciept
    asda1->getPrices();
    

    
    //delete memory allocation
    delete returnVector;
   
}