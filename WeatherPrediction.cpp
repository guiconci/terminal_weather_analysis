/**Own code written without assistance*/
#include "WeatherPrediction.h"
#include <iostream>

WeatherPrediction::WeatherPrediction(const std::vector<WeatherObservation>& weatherObservations, std::string countryCode)
{
    dailyCandleSticks = CandleSticksCollection::computeDailyCandleStick(weatherObservations, countryCode);
}

bool WeatherPrediction::predictWeather(std::string date)
{
    bool match = false; //flag to check if the date is in the data set
    //calculates the sum for the entered day through years in the data set
    unsigned int j = 0; //tracks the number of matched dates
    for (unsigned int i = 0; i < dailyCandleSticks.size(); ++i)
    {
        if(date.substr(5, 5) == dailyCandleSticks[i].getTimeStamp().substr(5, 5))
        {
            openTempPrediction += dailyCandleSticks[i].getOpenTemp();
            highTempPrediction += dailyCandleSticks[i].getHighTemp();
            lowTempPrediction += dailyCandleSticks[i].getLowTemp();
            closeTempPrediction += dailyCandleSticks[i].getCloseTemp();
            ++j;
            match = true;
        }
    }
    //calculates the mean
    openTempPrediction = openTempPrediction/j;
    highTempPrediction = highTempPrediction/j;
    lowTempPrediction = lowTempPrediction/j;
    closeTempPrediction = closeTempPrediction/j;

    return match;
}