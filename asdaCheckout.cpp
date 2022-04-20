#include "asdaCheckout.h"

tuple<vector<string>, vector<float>, vector<string>, vector<float>> asdaCheckoutSystem::getDiscountedPrice(vector<string> m_itemsList, vector<float> m_priceList, vector<string> m_savingsList, vector<float> m_savingsPriceList){
    auto tftSavings = threeForTwo(m_itemsList, m_priceList, m_savingsList, m_savingsPriceList);
    
    //create new variables to pass as updated list to the next function - required due to being private access
    //alternative is to make all functions and variable public
    //tuples returned to house all data
    auto newItemsList = get<3>(tftSavings);
    auto newPriceList = get<4>(tftSavings);
    auto newSavingsList = get<1>(tftSavings);
    auto newSavingsPriceList = get<2>(tftSavings);

    auto btSavings = buyThree(newItemsList, newPriceList, newSavingsList, newSavingsPriceList);

    //final output tuple created and passed to output for reciept printing
    tuple<vector<string>, vector<float>, vector<string>, vector<float>> finalOutput (m_itemsList, m_priceList, get<1>(btSavings), get<2>(btSavings));

    return finalOutput;
}

tuple<float, vector<string>, vector<float>, vector<string>, vector<float>> asdaCheckoutSystem::threeForTwo(vector<string> m_itemsList, vector<float> m_priceList, vector<string> m_savingsList, vector<float> m_savingsPriceList){
    
    //why start at one - as there it at least one instance of the item on the intial list and you can't compare this to the previous value (will lead to segmentatiomn error)
    int tempCount = 1;
    int dealNo = 0;

    vector<int> indexVector;
    
    // check if the next item matches the previous item - if it does increment the count variable
    //once it hits three, add the the items and its price to a saving list
    //increment deal number by one
    //else a new item type is found and restart
    for (int i = 1; i < m_itemsList.size() + 1; i++){
        if (m_itemsList[i-1] == m_itemsList[i]) {
            tempCount++;
            if (tempCount == 3){
                m_savingsList.push_back(m_itemsList[i] + " (Three for Two Deal)");
                m_savingsPriceList.push_back(m_priceList[i]);
                indexVector.push_back(i);
                tempCount = 0;
                dealNo++;
            }
        } else {
            tempCount = 1;
        }
    }


    //account for new index value of vector after removing lowest price from returning item and price vectors
    //accounts for multiple instances of three for 2 deals
    for (int j = 0; j < indexVector.size(); j++) {
        indexVector[j] = (indexVector[j] - (dealNo * j));
    }

    float total = 0;

    //erase items where savings apply from items vector - needs to be passed to the netx function so the deals cannot be applied
    //to items already part of a deal

    for (int k = 0; k < indexVector.size(); k++) {
        m_itemsList.erase(m_itemsList.begin() + int(indexVector[k]));
        m_priceList.erase(m_priceList.begin() + int(indexVector[k]));
    }

    //add up savings prices

    for (auto& n : m_savingsPriceList)
        total += n;

    //return tuple of data

    tuple<float, vector<string>, vector<float>, vector<string>, vector<float>> output (total, m_savingsList, m_savingsPriceList, m_itemsList, m_priceList);

    return output;
}

tuple<float, vector<string>, vector<float>, vector<string>, vector<float>> asdaCheckoutSystem::buyThree(vector<string> m_itemsList, vector<float> m_priceList, vector<string> m_savingsList, vector<float> m_savingsPriceList){
   
    
    vector<int> indexVector;


    //check if the the list is divisble buy three - find the number of buy 3 deals present
    int buyThreeRepeats = (m_itemsList.size() / 3 );

    // when there number of buy three deals available loop find the minimu price in the array
    // once found, add item and the corresponding price to savings vector 
    //save index for when removing tp update original items vector
    for (int i = 0; i < buyThreeRepeats; i++){
       auto minPrice = *min_element(m_priceList.begin(), m_priceList.end());
       m_savingsPriceList.push_back(minPrice);
       if (findIndex(m_priceList, minPrice) != -1 ){
           indexVector.push_back(findIndex(m_priceList, minPrice));
           m_savingsList.push_back(m_itemsList[findIndex(m_priceList, minPrice)] + " (Buy Three get the Cheapest Free)");
       };
    } 

    //account for new index value of vector after removing lowest price from returning item and price vectors
    //accounts for multiple instances of three for 2 deals
    for (int j = 0; j < indexVector.size(); j++) {
        indexVector[j] = (indexVector[j] - (buyThreeRepeats * j));
    }

    //find index of lowest price, push it to the end and remove it from the vector
      for (int k = 0; k < indexVector.size(); k++) {
        m_itemsList.erase(m_itemsList.begin() + int(indexVector[k]));
        m_priceList.erase(m_priceList.begin() + int(indexVector[k]));
    }

    float total = 0;

    //find new savings total
    for (auto& l : m_savingsPriceList)
        total += l;

    //output tuple containing all output data

    tuple<float, vector<string>, vector<float>, vector<string>, vector<float>> output (total, m_savingsList, m_savingsPriceList, m_itemsList, m_priceList);

    return output;
}


int asdaCheckoutSystem::findIndex(vector<float> m_priceList, float m_price) {

    //find the first instance of the passed price and return vector

    auto it = find( m_priceList.begin(),  m_priceList.end(), m_price);

    if (it !=  m_priceList.end()) {
        int index = it - m_priceList.begin();
        return index;
    } else {
        return -1;
    }

}