/*All code in this file was written without help, referring to cplusplus documentation*/
#pragma once

#include "CSVReader.h"
#include <vector>

//Own code - addapted from OrderBookEntry.h
/**  Candlestick class for storing candlestick data*/
class CandleStick
{
    public:
        /**  Constructor for single candlestick class*/
        CandleStick(std::string _timeStamp,
                    double _openTemp,
                    double _highTemp,
                    double _lowTemp,
                    double _closeTemp);

        //Access functions
        /** Function to get the timestamp */
        std::string getTimeStamp() const {return timeStamp;}

        /** Function to get the open temperature */
        double getOpenTemp() const& {return openTemp;}

        /** Function to get the high temperature */
        double getHighTemp() const& {return highTemp;}

        /** Function to get the low temperature */
        double getLowTemp() const& {return lowTemp;}

        /** Function to get the close temperature */
        double getCloseTemp() const& {return closeTemp;}

    private:
        /**  Variables for candlestick class*/
        std::string timeStamp;
        double openTemp;
        double highTemp;
        double lowTemp;
        double closeTemp;
    
    /**Operator << overload to pring single candlesticks */
    friend std::ostream& operator<<(std::ostream& os, const CandleStick& cs);

    /**Function to overload the << operator and print the collection */
    friend std::ostream& operator<<(std::ostream& os, const std::vector<CandleStick>& cs);
};