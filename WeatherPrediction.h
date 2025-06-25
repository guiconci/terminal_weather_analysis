/**Own code written without assistance*/
#pragma once
#include "ThermoCandle.h"
#include "CandleSticksColletion.h"
#include <vector>
#include <string>

class WeatherPrediction {
    public:
        /** Constructor for PredictWeather class */
        WeatherPrediction(const std::vector<WeatherObservation>&, std::string countryCode);

        /** Function to predict the weather for a day input YYY-MM-DD */
        bool predictWeather(std::string date);

        /** Function to get the open temperature prediction */
        double getOpenTempPrediction() const& {return openTempPrediction;}

        /** Function to get the high temperature prediction */
        double getHighTempPrediction() const& {return highTempPrediction;}

        /** Function to get the low temperature prediction */
        double getLowTempPrediction() const& {return lowTempPrediction;}

        /** Function to get the close temperature prediction */
        double getCloseTempPrediction() const& {return closeTempPrediction;}

    private:
        /**Prediction for open temperature */
        double openTempPrediction;

        /**Prediction for high temperature */
        double highTempPrediction;

        /**Prediction for low temperature */
        double lowTempPrediction;

        /**Prediction for close temperature */
        double closeTempPrediction;

        /**Vector to store the daily candlestick data */
        std::vector<CandleStick> dailyCandleSticks;
};