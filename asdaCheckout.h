

#include "checkoutSystemClass.h"
#pragma once

using namespace std;

class asdaCheckoutSystem : public checkoutSystem {
    public:
    using checkoutSystem::checkoutSystem;
    
    private:

    tuple<vector<string>, vector<float>, vector<string>, vector<float>> getDiscountedPrice( vector<string> m_itemsList, vector<float> m_priceList, vector<string> m_savingsList, vector<float> m_savingsPriceList);

    tuple<float, vector<string>, vector<float>, vector<string>, vector<float>> threeForTwo(vector<string> m_itemsList, vector<float> m_priceList, vector<string> m_savingsList, vector<float> m_savingsPriceList);

    tuple<float, vector<string>, vector<float>, vector<string>, vector<float>> buyThree(vector<string> m_itemsList, vector<float> m_priceList, vector<string> m_savingsList, vector<float> m_savingsPriceList);

    int findIndex (vector<float> m_itemsList, float m_price);

};