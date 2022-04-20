#include "checkoutSystemClass.h"


using namespace std;

//various get and set functions for setting identification details of each checkout system
int checkoutSystem::getID() {
    return ID;
}

void checkoutSystem::setID( int m_ID ){
    ID = m_ID;
}
    
string checkoutSystem::getLocation() {
    return Location;    
}

void checkoutSystem::setLocation( string m_Location) {
    Location = m_Location;
}

string checkoutSystem::getRetailer() {
    return Retailer;
}

void checkoutSystem::setRetailer( string m_Retailer ) {
    Retailer = m_Retailer;
}


int checkoutSystem::setList(map<string, float> database, vector<string> * userList){
    //initialise to 0 (if this is ran repeatedly - then this will need to be set to 0 everytime a new list is entered)
     if (database.size() == 0) {
         return -1;
     }
        
     for (int i = 0; i < userList->size(); i++){

         //check to see if item exists in map - if it does push price to vector where indexes correspond else push to the no match list
        if (database.find((*userList)[i]) != database.end()) {
            auto priceVal = database.find((*userList)[i]);
            itemList.push_back((*userList)[i]);
            priceList.push_back(priceVal->second);
        }   else {
            noMatchList.push_back((*userList)[i]);
        }
    } 

    cout << endl;

    cout << "The following items could not be found: " << endl;
    for (int j=0; j < noMatchList.size(); j++ ){
        cout << noMatchList[j] << endl;
    }
    cout << "please go to customer services for more help" << endl;

    cout << endl;
    
   return 1;

}

void checkoutSystem::getPrices() {
    auto reciptVariables = getDiscountedPrice(itemList, priceList, savingsList, savingsPricesList);


    printReciept(get<0>(reciptVariables), get<1>(reciptVariables), get<2>(reciptVariables), get<3>(reciptVariables));
    
}

void checkoutSystem::printReciept(vector<string> m_itemsList, vector<float> m_priceList, vector<string> m_savingsList, vector<float> m_savingsPriceList) {
    subTotal = 0; savingsTotal = 0; finalTotal = 0;

    //print to 2dp for pricing
    cout << endl;
    cout << fixed;
    cout << setprecision(2);
    
    cout << "               " << getRetailer() << "             " << endl;
    cout << "Till ID: " << getID() << "       " << "Location: " << getLocation() << endl;
    cout << endl;
    cout << endl;

    for (int i = 0; i < m_itemsList.size(); i++){
        cout << m_itemsList[i] << "                          £" << m_priceList[i] << endl;
    }

    cout << endl;
    
    for (auto& n : m_priceList)
        subTotal +=n;

    cout << "Subtotal:                     £" << subTotal << endl;

    cout << endl;

    for (int i = 0; i < m_savingsList.size(); i++){
        cout << m_savingsList[i] << "    £" << m_savingsPriceList[i] << endl;
    }

    cout << endl;

    for (auto& n : m_savingsPriceList)
        savingsTotal +=n;

    cout << "Total Savings:                £" << savingsTotal << endl;

    cout << endl;

    finalTotal = subTotal - savingsTotal;

    cout << "Your Final Total is:          £" << finalTotal << endl;
    
    cout << endl;

    cout << "  Thank you for Shopping at " << getRetailer() << endl;
    
}