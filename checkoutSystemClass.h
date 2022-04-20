#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <tuple>
#include <iomanip>

#pragma once

using namespace std;


class checkoutSystem
{
    
    private:
    
    int ID;
    string Location;
    string Retailer;
    vector<string> itemList;
    vector<string> noMatchList;
    vector<float> priceList;
    

    float subTotal;
    float finalTotal;
    float savingsTotal;

    vector<string> savingsList;
    vector<float> savingsPricesList;


    void printReciept(vector<string> m_itemsList, vector<float> m_priceList, vector<string> m_savingsList, vector<float> m_savingsPriceList);


    virtual tuple<vector<string>, vector<float>, vector<string>, vector<float>> getDiscountedPrice(vector<string> m_itemsList, vector<float> m_priceList, vector<string> m_savingsList, vector<float> m_savingsPriceList) = 0;

    public:


    int getID();
    void setID( int m_ID );
    string getLocation();
    void setLocation( string m_Location );
    string getRetailer();
    void setRetailer( string m_Retailer );

    

    int setList( map<string, float> database, vector<string> * userList);

    void getPrices();

    checkoutSystem(int m_ID, string m_Location, string m_Retailer) : ID(m_ID), Location(m_Location), Retailer(m_Retailer) {}

    
};