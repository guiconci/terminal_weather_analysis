#pragma once

#include "CandleStick.h"
#include "PlottingChart.h"

class CandleSticksCollection
{
    public:
        CandleSticksCollection();

        // Method to execute the correct computation based on the "period" argument
        void computeCandleStick(const std::vector<WeatherObservation>& weatherObservations, 
                            const std::string& countryCode, 
                            const std::string& timeRange, 
                            ChartType charType); // "yearly" or "monthly"

        /** Static function to compute daily candle stick data for the prediction function*/
        static std::vector<CandleStick> computeDailyCandleStick(const std::vector<WeatherObservation>& weatherObservations, 
                                                                const std::string& countryCode);
        
        // Get the candlesticks
        std::vector<CandleStick> getCandleSticks() const;

        // Get the country code
        std::string getCountryCode() const;
        
    private:

        std::string countryCode; // Country code

        std::vector<CandleStick> candleSticks; // Stores the result of the computation

         /** Static function to compute yearly candle stick data of a country within a time range*/
        static std::vector<CandleStick> computeYearlyCandleStick(const std::vector<WeatherObservation>& weatherObservations, 
                                                                 const std::string& countryCode, 
                                                                 const std::string& yearsRange);

        /** Static function to compute monthly candle stick data of a country showing montlhy temps*/
        static std::vector<CandleStick> computeMonthlyCandleStick(const std::vector<WeatherObservation>& weatherObservations, 
                                                                  const std::string& countryCode, 
                                                                  const std::string& year);
};