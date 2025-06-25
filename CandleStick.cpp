/*All code in this file was written without help, referring to cplusplus documentation*/
#include "CandleStick.h"
#include <iostream>
#include <string>
#include <iomanip>

/**  Constructor for single candlestick class*/
CandleStick::CandleStick 
                (std::string _timeStamp,
                double _openTemp,
                double _highTemp,
                double _lowTemp,
                double _closeTemp)
    //Initialise variables            
:   timeStamp(_timeStamp),
    openTemp(_openTemp),
    highTemp(_highTemp),
    lowTemp(_lowTemp),
    closeTemp(_closeTemp)
{

}

std::ostream& operator<<(std::ostream& os, const CandleStick& cs)
{
    //save current precision
    std::streamsize ss = os.precision();
    //set precision to 2 decimal places
    std::cout << std::fixed << std::setprecision(0);

    os << std::fixed << std::setprecision(2);
        os << cs.getTimeStamp() << 
                " - Open: " << std::setw(6) << cs.getOpenTemp() <<
                ", High: " << std::setw(6) << cs.getHighTemp() <<
                ", Low: " << std::setw(6) << cs.getLowTemp() <<
                ", Close: " << std::setw(6) << cs.getCloseTemp();
        return os;

    //Restore previous precision
    std::cout << std::setprecision(ss);
}

std::ostream& operator<<(std::ostream& os, const std::vector<CandleStick>& cs)
{
    for (CandleStick c: cs)
    {
        os << c << std::endl;
    }
    return os;
}