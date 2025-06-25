#pragma once
#include "WeatherObservation.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class ObservationsBook {
    public:
        /**Consturctor */
        ObservationsBook(std::string fileName);

        /** Function to calculate yearly open temperature for the first year in the range 
         * as the mean from previous year or as the mean from the first month of the year 
         * if the first year is the same as the year of the first data point*/
        static double firstYearOpenTemp(const std::vector<WeatherObservation>& weatherObservations, 
                                        const std::string& countryCode, 
                                        const std::string& firstYear);
        
        /**Calculate open temperature for the first month in a year
         */
        static double firstMonthOpenTemp(const std::vector<WeatherObservation>& weatherObservations, 
                                        const std::string& countryCode, 
                                        const std::string& year);

        /**Calculate open temperature for the first day in the data set as the average of itself
         * used for the prediction function
         */
        static double firstDayOpenTemp(const std::vector<WeatherObservation>& weatherObservations, 
                                        const std::string& countryCode);

        // /** Function to calculate yearly closing temperature
        //  * as the mean temperature of the year*/
        // static double yearlyCloseTemp(const std::vector<WeatherObservation>& weatherObservations, 
        //                               const std::string& countryCode, 
        //                               const std::string& year);

        /** Function to compute the max temperature difference per country */
        static const std::unordered_map<std::string, double> computeTempDifferencePerCountry(std::vector<WeatherObservation> obs);

        /** Function to access const reference to the weather obs vector */
        const std::vector<WeatherObservation>& getWeatherObservations() const {return weatherObservations;}

        
    private:
        std::vector<WeatherObservation> weatherObservations;

};